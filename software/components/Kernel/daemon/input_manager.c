#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"

#include "lvgl.h"
#include "hal_keypad.h"
#include "input_manager.h"

#include "minos_hal_indev.h"

#include "k_config.h"

static const char * TAG = "INPUT_MANAGER";
// static keypad_t keypad_status;

static uint8_t key_pressed;
static uint8_t key_status;
static unsigned int pressed_key_time;

void keypad_manager_init()
{
    key_pressed = 0; // NONE
    key_status  = 0;
    pressed_key_time = 0;
}

void keypad_update()
{
    uint16_t raw_input = raw_keypad_read();

    key_status = LV_INDEV_STATE_PR;

    if((raw_input&HAL_KEY_UP) == HAL_KEY_PRESSED)
    {
        #if INPUT_MONITOR_DEBUG
            ESP_LOGI(TAG, "KEY_PRESSED: UP");
        #endif
        key_pressed = LV_GROUP_KEY_UP;
    }
    else if((raw_input&HAL_KEY_DOWN) == HAL_KEY_PRESSED)
    {
        #if INPUT_MONITOR_DEBUG
            ESP_LOGI(TAG, "KEY_PRESSED: DOWN");
        #endif
        key_pressed = LV_GROUP_KEY_DOWN;
    }
    else if((raw_input&HAL_KEY_LEFT) == HAL_KEY_PRESSED)
    {
        #if INPUT_MONITOR_DEBUG
            ESP_LOGI(TAG, "KEY_PRESSED: LEFT");
        #endif
        key_pressed = LV_GROUP_KEY_LEFT;
    }
    else if((raw_input&HAL_KEY_RIGHT) == HAL_KEY_PRESSED)
    {
        #if INPUT_MONITOR_DEBUG
            ESP_LOGI(TAG, "KEY_PRESSED: RIGHT");
        #endif
        key_pressed = LV_GROUP_KEY_RIGHT;
    }
    else if((raw_input&HAL_KEY_A) == HAL_KEY_PRESSED)
    {
        #if INPUT_MONITOR_DEBUG
            ESP_LOGI(TAG, "KEY_PRESSED: A");
        #endif
        key_status = LV_INDEV_STATE_REL;
    }
    else if((raw_input&HAL_KEY_B) == HAL_KEY_PRESSED)
    {
        #if INPUT_MONITOR_DEBUG
            ESP_LOGI(TAG, "KEY_PRESSED: B");
        #endif
        key_status = LV_INDEV_STATE_REL;
        // key_pressed = LV_GROUP_KEY_ENTER;
    }
    else if((raw_input&HAL_KEY_MENU) == HAL_KEY_PRESSED)
    {
        #if INPUT_MONITOR_DEBUG
            ESP_LOGI(TAG, "KEY_PRESSED: MENU");
        #endif
        minos_keypad_set_menu();
        key_pressed = LV_GROUP_KEY_ESC;
    }
    else if((raw_input&HAL_KEY_VOL_D) == HAL_KEY_PRESSED)
    {
        #if INPUT_MONITOR_DEBUG
            ESP_LOGI(TAG, "KEY_PRESSED: VOLUME_DOWN");
        #endif
        minos_keypad_set_vol_down();
        key_status = LV_INDEV_STATE_REL;
        // key_pressed = LV_GROUP_KEY_ESC;
    }
    else if((raw_input&HAL_KEY_VOL_U) == HAL_KEY_PRESSED)
    {
        #if INPUT_MONITOR_DEBUG
            ESP_LOGI(TAG, "KEY_PRESSED: VOLUME_UP");
        #endif
        minos_keypad_set_vol_up();
        key_status = LV_INDEV_STATE_REL;
        // key_pressed = LV_GROUP_KEY_ESC;
    }
    else if((raw_input&HAL_KEY_SELECT) == HAL_KEY_PRESSED)
    {
        #if INPUT_MONITOR_DEBUG
            ESP_LOGI(TAG, "KEY_PRESSED: SELECT");
        #endif
        key_pressed = LV_GROUP_KEY_NEXT;
        // key_pressed = LV_GROUP_KEY_ESC;
    }
    else if((raw_input&HAL_KEY_START) == HAL_KEY_PRESSED)
    {
        #if INPUT_MONITOR_DEBUG
            ESP_LOGI(TAG, "KEY_PRESSED: START");
        #endif
        key_pressed = LV_GROUP_KEY_ENTER;
        // key_pressed = LV_GROUP_KEY_ESC;
    }
    else
    {
        key_status = LV_INDEV_STATE_REL;
    }
}

bool lv_keypad_read(lv_indev_data_t *data)
{
    data->state = key_status;
    data->key   = key_pressed;
    
    return false;
}