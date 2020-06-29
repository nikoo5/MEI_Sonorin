/*
 * FW_EEPROM.h
 *
 *  Created on: 23 de jun. de 2020
 *      Author: Nicoo
 */

#ifndef FW_EEPROM_H_
#define FW_EEPROM_H_

#include "chip.h"
#include "stdlib.h"
#include "string.h"

#define PUERTO_0  	 				0

#define I2C1						1

#define PIN_SDA1 	   	   			19
#define PIN_SCL1  	   	   			20

#define I2C_MODE					2 //NEITHER
#define I2C_FUNC     				3

#define I2C_CLOCKRATE				100000 //100kHz

#define BUILTIN_EEPROM_ADDRESS		0x50
#define W_ADDRESS					0x00B0

void EEPROM_Init_IO_Pins(void);
void EEPROM_Init(void);

void EEPROM_Write(uint16_t address, uint8_t* data);

#endif /* FW_EEPROM_H_ */
