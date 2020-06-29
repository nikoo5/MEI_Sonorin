/*
 * ut_common.h
 *
 *  Created on: 24 de jun. de 2020
 *      Author: Nicoo
 */

#ifndef UT_COMMON_H_
#define UT_COMMON_H_

#include "chip.h"
#include "stdlib.h"
#include "arm_math.h"

uint32_t UT_ComplementoA2(uint32_t valor);
uint32_t UT_ValorDAC(uint32_t valor);
uint32_t UT_ValorADC(uint32_t valor);
uint32_t UT_ValorDAC2(uint32_t valor);
uint32_t UT_ValorADC2(uint32_t valor);
uint32_t UT_ValorADC_lean(uint32_t valor);

float32_t UT_ScaleConverter(float32_t val, float32_t old_min, float32_t old_max, float32_t new_min, float32_t new_max);
uint16_t UT_ScaleConverter16(uint16_t val, uint16_t old_min, uint16_t old_max, uint16_t new_min, uint16_t new_max);

int _compare8(const void * elem1, const void * elem2);
int _compare16(const void * elem1, const void * elem2);
int _compare32(const void * elem1, const void * elem2);
uint8_t UT_SortArray8(uint8_t *array, uint16_t size_array);
uint16_t UT_SortArray16(uint16_t *array, uint16_t size_array);
uint32_t UT_SortArray32(uint32_t *array, uint16_t size_array);

#endif /* UT_COMMON_H_ */
