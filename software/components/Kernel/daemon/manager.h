#ifndef _MANAGER_H_
#define _MANAGER_H_

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "battery_manager.h"
#include "ui_manager.h"
#include "input_manager.h"
#include "ota_manager.h"

// #include "input_manager.h"

void manager_init();

void manager_update();

void manager_init()
{
    battery_manager_init();

    // lvgl_init();
    ota_manager_init();

    ui_manager_init();
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

#endif