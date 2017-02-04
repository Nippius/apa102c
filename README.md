# apa102c - Tiva C series driver for APA102C Super LED IC's

This repository contains the software driver for controling APA102C LED driver IC's using Tiva C series hardware.

The driver was tested using a Tiva C EK-TM4C123GXL development board.

## Getting started:

Using this driver is simple:

1. Add apa102c_conf.h, apa102c.h and apa102c.c to your project
2. Edit apa102c_conf.h and set the SPI peripheral you intend to use and the number of LED's in the strip.
3. Import apa102c.h

After that:

- Use clear_strip() to clear the strip data (this only clears the internal representation of the LED states).
- Use set_pixel() and clear_pixel() to manipulate individual pixel values.
- Use display_strip() to send the internal pixel data to the strip.

## TODOs:
- Use interrupts
- Use uDMA
- Use CMSIS instead of the TivaWare library
- Add functions to allow creation of effects by manipulating the internal representation.

## License

All files are licensed under the MIT License. For more information, please read the LICENSE file.
