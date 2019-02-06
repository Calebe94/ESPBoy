#ifndef _INPUTS_H_
#define _INPUTS_H_

#include <stdint.h>

#define HAL_KEY_UP      0x20     // (button_up<<0)       P5
#define HAL_KEY_DOWN    0x80     // (button_down<<1)     P7
#define HAL_KEY_LEFT    0x10     // (button_left<<2)     P4
#define HAL_KEY_RIGHT   0x40     // (button_right<<3)    P6
#define HAL_KEY_A       0x08     // (button_a<<4)        P3
#define HAL_KEY_B       0x04     // (button_b<<5)        P2
#define HAL_KEY_MENU    0x200    // (button_menu<<6)     
#define HAL_KEY_VOL_D   0x400    // (vol_down<<7)
#define HAL_KEY_VOL_U   0x100    // (vol_up<<8)
#define HAL_KEY_SELECT  0x01     // (button_select<<9)   P0
#define HAL_KEY_START   0x02     // (button_start<<10)   P1

#define HAL_KEY_PRESSED     0
#define HAL_KEY_RELEASED    1


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

// bool lv_keypad_read(lv_indev_data_t *data);

#endif