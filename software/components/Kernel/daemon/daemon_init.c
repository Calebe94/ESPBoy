/** @file launcher.c
 * 
 * @brief This module has the purpose to create the ESPBoy's game launcher. 
 *
 * @par       
 * COPYRIGHT NOTICE: (c) 2018 Barr Group. All rights reserved.
 */

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "battery_manager.h"
#include "input_manager.h"
#include "ota_manager.h"

#include "daemon_init.h"

#define TEST_WITHOUT_UI_MANAGER     0

#if TEST_WITHOUT_UI_MANAGER 
    #include "lvgl.h"
    #include "ili9341.h"
    #include "splash_screen.h"
#else
    #include "ui_manager.h"
#endif

void manager_init()
{
    /* Start the main Task of the MinOS wich is the UI manager */
    ui_manager_init();

    battery_manager_init();

    // ota_manager_init();

	// xTaskCreate(&ui_manager_update, "ui_manager_update", 4096, NULL, 5, NULL);

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
    while(1)
    {   
        battery_update();

        keypad_update();
        // lvgl_update();
        vTaskDelay(50);
    }
}
