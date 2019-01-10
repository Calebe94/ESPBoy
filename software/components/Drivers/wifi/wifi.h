#ifndef _WIFI_H_
#define _WIFI_H_

#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_event_loop.h"

#include "nvs_flash.h"

#define WIFI_SSID CONFIG_WIFI_SSID
#define WIFI_PASSWORD CONFIG_WIFI_PASSWORD

void wifi_init(void);

esp_err_t wifi_handler(void *ctx, system_event_t *event);

#endif