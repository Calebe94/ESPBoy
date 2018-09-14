#include "sysinit.h"

#include "hal_audio.h"
#include "hal_battery.h"
#include "hal_keypad.h"
#include "disp_spi.h"
#include "ili9341.h"

err_t modules_init(void)
{
    disp_spi_init();
    ili9431_init();
    jack_sense_init();
    audio_amplifier_init();
    amplifier_set_off();
    battery_manager_init();
    
    //keypad_init();
    
    return RESP_OK;
}

err_t os_init(void);
