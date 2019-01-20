/** @file sqlite3_conn.c
 * 
 * @brief This module has the purpose to create a SQLite3 connector. 
 *
 * @par       
 * COPYRIGHT NOTICE: (c) 2018 Barr Group.  All rights reserved.
 */ 

#include <stdio.h>
#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_spiffs.h"
#include "esp_timer.h"

#include "sqlite3.h"

static const char *TAG = "sqlite3_spiffs";

void db_init(void)
{
    ESP_LOGI(TAG, "Initializing SPIFFS");
    
    esp_vfs_spiffs_conf_t conf = {
      .base_path = "/spiffs",
      .partition_label = "storage",
      .max_files = 5,
      .format_if_mount_failed = true
    };
    
    // Use settings defined above to initialize and mount SPIFFS filesystem.
    // Note: esp_vfs_spiffs_register is an all-in-one convenience function.
    esp_err_t ret = esp_vfs_spiffs_register(&conf);

    if (ret != ESP_OK) 
    {
        if (ret == ESP_FAIL) {
            ESP_LOGE(TAG, "Failed to mount or format filesystem");
        } else if (ret == ESP_ERR_NOT_FOUND) {
            ESP_LOGE(TAG, "Failed to find SPIFFS partition");
        } else {
            ESP_LOGE(TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
        }
        return;
    }
    
    size_t total = 0, used = 0;
    ret = esp_spiffs_info(NULL, &total, &used);
    if (ret != ESP_OK) 
    {
        ESP_LOGE(TAG, "Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret));
    } else 
    {
        ESP_LOGI(TAG, "Partition size: total: %d, used: %d", total, used);
    }

    // remove existing file
    unlink("/spiffs/test1.db");
    // unlink("/spiffs/test2.db");

    sqlite3_initialize();
}

const char* data = "Callback function called";
static int callback(void *data, int argc, char **argv, char **azColName) 
{
   int i;
   printf("%s: ", (const char*)data);
   for (i = 0; i<argc; i++){
       printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int db_open(const char *filename, sqlite3 **db) 
{
   int rc = sqlite3_open(filename, db);
   if (rc) {
       printf("Can't open database: %s\n", sqlite3_errmsg(*db));
       return rc;
   } else {
       printf("Opened database successfully\n");
   }
   return rc;
}

char *zErrMsg = 0;
int db_exec(sqlite3 *db, const char *sql) 
{
   printf("%s\n", sql);
   int64_t start = esp_timer_get_time();
   int rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   if (rc != SQLITE_OK) {
       printf("SQL error: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
   } else {
       printf("Operation done successfully\n");
   }
   printf("Time taken: %lld\n", esp_timer_get_time()-start);
   return rc;
}