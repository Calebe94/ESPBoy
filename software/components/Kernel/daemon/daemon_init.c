/** @file launcher.c
 * 
 * @brief This module has the purpose to create the ESPBoy's game launcher. 
 *
 * @par       
 * COPYRIGHT NOTICE: (c) 2018 Barr Group. All rights reserved.
 */

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "esp_log.h"

#include "daemon/battery_manager.h"
#include "daemon/input_manager.h"
#include "daemon/ota_manager.h"
#include "daemon/ui_manager.h"

#include "daemon_init.h"


void manager_init()
{
    /* Start the main Task of the MinOS wich is the UI manager */
    #if USE_UI_MANAGER
        ui_manager_init();
    #endif

    #if USE_BATTERY_MANAGER
        battery_manager_init();
    #endif

    #if USE_OTA_MANAGER
        ota_manager_init();
    #endif

	xTaskCreate(
        &manager_update,    /* Function that implements the task. */
        "manager_update",   /* Text name for the task. */
        2048,               /* Stack size in words, not bytes. */
        NULL,               /* Parameter passed into the task. */
        5,                  /* Priority at which the task is created. */
        NULL
    );
}

void manager_update()
{
    #if USE_UI_MANAGER
        ui_stop_splash_screen();
    #endif

    while(1)
    {   
        // ESP_LOGI("DAEMONS UPDATE", "RAM left %d", esp_get_free_heap_size());
        
        // ESP_LOGI("DAEMONS UPDATE", "task stack: %d", uxTaskGetStackHighWaterMark(NULL));
        #if USE_BATTERY_MANAGER
            battery_update();
        #endif

        #if USE_INPUT_MANAGER
            keypad_update();
        #endif

        vTaskDelay(50);
    }
}
