#ifndef _MODULES_H_
#define _MODULES_H_

#include "freertos/FreeRTOS.h"

#include "nvs_flash.h"

#include "k_config.h"
#include "audio/hal_audio.h"
#include "display/disp_spi.h"
#include "display/ili9341.h"
#include "display/spi_lcd.h"
#include "input/controllers.h"
#include "input/hal_keypad.h"
#include "power/hal_battery.h"
#include "storage/sdcard.h"
#include "wifi/wifi.h"

#include "pins.h"

err_t modules_init(void)
{
    ESP_ERROR_CHECK( nvs_flash_init() );

    // sdcard_init();
    disp_spi_init();
    ili9431_init();
    jack_sense_init();
    audio_amplifier_init();
    amplifier_set_off();
    battery_init();
    
    keypad_init();
    
    // wifi_init();
    
    return RESP_OK;
}

#endif