/*
 * app_Memoria.c
 *
 *  Created on: 30 de jun. de 2020
 *      Author: Nicoo
 */

#include "app_Memoria.h"

bool memory_loaded = false;
float32_t constante_pre_amplificador = 0x0;

void loadMemory(void) {
	if(!memory_loaded) {
		memory_loaded = true;

		constante_pre_amplificador = EEPROM_ReadFloat(MEM_ADDRESS_PRE_AMP);
	}
}

float32_t memoryGetPreAmp(void) {
	loadMemory();
	return constante_pre_amplificador;
}
void memorySetPreAmp(float32_t value) {
	constante_pre_amplificador = value;
	EEPROM_WriteFloat(MEM_ADDRESS_PRE_AMP, constante_pre_amplificador);
}
