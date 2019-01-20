/** @file minos_hal_indev.h
 * 
 * @brief This file has the purpose to create the MinOS input declarations.
 *  
 * @par       
 * COPYRIGHT NOTICE: (c) 2018 Barr Group.  All rights reserved.
 */ 

#ifndef MINOS_HAL_INDEV_H
#define MINOS_HAL_INDEV_H

/**************
 * INCLUDES
***************/
#include <stdint.h>
#include <stdbool.h>

/***********
 * TYPEDEFS
***********/
typedef struct key
{
    uint8_t key;
    uint8_t status;
} minos_key_t;

typedef struct func_keys{
    bool vol_up;
    bool vol_down;
    bool menu;
}func_keys_t;

typedef struct keypad
{
    uint8_t KEY_UP;
    uint8_t KEY_DOWN;
    uint8_t KEY_LEFT;
    uint8_t KEY_RIGHT;
    uint8_t KEY_A;
    uint8_t KEY_B;
    uint8_t KEY_ENTER;
    uint8_t KEY_ESC;
    func_keys_t func_keys;
}keypad_t;

keypad_t minos_keypad;

/**************
* VOLUME UP KEY
**************/
inline bool minos_keypad_get_vol_up()
{
    return minos_keypad.func_keys.vol_up;
}

inline void minos_keypad_ack_vol_up()
{
    minos_keypad.func_keys.vol_up = false;
}

inline void minos_keypad_set_vol_up()
{
    minos_keypad.func_keys.vol_up = true;
}

/*******************
* VOLUME DOWN KEY
*******************/
inline bool minos_keypad_get_vol_down()
{
    return minos_keypad.func_keys.vol_down;
}

inline void minos_keypad_ack_vol_down()
{
    minos_keypad.func_keys.vol_down = false;
}

inline void minos_keypad_set_vol_down()
{
    minos_keypad.func_keys.vol_down = true;
}

/**************
* MENU KEY
**************/
inline bool minos_keypad_get_menu()
{
    return minos_keypad.func_keys.menu;
}

inline void minos_keypad_ack_menu()
{
    minos_keypad.func_keys.menu = false;
}

inline void minos_keypad_set_menu()
{
    minos_keypad.func_keys.menu = true;
}

#endif
/*** end of file ***/
