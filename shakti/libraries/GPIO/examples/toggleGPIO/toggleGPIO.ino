/***************************************************************************
* Project           			  :  Arduino Shakti Port
* Name of the file	     	  :  tglgpio.ino
* Created date			        :  16.03.2020
* Brief Description of file :  Control an led with the help of a button, gpio based.
* Name of Author    	      :  Sathya Narayanan N
* Email ID 	                :  sathya281@gmail.com

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
//Using Builtin LED pin on board
#define LED1 D16

void setup()
{	
  Serial.println("Toggling GPIO");
	//pinMode 1 ---> output, 0 ---> input
	pinMode(LED1,OUTPUT);
}

void loop()
{
  digitalWrite(LED1,HIGH);
  delay(1000);  //Wait for 1000ms- 1 second approximately
  
  digitalWrite(LED1,LOW);
  delay(1000); 
}