#include "battery_manager.h"
#include "hal_battery.h"
#include "array.h"
#include "bubble.h"
#include "k_utils.h"
#include "k_config.h"

#if BATTERY_DEBUG
#include <stdio.h>
#endif
/*
* Gera uma lista com 10 leituras
* Ordena por ordem crescente
* Remove os 3 maiores
* Remove os 3 menores
* Faz a média dos valores que sobram
*/

void battery_manager_init(void)
{
    // ArrayConf array_conf;
    // array_conf.capacity = 10;
    // enum cc_stat s = array_new_conf(&array_conf, &readings);
    // array_new(&readings);
    average_battery_voltage = 0.0;
    average_battery_voltage = 0; 
    readings_index = 0;
    for(uint8_t index = 0; index < 10; index++)
    {
        voltage_readings[index] = 0.0;
        porcentage_readings[index] = 0;
        battery_update();
    }

    battery_update();
}

void battery_update()
{
    #if DEBUG
        printf("> | BATTERY UPDATE | \n");
    #endif

    float aux_voltage = get_battery_voltage();
    // uint8_t aux_porcentage = get_battery_porcentage();

    if(readings_index == 10)
    {
        bubbleSort(voltage_readings, 10, sizeof(float), cmp_float);
        // bubbleSort(porcentage_readings, 10, sizeof(uint8_t), cmp_float);

        #if BATTERY_DEBUG 
            printf("\n> Voltage Readings: ");
            for ( uint8_t index = 0; index < 10; index++)
            {
                printf("%.2f ", voltage_readings[index]);
            }
            
            // printf("\n> Porcentage Readings: ");
            // for ( uint8_t index = 0; index < 10; index++)
            // {
            //     printf("%x ", porcentage_readings[index]);
            // }
        #endif
        
        average_battery_voltage = voltage_smoothing(voltage_readings);
        // average_battery_porcentage = porcentage_smoothing(porcentage_readings);

        readings_index = 0;
    }
    else
    {
        voltage_readings[readings_index] = aux_voltage;
        // porcentage_readings[readings_index] = aux_porcentage;
        readings_index++;
    }
}

// You can calculate the %error by:
// %error = ( | approx - exact | / exact ) * 100
// You can measure the voltage with your multimeter and then calculate the error.

// Returns the battery Porcentage with approximatelly 6% of error
uint8_t battery_porcent()
{
    if( average_battery_voltage > 4.1)
    {
        average_battery_porcentage = 100; // 100%
    }
    else if( (average_battery_voltage > 3.7) && (average_battery_voltage < 4.0) )
    {
        average_battery_porcentage = 75; // 75%
    }
    else if( (average_battery_voltage > 3.3) && (average_battery_voltage < 3.6) )
    {
        average_battery_porcentage = 50; // 50%
    }
    else if( (average_battery_voltage > 2.9) && (average_battery_voltage < 3.2) )
    {
        average_battery_porcentage = 25; // 25%
    }
    else if( average_battery_voltage < 2.6 )
    {
        average_battery_porcentage = 0; // 0%
    }

    #if DEBUG
        printf("> Battery Porcentage: %d \n", average_battery_porcentage);
    #endif
    return (uint8_t)average_battery_porcentage;
}

// Returns the battery Voltage with approximatelly 6% of error
float battery_voltage()
{
    #if DEBUG
        printf("> Battery Voltage: %.2f V\n", average_battery_voltage);
    #endif
    return (float)average_battery_voltage;
}
