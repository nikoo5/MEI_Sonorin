/*
===============================================================================
 Name        : Sonorin.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include "Sonorin.h"
#include "stdio.h"

static void prvSetupHardware(void)
{
	SystemCoreClockUpdate();
	Chip_GPIO_Init(LPC_GPIO);
	Chip_IOCON_Init(LPC_IOCON);

	#ifdef TFT_DEBUG_BOARD
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 22);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 22, false);
	#else
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 2, 0);
		Chip_GPIO_SetPinState(LPC_GPIO, 2, 0, true);
	#endif

	LCD_Init();
	//TOUCH_Init();
}

static void vLEDTask(void *pvParameters) {
	bool LedState = true;

	while (1) {
		LedState = (bool) !LedState;

		#ifdef TFT_DEBUG_BOARD
			Chip_GPIO_SetPinState(LPC_GPIO, 0, 22, LedState);
		#else
			Chip_GPIO_SetPinState(LPC_GPIO, 2, 0, LedState);
		#endif

		vTaskDelay(250);
	}
}

int main(void)
{
	prvSetupHardware();

	xTaskCreate(vLEDTask, "vTaskLed", configMINIMAL_STACK_SIZE, (void *) NULL, (tskIDLE_PRIORITY + 1UL), (xTaskHandle *) NULL);

	/* Start the scheduler */
	vTaskStartScheduler();

	/* Should never arrive here */
	return 1;
}
