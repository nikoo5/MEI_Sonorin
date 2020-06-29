/*
 * app_FFT.c
 *
 *  Created on: 24 de jun. de 2020
 *      Author: Nicoo
 */

#include "app_FFT.h"

arm_cfft_radix4_instance_f32 S;	//Instancio el modulo CFFT

uint32_t fft_size;

void FFT_Configure(uint32_t size) {
	fft_size = size;
	//Initialize the CFFT/CIFFT module, intFlag = 0, doBitReverse = 1
	arm_cfft_radix4_init_f32(&S, fft_size, 0, 1);
}

void FFT_Calculate(float32_t * fft_input, float32_t * fft_output) {
	//Process the data through the CFFT/CIFFT module
	arm_cfft_radix4_f32(&S, fft_input);
	//Process the data through the Complex Magniture Module for calculating the magnitude at each bin
	arm_cmplx_mag_f32(fft_input, fft_output, fft_size);
}

void FFT_MaxValue(float32_t * fft_output, float32_t * value, uint32_t * index) {
	//Calculates maxValue and returns corresponding value
	arm_max_f32(fft_output, fft_size, value, index);
}

