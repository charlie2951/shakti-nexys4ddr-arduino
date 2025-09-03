/***************************************************************************
* Project               	    		:  Arduino Shakti Port
* Name of the file	            		:  wiring.c
* Brief Description of file                     :  Implementation of delay()
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
#include "wiring.h"
#include "platform.h"
#include <stdint.h>

int_inverse f_cpu_1000_inv;
int_inverse f_cpu_1000000_inv;

//Used in millis and micros function
uint8_t millis_flag=1;
uint8_t micros_flag=1;

void calc_inv(uint32_t n, int_inverse * res)
{
  uint32_t one = ~0;
  uint32_t d = one/n;
  uint32_t r = one%n + 1;
  if (r >= n) ++d;
  if (d == 0) --d;
  uint32_t shift = 0;
  while ((d & 0x80000000) == 0)
  {
    d <<= 1;
    ++shift;
  }
  res->n = n;
  res->mult = d;
  res->shift = shift;
}

inline uint32_t divide32_using_inverse(uint32_t n, int_inverse *inv){

 uint32_t d =  (uint32_t)(((uint64_t)n * inv->mult) >> 32);
   d >>= inv->shift;
  if (n - d*inv->n >= inv->n) ++d;
  return d;
}

// Almost full-range 64/32 divide.
// If divisor-1 has i bits, then the answer is exact for n of up to 64-i bits
// e.g. for divisors up to a million, n can have up to 45 bits
// On RV32IM with divide32_using_inverse inlines this uses 5 multiplies,
// 33 instructions, zero branches, 3 loads, 0 stores.
uint64_t divide64_using_inverse(uint64_t n, int_inverse *inv){
  uint32_t preshift = (31 - inv->shift) & 31;
  uint64_t d = (uint64_t)divide32_using_inverse(n >> preshift, inv) << preshift;
  uint32_t r = n - d * inv->n;
  d += divide32_using_inverse(r, inv);
  return d;
}

void delay(uint32_t dwMs)
{
  uint64_t current, later;
  rdmcycle(&current);
  later = current + dwMs * (CLOCK_FREQUENCY/1000);
  if (later > current) // usual case
  {
    while (later > current)
    {
      rdmcycle(&current);
    }
  }
  else // wrap. Though this is unlikely to be hit w/ 64-bit mcycle
  {
    while (later < current)
    {
      rdmcycle(&current);
    }
    while (current < later)
    {
      rdmcycle(&current);
    }
  }
}

void delayMicroseconds(uint32_t usec)
{
  if (usec == 0)
  {
    return;
  }
  // TODO: Short delays at low frequencies.
  uint64_t current, later;
  rdmcycle(&current);
  later = current + usec * (CLOCK_FREQUENCY/1000000);
  if (later > current) // usual case
  {
    while (later > current)
    {
	    rdmcycle(&current);
    }
  }
  else // wrap. Though this is unlikely to be hit w/ 64-bit mcycle
  {
    while (later < current)
    {
	  rdmcycle(&current);
    }
    while (current < later)
    {
	    rdmcycle(&current);
    }
  }
}

uint32_t millis()
{
  do
  {
    // Compute F_CPU inverse, used for millis and micros functions.
    calc_inv(CLOCK_FREQUENCY/1000, &f_cpu_1000_inv);
    millis_flag=0;
  }while(millis_flag);

  uint64_t x;
  rdmcycle(&x);
  x = divide64_using_inverse(x, &f_cpu_1000_inv);
  return((uint32_t) (x & 0xFFFFFFFF));
}

uint32_t micros(void)
{
  do
  {
    // Compute F_CPU inverse, used for millis and micros functions.
    calc_inv(CLOCK_FREQUENCY/1000000, &f_cpu_1000000_inv);
    millis_flag=0;
  }while(millis_flag);
    
  uint64_t x;
  rdmcycle(&x);
  // For Power-of-two MHz F_CPU,
  // this compiles into a simple shift,
  // and is faster than the general solution.
#if F_CPU==16000000
  x = x / (F_CPU / 1000000);
#else
#if  F_CPU==256000000
  x = x / (F_CPU / 1000000);
#else
  x = divide64_using_inverse(x, &f_cpu_1000000_inv);
#endif
#endif
  return((uint32_t) (x & 0xFFFFFFFF));
}