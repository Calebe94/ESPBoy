
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "esp_freertos_hooks.h"

#include "lvgl.h"

#include "ili9341.h"
#include "ui_manager.h"
#include "hal_keypad.h"

#include "launcher.h"

// static void lvgl_init(void);

void ui_manager_init(void)
{
	lv_init();

	lv_disp_drv_t disp;
	lv_disp_drv_init(&disp);
	disp.disp_flush = ili9431_flush;
	lv_disp_drv_register(&disp);

	esp_register_freertos_tick_hook(lv_tick_task);

	lv_indev_drv_t indev_drv;
	lv_indev_drv_init(&indev_drv);     /*Basic initialization*/
	indev_drv.type = LV_INDEV_TYPE_KEYPAD;              /*See below.*/
	indev_drv.read = lv_keypad_read;           /*See below.*/
	lv_indev_drv_register(&indev_drv);     /*Register the driver in LittlevGL*/

	// create_header();
    // launcher_init();
	
	// while(1)
    // {
	// 	// TODO: should have a task to update the managers

    //     // gui_update(&screen, 4, 3, battery_voltage());
		
	// 	lv_task_handler();

	// 	vTaskDelay(1000);
	// }
}

void ui_manager_update(void)
{	
	lv_task_handler();
	// vTaskDelay(1000);
}

static void lv_tick_task(void)
{
	lv_tick_inc(portTICK_RATE_MS);
}
