/** @file daemon_init.h
 * 
 * @brief This module has the purpose to initiate the MinOS daemons. 
 *
 * @par       
 * COPYRIGHT NOTICE: (c) 2018 Barr Group.  All rights reserved.
 */ 
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "battery_manager.h"
#include "ui_manager.h"
#include "input_manager.h"
#include "ota_manager.h"

// #include "input_manager.h"

void manager_init();

void manager_update();

#endif