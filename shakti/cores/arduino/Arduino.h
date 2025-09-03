/*
  Arduino.h - Main include file for the Arduino SDK
  Copyright (c) 2005-2013 Arduino Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#ifndef Arduino_h
#define Arduino_h

#include <stdint.h>
#include <stdarg.h>
#include "platform.h"

// some libraries and sketches depend on this
// AVR stuff, assuming Arduino.h or WProgram.h
// automatically includes it...
#include <avr/pgmspace.h>
//#include <avr/interrupt.h>
//#include "binary.h"
#include "pins_arduino.h"
#include "HardwareSerial.h"

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

//#include "wiring.h"
//#include "wiring_constants.h"
//Arduino.h automatically includes shakti 
//supported libraries
#include "shakti_arduino.h"
#include "wiring.h"
#include "WInterrupts.h"

#define	SystemCoreClock CLOCK_FREQUENCY
#define clockCyclesPerMicrosecond() ( SystemCoreClock / 1000000L )
#define clockCyclesToMicroseconds(a) ( (  (a) * 1000L) / (SystemCoreClock / 1000L) )
#define microsecondsToClockCycles(a) ( (a) * (SystemCoreClock / 1000000L) )

void yield(void);
/* sketch */
extern void setup( void ) ;
extern void loop( void ) ;
typedef void (*voidFuncPtr)( void ) ;
/* Define attribute */
#define WEAK __attribute__ ((weak))

#ifdef __cplusplus
} // extern "C"

#include "WCharacter.h"
//#include "WString.h"
//#include "WMath.h"
//#include "HardwareSerial.h"
#include "wiring_pulse.h"

#endif // __cplusplus

// Include board variant
//#include "variant.h"
//#include "wiring_digital.h"
//#include "wiring_analog.h"
//#include "wiring_shift.h"
long random(long);
long random(long, long);
void randomSeed(unsigned long);
long map(long x, long in_min, long in_max, long out_min, long out_max);
void tone(int pin, unsigned int frequency, unsigned long duration =0);
void noTone(int pin);
uint32_t pulseIn(uint32_t ulPin, bool ulState, uint32_t ulTimeout = 1000000L);

#endif // Arduino_h