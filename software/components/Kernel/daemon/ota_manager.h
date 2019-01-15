/** @file ota_manager.h
 * 
 * @brief This module has the purpose to manage the ESPBoy's Over The Air Firmware Update. 
 *
 * @par       
 * COPYRIGHT NOTICE: (c) 2018 Barr Group.  All rights reserved.
 */ 
#ifndef OTA_MANAGER_H
#define OTA_MANAGER_H

/*********************
 *      DEFINES
 *********************/

#define WIFI_SSID CONFIG_WIFI_SSID
#define WIFI_PASSWORD CONFIG_WIFI_PASSWORD

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
void ota_manager_init(void);

#endif /* LAUNCHER_H */
/*** end of file ***/
