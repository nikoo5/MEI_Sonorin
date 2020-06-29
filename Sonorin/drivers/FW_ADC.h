/*
 * FW_ADC.h
 *
 *  Created on: 23 de jun. de 2020
 *      Author: Nicoo
 */

#ifndef FW_ADC_H_
#define FW_ADC_H_

#include <ut_constants.h>
#include "chip.h"
#include "arm_math.h"

#define		ADC_CHANNLE			ADC_CH0					//CH0
#define		ADC_RATE			ADC_MAX_SAMPLE_RATE		//200kHz
#define		ADC_DATA_LEN		8						//256 Muestras
#define		ADC_VREF			3.3						//3.3V
#define		ADC_RES				12						//12 BITS

void ADC_Init(void);

#endif /* FW_ADC_H_ */
