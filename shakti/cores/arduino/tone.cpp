/***************************************************************************
* Project               	  : Arduino Shakti Port
* Name of the file	          : tone.cpp
* Brief Description of file       : tone() & noTone() 
* Name of Author    	          : Sambhav Jain
* Email ID                        : sambhav.jv@gmail.com

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
/**
@file pwm_driver.c
@brief source file for pwm
@detail the device driver for the pwm module which is used to change the frequency, period and duty registers 
*/
extern "C" {
#include "pwm_driver.h"
#include "shakti_arduino.h"
#include "platform.h"
}

int *pinmux_reg = (const int*) PINMUX_CONFIGURE_REG;


/** @fn void tone(int pin, unsigned int frequency, unsigned long duration)
 * @brief Generates a square wave of the specified frequency on PWM Pin  
 * @details This function generates square on PWM Pins, Implementation for other GPIO will be implemented in future. 
 * @param int pin
 * @param unsigned int frequency
 * @return unsigned long duration
 */
void tone(int pin, unsigned int frequency, unsigned long duration)
{
    uint8_t pwm_mod = 0;
    uint16_t pwm_period = 0xf0;
    uint16_t pwm_duty = 0x80;
    uint32_t clock_divisor_value = CLOCK_FREQUENCY/(frequency/2)*(pwm_period+1) -1;
    
    switch(pin)
    {
        case (GPIO3):
        *pinmux_reg = 0x80;
        pwm_mod=0;
        break;

        case (GPIO5):
        *pinmux_reg = 0x200;
        pwm_mod=1;
        break;

        case (GPIO6):
        *pinmux_reg = 0x800;
        pwm_mod=2;
        break;

        case (GPIO9):
        *pinmux_reg = 0x2000;
        pwm_mod=3;
        break;

        case (GPIO10):
        *pinmux_reg = 0x8000;
        pwm_mod=4;
        break;

        case (GPIO11):
        *pinmux_reg = 0x20000;
        pwm_mod=5;
        break;

        default:
        return 0; 
        break;
    }
    
    pwm_configure(pwm_mod, clock_divisor_value, pwm_period, pwm_duty, false);

    if(duration)
    {
        pwm_start(pwm_mod,0);
        delay(duration);
        pwm_stop(pwm_mod);
    }
    else
    {
        pwm_start(pwm_mod,0);
    }
}

void noTone(int pin)
{
    uint8_t pwm_mod = 0;

    switch(pin)
    {
        case (GPIO3):
        *pinmux_reg = 0x80;
        pwm_mod=0;
        break;

        case (GPIO5):
        *pinmux_reg = 0x200;
        pwm_mod=1;
        break;

        case (GPIO6):
        *pinmux_reg = 0x800;
        pwm_mod=2;
        break;

        case (GPIO9):
        *pinmux_reg = 0x2000;
        pwm_mod=3;
        break;

        case (GPIO10):
        *pinmux_reg = 0x8000;
        pwm_mod=4;
        break;

        case (GPIO11):
        *pinmux_reg = 0x20000;
        pwm_mod=5;
        break;

        default:
        return 0; 
        break;
    }

    pwm_stop(pwm_mod);
}
