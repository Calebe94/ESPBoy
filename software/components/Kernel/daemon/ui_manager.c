
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

static app_t actual_app;

static lv_indev_t * indev;

static void _ui_start(void)
{
	lv_init();

	lv_disp_drv_t disp;
	lv_disp_drv_init(&disp);
	disp.disp_flush = ili9431_flush;
	lv_disp_drv_register(&disp);

	lv_indev_drv_t indev_drv;
	lv_indev_drv_init(&indev_drv);     /*Basic initialization*/
	indev_drv.type = LV_INDEV_TYPE_KEYPAD;              /*See below.*/
	indev_drv.read = lv_keypad_read;           /*See below.*/
	lv_indev_drv_register(&indev_drv);     /*Register the driver in LittlevGL*/
	indev = lv_indev_drv_register(&indev_drv);
	lv_indev_init();
}

void ui_manager_init()
{
	// xTaskCreatePinnedToCore(&ui_manager_update, "ui_manager_update", 1024 * 2, NULL, 5, NULL, 0);
	_ui_start();

	#if UI_OWN_TASK
		xTaskCreate(&ui_manager_start, "ui_manager_update", 4096, NULL, 5, NULL);
	#endif

	ui_start_splash_screen(NULL);
}

void ui_manager_start(void *args)
{	
	while(1)
    {	
		lv_task_handler();
		if(actual_app.update != NULL)
		{
			APP_UPDATE(actual_app);
		}
  		vTaskDelay(10/portTICK_PERIOD_MS);

  		lv_tick_inc(10/portTICK_RATE_MS);
	}
}

void ui_manager_update(void *param)
{
	lv_task_handler();

	if(actual_app.update != NULL)
	{
		APP_UPDATE(actual_app);
	}

  	vTaskDelay(10/portTICK_PERIOD_MS);

  	lv_tick_inc(10/portTICK_RATE_MS);
}

void ui_start_launcher(void *aux)
{
	actual_app.indev = (lv_indev_t*)aux;
	actual_app.init = (void*)launcher_init;
	actual_app.update = (void*)launcher_update;
	actual_app.deinit = (void*)launcher_deinit;

	APP_INIT(actual_app);
}

void ui_start_splash_screen(void *aux)
{
	actual_app.init = (void*)splash_screen_init;
	actual_app.deinit = (void*)splash_screen_deinit;
	APP_INIT(actual_app);
}

void ui_stop_splash_screen()
{
	APP_DEINIT(actual_app);

	ui_start_launcher(indev);
}
