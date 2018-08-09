#include <driver/adc.h>
#include <driver/gpio.h>
#include <hal_audio.h>
#include <pins.h>

void jack_sense_init()
{
    adc2_config_channel_atten(JACK_SENSE, ADC_WIDTH_12Bit);
}

uint8_t is_audio_plug_connected()
{
    uint8_t plug_status = 0;
    uint16_t raw_data;
    adc2_get_raw(JACK_SENSE, ADC_WIDTH_12Bit, &raw_data);
    // printf("JACK PLUG VALUE: %d\n", raw_data);
    if(raw_data > 2048)
    {
        plug_status = 1;
    }
    return plug_status;
}

void audio_amplifier_init()
{
	gpio_pad_select_gpio(AUDIO_SHDN);
	gpio_set_direction(AUDIO_SHDN, GPIO_MODE_OUTPUT);
}

void amplifier_set_on()
{
    gpio_set_level(AUDIO_SHDN, 0);
}

void amplifier_set_off()
{
    gpio_set_level(AUDIO_SHDN, 1);
}