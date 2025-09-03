/***************************************************************************
 * Project           			 : Arduino Shakti Port 
 * Name of the file	     		 : RGB.ino
 * Created date			         : 16.03.2020
 * Name of Author                : Sambhav Jain
 * Email ID                      : sambhav.jv@gmail.com

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

*****************************************************************************/
#define LED1 D18
#define LED2 D17
#define LED3 D16

void setup()
{
  //Assume  0 for INPUT and  1 for OUTPUT
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);

  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,LOW);
}

void loop()
{
  Serial.print("\nRED LIGHT");      
  digitalWrite(LED1,HIGH);
  delay(1000);

  digitalWrite(LED1,LOW);
  Serial.print("\nGREEN LIGHT");
  digitalWrite(LED2,HIGH);
  delay(1000);

  digitalWrite(LED2,LOW);
  Serial.print("\nBLUE LIGHT");   
  digitalWrite(LED3,HIGH);

  delay(1000);      
  digitalWrite(LED3,LOW);
}