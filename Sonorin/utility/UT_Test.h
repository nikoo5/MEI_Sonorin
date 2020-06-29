/*
 * UT_Test.h
 *
 *  Created on: 25 de jun. de 2020
 *      Author: Nicoo
 */

#ifndef UT_TEST_H_
#define UT_TEST_H_

#include "FW_ADC.h"

#include <ut_constants.h>
#include "chip.h"
#include "arm_math.h"

#define		SIGNAL_A_F			833					//1 ciclo a 200khz y 240 muestras
#define		SIGNAL_A_PP			(ADC_VREF - 10)
#define		SIGNAL_B_F			1666				//2 ciclo a 200khz y 240 muestras
#define		SIGNAL_B_PP			(ADC_VREF / 10)
#define		SIGNAL_NOISE_PP		(ADC_VREF / 100)

void createSignalTest(void);

#endif /* UT_TEST_H_ */
