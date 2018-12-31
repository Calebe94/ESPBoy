#include <stdio.h>
#include <stdint.h>
#include "status_screen.h"
#include "lvgl.h"
#include "system.h"

screen_t gui_create(void)
{
    lv_obj_t * scr = lv_scr_act();

    //*************************

    lv_obj_t *header = lv_label_create(scr, NULL); /*First parameters (scr) is the parent*/
    lv_label_set_text(header, "ESPBoy");  /*Set the text*/
    lv_obj_align(header, lv_scr_act(), LV_ALIGN_IN_TOP_MID, 0, 0);

    /****************
    * ADD A BATTERY ICON
    ****************/
    lv_obj_t * battery = lv_label_create(scr, NULL); /*First parameters (scr) is the parent*/
    lv_label_set_text(battery, SYMBOL_BATTERY_3); /*Set the text*/
    lv_obj_align(battery, header, LV_ALIGN_IN_TOP_RIGHT, (LV_HOR_RES - lv_obj_get_width(header)-10)/2, 0);

    /****************
    * ADD A CLOCK
    ****************/
    // lv_obj_t * clock = lv_label_create(scr, NULL); /*First parameters (scr) is the parent*/
    // lv_label_set_text(clock, "15:00"); /*Set the text*/
    // lv_obj_align(clock, header, LV_ALIGN_IN_TOP_LEFT, ((lv_obj_get_width(header)-LV_HOR_RES)/2)+5, 0);

    screen_t aux;
    lv_theme_t *th = lv_theme_night_init(LV_VER_RES, NULL);
    lv_theme_set_current(th);

    //*************************

//     lv_obj_t * page_sys = lv_page_create(scr,NULL);
//     lv_obj_set_size(page_sys,LV_HOR_RES,LV_VER_RES);
//     lv_page_set_sb_mode(page_sys,LV_SB_MODE_AUTO);
//     lv_obj_align(page_sys, scr, LV_ALIGN_CENTER,0,0);
//     lv_page_set_scrl_layout(page_sys, LV_LAYOUT_COL_L);     /*Arrange elements automatically*/

//     lv_obj_t * storage_obj = lv_cont_create(page_sys,NULL);
//     lv_obj_set_width(storage_obj,LV_HOR_RES-35);
//     lv_cont_set_fit(storage_obj,false,true);

//     lv_obj_t * cont_battery = lv_cont_create(page_sys, storage_obj);

//     lv_obj_t * label_storage= lv_label_create(storage_obj,NULL);
//     lv_label_set_text(label_storage," #0ff000 Storage#");
//     lv_label_set_recolor(label_storage,true);

//     lv_obj_t * label_battery= lv_label_create(cont_battery,NULL);
//     lv_label_set_text(label_battery," #0ff000 Battery#");
//     lv_label_set_recolor(label_battery,true);

// // /*Create a style and use the new font*/
// 	static lv_style_t style1;
// 	lv_style_copy(&style1, &lv_style_pretty_color);
// 	// style1.text.font = &lv_font_dejavu_10; /*Set the base font whcih is concatenated with the others*/
// 	style1.text.opa = 70;

//     static uint32_t TF_TotalSize = 7000;
//     static uint32_t TF_FreeSize = 300;

//     lv_obj_t *label_sdcard_cap = lv_label_create(storage_obj,NULL);
//     char buffer[60];
//     sprintf(buffer,"Total: %dMB\nFree:  %dMB", TF_TotalSize, TF_FreeSize);
//     lv_label_set_text(label_sdcard_cap,buffer);
//     lv_label_set_recolor(label_sdcard_cap, true);
//     lv_obj_align(label_sdcard_cap, label_storage, LV_ALIGN_OUT_BOTTOM_LEFT, 60, 0);

//     lv_obj_t * bar_sdcard  = lv_bar_create(storage_obj, NULL);
//     lv_bar_set_range(bar_sdcard,0,100);
//     lv_obj_set_size(bar_sdcard,180,15);
//     lv_bar_set_value(bar_sdcard,(TF_TotalSize-TF_FreeSize)*100/TF_TotalSize);
//     lv_obj_align(bar_sdcard, label_sdcard_cap, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);

//     lv_obj_t *label_battery_percent = lv_label_create(cont_battery, NULL);
//     lv_label_set_text(label_battery_percent,"70%");
//     lv_obj_align(label_battery_percent, label_battery, LV_ALIGN_OUT_LEFT_MID,190, 0);

//     aux.screen = scr;
//     aux.label_flash = label_sdcard_cap;
//     aux.bar_flash = bar_sdcard;
//     aux.label_battery = label_battery_percent;
    return aux;
}

void gui_update(screen_t *screen, uint32_t total_mem, uint32_t free_mem, float bat_level)
{
    char buffer[50];
    sprintf(buffer, "Total: %dMB\nFree: %dMB,", total_mem, free_mem);
    lv_label_set_text((*screen).label_flash, buffer);

    memset(buffer, 0, strlen(buffer));
    sprintf(buffer, "BAT: %.2f V\n", bat_level);
    #ifndef DEBUG == 1
    printf(buffer);
    #endif
    
    lv_label_set_text((*screen).label_battery, buffer);

    lv_bar_set_value((*screen).bar_flash, (total_mem-free_mem)*100/total_mem);
}