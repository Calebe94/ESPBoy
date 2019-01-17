#ifndef _LVGL_MANAGER_H_
#define _LVGL_MANAGER_H_

#define UI_OWN_TASK 	1

void ui_manager_init(void);

void ui_manager_start(void *);

void ui_start_launcher(void *);

void ui_start_splash_screen(void *);

void ui_stop_splash_screen();

void ui_manager_update(void *);

#endif