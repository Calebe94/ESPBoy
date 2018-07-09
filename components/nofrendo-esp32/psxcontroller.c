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
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"


#include "driver/gpio.h"
#include "soc/gpio_struct.h"
#include "psxcontroller.h"
#include "sdkconfig.h"

#define DELAY() asm("nop; nop; nop; nop;nop; nop; nop; nop;nop; nop; nop; nop;nop; nop; nop; nop;")

#define JOY_UP 			GPIO_NUM_17
#define JOY_DOWN 		GPIO_NUM_14
#define JOY_RIGHT 		GPIO_NUM_35
#define JOY_LEFT 		GPIO_NUM_34

#define JOY_SELECT 		GPIO_NUM_32
#define JOY_START 		GPIO_NUM_33
#define JOY_A 			GPIO_NUM_12
#define JOY_B 			GPIO_NUM_27
// #define JOY_VOL_UP 		GPIO_NUM_34 // NO INTERNAL PULLUP
// #define JOY_VOL_DOWN 	GPIO_NUM_39 // NO INTERNAL PULLUP
// #define JOY_MENU		GPIO_NUM_35 // NO INTERNAL PULLUP

#define BUTTON_UP		gpio_get_level(JOY_UP)
#define BUTTON_DOWN		gpio_get_level(JOY_DOWN)	
#define BUTTON_RIGHT	gpio_get_level(JOY_RIGHT)	
#define BUTTON_LEFT		gpio_get_level(JOY_LEFT)
#define BUTTON_SELECT 	gpio_get_level(JOY_SELECT)	
#define BUTTON_START 	gpio_get_level(JOY_START)
#define BUTTON_A	 	gpio_get_level(JOY_A)
#define BUTTON_B 		gpio_get_level(JOY_B)

#if CONFIG_HW_PSX_ENA

static void psxDone()
{
    DELAY();
    // GPIO_REG_WRITE(GPIO_OUT_W1TS_REG, (1 << PSX_ATT));
}

int psxReadInput() {
		// const int ev[16]={
		// 	event_joypad1_select,
		// 	0,
		// 	0,
		// 	event_joypad1_start,
		// 	event_joypad1_up,
		// 	event_joypad1_right,
		// 	event_joypad1_down,
		// 	event_joypad1_left,
		// 	0,
		// 	0,
		// 	0,
		// 	0,
		// 	event_soft_reset,
		// 	event_joypad1_a,
		// 	event_joypad1_b,
		// 	event_hard_reset
		// };
		// BIT0 = SELECT
		// BIT3 = START
		// BIT4 = U
		// BIT5 = R
		// BIT6 = D
		// BIT7 = L
		// BIT12 = RST
		// BIT13 = A
		// BIT14 = B

	// printf("U:%d-", !BUTTON_UP);
	// printf("-D:%d", !BUTTON_DOWN);
	printf("-R:%d", !BUTTON_RIGHT);
	printf("-L:%d", !BUTTON_LEFT);
	printf("\n");
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
	gpio_pad_select_gpio(JOY_UP);
	gpio_pad_select_gpio(JOY_DOWN);
	gpio_pad_select_gpio(JOY_RIGHT);
	gpio_pad_select_gpio(JOY_LEFT);
	gpio_pad_select_gpio(JOY_SELECT);
	gpio_pad_select_gpio(JOY_START);
	gpio_pad_select_gpio(JOY_A);
	gpio_pad_select_gpio(JOY_B);
	
	gpio_set_direction(JOY_UP, GPIO_MODE_INPUT);
	gpio_set_direction(JOY_DOWN, GPIO_MODE_INPUT);
	gpio_set_direction(JOY_RIGHT, GPIO_MODE_INPUT);
	gpio_set_direction(JOY_LEFT, GPIO_MODE_INPUT);
	gpio_set_direction(JOY_SELECT, GPIO_MODE_INPUT);
	gpio_set_direction(JOY_START, GPIO_MODE_INPUT);
	gpio_set_direction(JOY_A, GPIO_MODE_INPUT);
	gpio_set_direction(JOY_B, GPIO_MODE_INPUT);

	gpio_set_pull_mode(JOY_UP, GPIO_PULLUP_ONLY);
	gpio_set_pull_mode(JOY_DOWN, GPIO_PULLUP_ONLY);
	gpio_set_pull_mode(JOY_RIGHT, GPIO_PULLUP_ONLY);
	gpio_set_pull_mode(JOY_LEFT, GPIO_PULLUP_ONLY);
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