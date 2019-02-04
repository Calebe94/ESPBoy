/** @file i2c_scanner.h
 * 
 * @brief This file has the purpose to store the MinOS I2C bus scanner functions.
 *
 * @par       
 * COPYRIGHT NOTICE: (c) 2018 Barr Group.  All rights reserved.
 */ 
#ifndef I2C_SCANNER_H
#define I2C_SCANNER_H

/***********
 * INCLUDES
************/
#include "esp_err.h"
#include "minos_conf.h"

#if USE_COLLECTIONS_C
    #include "array.h"
#endif

/*******************
 * GLOBAL FUNCTIONS
********************/
#if USE_COLLECTIONS_C
esp_err_t i2c_scanner(Array * aux);
#else
esp_err_t i2c_scanner(void * aux);
#endif

#endif
/*** end of file ***/