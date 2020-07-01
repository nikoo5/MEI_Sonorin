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
#include "arm_math.h"
#include "fw_I2C.h"

#define		LEN(x)		sizeof(x)/sizeof(x[0])

#define BUILTIN_EEPROM_ADDRESS		0x50

typedef union {
    float f;
    struct
    {
        unsigned int mantissa : 23;
        unsigned int exponent : 8;
        unsigned int sign : 1;
    } raw;
} my32bitFloat;

void EEPROM_Init(void);

void EEPROM_Write(uint16_t address, uint8_t* data);
void EEPROM_Write8(uint16_t address, uint8_t data);
void EEPROM_Write16(uint16_t address, uint16_t data);
void EEPROM_Write32(uint16_t address, uint32_t data);
void EEPROM_WriteFloat(uint16_t address, float32_t data);

void EEPROM_Read(uint16_t address, uint8_t* data, uint16_t size);
uint8_t EEPROM_Read8(uint16_t address);
uint16_t EEPROM_Read16(uint16_t address);
uint32_t EEPROM_Read32(uint16_t address);
float32_t EEPROM_ReadFloat(uint16_t address);
#endif /* FW_EEPROM_H_ */
