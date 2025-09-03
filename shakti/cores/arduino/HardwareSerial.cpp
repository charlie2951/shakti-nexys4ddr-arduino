/***************************************************************************
* Project               	    		:  Arduino Shakti Port
* Name of the file	            		:  HardwareSerial.cpp
* Brief Description of file                     :  CPP wrapper file .
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
#include "HardwareSerial.h"
#include <stdint.h>
#include <stdarg.h>
#include "platform.h"
#include "uart.h"
#include "utils.h"

//Adding Serial object 
HardwareSerial Serial;

void HardwareSerial::begin(unsigned long baudrate)
{   
   	unsigned int baud_count = 0;
	baud_count = CLOCK_FREQUENCY / (16 * baudrate);
	uart_instance[0]->baud = baud_count;
}

int HardwareSerial::print(const char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	_printf_(fmt, ap);
	va_end(ap);
	return 0; // incorrect return value, but who cares, anyway?
}

int HardwareSerial::print(char c)
{
	printf("%c",c);
	return 0; // incorrect return value, but who cares, anyway?
}

int HardwareSerial::print(int n,int base)
{
	if (base == OCT)
		printf("%o",n);
	else if (base == HEX)
		printf("%x",n);
	else if (base == BIN)
		bin_conv(n);
	else
		printf("%d",n);
	return 0; // incorrect return value, but who cares, anyway?
}

int HardwareSerial::print(char s[])
{
	printf("%s",s);
	return 0; // incorrect return value, but who cares, anyway?
}

int HardwareSerial::println(const char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	_printf_(fmt, ap);
	va_end(ap);
    printf("\n");
	return 0; // incorrect return value, but who cares, anyway?
}

int HardwareSerial::println(char c)
{
	printf("%c\n",c);
	return 0; // incorrect return value, but who cares, anyway?
}

int HardwareSerial::println(int n,int base)
{
	if (base == OCT)
		printf("%o\n",n);
	else if (base == HEX)
		printf("%x\n",n);
	else if (base == BIN){
		bin_conv(n);
	    printf("\n");
	}
	else
		printf("%d\n",n);
	return 0; // incorrect return value, but who cares, anyway?
}

int HardwareSerial::println(char s[])
{
	printf("%s\n",s);
	return 0; // incorrect return value, but who cares, anyway?
}

int HardwareSerial::println(void)
{
	printf("\n");
	return 0; // incorrect return value, but who cares, anyway?
}

int HardwareSerial::available(void)
{
	return ((uart_instance[0]->status & STS_RX_NOT_EMPTY)>>2);
}

int HardwareSerial::availableForWrite(void)
{
	return (uart_instance[0]->status & STS_TX_EMPTY);
}

int HardwareSerial::read(void)
{
	uint8_t temp = 0;
	temp = uart_instance[0]->rcv_reg;
	return temp;
}

void HardwareSerial::write( uint8_t prn_character)
{
    while(uart_instance[0]->status & STS_TX_FULL);
	uart_instance[0]->tx_reg  = prn_character;
}

void HardwareSerial::bin_conv(int n)
{
    if (n > 1) 
        bin_conv(n/2); 
    printf("%d",(n%2)); 
}
