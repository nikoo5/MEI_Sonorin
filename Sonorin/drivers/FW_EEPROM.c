/*
 * FW_EEPROM.c
 *
 *  Created on: 23 de jun. de 2020
 *      Author: Nicoo
 */

#include "FW_EEPROM.h"

void EEPROM_Init(void) {
	I2C_Init();
	uint8_t data_tx[3] = {0x00, 0xFF, 123};

	Chip_I2C_MasterSend(I2C1, BUILTIN_EEPROM_ADDRESS, data_tx, 3);

	uint8_t data_rx[1] =  {0};
	Chip_I2C_MasterSend(I2C1, BUILTIN_EEPROM_ADDRESS, data_tx, 2);
	Chip_I2C_MasterRead(I2C1, BUILTIN_EEPROM_ADDRESS, data_rx, 1);
}

void EEPROM_Write(uint16_t address, uint8_t* data) {
	uint16_t size = LEN(data);
	uint8_t position[] = {(address & 0xFF00) >> 8, address & 0x00FF};
	uint8_t* position_data = malloc(size + 2);

	memcpy(position_data, position, 2 * sizeof(uint8_t));
	memcpy(position_data + 2, data, size * sizeof(uint8_t));

	Chip_I2C_MasterSend(I2C1, BUILTIN_EEPROM_ADDRESS, position_data, size + 2);
}

void EEPROM_Write8(uint16_t address, uint8_t data) {
	uint8_t send_data[1] = {0};
	send_data[0] = data;
	EEPROM_Write(address, send_data);
}
void EEPROM_Write16(uint16_t address, uint16_t data) {
	uint8_t send_data[2] = {0};
	send_data[0] = ((data & 0xFF00) >> 8) & 0x000000FF;
	send_data[1] = ((data & 0x00FF) >> 0) & 0x000000FF;
	EEPROM_Write(address, send_data);
}
void EEPROM_Write32(uint16_t address, uint32_t data) {
	uint8_t send_data[4] = {0};
	send_data[0] = ((data & 0xFF000000) >> 24) & 0x000000FF;
	send_data[1] = ((data & 0x00FF0000) >> 16) & 0x000000FF;
	send_data[2] = ((data & 0x0000FF00) >> 8) & 0x000000FF;
	send_data[3] = ((data & 0x000000FF) >> 0) & 0x000000FF;
	EEPROM_Write(address, send_data);
}
void EEPROM_WriteFloat(uint16_t address, float32_t data) {
	my32bitFloat var;
	var.f = data;
	uint32_t send = (((uint32_t)var.raw.sign & 0x00000001) << 31) | (((uint32_t)var.raw.exponent & 0x000000FF) << 23) | (((uint32_t)var.raw.mantissa & 0x007FFFFF));
	uint8_t send_data[4] = {(send & 0xFF000000) >> 24, (send & 0x00FF0000) >> 16, (send & 0x0000FF00) >> 8, (send & 0x000000FF)};
	EEPROM_Write(address, send_data);
}

void EEPROM_Read(uint16_t address, uint8_t* data, uint16_t size) {
	uint8_t position[2] = {(address & 0xFF00) >> 8, address & 0x00FF};
	Chip_I2C_MasterSend(I2C1, BUILTIN_EEPROM_ADDRESS, position, 2);
	Chip_I2C_MasterRead(I2C1, BUILTIN_EEPROM_ADDRESS, data, size);
}
uint8_t EEPROM_Read8(uint16_t address) {
	uint8_t data[1] = {0};
	EEPROM_Read(address, data, 1);
	return data[0];
}
uint16_t EEPROM_Read16(uint16_t address) {
	uint8_t data[2] = {0};
	EEPROM_Read(address, data, 2);

	uint16_t retorno = 0;

	for(uint8_t i = 2; i > 0; i--) {
		retorno |= (data[2 - i] << (8*(i - 1))) & (0x000000FF << (8*(i - 1)));
	}

	return retorno;
}
uint32_t EEPROM_Read32(uint16_t address) {
	uint8_t data[4] = {0};
	EEPROM_Read(address, data, 4);

	uint32_t retorno = 0;

	for(uint8_t i = 4; i > 0; i--) {
		retorno |= (data[4 - i] << (8*(i - 1))) & (0x000000FF << (8*(i - 1)));
	}

	return retorno;
}
float32_t EEPROM_ReadFloat(uint16_t address) {
	uint8_t data[4] = {0};
	EEPROM_Read(address, data, 4);

	uint32_t tmp = 0;

	for(uint8_t i = 4; i > 0; i--) {
		tmp |= (data[4 - i] << (8*(i - 1))) & (0x000000FF << (8*(i - 1)));
	}

	my32bitFloat var;
	var.raw.sign = (tmp >> 31) & 0x00000001;
	var.raw.exponent = (tmp >> 23) & 0x000000FF;
	var.raw.mantissa = tmp & 0x007FFFFF;

	return (float32_t)var.f;
}
