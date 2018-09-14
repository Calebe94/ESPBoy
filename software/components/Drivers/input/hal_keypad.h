#ifndef _INPUTS_H_
#define _INPUTS_H_

#include <stdint.h>
#include <stdbool.h>
#include "lvgl/lv_hal/lv_hal_indev.h"

void keypad_init(void);

/*
    Read the ESPBoy keypad.
    Byte:
        Bit 0: KEY_UP,
        Bit 1: KEY_DOWN,
        Bit 2: KEY_LEFT,
        Bit 3: KEY_RIGHT,
        Bit 4: KEY_A,
        Bit 5: KEY_B,
        Bit 6: KEY_START,
        Bit 7: KEY_SELECT,
        Bit 8: KEY_VOL_UP,
        Bit 9: KEY_VOL_DOWN,
        Bit 10: KEY_MENU
*/
uint16_t raw_keypad_read();

bool lv_keypad_read(lv_indev_data_t *data);

#endif