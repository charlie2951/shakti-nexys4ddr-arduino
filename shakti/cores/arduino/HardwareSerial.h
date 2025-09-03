/***************************************************************************
* Project               	    		:  Arduino Shakti Port
* Name of the file	            		:  HardwareSerial.cpp
* Brief Description of file                     :  Header file for Hardware Serial
* Name of Author    	                        :  Sambhav Jain
* Email ID                                      :  sambhav.jv@gmail.com

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

#ifndef HardwareSerial_h
#define HardwareSerial_h

#include <stdint.h>
#include <inttypes.h>
#include <stdarg.h>
#include "platform.h"
#include "uart.h"
  
#define BIN 2  
#define OCT 8
#define DEC 10
#define HEX 16

class HardwareSerial                      //: public Stream
{
  public:
    void begin(unsigned long baudrate);
    int print(const char* fmt, ...);
    int print(char);
    int print(int, int = DEC);
    int print(char[]);
    int println(const char* fmt, ...);
    int println(char);
    int println(int, int = DEC);
    int println(char[]);
    int println(void);
    int available(void);
    int availableForWrite(void);
    int read(void);
    void write( uint8_t prn_character);
    void bin_conv(int);
    //TODO:
    // virtual void end();
    // virtual int peek(void) = 0;
    // virtual void flush(void) = 0;
    //virtual size_t write(uint8_t) = 0;
    // using Print::write; // pull in write(str) and write(buf, size) from Print
    // virtual operator bool() = 0;
};

extern HardwareSerial Serial;
//The object is defined in Arduino.h 
//extern void serialEventRun(void) __attribute__((weak));

#endif
