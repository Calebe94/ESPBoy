/*

This code is based on Espressif provided SPI Master example which was
released to Public Domain: https://goo.gl/ksC2Ln


Copyright (c) 2017-2018 Espressif Systems (Shanghai) PTE LTD
Copyright (c) 2018 Mika Tuupola

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_system.h>
#include <driver/spi_master.h>
#include <soc/gpio_struct.h>
#include <driver/gpio.h>
#include <esp_log.h>
#include <driver/spi_common.h>

#include "ili9341.h"

static const char *TAG = "ili9341";

DRAM_ATTR static const lcd_init_cmd_t lcd_init_cmds[]={
    /* Power contorl B, power control = 0, DC_ENA = 1 */
    {ILI9341_PWCTRB, {0x00, 0x83, 0X30}, 3},
    /* Power on sequence control,
     * cp1 keeps 1 frame, 1st frame enable
     * vcl = 0, ddvdh=3, vgh=1, vgl=2
     * DDVDH_ENH=1
     */
    {ILI9341_PWONCTR, {0x64, 0x03, 0X12, 0X81}, 4},
    /* Driver timing control A,
     * non-overlap=default +1
     * EQ=default - 1, CR=default
     * pre-charge=default - 1
     */
    {ILI9341_DRVTCTRA, {0x85, 0x01, 0x79}, 3},
    /* Power control A, Vcore=1.6V, DDVDH=5.6V */
    {ILI9341_PWCTRA, {0x39, 0x2C, 0x00, 0x34, 0x02}, 5},
    /* Pump ratio control, DDVDH=2xVCl */
    {ILI9341_PUMPRTC, {0x20}, 1},
    /* Driver timing control, all=0 unit */
    {ILI9341_TMCTRA, {0x00, 0x00}, 2},
    /* Power control 1, GVDD=4.75V */
    {ILI9341_PWCTR1, {0x26}, 1},
    /* Power control 2, DDVDH=VCl*2, VGH=VCl*7, VGL=-VCl*3 */
    {ILI9341_PWCTR2, {0x11}, 1},
    /* VCOM control 1, VCOMH=4.025V, VCOML=-0.950V */
    {ILI9341_VMCTR1, {0x35, 0x3E}, 2},
    /* VCOM control 2, VCOMH=VMH-2, VCOML=VML-2 */
    {ILI9341_VMCTR2, {0xBE}, 1},
    /* Memory access contorl, MX=MY=0, MV=1, ML=0, BGR=1, MH=0 */
    //{ILI9341_MADCTL, {0x28}, 1},
    {ILI9341_MADCTL, {0x08}, 1}, // for M5Stack
    /* Pixel format, 16bits/pixel for RGB/MCU interface */
    {ILI9341_PIXFMT, {0x55}, 1}, // 0b01010101 ie. 16 bits per pixel
    /* Frame rate control, f=fosc, 70Hz fps */
    {ILI9341_FRMCTR1, {0x00, 0x1B}, 2},
    /* Enable 3 gamma control, disabled */
    {ILI9341_3GENABLE, {0x08}, 1},
    /* Gamma set, curve 1 */
    {ILI9341_GAMMASET, {0x01}, 1},
    /* Positive gamma correction */
    {ILI9341_GMCTRP1, {0x1F, 0x1A, 0x18, 0x0A, 0x0F, 0x06, 0x45, 0X87, 0x32, 0x0A, 0x07, 0x02, 0x07, 0x05, 0x00}, 15},
    /* Negative gamma correction */
    {ILI9341_GMCTRN1, {0x00, 0x25, 0x27, 0x05, 0x10, 0x09, 0x3A, 0x78, 0x4D, 0x05, 0x18, 0x0D, 0x38, 0x3A, 0x1F}, 15},
    /* Column address set, SC=0, EC=0xEF */
    {ILI9341_CASET, {0x00, 0x00, 0x00, 0xEF}, 4},
    /* Page address set, SP=0, EP=0x013F */
    {ILI9341_PASET, {0x00, 0x00, 0x01, 0x3f}, 4},
    /* Memory write */
    {ILI9341_RAMWR, {0}, 0},
    /* Entry mode set, Low vol detect disabled, normal display */
    {ILI9341_ENTRYMODE, {0x07}, 1},
    /* Display function control */
    {ILI9341_DFUNCTR, {0x0A, 0x82, 0x27, 0x00}, 4},
    /* Sleep out */
    {ILI9341_SLPOUT, {0}, 0x80},
    /* Display on */
    {ILI9341_DISPON, {0}, 0x80},
    /* End of commands . */
    {0, {0}, 0xff},
};

/* Uses spi_device_transmit, which waits until the transfer is complete. */
static void ili9341_command(spi_device_handle_t spi, const uint8_t command)
{
    spi_transaction_t transaction;

    memset(&transaction, 0, sizeof(transaction));
    transaction.length = 1 * 8; /* Command is 1 byte ie 8 bits. */
    transaction.tx_buffer = &command; /* The data is the cmd itself. */
    transaction.user = (void*)0; /* DC needs to be set to 0. */
    ESP_ERROR_CHECK(spi_device_transmit(spi, &transaction));
}

/* Uses spi_device_transmit, which waits until the transfer is complete. */
static void ili9341_data(spi_device_handle_t spi, const uint8_t *data, uint16_t length)
{
    spi_transaction_t transaction;

    if (0 == length) { return; };
    memset(&transaction, 0, sizeof(transaction));
    transaction.length = length * 8; /* Length in bits. */
    transaction.tx_buffer = data;
    transaction.user = (void*)1; /* DC needs to be set to 1. */
    ESP_ERROR_CHECK(spi_device_transmit(spi, &transaction));
}


