
#include <stdio.h>
#include <stdbool.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "esp_freertos_hooks.h"

#include "lvgl.h"

#include "ili9341.h"
#include "ui_manager.h"
// #include "hal_keypad.h"
#include "input_manager.h"

#include "splash_screen.h"
#include "app_object.h"
#include "launcher.h"

static bool start_launcher;

void ui_manager_init()
{
	// xTaskCreatePinnedToCore(&ui_manager_update, "ui_manager_update", 1024 * 2, NULL, 5, NULL, 0);
	xTaskCreate(&ui_manager_update, "ui_manager_update", 4096, NULL, 5, NULL);
}

void ui_manager_update(void *args)
{	
	lv_init();

	lv_disp_drv_t disp;
	lv_disp_drv_init(&disp);
	disp.disp_flush = ili9431_flush;
	lv_disp_drv_register(&disp);

    // xTaskCreatePinnedToCore(&lv_tick_task, "lv_tick_task", 1024 * 2, NULL, 5, NULL, 1);
	// esp_register_freertos_tick_hook(lv_tick_task);

	lv_indev_drv_t indev_drv;
	lv_indev_drv_init(&indev_drv);     /*Basic initialization*/
	indev_drv.type = LV_INDEV_TYPE_KEYPAD;              /*See below.*/
	indev_drv.read = lv_keypad_read;           /*See below.*/
	lv_indev_drv_register(&indev_drv);     /*Register the driver in LittlevGL*/
	lv_indev_t * indev = lv_indev_drv_register(&indev_drv);
	lv_indev_init();

	// app_t splash_screen = {
	// 	.indev = indev,
	// 	.init = splash_screen_init,
	// 	.deinit = splash_screen_deinit
	// };
 
	// splash_screen.init(&splash_screen);

	app_t launcher = {
		.indev = indev,
		.init = launcher_init,
		.update = launcher_update,
		.deinit = launcher_deinit
	};

	// launcher.init(&launcher);
	APP_INIT(launcher);

	while(1)
    {	
		lv_task_handler();

		// launcher_update(&launcher);

		// lv_tick_task();

  		vTaskDelay(10/portTICK_PERIOD_MS);

  		lv_tick_inc(10/portTICK_RATE_MS);

		// TODO: should have a task to update the managers
        // gui_update(&screen, 4, 3, battery_voltage());
	}
}

static void lv_tick_task(void)
{
    // while(1)
    // {
    //     lv_tick_inc(portTICK_RATE_MS);
    //     vTaskDelay(1);
    // }

	vTaskDelay(10/portTICK_PERIOD_MS);

	lv_tick_inc(10/portTICK_RATE_MS);
	// lv_tick_inc(portTICK_RATE_MS);
}
