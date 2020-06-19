#ifndef TFT_PIN_CONNECTION_H_
#define TFT_PIN_CONNECTION_H_

/*DEFINES DE PINES*/
#ifdef PLACA_PRUEBA
	#define LCD_RST	LPC_GPIO,1,24
	#define LCD_CS	LPC_GPIO,1,18	//CHIP-SELECT HABILITA O DESABILITA EL ILI9341, SI ESTA DESABILITADO NO LE DA BOLA A NADA
	#define LCD_RS	LPC_GPIO,2,1	//DATA/COMAND SELECTION
	#define LCD_WR	LPC_GPIO,2,2
	#define LCD_RD	LPC_GPIO,2,3	//creo que este no es necesario utilizar, ESTE DEBE SER PARA LEER DATOS. SI NO SE USA, SIEMPRE HIGH

	#define LCD_D0	LPC_GPIO,0,9
	#define LCD_D1	LPC_GPIO,0,8
	#define LCD_D2	LPC_GPIO,0,7
	#define LCD_D3	LPC_GPIO,0,6
	#define LCD_D4	LPC_GPIO,2,13
	#define LCD_D5	LPC_GPIO,4,29
	#define LCD_D6	LPC_GPIO,3,25
	#define LCD_D7	LPC_GPIO,1,27
	#define LCD_D8	LPC_GPIO,2,4
	#define LCD_D9	LPC_GPIO,2,5
	#define LCD_D10	LPC_GPIO,2,6
	#define LCD_D11	LPC_GPIO,2,7
	#define LCD_D12	LPC_GPIO,2,8
	#define LCD_D13	LPC_GPIO,2,10
	#define LCD_D14	LPC_GPIO,2,11
	#define LCD_D15	LPC_GPIO,2,12
#else
	#define LCD_RST	LPC_GPIO,0,1
	#define LCD_CS	LPC_GPIO,0,4		//CHIP-SELECT HABILITA O DESABILITA EL ILI9341, SI ESTA DESABILITADO NO LE DA BOLA A NADA
	#define LCD_RS	LPC_GPIO,0,19	//DATA/COMAND SELECTION
	#define LCD_WR	LPC_GPIO,1,28
	#define LCD_RD	LPC_GPIO,1,23		//creo que este no es necesario utilizar, ESTE DEBE SER PARA LEER DATOS. SI NO SE USA, SIEMPRE HIGH

	#define LCD_D0	LPC_GPIO,2,13
	#define LCD_D1	LPC_GPIO,3,25
	#define LCD_D2	LPC_GPIO,1,27
	#define LCD_D3	LPC_GPIO,1,24
	#define LCD_D4	LPC_GPIO,3,26
	#define LCD_D5	LPC_GPIO,1,25
	#define LCD_D6	LPC_GPIO,0,20
	#define LCD_D7	LPC_GPIO,0,22
	#define LCD_D8	LPC_GPIO,1,29
	#define LCD_D9	LPC_GPIO,1,26
	#define LCD_D10	LPC_GPIO,1,23
	#define LCD_D11	LPC_GPIO,0,21
	#define LCD_D12	LPC_GPIO,0,3
	#define LCD_D13	LPC_GPIO,0,2
	#define LCD_D14	LPC_GPIO,1,31
	#define LCD_D15	LPC_GPIO,1,30
#endif

#endif /* TFT_PIN_CONNECTION_H_ */
