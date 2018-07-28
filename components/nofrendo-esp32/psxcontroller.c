// Copyright 2015-2016 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

#include <driver/adc.h>
#include "driver/gpio.h"
#include "soc/gpio_struct.h"
#include "psxcontroller.h"
#include "sdkconfig.h"
#include "pins.h"

#define DELAY() asm("nop; nop; nop; nop;nop; nop; nop; nop;nop; nop; nop; nop;nop; nop; nop; nop;")

#if CONFIG_HW_PSX_ENA

static void psxDone()
{
    DELAY();
}

int psxReadInput() {
	uint8_t BUTTON_UP = 1, BUTTON_DOWN = 1, BUTTON_LEFT = 1, BUTTON_RIGHT = 1;

	int joyX = adc1_get_raw(JOY_X_AXIS);
    int joyY = adc1_get_raw(JOY_Y_AXIS);

	if(joyX > 3500)
	{
		BUTTON_LEFT = 0;
	}
	else if(joyX > 1000)
	{
		BUTTON_RIGHT = 0;
	}

	if(joyY > 3500)
	{
		BUTTON_UP = 0;
	}
	else if(joyY > 1000)
	{
		BUTTON_DOWN = 0;
	}

	// printf("JOY_X: %d - ", joyX);
	// printf("JOY_Y: %d - ", joyY);

	// printf("U:%d-", !BUTTON_UP);
	// printf("-D:%d", !BUTTON_DOWN);
	// printf("-R:%d", !BUTTON_RIGHT);
	// printf("-L:%d", !BUTTON_LEFT);
	// printf("\n");
	// printf("-SELECT:%d", !BUTTON_SELECT);
	// printf("-START:%d", !BUTTON_START);
	// printf("-A:%d", !BUTTON_A);
	// printf("-B:%d\n", !BUTTON_B);

	int b1, b2;
	b2 = 1<<7 | (BUTTON_B<<6) | (BUTTON_A<<5) | 1<<4 | 1<<3 | 1<<2 | 1<<1 | 1<<0;
	b1 = (BUTTON_LEFT<<7) | (BUTTON_DOWN<<6) | (BUTTON_RIGHT<<5) | (BUTTON_UP<<4) | (BUTTON_START<<3) | 1<<2 | 1<<1 | (BUTTON_SELECT<<0);
	psxDone();
	return (b2<<8)|b1;
}

void psxcontrollerInit() {
	adc1_config_width(ADC_WIDTH_12Bit);
    adc1_config_channel_atten(JOY_X_AXIS, ADC_ATTEN_11db);
	adc1_config_channel_atten(JOY_Y_AXIS, ADC_ATTEN_11db);

	gpio_pad_select_gpio(JOY_SELECT);
	gpio_pad_select_gpio(JOY_START);
	gpio_pad_select_gpio(JOY_A);
	gpio_pad_select_gpio(JOY_B);
	
	gpio_set_direction(JOY_SELECT, GPIO_MODE_INPUT);
	gpio_set_direction(JOY_START, GPIO_MODE_INPUT);
	gpio_set_direction(JOY_A, GPIO_MODE_INPUT);
	gpio_set_direction(JOY_B, GPIO_MODE_INPUT);

	gpio_set_pull_mode(JOY_SELECT, GPIO_PULLUP_ONLY);
	gpio_set_pull_mode(JOY_START, GPIO_PULLUP_ONLY);
	gpio_set_pull_mode(JOY_A, GPIO_PULLUP_ONLY);
	gpio_set_pull_mode(JOY_B, GPIO_PULLUP_ONLY);
}

#else

int psxReadInput() {
	return 0xFFFF;
}


void psxcontrollerInit() {
	printf("PSX controller disabled in menuconfig; no input enabled.\n");
}

#endif