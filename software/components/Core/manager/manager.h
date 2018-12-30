#ifndef _MANAGER_H_
#define _MANAGER_H_

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "battery_manager.h"
// #include "input_manager.h"

void manager_init();

void manager_update();

void manager_init()
{
    battery_manager_init();

	xTaskCreatePinnedToCore(
        &manager_update,    /* Function that implements the task. */
        "manager_update",   /* Text name for the task. */
        2048,               /* Stack size in words, not bytes. */
        NULL,               /* Parameter passed into the task. */
        5,                  /* Priority at which the task is created. */
        NULL, 
        1
    );
}

void manager_update()
{
    while(1)
    {
        battery_update();

        vTaskDelay(50);
    }
}

#endif