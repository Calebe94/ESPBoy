# ESP ILI9341 Driver

ESP ILI9341 display driver. Supports M5Stack out of the box. Everything is still work in progress. Things will change without warning. I'm doing this to learn C.

[![Software License](https://img.shields.io/badge/license-MIT-brightgreen.svg?style=flat-square)](LICENSE.md)

## Usage

First initialise the ILI9341 driver. SPI speed and pins can be changed with `$ make menuconfig`. Default settings will work with M5Stack. Other than that the driver provides only putpixel and blit functions. It is meant to be used with an external graphics library such as [copepod](https://github.com/tuupola/copepod).

```c
#include <driver/spi_master.h>

#include "ili9341.h"

spi_device_handle_t spi;
ili9341_init(&spi);

ili9431_putpixel(spi, x0, y0, color);
ili9431_blit(spi, x0, y0, w, h, &bitmap)
```

## License

The MIT License (MIT). Please see [License File](LICENSE.md) for more information.

Based on Espressif provided SPI Master example which was released to Public Domain: https://goo.gl/ksC2Ln
