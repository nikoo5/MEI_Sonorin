/*
 * fw_DMA.h
 *
 *  Created on: 25 de jun. de 2020
 *      Author: Nicoo
 */

#ifndef FW_DMA_H_
#define FW_DMA_H_

#include "cr_section_macros.h"
#include "chip.h"
#include "FW_ADC.h"

#define		DMA_ADC_Buffer_SIZE		ADC_DATA_LEN

void DMA_Init(void);
void DMA_ADC_Init(void);
void DMA_ADC_Transfer(void);

#endif /* FW_DMA_H_ */
