/*
 * app_FFT.h
 *
 *  Created on: 24 de jun. de 2020
 *      Author: Nicoo
 */

#ifndef APP_FFT_H_
#define APP_FFT_H_

#include "arm_math.h"

void FFT_Configure(uint32_t size);
void FFT_Calculate(float32_t * fft_input, float32_t * fft_output);
void FFT_MaxValue(float32_t * fft_output, float32_t * value, uint32_t * index);

#endif /* APP_FFT_H_ */
