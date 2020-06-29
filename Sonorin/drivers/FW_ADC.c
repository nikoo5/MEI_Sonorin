/*
 * FW_ADC.c
 *
 *  Created on: 23 de jun. de 2020
 *      Author: Nicoo
 */

#include "FW_ADC.h"

static ADC_CLOCK_SETUP_T ADCSetup;

uint16_t adc_data[ADC_DATA_LEN] = {0};

void ADC_Init(void) {
	Chip_ADC_Init(LPC_ADC, &ADCSetup);
	Chip_ADC_EnableChannel(LPC_ADC, ADC_CHANNLE, ENABLE);
	Chip_ADC_SetSampleRate(LPC_ADC, &ADCSetup, ADC_RATE);
	Chip_ADC_SetBurstCmd(LPC_ADC, ENABLE);
	Chip_ADC_SetStartMode(LPC_ADC, ADC_START_NOW, ADC_TRIGGERMODE_RISING);
	NVIC_DisableIRQ(ADC_IRQn);
	Chip_ADC_Int_SetChannelCmd(LPC_ADC, ADC_CHANNLE, ENABLE);
}
