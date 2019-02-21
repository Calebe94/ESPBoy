#include "sdcard.h"

#include "esp_err.h"
#include "esp_log.h"
#include "esp_vfs_fat.h"
#include "driver/sdmmc_host.h"
#include "driver/sdspi_host.h"
#include "sdmmc_cmd.h"
#include "esp_heap_caps.h"
#include "esp_spiffs.h"

#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define SD_PIN_NUM_MISO 22
#define SD_PIN_NUM_MOSI 23
#define SD_PIN_NUM_CLK  18
#define SD_PIN_NUM_CS 4

static bool isOpen = false;

inline static void swap(char** a, char** b)
{
    char* t = *a;
    *a = *b;
    *b = t;
}

static int strcicmp(char const *a, char const *b)
{
    for (;; a++, b++)
    {
        int d = tolower((int)*a) - tolower((int)*b);
        if (d != 0 || !*a) return d;
    }
}

static int partition (char* arr[], int low, int high)
{
    char* pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high- 1; j++)
    {
        if (strcicmp(arr[j], pivot) < 0)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

static void quick_sort(char* arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

static void sort_files(char** files, int count)
{
    int n = count;
    bool swapped = true;

    if (count > 1)
    {
        quick_sort(files, 0, count - 1);
    }
}



int sdcard_files_get(const char* path, const char* extension, char*** filesOut)
{
    const int MAX_FILES = 1024;
    const uint32_t MALLOC_CAPS = MALLOC_CAP_DEFAULT; //MALLOC_CAP_SPIRAM


    int count = 0;
    char** result = (char**)malloc(MAX_FILES * sizeof(void*));
    if (!result) abort();


    DIR *dir = opendir(path);
    if( dir == NULL )
    {
        printf("opendir failed.\n");
        //abort();
        return 0;
    }

    int extensionLength = strlen(extension);
    if (extensionLength < 1) abort();


    char* temp = (char*)malloc(extensionLength + 1);
    if (!temp) abort();

    memset(temp, 0, extensionLength + 1);


    struct dirent *entry;
    while((entry=readdir(dir)) != NULL)
    {
        size_t len = strlen(entry->d_name);


        // ignore 'hidden' files (MAC)
        bool skip = false;
        if (entry->d_name[0] == '.') skip = true;


        memset(temp, 0, extensionLength + 1);
        if (!skip)
        {
            for (int i = 0; i < extensionLength; ++i)
            {
                temp[i] = tolower((int)entry->d_name[len - extensionLength + i]);
            }

            if (len > extensionLength)
            {
                if (strcmp(temp, extension) == 0)
                {
                    result[count] = (char*)malloc(len + 1);
                    // printf("%s: allocated %s\n", __func__, result[count]);

                    if (!result[count])
                    {
                        abort();
                    }

                    strcpy(result[count], entry->d_name);

                    printf("%s: allocated %s\n", __func__, result[count]);

                    ++count;

                    if (count >= MAX_FILES) break;
                }
            }
        }
    }

    closedir(dir);
    free(temp);

    sort_files(result, count);

    *filesOut = result;
    return count;
}

void sdcard_files_free(char** files, int count)
{
    for (int i = 0; i < count; ++i)
    {
        //printf("%s: freeing item %p\n", __func__, files[i]);
        free(files[i]);
    }

    //printf("%s: freeing array %p\n", __func__, files);
    free(files);
}

esp_err_t sdcard_open(const char* base_path)
{
    esp_err_t ret;

    if (isOpen)
    {
        printf("sdcard_open: alread open.\n");
        ret = ESP_FAIL;
    }
    else
    {
        // sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    	// host.slot = HSPI_HOST; // HSPI_HOST;
    	// //host.max_freq_khz = SDMMC_FREQ_HIGHSPEED; //10000000;
        // host.max_freq_khz = SDMMC_FREQ_DEFAULT;

    	// sdspi_slot_config_t slot_config = SDSPI_SLOT_CONFIG_DEFAULT();
    	// slot_config.gpio_miso = (gpio_num_t)SD_PIN_NUM_MISO;
    	// slot_config.gpio_mosi = (gpio_num_t)SD_PIN_NUM_MOSI;
    	// slot_config.gpio_sck  = (gpio_num_t)SD_PIN_NUM_CLK;
    	// slot_config.gpio_cs = (gpio_num_t)SD_PIN_NUM_CS;
    	// slot_config.dma_channel = 2;


        sdmmc_host_t host = SDMMC_HOST_DEFAULT();

        // This initializes the slot without card detect (CD) and write protect (WP) signals.
        // Modify slot_config.gpio_cd and slot_config.gpio_wp if your board has these signals.
        sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();

        // To use 1-line SD mode, uncomment the following line:
        slot_config.width = 1;

        // GPIOs 15, 2, 4, 12, 13 should have external 10k pull-ups.
        // Internal pull-ups are not sufficient. However, enabling internal pull-ups
        // does make a difference some boards, so we do that here.
        gpio_pullup_en(GPIO_NUM_13);  
        gpio_set_pull_mode(15, GPIO_PULLUP_ONLY);   // CMD, needed in 4- and 1- line modes
        gpio_set_pull_mode(2, GPIO_PULLUP_ONLY);    // D0, needed in 4- and 1-line modes
        gpio_set_pull_mode(4, GPIO_PULLUP_ONLY);    // D1, needed in 4-line mode only
        gpio_set_pull_mode(12, GPIO_PULLUP_ONLY);   // D2, needed in 4-line mode only
        gpio_set_pull_mode(13, GPIO_PULLUP_ONLY);   // D3, needed in 4- and 1-line modes

        // Options for mounting the filesystem.
        // If format_if_mount_failed is set to true, SD card will be partitioned and
        // formatted in case when mounting fails.
        // esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        //     .format_if_mount_failed = true,
        //     .max_files = 5,
        //     .allocation_unit_size = 16 * 1024
        // };
        



    	// Options for mounting the filesystem.
    	// If format_if_mount_failed is set to true, SD card will be partitioned and
    	// formatted in case when mounting fails.
    	esp_vfs_fat_sdmmc_mount_config_t mount_config;
        memset(&mount_config, 0, sizeof(mount_config));

    	mount_config.format_if_mount_failed = false;
    	mount_config.max_files = 5;


    	// Use settings defined above to initialize SD card and mount FAT filesystem.
    	// Note: esp_vfs_fat_sdmmc_mount is an all-in-one convenience function.
    	// Please check its source code and implement error recovery when developing
    	// production applications.
    	sdmmc_card_t* card;
    	ret = esp_vfs_fat_sdmmc_mount(base_path, &host, &slot_config, &mount_config, &card);

    	if (ret == ESP_OK)
        {
            isOpen = true;
        }
        else
        {
            printf("sdcard_open: esp_vfs_fat_sdmmc_mount failed (%d)\n", ret);
        }
    }

	return ret;
}


esp_err_t sdcard_close()
{
    esp_err_t ret;

    if (!isOpen)
    {
        printf("sdcard_close: not open.\n");
        ret = ESP_FAIL;
    }
    else
    {
        ret = esp_vfs_fat_sdmmc_unmount();

        if (ret != ESP_OK)
        {
            printf("sdcard_close: esp_vfs_fat_sdmmc_unmount failed (%d)\n", ret);
    	}
        else
        {
            isOpen = false;
        }


    }

    return ret;
}


size_t sdcard_get_filesize(const char* path)
{
    size_t ret = 0;

    if (!isOpen)
    {
        printf("sdcard_get_filesize: not open.\n");
    }
    else
    {
        FILE* f = fopen(path, "rb");
        if (f == NULL)
        {
            printf("sdcard_get_filesize: fopen failed.\n");
        }
        else
        {
            // get the file size
            fseek(f, 0, SEEK_END);
            ret = ftell(f);
            fseek(f, 0, SEEK_SET);
        }
    }

    return ret;
}

size_t sdcard_copy_file_to_memory(const char* path, void* ptr)
{
    size_t ret = 0;

    if (!isOpen)
    {
        printf("sdcard_copy_file_to_memory: not open.\n");
    }
    else
    {
        if (!ptr)
        {
            printf("sdcard_copy_file_to_memory: ptr is null.\n");
        }
        else
        {
            FILE* f = fopen(path, "rb");
            if (f == NULL)
            {
                printf("sdcard_copy_file_to_memory: fopen failed.\n");
            }
            else
            {
                // copy
                const size_t BLOCK_SIZE = 512;
                while(true)
                {
                    __asm__("memw");
                    size_t count = fread((uint8_t*)ptr + ret, 1, BLOCK_SIZE, f);
                    __asm__("memw");

                    ret += count;

                    if (count < BLOCK_SIZE) break;
                }
            }
        }
    }

    return ret;
}

char* sdcard_create_savefile_path(const char* base_path, const char* fileName)
{
    char* result = NULL;

    if (!base_path) abort();
    if (!fileName) abort();

    //printf("%s: base_path='%s', fileName='%s'\n", __func__, base_path, fileName);

    // Determine folder
    char* extension = fileName + strlen(fileName); // place at NULL terminator
    while (extension != fileName)
    {
        if (*extension == '.')
        {
            ++extension;
            break;
        }
        --extension;
    }

    if (extension == fileName)
    {
        printf("%s: File extention not found.\n", __func__);
        abort();
    }

    //printf("%s: extension='%s'\n", __func__, extension);

    const char* DATA_PATH = "/esplay/data/";
    const char* SAVE_EXTENSION = ".sav";

    size_t savePathLength = strlen(base_path) + strlen(DATA_PATH) + strlen(extension) + 1 + strlen(fileName) + strlen(SAVE_EXTENSION) + 1;
    char* savePath = malloc(savePathLength);
    if (savePath)
    {
        strcpy(savePath, base_path);
        strcat(savePath, DATA_PATH);
        strcat(savePath, extension);
        strcat(savePath, "/");
        strcat(savePath, fileName);
        strcat(savePath, SAVE_EXTENSION);

        printf("%s: savefile_path='%s'\n", __func__, savePath);

        result = savePath;
    }

    return result;
}