/* This function is called (in irq context!) just before a transmission starts. */
/* It will set the DC line to the value indicated in the user field. */
static void ili9341_pre_callback(spi_transaction_t *transaction)
{
    int dc=(int)transaction->user;
    gpio_set_level(CONFIG_ILI9341_PIN_DC, dc);
}

static void ili9341_wait(spi_device_handle_t spi)
{
    spi_transaction_t *rtrans;

    /* TODO: This should be all transactions. */
    for (uint8_t i = 0; i <= 5; i++) {
        ESP_ERROR_CHECK(spi_device_get_trans_result(spi, &rtrans, portMAX_DELAY));
        /* Do something with the result. */
    }
}

static void ili9431_spi_master_init(spi_device_handle_t *spi)
{
    spi_bus_config_t buscfg = {
        .miso_io_num = CONFIG_ILI9341_PIN_MISO,
        .mosi_io_num = CONFIG_ILI9341_PIN_MOSI,
        .sclk_io_num = CONFIG_ILI9341_PIN_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = SPI_MAX_TRANSFER_SIZE /* Max transfer size in bytes. */
    };
    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = CONFIG_SPI_CLOCK_SPEED_HZ,
        .mode = 0,
        .spics_io_num = CONFIG_ILI9341_PIN_CS,
        .queue_size = 64,
        .pre_cb = ili9341_pre_callback, /* Handles D/C line. */
        .flags = SPI_DEVICE_NO_DUMMY
    };
    ESP_ERROR_CHECK(spi_bus_initialize(1, &buscfg, 1));
    ESP_ERROR_CHECK(spi_bus_add_device(1, &devcfg, spi));
}

void ili9341_init1(spi_device_handle_t *spi)
{
    uint8_t cmd = 0;

    /* Init SPI driver. */
    ili9431_spi_master_init(spi);

    /* Init non spi gpio. */
    gpio_set_direction(CONFIG_ILI9341_PIN_DC, GPIO_MODE_OUTPUT);
    gpio_set_direction(CONFIG_ILI9341_PIN_RST, GPIO_MODE_OUTPUT);
    gpio_set_direction(CONFIG_ILI9341_PIN_BCKL, GPIO_MODE_OUTPUT);

    /* Reset the display. */
    gpio_set_level(CONFIG_ILI9341_PIN_RST, 0);
    vTaskDelay(100 / portTICK_RATE_MS);
    gpio_set_level(CONFIG_ILI9341_PIN_RST, 1);
    vTaskDelay(100 / portTICK_RATE_MS);

    ESP_LOGD(TAG, "Initialize the display.");

    /* Send all the commands. */
    while (lcd_init_cmds[cmd].databytes != 0xff) { /* 0xff is the end marker. */
        ili9341_command(*spi, lcd_init_cmds[cmd].cmd);
        ili9341_data(*spi, lcd_init_cmds[cmd].data, lcd_init_cmds[cmd].databytes & 0x1F);
        if (lcd_init_cmds[cmd].databytes & 0x80) {
            vTaskDelay(100 / portTICK_RATE_MS);
        }
        cmd++;
    }

    /* Enable backlight. */
    gpio_set_level(CONFIG_ILI9341_PIN_BCKL, 1);
}

void ili9431_blit(spi_device_handle_t spi, uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t *bitmap)
{
    int x;

    int32_t x2 = x1 + w - 1;
    int32_t y2 = y1 + h - 1;

    static spi_transaction_t trans[6];
    uint32_t size = w * h;

    /* In theory, it's better to initialize trans and data only once and hang */
    /* on to the initialized variables. We allocate them on the stack, so we need */
    /* to re-init them each call. */
    for (x = 0; x < 6; x++) {
        memset(&trans[x], 0, sizeof(spi_transaction_t));
        if (0 == (x&1)) {
            /* Even transfers are commands. */
            trans[x].length = 8;
            trans[x].user = (void*)0;
        } else {
            /* Odd transfers are data. */
            trans[x].length = 8 * 4;
            trans[x].user = (void*)1;
        }
        trans[x].flags = SPI_TRANS_USE_TXDATA;
    }

    trans[0].tx_data[0] = 0x2A;           //Column Address Set
    trans[1].tx_data[0] = x1 >> 8;              //Start Col High
    trans[1].tx_data[1] = x1 & 0xff;              //Start Col Low
    trans[1].tx_data[2] = x2 >> 8;       //End Col High
    trans[1].tx_data[3] = x2 &0xff;     //End Col Low
    trans[2].tx_data[0] = 0x2B;           //Page address set
    trans[3].tx_data[0] = y1 >> 8;        //Start page high
    trans[3].tx_data[1] = y1 & 0xff;      //start page low
    trans[3].tx_data[2] = y2 >> 8;    //end page high
    trans[3].tx_data[3] = y2 & 0xff;  //end page low
    trans[4].tx_data[0] = 0x2C;           //memory write
    trans[5].tx_buffer = bitmap;        //finally send the line data
    trans[5].length = size * 2 * 8; //320*2*8*PARALLEL_LINES;          //Data length, in bits
    trans[5].flags = 0; //undo SPI_TRANS_USE_TXDATA flag

    for (x = 0; x <= 5; x++) {
        ESP_ERROR_CHECK(spi_device_queue_trans(spi, &trans[x], portMAX_DELAY));
    }

    /* Could do stuff here... */

    ili9341_wait(spi);
}

void ili9431_putpixel(spi_device_handle_t spi, uint16_t x1, uint16_t y1, uint16_t colour)
{
    ili9431_blit(spi, x1, y1, 1, 1, &colour);
}

