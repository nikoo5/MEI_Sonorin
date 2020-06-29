/*
 * Sonorin.h
 *
 *  Created on: 19 de jun. de 2020
 *      Author: Nicoo
 */

#ifndef SONORIN_H_
#define SONORIN_H_

#include <cr_section_macros.h>
#include "stdio.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "ut_common.h"
#include "ut_constants.h"
#include "ut_pll.h"
#include "ut_signal.h"
#include "UT_Test.h"

#include "app_FFT.h"

#include "TFT_320QVT_9341.h"
//#include "FW_TOUCH.h"
//#include "FW_EEPROM.h"
#include "FW_ADC.h"
#include "FW_DMA.h"
#include "fw_RTC.h"

static void prvSetupHardware(void);

static void vLEDTask(void *pvParameters);
static void vDBDigTask(void *pvParameters);
static void vDataADCTask(void *pvParameters);
static void vSignalWaveADCTask(void *pvParameters);
static void vSignalFrecADCTask(void *pvParameters);

#endif /* SONORIN_H_ */
