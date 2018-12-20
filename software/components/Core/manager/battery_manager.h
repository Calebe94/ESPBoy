#ifndef _BATERY_MANAGER_H_
#define _BATERY_MANAGER_H_

#include "system.h"

void battery_manager_init(void);

uint8_t battery_porcent();

float battery_voltage();

#endif