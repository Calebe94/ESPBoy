#ifndef _MODULES_H_
#define _MODULES_H_

#include "freertos/FreeRTOS.h"

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
#include "storage/odroid_sdcard.h"
#include "driver/gpio.h"

#include "pins.h"

void sdcard_initilize()
{
    odroid_sdcard_open("/sd");
    while(1)
    {

    }
}

err_t modules_init(void)
{
    gpio_pullup_en(GPIO_NUM_22);    
    sdcard_init();

    ESP_ERROR_CHECK( nvs_flash_init() );
    // disp_spi_init();
    // ili9431_init();
    ili9341_init();
    ili9341_clear(0xffff);
    // odroid_sdcard_open("/sd");

    jack_sense_init();
    audio_amplifier_init();
    amplifier_set_off();
    battery_init();

    keypad_init();

    // wifi_init();
    
    return RESP_OK;
}

#endif