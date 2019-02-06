#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
// #include "lvgl/lv_hal/lv_hal_indev.h"
#include "lvgl/lv_core/lv_group.h"

#include <driver/adc.h>
#include <driver/gpio.h>

#include "i2cdev.h"
#include "pcf8574.h"

#include "pins.h"
#include "hal_keypad.h"

#include "minos_config.h"

#define SDA_GPIO 33
#define SCL_GPIO 32

#define ADDR 	0x20

static i2c_dev_t dev;

void keypad_init(void)
{
	if(i2cdev_init()!= ESP_OK)
	{

	}

	if(pcf8574_init_desc(&dev, 1, ADDR, SDA_GPIO, SCL_GPIO) != ESP_OK)
	{

	}
	// adc1_config_width(ADC_WIDTH_12Bit);
    // adc1_config_channel_atten(JOY_X_AXIS, ADC_ATTEN_11db);
	// adc1_config_channel_atten(JOY_Y_AXIS, ADC_ATTEN_11db);
	// adc1_config_channel_atten(JOY_VOL, ADC_ATTEN_11db);

	// gpio_pad_select_gpio(JOY_SELECT);
	// gpio_pad_select_gpio(JOY_START);
	// gpio_pad_select_gpio(JOY_A);
	// gpio_pad_select_gpio(JOY_B);
	// gpio_pad_select_gpio(JOY_MENU);

	// gpio_set_direction(JOY_SELECT, GPIO_MODE_INPUT);
	// gpio_set_direction(JOY_START, GPIO_MODE_INPUT);
	// gpio_set_direction(JOY_A, GPIO_MODE_INPUT);
	// gpio_set_direction(JOY_B, GPIO_MODE_INPUT);
    // gpio_set_direction(JOY_MENU, GPIO_MODE_INPUT);

	// gpio_set_pull_mode(JOY_SELECT, GPIO_PULLUP_ONLY);
	// gpio_set_pull_mode(JOY_START, GPIO_PULLUP_ONLY);
	// gpio_set_pull_mode(JOY_A, GPIO_PULLUP_ONLY);
	// gpio_set_pull_mode(JOY_B, GPIO_PULLUP_ONLY);
    // gpio_set_pull_mode(JOY_MENU, GPIO_PULLUP_ONLY);
}

uint16_t raw_keypad_read()
{
    // /*************************
    // * BYTE TO RETURN STATUS
    // **************************/
	// uint16_t raw_byte;
    // /*************************
    // * DIRECTIONAL KEYS STATUS
    // **************************/
	// uint8_t button_up = 1, 
    //     button_down   = 1, 
    //     button_left   = 1, 
    //     button_right  = 1;
    // /********************
    // * ACTION KEYS STATUS
    // ********************/
    // uint8_t button_a = 1, button_b = 1;
    // /********************
    // * MENU KEYS STATUS
    // ********************/
    // uint8_t button_select 	= 1,
    //     button_start 		= 1,
    //     button_menu 		= 1,
    //     vol_up 				= 1,
    //     vol_down 			= 1;
    // /*===================
    // * ASSIGN KEYS STATUS
    // ====================*/
    // button_select   = gpio_get_level(JOY_SELECT);	
    // button_start    = gpio_get_level(JOY_START);
    // button_menu     = gpio_get_level(JOY_MENU);
    // button_a	 	= gpio_get_level(JOY_A);
    // button_b 		= gpio_get_level(JOY_B);

	// uint16_t joy_x   = adc1_get_raw(JOY_X_AXIS);
    // uint16_t joy_y   = adc1_get_raw(JOY_Y_AXIS);
	// uint16_t joy_vol = adc1_get_raw(JOY_VOL);

	// if(joy_x > 2000)
	// {
	// 	button_left = 0;
	// }
	// else if(joy_x > 1000)
	// {
	// 	button_right = 0;
	// }

	// if(joy_y > 2000)
	// {
	// 	button_up = 0;
	// }
	// else if(joy_y > 1000)
	// {
	// 	button_down = 0;
	// }

    // if(joy_vol > 2000)
	// {
	// 	vol_up = 0;
	// }
	// else if(joy_vol > 1000)
	// {
	// 	vol_down = 0;
	// }
    // // printf("joy_x: %d = joy_y: %d = joy_vol: %d - ", joy_x, joy_y, joy_vol);

    // #if KEYPAD_DEBUG
    //     printf("U:%d=D:%d=L:%d=R:%d=B:%d=A:%d=ST:%d=SEL:%d=M:%d=+:%d=-:%d\n",
    //         button_up, button_down, button_left, button_right, button_b, button_a, 
    //         button_start, button_select, button_menu, vol_up, vol_down);
    // #endif

    // raw_byte = (button_start<<10) | (button_select<<9) | (vol_up<<8) | 
    //     (vol_down<<7) | (button_menu<<6) | (button_b<<5) | (button_a<<4) | 
    //     (button_right<<3) | (button_left<<2) | (button_down<<1) | (button_up<<0);
    
	// return (raw_byte);
	esp_err_t res;
    uint8_t val;
	
    if ( (res=pcf8574_port_read(&dev, &val)) != ESP_OK)
	{
        printf("Could not read ADC value, error %d\n", res);
		val = 0xFF;
	}

	return (val);
}

