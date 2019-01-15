#ifndef _SYS_APPS_H_
#define _SYS_APPS_H_

#include "lvgl.h"

#include "launcher.h"

void system_apps_init(void)
{
    lv_indev_t * indev = NULL; // Should init first
    launcher_init(indev);
}

#endif