#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
// #include "lvgl/lv_hal/lv_hal_indev.h"
#include "lvgl/lv_core/lv_group.h"

#include <driver/adc.h>
#include <driver/gpio.h>

#include "pins.h"
#include "hal_keypad.h"

void keypad_init(void)
{
	adc1_config_width(ADC_WIDTH_12Bit);
  adc1_config_channel_atten(JOY_X_AXIS, ADC_ATTEN_11db);
	adc1_config_channel_atten(JOY_Y_AXIS, ADC_ATTEN_11db);
	adc1_config_channel_atten(JOY_VOL, ADC_ATTEN_11db);

	gpio_pad_select_gpio(JOY_SELECT);
	gpio_pad_select_gpio(JOY_START);
	gpio_pad_select_gpio(JOY_A);
	gpio_pad_select_gpio(JOY_B);
	gpio_pad_select_gpio(JOY_MENU);

	gpio_set_direction(JOY_SELECT, GPIO_MODE_INPUT);
	gpio_set_direction(JOY_START, GPIO_MODE_INPUT);
	gpio_set_direction(JOY_A, GPIO_MODE_INPUT);
	gpio_set_direction(JOY_B, GPIO_MODE_INPUT);
  gpio_set_direction(JOY_MENU, GPIO_MODE_INPUT);

	gpio_set_pull_mode(JOY_SELECT, GPIO_PULLUP_ONLY);
	gpio_set_pull_mode(JOY_START, GPIO_PULLUP_ONLY);
	gpio_set_pull_mode(JOY_A, GPIO_PULLUP_ONLY);
	gpio_set_pull_mode(JOY_B, GPIO_PULLUP_ONLY);
  gpio_set_pull_mode(JOY_MENU, GPIO_PULLUP_ONLY);
}

uint16_t raw_keypad_read()
{
	uint8_t BUTTON_UP = 1, BUTTON_DOWN = 1, BUTTON_LEFT = 1, BUTTON_RIGHT = 1, VOL_UP = 1, VOL_DOWN = 1;
	uint8_t byte_1, byte_2;

	uint16_t joy_x = adc1_get_raw(JOY_X_AXIS);
    uint16_t joy_y = adc1_get_raw(JOY_Y_AXIS);
	uint16_t joy_vol = adc1_get_raw(JOY_VOL);

	if(joy_x > 2000)
	{
		BUTTON_LEFT = 0;
	}
	else if(joy_x > 1000)
	{
		BUTTON_RIGHT = 0;
	}

	if(joy_y > 2000)
	{
		BUTTON_UP = 0;
	}
	else if(joy_y > 1000)
	{
		BUTTON_DOWN = 0;
	}

    if(joy_vol > 2000)
	{
		VOL_UP = 0;
	}
	else if(joy_vol > 1000)
	{
		VOL_DOWN = 0;
	}
    printf("joy_x: %d = joy_y: %d = joy_vol: %d\n", joy_x, joy_y, joy_vol);
    printf("U:%d=D:%d=L:%d=R:%d=B:%d=A:%d=ST:%d=SEL:%d=M:%d=+:%d=-:%d\n",BUTTON_UP, BUTTON_DOWN, BUTTON_LEFT, BUTTON_RIGHT, BUTTON_B, BUTTON_A, BUTTON_START, BUTTON_SELECT, BUTTON_MENU, VOL_UP, VOL_DOWN);
    byte_1 = (BUTTON_B<<5) | (BUTTON_A<<4) | (BUTTON_RIGHT<<3) | (BUTTON_LEFT<<2) | (BUTTON_DOWN<<1) | (BUTTON_UP<<0);
    byte_2 = (BUTTON_SELECT<<4) | (BUTTON_START<<3) | (VOL_UP<<2) | (VOL_DOWN<<1) | BUTTON_MENU; 
    
	return (byte_2<<8)|byte_1;
}

bool lv_keypad_read(lv_indev_data_t *data)
{
    uint16_t raw_input = raw_keypad_read();
    
    if((raw_input&0x01) == 0)
    {
       // printf("UP\n");
        data->state = LV_INDEV_STATE_PR;
        data->key = LV_GROUP_KEY_UP;
    }
    else if((raw_input&0x02) == 0)
    {
       // printf("DOWN\n");
        data->state = LV_INDEV_STATE_PR;
        data->key = LV_GROUP_KEY_DOWN;
    }
    else if((raw_input&0x04) == 0) 
    {
       // printf("LEFT\n");
        data->state = LV_INDEV_STATE_PR;
        data->key = LV_GROUP_KEY_LEFT;
    }
    else if((raw_input&0x08) == 0)
    {
       // printf("RIGHT\n");
        data->state = LV_INDEV_STATE_PR;
        data->key = LV_GROUP_KEY_RIGHT;
    }
    else if((raw_input&0x16) == 0)
    {
       // printf("ESC\n");
        data->state = LV_INDEV_STATE_PR;
        data->key = LV_GROUP_KEY_ESC;
    }
    else if((raw_input&0x32) == 0)
    { 
       // printf("ENTER\n");
        data->state = LV_INDEV_STATE_PR;
        data->key = LV_GROUP_KEY_ENTER;
    }
    else
    {
        data->state = LV_INDEV_STATE_REL;
    }

    return false;
}

