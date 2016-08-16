/**
 * MIT License
 *
 * Copyright (c) 2016 Tiago Costa <nippius+github@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdint.h>
#include <stdbool.h>
#include <driverlib/ssi.h>
#include <driverlib/debug.h>

#include "apa102c.h"

/**
 * Stores the LED frames to send to LED strip.
 */
static uint32_t g_pui32LedFrames[LED_STRIP_SIZE];

/**
 * Send a LED frame starting with the most significant byte.
 */
static void send_frame(uint32_t ui32Frame) {
    for (uint32_t i = 0; i < APA102_FRAME_SIZE; i++) {
        // Grab most significant byte
        uint32_t frame_msb = (ui32Frame & 0xFF000000) >> 24;
        // Send it
        SSIDataPut(SPI_BASE, frame_msb);
        // Prepare next byte to send.
        ui32Frame <<= 8;
    }
}

/**
 * Sets a pixel with the given brightness and color value.
 */
void set_pixel(uint8_t ui8Index, uint8_t ui8Brightness, uint32_t ui32Color) {
    ASSERT(ui8Index < LED_STRIP_SIZE);

    // Create led frame
    uint32_t led_frame = BASE_LED_FRAME;
    // Apply brightness value
    led_frame |= ((ui8Brightness & BRIGHTNESS_MASK) << BRIGHTNESS_OFFSET);
    // Apply color
    led_frame |= (ui32Color & COLOR_MASK);

    g_pui32LedFrames[ui8Index] = led_frame;
}

/**
 * Sets all pixel to given brightness and color values.
 */
void set_all(uint8_t ui8Brightness, uint32_t ui32Color)
{
    for(uint32_t i=0;i<LED_STRIP_SIZE;i++)
    {
        set_pixel(i, ui8Brightness, ui32Color);
    }
}

/**
 * Clears a pixel.
 */
void clear_pixel(uint8_t ui8Index) {
    ASSERT(ui8Index < LED_STRIP_SIZE);

    g_pui32LedFrames[ui8Index] = BASE_LED_FRAME;
}

/**
 * Clears the entire strip.
 */
void clear_strip() {
    for (uint32_t i = 0; i < LED_STRIP_SIZE; i++) {
        g_pui32LedFrames[i] = BASE_LED_FRAME;
    }
}

/**
 * Sends the pixel data to the strip.
 */
void display_strip() {
    send_frame(START_FRAME);

    for (uint32_t i = 0; i < LED_STRIP_SIZE; i++) {
        send_frame(g_pui32LedFrames[i]);
    }

    // Send enough end frames to support strips larger then 64 leds
    // Send 32 bits for each group of 64 leds in the strip.
    // This could be improved by sending 1 byte at a time instead of 4
    // For more info, check "The End Frame" section:
    //      https://cpldcpu.wordpress.com/2014/11/30/understanding-the-apa102-superled/
    for (uint32_t i = 0; i <= LED_STRIP_SIZE / 64; i++) {
        send_frame(END_FRAME);
    }
}

