/*
 * fw_I2C.h
 *
 *  Created on: 30 de jun. de 2020
 *      Author: Nicoo
 */

#ifndef FW_I2C_H_
#define FW_I2C_H_

#include "chip.h"

#define I2C1						1

#define PIN_SDA1 	   	   			0,19
#define PIN_SCL1  	   	   			0,20

#define I2C_MODE					2 //NEITHER
#define I2C_FUNC     				3

#define I2C_CLOCKRATE				400000 //100kHz

void I2C_Init_IO_Pins(void);
void I2C_Init(void);

#endif /* FW_I2C_H_ */
