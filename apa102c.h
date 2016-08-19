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

#ifndef APA102C_APA102C_H_
#define APA102C_APA102C_H_

#include "apa102c_conf.h"

#define APA102_FRAME_SIZE       4           // 4 bytes, 32 bits

#define START_FRAME             0x00000000
#define BASE_LED_FRAME          0xE0000000
#define END_FRAME               0xFFFFFFFF

#define BRIGHTNESS_MASK         0x1F
#define BRIGHTNESS_OFFSET       24

#define COLOR_MASK              0x00FFFFFF
#define RED                     0x00FF0000
#define GREEN                   0x0000FF00
#define BLUE                    0x000000FF
#define RED_OFFSET              (8*2)
#define GREEN_OFFSET            (8*1)
#define BLUE_OFFSET             (0)

// Composes the pixel color from the individual red, green and blue components
#define PIXEL_COLOR(R,G,B)      (((R)<<RED_OFFSET) | ((G)<<GREEN_OFFSET) | ((B)<<BLUE_OFFSET))

void set_pixel(uint8_t ui8Index, uint8_t ui8Brightness, uint32_t ui32Color);
void set_all(uint8_t ui8Brightness, uint32_t ui32Color);
void clear_pixel(uint8_t ui8Index);
void clear_strip();
void display_strip();

#endif /* APA102C_APA102C_H_ */
