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

#include "ut_pll.h"



static void prvSetupHardware(void)
{
	setPLL(120);

	//SystemCoreClockUpdate();

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

static void vTestTask(void *pvParameters) {
	uint8_t a = 0;
	uint8_t b = 0;
	uint8_t c = 0;
	uint8_t d = 0;
	uint8_t e = 0;

	while (1) {
		e++;
		if(e > 9) {
			e = 0;
			d++;
			if(d > 9) {
				d = 0;
				c++;
				if(c > 9) {
					c = 0;
					b++;
					if(b > 9) {
						b = 0;
						a++;
						if(a > 9) {
							a = 0;
						}
						LCD_DrawSevenSeg(20+(40*0),20,a,false);
					}
					LCD_DrawSevenSeg(20+(40*1),20,b,false);
				}
				LCD_DrawSevenSeg(20+(40*2),20,c,true);
			}
			LCD_DrawSevenSeg(20+(40*3),20,d,false);
		}
		LCD_DrawSevenSeg(20+(40*4),20,e,false);

		vTaskDelay(6);
	}
}

int main(void)
{
	prvSetupHardware();

	xTaskCreate(vLEDTask, "vTaskLed", configMINIMAL_STACK_SIZE, (void *) NULL, (tskIDLE_PRIORITY + 1UL), (xTaskHandle *) NULL);
	xTaskCreate(vTestTask, "vTestTask", configMINIMAL_STACK_SIZE, (void *) NULL, (tskIDLE_PRIORITY + 1UL), (xTaskHandle *) NULL);

	LCD_SetColorRGB(255,0,0);
	LCD_DrawRectangle(10,160-25,220,50,false);

	LCD_DrawSevenSeg(20,20,0,false);
	LCD_DrawSevenSeg(20+(40*1),20,0,false);
	LCD_DrawSevenSeg(20+(40*2),20,0,true);
	LCD_DrawSevenSeg(20+(40*3),20,0,false);
	LCD_DrawSevenSeg(20+(40*4),20,0,false);

	/* Start the scheduler */
	vTaskStartScheduler();

	/* Should never arrive here */
	return 1;
}
