#ifndef _INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_

#include "system.h"

keypad_t *keypad_init();

err_t keypad_update(keypad_t *keypad);

err_t keypad_read(keypad_t *keypad);

#endif