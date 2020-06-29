/*
 * UT_Test.c
 *
 *  Created on: 25 de jun. de 2020
 *      Author: Nicoo
 */

#include "UT_Test.h"

extern uint16_t adc_data[ADC_DATA_LEN];
uint16_t signal[ADC_DATA_LEN] = {0};

void createSignalTest(void) {
	float32_t signal_a, signal_b, noise;

	for(uint16_t i = 0; i < ADC_DATA_LEN; i++) {
		signal_a = (float32_t)SIGNAL_A_PP * sin(2.0 * PI * (1.0 / (float32_t)ADC_RATE) * (float32_t)SIGNAL_A_F * (float32_t)i);
		signal_b = (float32_t)SIGNAL_B_PP * sin(2.0 * PI * (1.0 / (float32_t)ADC_RATE) * (float32_t)SIGNAL_B_F * (float32_t)i);
		noise = (float32_t)SIGNAL_NOISE_PP * (2.0 * (float32_t)adc_data[i] - 1.0);

		signal[i] = adc_data[i];
	}
}
