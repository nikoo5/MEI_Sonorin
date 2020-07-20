/*
===============================================================================
 Name        : Sonorin.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/
s
#include "Sonorin.h"

#define FFT_SIZE	256

// ----- SEMAFOROS -----
SemaphoreHandle_t xMutex;

// ----- VARIABLES EXTERNAS -----
extern uint16_t adc_data[ADC_DATA_LEN]; //FW_ADC.c
extern uint16_t signal[ADC_DATA_LEN]; //UT_Test.c

// ----- VARIABLES GLOBALES -----
float32_t signal_fft[FFT_SIZE] = {0};


float32_t FFT_Input[FFT_SIZE * 2];
float32_t FFT_Output[FFT_SIZE];
float32_t maxValueFFT = 0;
uint32_t maxValueIndexFFT = 0;
uint16_t BufferCountFFT = 0;

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
	RTC_Init();
	EEPROM_Init();
	//ADC_Init();
	//DMA_ADC_Init();
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

static void vDBDigTask(void *pvParameters) {
	uint8_t a = 0;
	uint8_t b = 0;
	uint8_t c = 0;
	uint8_t d = 0;
	uint8_t e = 0;

	char fecha[] = "dd/mm/yyyy hh:mm:ss";

	uint16_t year; uint8_t month; uint8_t day; uint8_t hour; uint8_t minute; uint8_t second;

	int db = 0;

	while (1) {
		xSemaphoreTake(xMutex, portMAX_DELAY);

		RTC_GetFull(&year, &month, &day, &hour, &minute, &second);
		if(year != 2020) {
			RTC_SetFull(2020,6,29,17,51,00);
		}

		RTC_GetFull(&year, &month, &day, &hour, &minute, &second);
		//ut_dateString(fecha, year, month, day, hour, minute, second);
		sprintf(fecha, "%02d/%02d/%04d %02d:%02d:%02d", day, month, year, hour, minute, second);

		LCD_ClearArea(0,0,152,16);
		LCD_SetColorRGB(255,255,255);
		LCD_DrawText(0,0, fecha, LCD_FONT_SIZE_MEDIUM);

		LCD_SetColorRGB(255, 0, 0);

		//db = (int)(round(getDB(adc_data, ADC_DATA_LEN)) * 100.0);

		if(db / 10000 != a) {
			a = db / 10000;
			a = a % 10;
			LCD_DrawSevenSeg(20+(40*0),20,a,false);
		}
		db = db % 10000;

		if(db / 1000 != b) {
			b = db / 1000;
			LCD_DrawSevenSeg(20+(40*1),20,b,false);
		}
		db = db % 1000;

		if(db / 100 != c) {
			c = db / 100;
			LCD_DrawSevenSeg(20+(40*2),20,c,true);
		}
		db = db % 100;

		if(db / 10 != d) {
			d = db / 10;
			LCD_DrawSevenSeg(20+(40*3),20,d,false);
		}
		db = db % 10;

		if(db != e) {
			e = db;
			LCD_DrawSevenSeg(20+(40*4),20,e,false);
		}

		xSemaphoreGive(xMutex);

		vTaskDelay(1000);
	}
}

static void vDataADCTask(void *pvParameters) {
	while(1) {
		xSemaphoreTake(xMutex, portMAX_DELAY);

		createSignalTest();

		xSemaphoreGive(xMutex);
		vTaskDelay(10);
	}
}

static void vSignalWaveADCTask(void *pvParameters) {
	float32_t last_sig = 0;

	while(1) {
		xSemaphoreTake(xMutex, portMAX_DELAY);

		for(uint8_t i = 0; i < 240; i++) {


			signal[i] = adc_data[i];

			if(last_sig != signal[i]) {
				LCD_SetColor(0x0000);
				LCD_DrawPixel(0+i, 240-last_sig);
				LCD_SetColorRGB(0,255,255);
				LCD_DrawPixel(0+i, 240-signal[i]);
			}
		}

		xSemaphoreGive(xMutex);
		vTaskDelay(10);
	}
}

static void vSignalFrecADCTask(void *pvParameters) {
	float32_t last_sig = 0;
	float32_t topMaxValueFFT = 0;

	while(1) {
		xSemaphoreTake(xMutex, portMAX_DELAY);

		//Convierto
		for(uint16_t i = 0; i < FFT_SIZE; i++) {
			FFT_Input[i * 2] = (float32_t)UT_ScaleConverter(adc_data[i], -80, 80, -0xFFF, 0xFFF);
			FFT_Input[i * 2 + 1] = (float32_t)0;
		}

		FFT_Calculate(FFT_Input, FFT_Output);
		FFT_MaxValue(FFT_Output, &maxValueFFT, &maxValueIndexFFT);

		if(maxValueFFT > topMaxValueFFT && maxValueIndexFFT > 0) topMaxValueFFT = maxValueFFT;

		for(uint16_t i = 0; i < 240; i++) {
			if(maxValueFFT < 5000) {
				FFT_Output[i] = 4;
			} else {
				FFT_Output[i] = UT_ScaleConverter(FFT_Output[i], 0, topMaxValueFFT, 0, 80);
			}
		}

		for(uint8_t i = 0; i < 80; i++) {
			last_sig = signal[i];

			signal[i] = FFT_Output[i];

			if(last_sig > signal[i]) {
				LCD_SetColor(0x0000);
				LCD_DrawRectangle(0+i*3, 320-last_sig, 3, last_sig-signal[i], true);
			} else if (last_sig < signal[i]) {
				LCD_SetColorRGB(0,255,255);
				LCD_DrawRectangle(0+i*3, 320-signal[i], 3, signal[i]-last_sig, true);
			}
		}

		xSemaphoreGive(xMutex);
		vTaskDelay(10);
	}
}

int main(void)
{
	prvSetupHardware();

	//FFT_Configure(FFT_SIZE);

	xMutex = xSemaphoreCreateMutex();

	xTaskCreate(vLEDTask, "vTaskLed", configMINIMAL_STACK_SIZE, (void *) NULL, (tskIDLE_PRIORITY + 1UL), (xTaskHandle *) NULL);
	xTaskCreate(vDBDigTask, "vDBDigTask", configMINIMAL_STACK_SIZE*4, (void *) NULL, (tskIDLE_PRIORITY + 1UL), (xTaskHandle *) NULL);
	//xTaskCreate(vDataADCTask, "vDataADCTask", configMINIMAL_STACK_SIZE, (void *) NULL, (tskIDLE_PRIORITY + 1UL), (xTaskHandle *) NULL);
	//xTaskCreate(vSignalWaveADCTask, "vSignalWaveADCTask", configMINIMAL_STACK_SIZE, (void *) NULL, (tskIDLE_PRIORITY + 1UL), (xTaskHandle *) NULL);
	//xTaskCreate(vSignalFrecADCTask, "vSignalFrecADCTask", configMINIMAL_STACK_SIZE, (void *) NULL, (tskIDLE_PRIORITY + 1UL), (xTaskHandle *) NULL);

	LCD_SetColorRGB(255, 0, 0);
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
