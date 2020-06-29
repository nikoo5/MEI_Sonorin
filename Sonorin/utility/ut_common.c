/*
 * ut_common.c
 *
 *  Created on: 24 de jun. de 2020
 *      Author: Nicoo
 */

#include "ut_common.h"

uint32_t UT_ComplementoA2(uint32_t valor) {
	valor = valor - 1;
	valor = ~valor;
	return valor;
}

uint32_t UT_ValorDAC(uint32_t valor) {
	valor &= 0xFFFFFF;

	if(valor < 0x800000) valor += 0x800000;
	else valor -= 0x800000;

	return valor << 8;
}

uint32_t UT_ValorADC(uint32_t valor) {
	uint32_t tmp = valor >> 8;

	if(tmp < 0x800000) tmp += 0x800000;
	else tmp -= 0x800000;

	return tmp;
}
//Idem funciones anteriores pero hechas con operaciones de bits, para ver si logro aumentar la
// velocidad del proceso de filtrado
uint32_t UT_ValorDAC2(uint32_t valor) {
	valor &= 0xFFFFFF;

	if(valor & (1<<23))
	{
		valor &= ~(1<<23);
	}
	else
	{
		valor |= (1<<23);
	}

	return valor << 8;
}

uint32_t UT_ValorADC2(uint32_t valor) {
	uint32_t tmp = valor >> 8;

	if(tmp & (1<<23))
	{
		tmp &= ~(1<<23);
	}
	else
	{
		tmp |= (1<<23);
	}


	return tmp;
}
//-----------------------------

uint32_t UT_ValorADC_lean(uint32_t valor) {
	uint32_t tmp = valor >> 12;

	if(tmp < 0x800000) tmp += 0x800000;
	else tmp -= 0x800000;

	return tmp;
}

float32_t UT_ScaleConverter(float32_t val, float32_t old_min, float32_t old_max, float32_t new_min, float32_t new_max) {
	float32_t oldRange = old_max - old_min;
	float32_t newRange = new_max - new_min;

	return ((val - old_min) * newRange / oldRange) + new_min;
}

uint16_t UT_ScaleConverter16(uint16_t val, uint16_t old_min, uint16_t old_max, uint16_t new_min, uint16_t new_max) {
	uint16_t oldRange = old_max - old_min;
	uint16_t newRange = new_max - new_min;

	return ((val - old_min) * newRange / oldRange) + new_min;
}

int _compare8(const void * elem1, const void * elem2) {
	uint8_t f = *((uint8_t*)elem1);
	uint8_t s = *((uint8_t*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

int _compare16(const void * elem1, const void * elem2) {
	uint16_t f = *((uint16_t*)elem1);
	uint16_t s = *((uint16_t*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

int _compare32(const void * elem1, const void * elem2) {
	uint32_t f = *((uint32_t*)elem1);
	uint32_t s = *((uint32_t*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

uint8_t UT_SortArray8(uint8_t *array, uint16_t size_array) {
	uint8_t *data = array;

	qsort(data, size_array, 1, _compare8);

	float32_t prom = 0;
	float32_t count = 0;

	for(uint16_t i = size_array / 3; i < (size_array / 3) * 2; i++) {
		prom += data[i];
		count++;
	}
	return (uint8_t)(prom / count);
}

uint16_t UT_SortArray16(uint16_t *array, uint16_t size_array) {
	uint16_t *data = array;

	qsort(data, size_array, 2, _compare16);

	float32_t prom = 0;
	float32_t count = 0;

	for(uint16_t i = size_array / 3; i < (size_array / 3) * 2; i++) {
		prom += data[i];
		count++;
	}
	return (uint16_t)(prom / count);
}

uint32_t UT_SortArray32(uint32_t *array, uint16_t size_array) {
	uint32_t *data = array;

	qsort(data, size_array, 4, _compare32);

	float32_t prom = 0;
	float32_t count = 0;

	for(uint16_t i = size_array / 3; i < (size_array / 3) * 2; i++) {
		prom += data[i];
		count++;
	}
	return (uint32_t)(prom / count);
}
