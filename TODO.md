# TODO list

## Unreleased

- [x] make audio p2 connector be detected
- [x] power the audio amplifier on/off if p2 connector is detected
- [x] enable the battery voltage level monitor
- [x] Should have a .h file called managers.h which include all managers, just like modules.h have
- [x] Should create a task to update the managers
- [x] enable menu and volume buttons
- [x] display battery level graphically
- [x] display volume level graphically (just when volume changed)
- [x] enable the battery charging sensing
- [x] Add OTA(Over the Air Update) to upload new firmware via wifi
- [x] Make **lvgl** recognize ESPBoy's keyboard. [see lvgl issue #527](https://github.com/littlevgl/lvgl/issues/527)
- [x] Add Setup topic to README.md
- [x] create UI to list the ROM files stored in SD Card by Platform ( NES, GameBoy ...). See [ESPBoy_launcher](https://github.com/Calebe94/ESPBoy_launcher)
- [x] enable wifi module. See [commit 1c6d38b56595113f0b3275fb9b26d07ebe77d00f](https://github.com/Calebe94/ESPBoy/commit/1c6d38b56595113f0b3275fb9b26d07ebe77d00f)

## NEXT 

- [] Make ESPBoy Launcher recognize when to display Audio Volume Message Box.
- [] Make ESPBoy Launcher recognize when WiFi is connected.
- [] Make ESPBoy Launcher recognize when Battery is Charging
- [] Make ESPBoy Launcher recognize Battery Level
- [] Make ESPBoy Launcher recognize when SDCard is connected.
- [] Make ESPBoy Launcher recognize when earphone is connected.
- [] Make ESPBoy open Splash Screen during booting process.

- [] enable the SD Card reader
- [] change audio volume
- [] read rom files stored in SD Card
- [] write rom files in SD Card (in the future I want to download ROM files from [archive.org](https://archive.org))
- [] Add [SQLite](https://github.com/siara-cc/esp32-idf-sqlite3) to project to manage configurations and games inside SDCard.

- [] use [KairOS](https://github.com/kairos-dev/KairOS) 
- [] enable bluetooth module
- [] create UI to connect to wifi (*scan* wifi networks available and *insert password* if necessary)
- [] create UI to configure the device (username, display favorite games?, etc.)
- [] port sega master system emulator. See [PocketSprite](https://github.com/PocketSprite) or [ODROID-GO](https://github.com/OtherCrashOverride/go-play)
- [] port nintendo gameboy emulator. See [PocketSprite](https://github.com/PocketSprite) or [ODROID-GO](https://github.com/OtherCrashOverride/go-play)
- [] port sega game gear emulator. See [PocketSprite](https://github.com/PocketSprite) or [ODROID-GO](https://github.com/OtherCrashOverride/go-play)
- [] Add resolution do battery porcentage measurement.


### BUGS:

- [x] When keyboard is enable the battery manager doesn't read the right battery level.
- [x] Can't add wifi to ESPBoy. See [issue #2](https://github.com/Calebe94/ESPBoy/issues/2). *Resolved by changing the name of the folder "Core" to "Kernel". See: [esp-idf issue #2087](https://github.com/espressif/esp-idf/issues/2087)*
    - [] Revise the "filesystem" name. Maybe adopt the Linux file system structure. See: [Linux Directory Structure (File System Structure)](https://www.thegeekstuff.com/2010/09/linux-file-system-structure) or [Linux directory structure explained](http://dev-random.net/linux-directory-structure-explained/)