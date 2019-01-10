#ifndef _BATERY_MANAGER_H_
#define _BATERY_MANAGER_H_

#include "system.h"
#include "array.h"

// Array *readings;
float voltage_readings[10];
uint8_t porcentage_readings[10];

uint8_t readings_index;

float average_battery_voltage; // The average value from voltage battery
uint8_t average_battery_porcentage; // The average value from voltage porcentage

void battery_manager_init(void);

void battery_update();

uint8_t battery_porcent();

float battery_voltage();

#endif