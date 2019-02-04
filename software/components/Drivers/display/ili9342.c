/**
 * @file ili9341.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "ili9341.h"
#include "disp_spi.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/*The LCD needs a bunch of command/argument values to be initialized. They are stored in this struct. */
typedef struct {
    uint8_t cmd;
    uint8_t data[16];
    uint8_t databytes; //No of data in data; bit 7 = delay after set; 0xFF = end of cmds.
} lcd_init_cmd_t;

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void ili9441_send_cmd(uint8_t cmd);
static void ili9341_send_data(void * data, uint16_t length);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void ili9431_init(void)
{
	lcd_init_cmd_t ili_init_cmds[]={
		{0xCF, {0x00, 0x83, 0X30}, 3},
		{0xED, {0x64, 0x03, 0X12, 0X81}, 4},
		{0xE8, {0x85, 0x01, 0x79}, 3},
		{0xCB, {0x39, 0x2C, 0x00, 0x34, 0x02}, 5},
		{0xF7, {0x20}, 1},
		{0xEA, {0x00, 0x00}, 2},
		{0xC0, {0x26}, 1},			/*Power control*/
		{0xC1, {0x11}, 1},			/*Power control */
		{0xC5, {0x35, 0x3E}, 2},	/*VCOM control*/
		{0xC7, {0xBE}, 1},			/*VCOM control*/
		{0x36, {0x28^0xC0}, 1},			/*Memory Access Control*/
		{0x3A, {0x55}, 1},			/*Pixel Format Set*/
		{0xB1, {0x00, 0x1B}, 2},
		{0xF2, {0x08}, 1},
		{0x26, {0x01}, 1},
		{0xE0, {0x1F, 0x1A, 0x18, 0x0A, 0x0F, 0x06, 0x45, 0X87, 0x32, 0x0A, 0x07, 0x02, 0x07, 0x05, 0x00}, 15},
		{0XE1, {0x00, 0x25, 0x27, 0x05, 0x10, 0x09, 0x3A, 0x78, 0x4D, 0x05, 0x18, 0x0D, 0x38, 0x3A, 0x1F}, 15},
		{0x2A, {0x00, 0x00, 0x00, 0xEF}, 4},
		{0x2B, {0x00, 0x00, 0x01, 0x3f}, 4},
		{0x2C, {0}, 0},
		{0xB7, {0x07}, 1},
		{0xB6, {0x0A, 0x82, 0x27, 0x00}, 4},
		{0x11, {0}, 0x80},
		{0x29, {0}, 0x80},
		{0, {0}, 0xff},
	};

	//Initialize non-SPI GPIOs
	gpio_set_direction(ILI9341_DC, GPIO_MODE_OUTPUT);
	// gpio_set_direction(ILI9341_RST, GPIO_MODE_OUTPUT);
	gpio_set_direction(ILI9341_BCKL, GPIO_MODE_OUTPUT);

	//Reset the display
	// gpio_set_level(ILI9341_RST, 0);
	// vTaskDelay(100 / portTICK_RATE_MS);
	// gpio_set_level(ILI9341_RST, 1);
	// vTaskDelay(100 / portTICK_RATE_MS);


	// printf("ILI9341 initialization.\n");


	//Send all the commands
	uint16_t cmd = 0;
	while (ili_init_cmds[cmd].databytes!=0xff) 
	{
		ili9441_send_cmd(ili_init_cmds[cmd].cmd);
		ili9341_send_data(ili_init_cmds[cmd].data, ili_init_cmds[cmd].databytes&0x1F);
		if (ili_init_cmds[cmd].databytes & 0x80) 
		{
			vTaskDelay(100 / portTICK_RATE_MS);
		}
		cmd++;
	}

	///Enable backlight
	// printf("Enable backlight.\n");
	gpio_set_level(ILI9341_BCKL, 1);
}

