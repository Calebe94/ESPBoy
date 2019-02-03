#ifndef _PINS_H_
#define _PINS_H_

#include <driver/adc.h>
#include "driver/gpio.h"
#include "soc/gpio_struct.h"

//-------------------- GAMEPAD PINS --------------------
#define JOY_X_AXIS 		ADC1_CHANNEL_6 //GPIO_NUM_34
#define JOY_Y_AXIS 		ADC1_CHANNEL_7 //GPIO_NUM_35
#define JOY_SELECT 		GPIO_NUM_27
#define JOY_START 		GPIO_NUM_14
#define JOY_A 			GPIO_NUM_13
#define JOY_B 			GPIO_NUM_12
#define JOY_MENU		GPIO_NUM_33
#define JOY_VOL 	 	ADC1_CHANNEL_3 // GPIO_NUM_39 or VN pin

//-------------------- SIGNAL INPUTS --------------------
#define BAT_LEVEL		    ADC1_CHANNEL_0 // GPIO_NUM_36 or VP pin
#define JACK_SENSE		    ADC2_CHANNEL_8 // GPIO_NUM_25
#define CHARGING_SENSIGN    ADC1_CHANNEL_4 // GPIO_NUM_32

//-------------------- SIGNAL OUTPUTS --------------------
#define AUDIO_SHDN      GPIO_NUM_15
#define STATUS_PIN      GPIO_NUM_2
#define AUDIO           GPIO_NUM_26

//-------------------- GAMEPAD READING --------------------
// #define BUTTON_SELECT 	gpio_get_level(JOY_SELECT)	
// #define BUTTON_START 	gpio_get_level(JOY_START)
// #define BUTTON_A	 	gpio_get_level(JOY_A)
// #define BUTTON_B 		gpio_get_level(JOY_B)
// #define BUTTON_MENU     gpio_get_level(JOY_MENU)

//-------------------- DISPLAY ILI9341 --------------------
#define PIN_NUM_MISO    GPIO_NUM_19
#define PIN_NUM_MOSI    GPIO_NUM_23
#define PIN_NUM_CLK     GPIO_NUM_18
#define PIN_NUM_CS      GPIO_NUM_5
#define PIN_NUM_DC      GPIO_NUM_21
#define PIN_NUM_BCKL    GPIO_NUM_22
#define PIN_NUM_RST     GPIO_NUM_0 // No need! Connected on ESP32 RST Pin

//-------------------- SD CARD --------------------
#define SD_CS           GPIO_NUM_22
#define SD_MOSI         GPIO_NUM_23
#define SD_MISO         GPIO_NUM_19
#define SD_SCK          GPIO_NUM_18

#endif