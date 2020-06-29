/*
 * fw_DMA.c
 *
 *  Created on: 25 de jun. de 2020
 *      Author: Nicoo
 */

#include "FW_DMA.h"

bool DMA_Initialized = false;
bool DMA_ADC_Initialized = false;

uint8_t DMA_ADC_Channel = 0xFF;
DMA_TransferDescriptor_t DMA_ADC_Config;

__BSS(RAM2) uint32_t DMA_ADC_Buffer[DMA_ADC_Buffer_SIZE];

extern uint16_t adc_data[ADC_DATA_LEN];

void DMA_Init(void) {
	if(!DMA_Initialized) {
		Chip_GPDMA_Init(LPC_GPDMA);

		NVIC_DisableIRQ(DMA_IRQn);
		NVIC_SetPriority(DMA_IRQn, ((0x01 << 3) | 0x01));
		NVIC_EnableIRQ(DMA_IRQn);

		DMA_Initialized = true;
	}
}

void DMA_ADC_Init(void) {
	if(!DMA_ADC_Initialized) {
		DMA_Init();

		DMA_ADC_Channel = Chip_GPDMA_GetFreeChannel(LPC_GPDMA, GPDMA_CONN_ADC);

		Chip_GPDMA_PrepareDescriptor(LPC_GPDMA, &DMA_ADC_Config, GPDMA_CONN_ADC, (uint32_t)&DMA_ADC_Buffer[0], DMA_ADC_Buffer_SIZE, GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA, &DMA_ADC_Config);

		DMA_ADC_Config.src = GPDMA_CONN_ADC;
		DMA_ADC_Config.ctrl |= GPDMA_DMACCxControl_I;

		DMA_ADC_Transfer();

		DMA_ADC_Initialized = true;
	}
}

void DMA_ADC_Transfer(void) {
	Chip_GPDMA_SGTransfer(LPC_GPDMA, DMA_ADC_Channel, &DMA_ADC_Config, GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA);
	Chip_GPDMA_PrepareDescriptor(LPC_GPDMA, &DMA_ADC_Config, GPDMA_CONN_ADC, (uint32_t)&DMA_ADC_Buffer[0], DMA_ADC_Buffer_SIZE, GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA, &DMA_ADC_Config);
	DMA_ADC_Config.ctrl |= GPDMA_DMACCxControl_I;
}

void DMA_IRQHandler(void) {
	uint32_t i;

	if (Chip_GPDMA_IntGetStatus(LPC_GPDMA, GPDMA_STAT_INT, DMA_ADC_Channel)) {
		if (Chip_GPDMA_Interrupt(LPC_GPDMA, DMA_ADC_Channel) == SUCCESS) {
			for(i = 0; i < DMA_ADC_Buffer_SIZE; i++) {
				adc_data[i] = (DMA_ADC_Buffer[i] & 0xFFF) ? (DMA_ADC_Buffer[i] & 0xFFF) : 0;
			}
		}
	}
}
