/*
 * fw_I2C.c
 *
 *  Created on: 30 de jun. de 2020
 *      Author: Nicoo
 */

#include "fw_I2C.h"

bool i2c_initialized = false;

void I2C1_IRQHandler(void)
{
	Chip_I2C_MasterStateHandler (I2C1);
}

void I2C_Init_IO_Pins(void) {
	Chip_IOCON_PinMux (LPC_IOCON, PIN_SDA1, I2C_MODE, I2C_FUNC);
	Chip_IOCON_PinMux (LPC_IOCON, PIN_SCL1, I2C_MODE, I2C_FUNC);

	Chip_IOCON_EnableOD(LPC_IOCON, PIN_SDA1);
	Chip_IOCON_EnableOD(LPC_IOCON, PIN_SCL1);
}

void I2C_Init(void) {
	if(!i2c_initialized) {
		I2C_Init_IO_Pins();

		Chip_I2C_Init (I2C1);
		Chip_I2C_SetClockRate(I2C1, I2C_CLOCKRATE);

		Chip_I2C_SetMasterEventHandler (I2C1, Chip_I2C_EventHandler);
		NVIC_EnableIRQ(I2C1_IRQn);

		i2c_initialized = true;
	}
}
