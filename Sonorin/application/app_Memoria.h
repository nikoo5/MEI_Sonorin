/*
 * app_Memoria.h
 *
 *  Created on: 30 de jun. de 2020
 *      Author: Nicoo
 */

#ifndef APP_MEMORIA_H_
#define APP_MEMORIA_H_

#include "FW_EEPROM.h"
#include "arm_math.h"

#define		MEM_ADDRESS_PRE_AMP	0x0000

void loadMemory(void);

float32_t memoryGetPreAmp(void);
void memorySetPreAmp(float32_t value);

#endif /* APP_MEMORIA_H_ */
