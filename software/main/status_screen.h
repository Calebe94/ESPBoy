#ifndef _STATUS_SCREEN_H_
#define _STATUS_SCREEN_H_

#include <stdint.h>
#include "lvgl.h"

typedef struct _screen 
{
    lv_obj_t *screen;
    lv_obj_t *label_flash;
    lv_obj_t *bar_flash;
    lv_obj_t *label_battery;
}screen_t;

screen_t gui_create(void);

void gui_update(screen_t *screen, uint32_t total_mem, uint32_t free_mem, float bat_level);

#endif