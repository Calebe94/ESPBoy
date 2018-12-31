#include "launcher.h"
#include "lvgl.h"

void create_header()
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
    * ADD A VOLUME ICON
    ****************/
    lv_obj_t * volume = lv_label_create(scr, NULL); /*First parameters (scr) is the parent*/
    lv_label_set_text(volume, SYMBOL_VOLUME_MAX); /*Set the text*/
    lv_obj_align(volume, header, LV_ALIGN_IN_TOP_RIGHT, (LV_HOR_RES - lv_obj_get_width(header)-10)/2.6, 0);

    /****************
    * ADD A WIFI ICON
    ****************/
    lv_obj_t * wifi = lv_label_create(scr, NULL); /*First parameters (scr) is the parent*/
    lv_label_set_text(wifi, SYMBOL_WIFI); /*Set the text*/
    lv_obj_align(wifi, header, LV_ALIGN_IN_TOP_RIGHT, (LV_HOR_RES - lv_obj_get_width(header)-10)/3.4, 0);

    /****************
    * ADD A BLUETOOTH ICON
    ****************/
    lv_obj_t * bluetooth = lv_label_create(scr, NULL); /*First parameters (scr) is the parent*/
    lv_label_set_text(bluetooth, SYMBOL_BLUETOOTH); /*Set the text*/
    lv_obj_align(bluetooth, header, LV_ALIGN_IN_TOP_LEFT, -80, 0);

    /****************
    * ADD A CLOCK
    ****************/
    // lv_obj_t * clock = lv_label_create(scr, NULL); /*First parameters (scr) is the parent*/
    // lv_label_set_text(clock, "15:00"); /*Set the text*/
    // lv_obj_align(clock, header, LV_ALIGN_IN_TOP_LEFT, ((lv_obj_get_width(header)-LV_HOR_RES)/2)+5, 0);

    // screen_t aux;
    // lv_theme_t *th = lv_theme_night_init(LV_VER_RES, NULL);
    // lv_theme_set_current(th);

}