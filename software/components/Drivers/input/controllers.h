#ifndef _CONTROLLERS_H_
#define _CONTROLLERS_H_

#include <stdint.h>
#include "hal_keypad.h"
/*
    Nintendo Entertainement System controller format that nofrendo recognizes
*/
uint16_t nes_controller_read();

/*
    Sega Master System controller format that ... recognizes
*/
uint16_t sms_controller_read();

/*
    Sega Game Gear controller format that ... recognizes
*/
uint16_t gg_controller_read();

/*
    Nintendo Game Boy controller format that ... recognizes
*/
uint16_t gb_controller_read();

/*
    Nintendo Game Boy Color controller format that ... recognizes
*/
uint16_t gbc_controller_read();

#endif