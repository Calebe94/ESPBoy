#ifndef _AUDIO_H_
#define _AUDIO_H_

#include <stdint.h>

/*
    Initialize the jack sensor. The jack sensor can be a voltage divider or something to identificate if the p2 plug is connected or not.
*/
void jack_sense_init();

/*
    Verifies if the audio plug is connected to jack.
    return: Non-Zero if true
*/
uint8_t is_audio_plug_connected();


/*
    Initialize the audio amplifier circuit
*/
void audio_amplifier_init();

/*
    Turn On the audio amplifier circuit
*/
void amplifier_set_on();

/*
    Turn Of the audio amplifier circuit
*/
void amplifier_set_off();

#endif