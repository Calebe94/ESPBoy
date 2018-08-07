#include <stdint.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <driver/adc.h>
#include <driver/gpio.h>

#include "power.h"
#include "pins.h"

/*
    Initialize the power manager wich will read the battery's voltage level
*/
void power_manager_init()
{
	adc1_config_channel_atten(BAT_LEVEL, ADC_ATTEN_11db);
}

/*
    Get the voltage value from 0V to approximatelly 3.3V
*/
float get_battery_voltage()
{
    return (float)(adc1_get_raw(BAT_LEVEL) * 3.3 )/4095;
}

/*
    Get the analog voltage raw data 
*/
uint16_t get_battery_value()
{
    return (uint16_t) adc1_get_raw(BAT_LEVEL);
}

/*
    Get the battery voltage porcentage from 0% to 100% 
*/
uint8_t get_battery_porcentage()
{
    return (uint8_t) 255;
}

