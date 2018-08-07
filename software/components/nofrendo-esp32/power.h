#ifndef _POWER_H_
#define _POWER_H_

#include <stdint.h>

/*
    Initialize the power manager wich will read the battery's voltage level
*/
void power_manager_init();

/*
    Get the voltage value from 0V to approximatelly 3.3V
*/
float get_battery_voltage();

/*
    Get the analog voltage raw data 
*/
uint16_t get_battery_value();

/*
    Get the battery voltage porcentage from 0% to 100% 
*/
uint8_t get_battery_porcentage();

#endif