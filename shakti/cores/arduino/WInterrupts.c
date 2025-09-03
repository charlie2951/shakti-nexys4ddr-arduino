/*
  Copyright (c) 2015 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "WInterrupts.h"
#include "shakti_arduino.h"
#include "plic_driver.h"

typedef void (*voidFuncPtr)( void ) ;
static voidFuncPtr callbacksInt[PLIC_MAX_INTERRUPT_SRC];
static interrupt_init_temp = 1;

void attachInterrupt(uint32_t intnum, voidFuncPtr callback, uint32_t mode)
{
	if(interrupt_init_temp)
	{
		plic_init();
		interrupt_init_temp = 0;
	}
	
	configure_interrupt(intnum);
	isr_table[intnum]= callback;
  
	// Enable Global (PLIC) interrupts.
	asm volatile("li      t0, 8\t\n"
		     "csrrs   zero, mstatus, t0\t\n"
		    );

	asm volatile("li      t0, 0x800\t\n"
		     "csrrs   zero, mie, t0\t\n"
		    );
}

void detachInterrupt(uint32_t intnum)
{
	interrupt_disable(intnum);
} 

void interrupts()
{
  //Enabling Interrupts 
	asm volatile("li      t0, 8\t\n"
		     "csrrs   zero, mstatus, t0\t\n"
		    );

	asm volatile("li      t0, 0x800\t\n"
		     "csrrs   zero, mie, t0\t\n"
		    );
}

void noInterrupts()
{
	asm volatile("li      t0, 8\t\n"
		     "csrrc   zero, mstatus, t0\t\n"
		    );

	asm volatile("li      t0, 0x800\t\n"
		     "csrrc   zero, mie, t0\t\n"
		    );
}
