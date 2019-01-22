#ifndef _K_UTILS_H_
#define _K_UTILS_H_

#include <stdint.h>
#include <stddef.h> 

int cmp_float(const void *i, const void *j)
{
    if(*(const float *)i < *(const float *)j) return -1;
    if(*(const float *)i > *(const float *)j)
        return +1;
    else
        return 0;
}

void swap(uint8_t  *x, uint8_t  *y, size_t size)
{
  while(size-- > 0) {
    uint8_t  tmp = *x;
    *x++ = *y;
    *y++ = tmp;
  }
}

void bubble_sort(void *base,
                size_t num,
                size_t size,
                int (*cmp)(const void *, const void *))
{
    uint8_t  *pbBase = (uint8_t  *)base;
    int sorted = true;
    size_t i, j;

    num -= 1;

    if(num) {
        for(i = 0; i < num; i++) {
        sorted = true;
        for(j = 0; j < num - i; j++) {
            if(cmp(pbBase + (j + 1) * size, pbBase + j * size) > 0) {
            swap(pbBase + (j + 1) * size, pbBase + j * size, size);
            sorted = false;
            }
        }
        if(sorted) break;
        }
    }
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