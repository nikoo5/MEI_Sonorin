/*
 * FW_EEPROM.c
 *
 *  Created on: 23 de jun. de 2020
 *      Author: Nicoo
 */

#include "FW_EEPROM.h"

#define		LEN(x)		sizeof(x)/sizeof(x[0])

void EEPROM_Init_IO_Pins(void) {
	Chip_IOCON_PinMux (LPC_IOCON, PUERTO_0, PIN_SDA1, I2C_MODE, I2C_FUNC);
	Chip_IOCON_PinMux (LPC_IOCON, PUERTO_0, PIN_SCL1, I2C_MODE, I2C_FUNC);

	Chip_IOCON_EnableOD(LPC_IOCON, PUERTO_0, PIN_SDA1);
	Chip_IOCON_EnableOD(LPC_IOCON, PUERTO_0, PIN_SCL1);
}

void EEPROM_Init(void) {
	EEPROM_Init_IO_Pins();

	Chip_I2C_Init (I2C1);
	Chip_I2C_SetClockRate(I2C1, I2C_CLOCKRATE);

	Chip_I2C_SetMasterEventHandler (I2C1, Chip_I2C_EventHandler);
	NVIC_EnableIRQ(I2C1_IRQn);
}

void EEPROM_Write(uint16_t address, uint8_t* data) {
	uint8_t position[] = {(address & 0xFF00) >> 8, address & 0x00FF};

	uint8_t* position_data = malloc(LEN(data) + 2);

	memcpy(position_data, position, 2 * sizeof(uint8_t)); // copy 4 floats from x to total[0]...total[3]
	memcpy(position_data + 2, data, LEN(data) * sizeof(uint8_t)); // copy 4 floats from y to total[4]...total[7]

	Chip_I2C_MasterSend(I2C1, BUILTIN_EEPROM_ADDRESS, position_data, LEN(position_data));
}
