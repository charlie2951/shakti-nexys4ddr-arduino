/***************************************************************************
* Project               	    		:  shakti devt board
* Name of the file	            		:  log.h
* Brief Description of file                     :  Header file for logger.
* Name of Author    	                        :  Abhinav Ramnath
* Email ID                                      :  abhinavramnath13@gmail.com

    Copyright (C) 2019  IIT Madras. All rights reserved.

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
#include "shakti_arduino.h"

void digitalWrite(unsigned long gpio_pin, int gpio_pin_mode )
{
  unsigned long read_data = 0;
  read_data = read_word(GPIO_DATA_REG);
  if(gpio_pin_mode == 1)
  {
    write_word(GPIO_DATA_REG, ( read_data | (gpio_pin ) ) );
  }
  else
  {
    write_word(GPIO_DATA_REG, ( read_data & ( ~gpio_pin ) ) );  
  }

}

int digitalRead(unsigned long gpio_pin)
{
  if ( ( read_word (GPIO_DATA_REG) ) & gpio_pin ){ 
    return HIGH;
  }
  else{
    return LOW;
  } 
}

void pinMode(unsigned long gpio_pin, int gpio_pin_mode )
{
  unsigned long read_data = 0;
  read_data = read_word(GPIO_DIRECTION_CNTRL_REG);
  if(gpio_pin_mode == 1)
  {
    write_word (GPIO_DIRECTION_CNTRL_REG, ( read_data | (gpio_pin ) ) );
  }
  else
  {
    write_word(GPIO_DIRECTION_CNTRL_REG, ( read_data & ( ~gpio_pin ) ) );  
  } 
}






