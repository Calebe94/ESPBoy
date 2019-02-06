/** @file minos_conf.h
 * 
 * @brief This file has the purpose to store MinOS configurations.
 *
 * @par       
 * COPYRIGHT NOTICE: (c) 2018 Barr Group.  All rights reserved.
 */ 
#ifndef MINOS_CONF_H
#define MINOS_CONF_H

/*********
 * MACROS
**********/

/*  DRIVERS  */
#define USE_DISPLAY             1
#define USE_AUDIO               0
#define USE_INPUT               1
#define USE_POWER               0
#define USE_SDCARD              1
#define USE_WIFI                0

/*  LIBS  */
#define USE_SQLITE              1
#define USE_COLLECTIONS_C       1
#define USE_ESP32_OTA           1
#define USE_SORT                1
#define USE_CIRC_LINK_LIST      1
#define USE_LINK_LIST           1
#define USE_DYNAMIC_LIST        1

/*  DAEMONS  */
#define USE_OTA_MANAGER         0
#define USE_UI_MANAGER          1
#define USE_INPUT_MANAGER       1
#define USE_BATTERY_MANAGER     0

/* DEBUG */

#endif

/*** end of file ***/