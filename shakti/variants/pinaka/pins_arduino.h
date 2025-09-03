/*
  pins_arduino.h - Pin definition functions for Arduino
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2007 David A. Mellis
  Modified for Shakti by Sambhav Jain,2020

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA

  $Id: wiring.h 249 2007-02-03 16:52:51Z mellis $
*/

#ifndef Pins_Arduino_h
#define Pins_Arduino_h


static const uint32_t D0   = (1<<0);
static const uint32_t D1   = (1<<1);
static const uint32_t D2   = (1<<2);
static const uint32_t D3   = (1<<3);
static const uint32_t D4   = (1<<4);
static const uint32_t D5   = (1<<5);
static const uint32_t D6   = (1<<6);
static const uint32_t D7   = (1<<7);
static const uint32_t D8   = (1<<8);
static const uint32_t D9   = (1<<9);
static const uint32_t D10  = (1<<10);
static const uint32_t D11  = (1<<11);
static const uint32_t D12  = (1<<12);
static const uint32_t D13  = (1<<13);
static const uint32_t D14  = (1<<14);
static const uint32_t D15  = (1<<15);
static const uint32_t D16  = (1<<16);
static const uint32_t D17  = (1<<17);
static const uint32_t D18  = (1<<18);
static const uint32_t D19  = (1<<19);
static const uint32_t D20  = (1<<20);
static const uint32_t D21  = (1<<21);
static const uint32_t D22  = (1<<22);
static const uint32_t D23  = (1<<23);
static const uint32_t D24  = (1<<24);
static const uint32_t D25  = (1<<25);
static const uint32_t D26  = (1<<26);
static const uint32_t D27  = (1<<27);
static const uint32_t D28  = (1<<28);
static const uint32_t D29  = (1<<29);
static const uint32_t D30  = (1<<30);
static const uint32_t D31  = (1<<31);



// #define PIN_WIRE_SDA (D1)
// #define PIN_WIRE_SCL (D0)

// static const uint32_t SDA = PIN_WIRE_SDA;
// static const uint32_t SCL = PIN_WIRE_SCL;

#define LED_BUILTIN         D16


#endif /* Pins_Arduino_h */
