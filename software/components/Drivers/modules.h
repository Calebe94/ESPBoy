#ifndef _MODULES_H_
#define _MODULES_H_

#include <driver/i2c.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>

#include "sdkconfig.h"

#include "nvs_flash.h"

#include "k_config.h"
#include "audio/hal_audio.h"

// #include "display/disp_spi.h"
// #include "display/ili9341.h"
// #include "display/spi_lcd.h"
#include "display/display.h"

#include "input/controllers.h"
#include "input/hal_keypad.h"
#include "power/hal_battery.h"
#include "storage/sdcard.h"
#include "wifi/wifi.h"
#include "storage/sdcard.h"
#include "driver/gpio.h"

#include "pins.h"

#define TEST_PCF8574 0
#define USE_DRIVERS  0

#if TEST_PCF8574


static char tag[] = "i2cscanner";

#define SDA_PIN 33
#define SCL_PIN 32

void task_i2cscanner()
{
	ESP_LOGD(tag, ">> i2cScanner");

	i2c_config_t conf;
	conf.mode = I2C_MODE_MASTER;
	conf.sda_io_num = SDA_PIN;
	conf.scl_io_num = SCL_PIN;
	conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
	conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
	conf.master.clk_speed = 100000;

	ESP_ERROR_CHECK(i2c_param_config(I2C_NUM_0, &conf));

	ESP_ERROR_CHECK(i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0));

	int i;
	esp_err_t espRc;

	printf("     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\n");
	printf("00:         ");

	for (i=3; i< 0x78; i++) 
    {
		i2c_cmd_handle_t cmd = i2c_cmd_link_create();
		i2c_master_start(cmd);
		i2c_master_write_byte(cmd, (i << 1) | I2C_MASTER_WRITE, 1 /* expect ack */);
		i2c_master_stop(cmd);

		espRc = i2c_master_cmd_begin(I2C_NUM_0, cmd, 10/portTICK_PERIOD_MS);
		if (i%16 == 0) 
        {
			printf("\n%.2x:", i);
		}
		if (espRc == 0) 
        {
			printf(" %.2x", i);
		} 
        else 
        {
			printf(" --");
		}
		ESP_LOGD(tag, "i=%d, rc=%d (0x%x)", i, espRc, espRc);
		i2c_cmd_link_delete(cmd);
	}

	printf("\n");

	// vTaskDelete(NULL);
}

#endif

err_t modules_init(void)
{  
    sdcard_init();

    ESP_ERROR_CHECK( nvs_flash_init() );
    
    ili9341_init();
    ili9341_clear(0xffff);


    #if TEST_PCF8574

        task_i2cscanner();

    #else
        #if USE_DRIVERS
        jack_sense_init();
        audio_amplifier_init();
        amplifier_set_off();
        battery_init();

        keypad_init();
        #endif
    #endif

    // wifi_init();
    
    return RESP_OK;
}

#endif