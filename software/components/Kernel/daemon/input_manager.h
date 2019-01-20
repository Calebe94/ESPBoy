#ifndef _INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_

#include "k_config.h"
#include "lv_indev.h"


void keypad_manager_init();

void keypad_update();

bool minos_keypad_read();


// err_t keypad_update(keypad_t *keypad);

// err_t keypad_read(keypad_t *keypad);

bool lv_keypad_read(lv_indev_data_t *data);

#endif