#ifndef _K_UTILS_H_
#define _K_UTILS_H_

static int cmp_float(const void *i, const void *j)
{
    if(*(const float *)i < *(const float *)j) return -1;
    if(*(const float *)i > *(const float *)j)
        return +1;
    else
        return 0;
}

float voltage_smoothing(float *voltages)
{
    float smoothed_value = 0.0;
    for( uint8_t index = 3; index < 7 ; index++ )
    {
        smoothed_value+= voltages[index];
    }
    return (float)(smoothed_value/4);
}

uint8_t porcentage_smoothing(uint8_t *porcentage)
{
    float smoothed_value = 0.0;
    for( uint8_t index = 3; index < 7 ; index++ )
    {
        smoothed_value+= porcentage[index];
    }
    return (uint8_t)(smoothed_value/4);
}

#endif