#ifndef _BATERY_MANAGER_H_
#define _BATERY_MANAGER_H_

#include "minos_config.h"

/*******************
 * GLOBAL FUNCTIONS
*******************/

void battery_manager_init(void);

void battery_update();

uint8_t battery_porcent();

float battery_voltage();

#endif