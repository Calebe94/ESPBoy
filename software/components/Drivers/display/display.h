#pragma once

/*********************
 *      INCLUDES
 *********************/
#include "../lvgl/lvgl.h"

void ili9341_init();
void ili9341_write_frame(uint16_t* buffer);
void ili9341_write_frame_rectangle(short left, short top, short width, short height, uint16_t* buffer);
void ili9341_write_frame_rectangleLE(short left, short top, short width, short height, uint16_t* buffer);

void ili9341_clear(uint16_t color);

void backlight_deinit();

void display_flush(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_map);