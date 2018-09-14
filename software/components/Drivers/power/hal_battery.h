#ifndef _BATTERY_H_
#define _BATTERY_H_

#include <stdint.h>

/*
    Initialize the power manager wich will read the battery's voltage level
*/
void battery_manager_init();

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

/*
    Check if the battery is charging.
    Returns Non-zero if it's true.
*/
uint8_t is_battery_charging();
    
#endif