/*
 * ut_signal.h
 *
 *  Created on: 24 de jun. de 2020
 *      Author: Nicoo
 */

#ifndef UT_SIGNAL_H_
#define UT_SIGNAL_H_

#include "chip.h"
#include "arm_math.h"

float32_t getRMS(float32_t data[], uint16_t len);
float32_t getDB(float32_t data[], uint16_t len);
//float32_t round(float32_t var);

#endif /* UT_SIGNAL_H_ */
