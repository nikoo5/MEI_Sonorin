/*
 * ut_signal.c
 *
 *  Created on: 24 de jun. de 2020
 *      Author: Nicoo
 */

#include "ut_signal.h"

float32_t getRMS(float32_t data[], uint16_t len) {
	if(len == 0) return 0;

	float32_t val = 0;

	for(uint16_t i = 0; i < len; i++) {
		val += (data[i] * data[i]);
	}

	val /= len;
	val = sqrt(val);

	return val;
}

float32_t getDB(float32_t data[], uint16_t len) {
	float32_t rms = getRMS(data, len);

	//1V -> 1Pa --> RMS = Pa
	//Pref = 20uPa

	return 20.0 * log10(rms);
}
/*
float32_t round(float32_t var) {
	float32_t value = (int)(var * 100 + 0.5);
    return (float32_t)value / 100;
}*/

