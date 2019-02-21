#ifndef _MODULES_H_
#define _MODULES_H_

#include "nvs_flash.h"

#include "audio/hal_audio.h"
#include "display/display.h"
#include "input/hal_keypad.h"
#include "power/hal_battery.h"
#include "storage/sdcard.h"
#include "storage/sdcard_pebri.h"

#include "wifi/wifi.h"

#include "minos_conf.h"
#include "minos_config.h"

err_t modules_init(void)
{  
	#if USE_DISPLAY
		ili9341_init();
		ili9341_clear(0xffff);
	#endif

	#if USE_AUDIO
        jack_sense_init();
        audio_amplifier_init();
        amplifier_set_off();
	#endif

	#if USE_INPUT
        keypad_init();
	#endif

	#if USE_POWER
		battery_init();
	#endif

	#if USE_SDCARD
    	// sdcard_init();
		char **files;
		sdcard_open("/sdcard");
		sdcard_files_get("/sdcard/nes", ".nes", &files);
	#endif

	#if USE_WIFI
    	wifi_init();		
	#endif


    ESP_ERROR_CHECK( nvs_flash_init() );
    
    return RESP_OK;
}

#endif