void ili9431_fill(int32_t x1, int32_t y1, int32_t x2, int32_t y2, lv_color_t color)
{
	uint8_t data[4];

	/*Column addresses*/
	ili9441_send_cmd(0x2A);
	data[0] = (x1 >> 8) & 0xFF;
	data[1] = x1 & 0xFF;
	data[2] = (x2 >> 8) & 0xFF;
	data[3] = x2 & 0xFF;
	ili9341_send_data(data, 4);

	/*Page addresses*/
	ili9441_send_cmd(0x2B);
	data[0] = (y1 >> 8) & 0xFF;
	data[1] = y1 & 0xFF;
	data[2] = (y2 >> 8) & 0xFF;
	data[3] = y2 & 0xFF;
	ili9341_send_data(data, 4);

	/*Memory write*/
	ili9441_send_cmd(0x2C);

	uint32_t size = (x2 - x1 + 1) * (y2 - y1 + 1);
	uint16_t color_swap = ((color.full >> 8) & 0xFF) | ((color.full & 0xFF) << 8);	/*It's a 8 bit SPI bytes need to be swapped*/
	uint16_t buf[ILI9341_HOR_RES];

	uint32_t i;
	if(size < ILI9341_HOR_RES) {
		for(i = 0; i < size; i++) buf[i] = color_swap;

	} else {
		for(i = 0; i < ILI9341_HOR_RES; i++) buf[i] = color_swap;
	}

	while(size > ILI9341_HOR_RES) {
		ili9341_send_data(buf, ILI9341_HOR_RES * 2);
		size -= ILI9341_HOR_RES;
	}

	ili9341_send_data(buf, size * 2);	/*Send the remaining data*/
}


void ili9431_flush(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_map)
{
	uint8_t data[4];

	/*Column addresses*/
	ili9441_send_cmd(0x2A);
	data[0] = (x1 >> 8) & 0xFF;
	data[1] = x1 & 0xFF;
	data[2] = (x2 >> 8) & 0xFF;
	data[3] = x2 & 0xFF;
	ili9341_send_data(data, 4);

	/*Page addresses*/
	ili9441_send_cmd(0x2B);
	data[0] = (y1 >> 8) & 0xFF;
	data[1] = y1 & 0xFF;
	data[2] = (y2 >> 8) & 0xFF;
	data[3] = y2 & 0xFF;
	ili9341_send_data(data, 4);

	/*Memory write*/
	ili9441_send_cmd(0x2C);


	uint32_t size = (x2 - x1 + 1) * (y2 - y1 + 1);

	/*Byte swapping is required*/
	uint32_t i;
	uint8_t * color_u8 = (uint8_t *) color_map;
	uint8_t color_tmp;
	for(i = 0; i < size * 2; i += 2) {
		color_tmp = color_u8[i + 1];
		color_u8[i + 1] = color_u8[i];
		color_u8[i] = color_tmp;
	}


	while(size > ILI9341_HOR_RES) {

		ili9341_send_data((void*)color_map, ILI9341_HOR_RES * 2);
		//vTaskDelay(10 / portTICK_PERIOD_MS);
		size -= ILI9341_HOR_RES;
		color_map += ILI9341_HOR_RES;
	}

	ili9341_send_data((void*)color_map, size * 2);	/*Send the remaining data*/

	lv_flush_ready();

}

void ili9341_rotate(uint8_t degrees)
{
	switch(degrees)
	{
		case 0:
			break;
		case 90:
			ili9441_send_cmd(0x36);    // Memory Access Control 
    		// ili9341_send_data((void*)(0x48^0xC0), 1);  
			ili9441_send_cmd(0x48^0xC0);
			break;
		case 180:
			break;
		default:
			ili9441_send_cmd(0x36);    // Memory Access Control 
    		ili9341_send_data((void*)0x48, 1);  
			break;
	}
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void ili9441_send_cmd(uint8_t cmd)
{
	gpio_set_level(ILI9341_DC, 0);	 /*Command mode*/
	disp_spi_send(&cmd, 1);
}

static void ili9341_send_data(void * data, uint16_t length)
{
	gpio_set_level(ILI9341_DC, 1);	 /*Data mode*/
	disp_spi_send(data, length);
}
