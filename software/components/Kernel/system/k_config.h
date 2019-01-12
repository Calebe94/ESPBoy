#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include <stdint.h>

#define DEBUG               0
#define KEYPAD_DEBUG        0
#define BATTERY_DEBUG       0
#define INPUT_MONITOR_DEBUG 0
#define OTA_MONITOR_DEBUG   0

#define RESP_OK             0
#define RESP_FAIL           1

typedef int8_t err_t;

typedef struct audio
{
    uint8_t volume;
    uint8_t jack_status;
    uint8_t amplifier_status;
}audio_t;

typedef struct power
{
    uint8_t battery_voltage;
    uint8_t battery_porcentage;
    uint8_t charging;
}power_t;

typedef struct keypad
{
    uint8_t KEY_UP;
    uint8_t KEY_DOWN;
    uint8_t KEY_LEFT;
    uint8_t KEY_RIGHT;
    uint8_t KEY_A;
    uint8_t KEY_B;
    uint8_t KEY_MENU;
    uint8_t KEY_VOL_U;
    uint8_t KEY_VOL_D;
    uint8_t KEY_ENTER;
    uint8_t KEY_ESC;
}keypad_t;

typedef struct input
{
    keypad_t keypdad; 
}input_t;

typedef struct system_settings 
{
    audio_t audio;
    power_t power;
    input_t input;

    // context
    // theme
    // ...
}sys_settings_t;

#endif