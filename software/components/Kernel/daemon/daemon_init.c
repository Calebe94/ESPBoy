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

#include "ui_manager.h"

void manager_init()
{
    /* Start the main Task of the MinOS wich is the UI manager */
    ui_manager_init();

    battery_manager_init();

    // ota_manager_init();

    vTaskDelay(5000);

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
    ui_stop_splash_screen();

    while(1)
    {   
        battery_update();

        keypad_update();

        vTaskDelay(50);
    }
}
