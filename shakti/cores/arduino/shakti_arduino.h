/***************************************************************************
* Project               	    		:  Arduino Shakti Port
* Name of the file	            		:  shakti_arduino.h
* Brief Description of file                     :  Header file for shakti_arduino.
* Name of Author    	                        :  Sambhav Jain
* Email ID                                      :  sambhav@gmail.com

    Copyright (C) 2020  IIT Madras. All rights reserved.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

***************************************************************************/
#ifndef SHAKTI_ARDUINO_H
#define SHAKTI_ARDUINO_H

#include <stdarg.h>
#include <math.h>
#include <stdlib.h>
#include "platform.h"
#include "gpio.h"
#include "uart.h"
#include "utils.h"
#include "stdbool.h"

#define HIGH            1
#define LOW             0
#define OUTPUT          1
#define INPUT           0
#define LSBFIRST        0
#define MSBFIRST        1

#ifdef abs
#undef abs
#endif

typedef bool boolean ;
typedef uint8_t byte ;

#define abs(x) ((x)>0?(x):-(x))
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x)*(x))
#define bit(b) (1UL << (b))
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))
#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

void digitalWrite(unsigned long gpio_pin, int gpio_pin_mode );
void pinMode(unsigned long gpio_pin, int gpio_pin_mode );
int digitalRead(unsigned long gpio_pin);

uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder);
void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val);
uint32_t millis( void ) ;
uint32_t micros( void ) ;
void delay( uint32_t dwMs ) ;
void delayMicroseconds(uint32_t usec);

#endif