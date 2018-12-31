#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "nofrendo.h"
#include "esp_partition.h"

#include "esp_freertos_hooks.h"
#include "lvgl.h"

#include "disp_spi.h"
#include "ili9341.h"
#include "sysinit.h"
#include "hal_battery.h"
#include "hal_keypad.h"
#include "status_screen.h"

#include "battery_manager.h"

#include "launcher.h"

static void lv_tick_task(void);

char *osd_getromdata();

esp_err_t event_handler(void *ctx, system_event_t *event);

void nes_run();

void lvgl_run();

int app_main(void)
{
	os_init();
  	// nes_run();
	lvgl_run();

  	return 0;
}

void lvgl_run()
{
	lv_init();

	// disp_spi_init();
	// ili9431_init();

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

	// demo_create();
	// screen_t screen = gui_create();
    // uint16_t delay = 0;
	create_header();

	
	while(1)
    {
		// TODO: should have a task to update the managers

        // gui_update(&screen, 4, 3, battery_voltage());
		
		lv_task_handler();

		vTaskDelay(1000);
	}
}

char *osd_getromdata() 
{
	char* romdata;
	const esp_partition_t* part;
	spi_flash_mmap_handle_t hrom;
	esp_err_t err;
	nvs_flash_init();
	part=esp_partition_find_first(0x40, 1, NULL);
	if (part==0) printf("Couldn't find rom part!\n");
	err=esp_partition_mmap(part, 0, 3*1024*1024, SPI_FLASH_MMAP_DATA, (const void**)&romdata, &hrom);
	if (err!=ESP_OK) printf("Couldn't map rom part!\n");
	printf("Initialized. ROM@%p\n", romdata);
    return (char*)romdata;
}

esp_err_t event_handler(void *ctx, system_event_t *event)
{
    return ESP_OK;
}

void nes_run()
{
	printf("NoFrendo start!\n");
	nofrendo_main(0, NULL);
	printf("NoFrendo died? WtF?\n");
	asm("break.n 1");
}

static void lv_tick_task(void)
{
	lv_tick_inc(portTICK_RATE_MS);
}
