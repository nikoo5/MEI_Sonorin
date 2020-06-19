/*
 * Sonorin.h
 *
 *  Created on: 19 de jun. de 2020
 *      Author: Nicoo
 */

#ifndef SONORIN_H_
#define SONORIN_H_

#include <cr_section_macros.h>

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "TFT_320QVT_9341.h"
//#include "FW_TOUCH.h"

#include "math.h"

#define PI	3.14159265359

static void prvSetupHardware(void);

static void vLEDTask(void *pvParameters);
static void vTestTask(void *pvParameters);


#endif /* SONORIN_H_ */
