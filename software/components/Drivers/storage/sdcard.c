#include <stdio.h>
#include <string.h>
#include <dirent.h> 
#include <sys/unistd.h>
#include <sys/stat.h>

#include "esp_err.h"
#include "esp_log.h"
#include "esp_vfs_fat.h"
#include "driver/sdmmc_host.h"
#include "driver/sdspi_host.h"
#include "sdmmc_cmd.h"

#include "pins.h"

#include "sdcard.h"

static const char *TAG = "sdcard_driver";

void sdcard_init(void)
{
    // This initializes the slot without card detect (CD) and write protect (WP) signals.
    // Modify slot_config.gpio_cd and slot_config.gpio_wp if your board has these signals.
    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    host.max_freq_khz = SDMMC_FREQ_PROBING;
    
    sdspi_slot_config_t slot_config = SDSPI_SLOT_CONFIG_DEFAULT();
    slot_config.gpio_miso = SD_MISO;
    slot_config.gpio_mosi = SD_MOSI;
    slot_config.gpio_sck  = SD_SCK;
    slot_config.gpio_cs   = SD_CS;

    // Options for mounting the filesystem.
    // If format_if_mount_failed is set to true, SD card will be partitioned and
    // formatted in case when mounting fails.
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = false,
        .max_files = 5,
        .allocation_unit_size = 16 * 1024
    };
    
    sdmmc_card_t* card;
    esp_err_t ret = esp_vfs_fat_sdmmc_mount("/sdcard", &host, &slot_config, &mount_config, &card);

    if (ret != ESP_OK) 
    {
        if (ret == ESP_FAIL) 
        {
            ESP_LOGE(TAG, "Failed to mount filesystem. "
                "If you want the card to be formatted, set format_if_mount_failed = true.");
        } 
        else if(ret == ESP_ERR_INVALID_STATE)
        {
            ESP_LOGE(TAG, "esp_vfs_fat_sdmmc_mount was already called");
        }
        else if(ret == ESP_ERR_NO_MEM)
        {
            ESP_LOGE(TAG, "memory can not be allocated");
        }
        else 
        {
            ESP_LOGE(TAG, "Failed to initialize the card (%s). "
                "Make sure SD card lines have pull-up resistors in place.", esp_err_to_name(ret));
        }
        return;
    }

    // Card has been initialized, print its properties
    sdmmc_card_print_info(stdout, card);

    // Use POSIX and C standard library functions to work with files.
    // First create a file.
    // ESP_LOGI(TAG, "Opening file");
    // FILE* f = fopen("/sdcard/foo.txt", "w");
    FILE * f = NULL;
    // if (f == NULL) 
    // {
    //     ESP_LOGE(TAG, "Failed to open file for writing");
    //     return;
    // }

    // fprintf(f, "Hello %s!\n", card->cid.name);
    // fclose(f);
    // ESP_LOGI(TAG, "File written");

    // Check if destination file exists before renaming
    // struct stat st;
    // if (stat("/sdcard/foo.txt", &st) == 0) {
    //     // Delete it if it exists
    //     unlink("/sdcard/foo.txt");
    // }

    // Rename original file
    // ESP_LOGI(TAG, "Renaming file");
    // if (rename("/sdcard/hello.txt", "/sdcard/foo.txt") != 0) {
    //     ESP_LOGE(TAG, "Rename failed");
    //     return;
    // }

    // Open renamed file for reading
    ESP_LOGI(TAG, "Reading file");
    f = fopen("/sdcard/foo.txt", "r");
    if (f == NULL) 
    {
        ESP_LOGE(TAG, "Failed to open file for reading");
        return;
    }

    char line[64];
    fgets(line, sizeof(line), f);
    fclose(f);
    // strip newline
    char* pos = strchr(line, '\n');
    if (pos) 
    {
        *pos = '\0';
    }
    
    ESP_LOGI(TAG, "Read from file: '%s'", line);

    ESP_LOGI(TAG, "Reading NES ROMS");
    char file_path[30];

    struct stat st;
    DIR *dir;
    struct dirent *dp;
    // char * file_name;
    dir = opendir("/sdcard/nes");

    while ( (dp=readdir(dir) ) != NULL) 
    {
        if ( !strcmp(dp->d_name, "/sdcard/nes") || !strcmp(dp->d_name, "..") )
        {
            // do nothing (straight logic)
        }
        else 
        {
            // file_name = dp->d_name; // use it
            // printf("file_name: \"%s\"\n",file_name);
            memset(file_path, 0, 30);
            sprintf(file_path, "/sdcard/nes/%s", dp->d_name);
            if (stat(file_path, &st) == 0) 
            {
                ESP_LOGI(TAG, "file_name: \"%s\" - strlen(file_name): %d - ARQUIVO EXISTE!", dp->d_name, strlen(dp->d_name));
            }
            else
            {
                ESP_LOGI(TAG, "file_name: \"%s\" - strlen(file_name): %d - ARQUIVO NÃO EXISTE!", dp->d_name, strlen(dp->d_name));
            }
            
        }
    }
    closedir(dir);

    // All done, unmount partition and disable SDMMC or SPI peripheral
    esp_vfs_fat_sdmmc_unmount();
    ESP_LOGI(TAG, "Card unmounted");

}