/*************************************************************************
 * Project                     : Arduino Shakti Port
 * Name of the file            : pcf8591.ino
 * Brief Description of file   : Contains the driver routines to configure and read pcf8591.
 * Name of Author              : Kotteeswaran
 * Email ID                    : kottee.1@gmail.com

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
@file   pcf8591.ino
@brief  Contains the driver routines to configure and read pcf8591.
@detail I2C based routines to configures and read the adc value from pcf8591.
*/
extern "C"{
#include <stdint.h>//Includes the definitions of standard input/output functions//
#include "i2c.h"
#include "log.h"
#include "uart.h"
}

#define PCF8591_SLAVE_ADDRESS 0x90 // I2C bus address //doubt
#define PCF8591_CONTROL_REGISTER_VALUE 0x04
#define PCF8591_REG_OFFSET 0
#define DELAY_VALUE 900
#define PRESCALER_COUNT 0x1F
#define SCLK_COUNT 0x91
#define I2C i2c_instance[1]

unsigned char i = 0;
unsigned int tempReadValue = 0;
unsigned long delay1 = 1000;
unsigned int write_buf[7] = {0x00}, read_buf[7] = {0x00};
unsigned char length1 = 0;

/** @fn int read_pcf8591_registers(i2c_struct * i2c_instance, unsigned int reg_offset, unsigned int *readTemp, unsigned char length, unsigned long delay)
 * @brief Reads the ADC value from PCF8591
 * @details Reads 4 ADC values from PCF8591 over I2C interface
 * @param i2c_struct*
 * @param reg_offset
 * @param *readTemp
 * @param length
 * @param delay
 * @return read status (zero on success)
 */
int read_pcf8591_registers(i2c_struct * i2c_instance, unsigned int reg_offset, unsigned int *readTemp, unsigned char length, unsigned long delay)
{
  unsigned char read_buf[4] = {'\0'};
  int i = 0, j = 0,  k = 0, status=0;
  unsigned char temp = 0;
//Writes the slave address for write
  i2c_send_slave_address(i2c_instance, PCF8591_SLAVE_ADDRESS, I2C_WRITE, 800);
//Writes the pointer to address that needs to be read
  i2c_write_data(i2c_instance, reg_offset, delay);
//Stops the I2C transaction to start reading the temperature value.
  i2c_instance->control = I2C_STOP;

//Writes the slave address for read
  i2c_send_slave_address(i2c_instance, PCF8591_SLAVE_ADDRESS, I2C_READ, 800);

/* Make a dummy read as per spec of the I2C controller */
  i2c_read_data(i2c_instance, &temp, delay);


//Reads the MSB Byte of temperature [D9 - D1]
  for(i = 0; i < length; i++)
  {
    i2c_read_data(i2c_instance, &temp, delay);
    *readTemp = temp;
    if( i == (length - 2) )
    i2c_instance->control = I2C_NACK;
    *readTemp++;
  }
  
  i2c_instance->control = I2C_STOP;
  return 0;
}

/** @fn int write_pcf8591_registers(i2c_struct * i2c_instance, unsigned int reg_offset, unsigned int *write_value, unsigned char length, unsigned long delay)
 * @brief WRites into PCF8591 Register
 * @details WRites the passed value into passed PCF8591 Register (address) over I2C interface.
 * @param i2c_struct*
 * @param reg_offset
 * @param write_value
 * @param length
 * @param delay
 * @return Write status (Zero on success)
 */
int write_pcf8591_registers(i2c_struct * i2c_instance, unsigned int reg_offset, unsigned int *write_value, unsigned char length, unsigned long delay)
{
  int i = 0, j = 0,  k = 0, status=0;
  unsigned int temp = 0;
  i2c_send_slave_address(i2c_instance, PCF8591_SLAVE_ADDRESS, I2C_WRITE, delay);
  i2c_write_data(i2c_instance, reg_offset, delay);
  for(i = 0; i < length; i++)
  {
    i2c_write_data(i2c_instance,  ( *write_value++  & 0xff) /*LM75_TEMP_REG_OFFSET */, delay);
  }
//Stops the I2C transaction to start reading the temperature value.
  i2c_instance->control = I2C_STOP;;
  return 0;
}

/** @fn int main()
 * @brief Configures and reads the ADC values.
 * @details Configures the PCF8591 to read 4 ADC values, reads the same 
 * prints the read values
 * @return Zero
 */
void setup()
{
  Serial.print("\tI2C: PCF8591 - ADC test\n");
  i2c_init();

  if(config_i2c(I2C, PRESCALER_COUNT, SCLK_COUNT))
  {
      Serial.print("\tSomething Wrong In Initialization\n");
      return 0;
  }
  else
  {
      Serial.print("\tInitialization Happened Fine\n");
  } 

  length1 = 1;
  write_buf[0] = PCF8591_CONTROL_REGISTER_VALUE;
  write_pcf8591_registers(I2C, 0x00, &write_buf[0], length1, delay1);
  Serial.print("\nWrite complete");
  length1 = 5;
}

void loop()
{
  read_pcf8591_registers(I2C, PCF8591_CONTROL_REGISTER_VALUE, &read_buf[0], length1, 800);

  for( i = 1; i < length1; i++)
    Serial.print("\nADC Input[%d]: %x", i, read_buf[i]);

  delay_loop(3000, 2000);
}