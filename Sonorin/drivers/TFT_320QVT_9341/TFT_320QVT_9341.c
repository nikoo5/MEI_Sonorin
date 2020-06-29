#include "TFT_320QVT_9341.h"

#define swap(type, v1, v2) {type v3 = v1; v1 = v2; v2 = v3;}

uint8_t _dataDir = LCD_DATA_DIR;
uint8_t _orientacion = PORTRAIT;
uint8_t TFT_busy = 0;

uint32_t _color = 0x0;
uint16_t _borderWidth = 2;

/* GPIO */
void LCD_Init_IO_Pins(void) {
	Chip_GPIO_SetPinDIROutput(LCD_RST);
	Chip_GPIO_SetPinDIROutput(LCD_CS);
	Chip_GPIO_SetPinDIROutput(LCD_RS);
	Chip_GPIO_SetPinDIROutput(LCD_WR);
	Chip_GPIO_SetPinDIROutput(LCD_RD);

	LCD_SetDataDir(LCD_DATA_DIR_OUTPUT);

	Chip_GPIO_SetPinState(LCD_RST,0);
	Chip_GPIO_SetPinState(LCD_CS,1);//IGNORA TODO, PARA MANDAR COMANDOS Y DATOS PONER CS EN 0
	Chip_GPIO_SetPinState(LCD_RS,1);
	Chip_GPIO_SetPinState(LCD_WR,1);
	Chip_GPIO_SetPinState(LCD_RD,1);
}
void LCD_Reset(void) {
	Chip_GPIO_SetPinOutHigh(LCD_RST);
	TIMER_delay_ms(5);
	Chip_GPIO_SetPinOutLow(LCD_RST);
	TIMER_delay_ms(15);
	Chip_GPIO_SetPinOutHigh(LCD_RST);
	TIMER_delay_ms(15);

	LCD_DisableWrite();
}
void LCD_SetDataDir(uint8_t dir) {
	if(dir != LCD_DATA_DIR) {
		if(_dataDir != dir) {
			bool output = true;
			if (dir == LCD_DATA_DIR_INPUT) output = false;

			Chip_GPIO_SetPinDIR(LCD_D0, output);
			Chip_GPIO_SetPinDIR(LCD_D1, output);
			Chip_GPIO_SetPinDIR(LCD_D2, output);
			Chip_GPIO_SetPinDIR(LCD_D3, output);
			Chip_GPIO_SetPinDIR(LCD_D4, output);
			Chip_GPIO_SetPinDIR(LCD_D5, output);
			Chip_GPIO_SetPinDIR(LCD_D6, output);
			Chip_GPIO_SetPinDIR(LCD_D7, output);
			Chip_GPIO_SetPinDIR(LCD_D8, output);
			Chip_GPIO_SetPinDIR(LCD_D9, output);
			Chip_GPIO_SetPinDIR(LCD_D10, output);
			Chip_GPIO_SetPinDIR(LCD_D11, output);
			Chip_GPIO_SetPinDIR(LCD_D12, output);
			Chip_GPIO_SetPinDIR(LCD_D13, output);
			Chip_GPIO_SetPinDIR(LCD_D14, output);
			Chip_GPIO_SetPinDIR(LCD_D15, output);

			if (output) LCD_SetDataValue(0x0);

			_dataDir = dir;
		}
	}
}
void LCD_EnableDataWrite(void) {
	LCD_SetDataDir(LCD_DATA_DIR_OUTPUT);
	Chip_GPIO_SetPinOutLow(LCD_CS);
	Chip_GPIO_SetPinOutHigh(LCD_RS);
	Chip_GPIO_SetPinOutLow(LCD_WR);
}
void LCD_EnableCommandWrite(void) {
	LCD_SetDataDir(LCD_DATA_DIR_OUTPUT);
	Chip_GPIO_SetPinOutLow(LCD_CS);
	Chip_GPIO_SetPinOutLow(LCD_RS);
	Chip_GPIO_SetPinOutLow(LCD_WR);
}
void LCD_DisableWrite(void) {
	Chip_GPIO_SetPinOutHigh(LCD_CS);
	Chip_GPIO_SetPinOutHigh(LCD_WR);
}
void LCD_Write(void) {
	Chip_GPIO_SetPinOutHigh(LCD_WR);
	Chip_GPIO_SetPinOutLow(LCD_WR);
}
void LCD_SetDataValue(uint16_t data) {
	Chip_GPIO_SetPinState(LCD_D0,( data >> 0 & 0x01));
	Chip_GPIO_SetPinState(LCD_D1,( data >> 1 & 0x01));
	Chip_GPIO_SetPinState(LCD_D2,( data >> 2 & 0x01));
	Chip_GPIO_SetPinState(LCD_D3,( data >> 3 & 0x01));
	Chip_GPIO_SetPinState(LCD_D4,( data >> 4 & 0x01));
	Chip_GPIO_SetPinState(LCD_D5,( data >> 5 & 0x01));
	Chip_GPIO_SetPinState(LCD_D6,( data >> 6 & 0x01));
	Chip_GPIO_SetPinState(LCD_D7,( data >> 7 & 0x01));
	Chip_GPIO_SetPinState(LCD_D8,( data >> 8 & 0x01));
	Chip_GPIO_SetPinState(LCD_D9,( data >> 9 & 0x01));
	Chip_GPIO_SetPinState(LCD_D10,( data >> 10 & 0x01));
	Chip_GPIO_SetPinState(LCD_D11,( data >> 11 & 0x01));
	Chip_GPIO_SetPinState(LCD_D12,( data >> 12 & 0x01));
	Chip_GPIO_SetPinState(LCD_D13,( data >> 13 & 0x01));
	Chip_GPIO_SetPinState(LCD_D14,( data >> 14 & 0x01));
	Chip_GPIO_SetPinState(LCD_D15,( data >> 15 & 0x01));
}

/* LCD */
void LCD_Init(void) {
	_color = 0;

	LCD_Init_IO_Pins();
	LCD_Reset();

	LCD_WriteCommand(LCD_POWERA);
	LCD_WriteData(0x39);
	LCD_WriteData(0x2C);
	LCD_WriteData(0x00);
	LCD_WriteData(0x34);
	LCD_WriteData(0x02);

	LCD_WriteCommand(LCD_POWERB);
	LCD_WriteData(0x00);
	LCD_WriteData(0X81);
	LCD_WriteData(0X30);

	LCD_WriteCommand(LCD_DTCA);
	LCD_WriteData(0x85);
	LCD_WriteData(0x00);
	LCD_WriteData(0x78);

	LCD_WriteCommand(LCD_DTCB);
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);

	LCD_WriteCommand(LCD_POWER_SEQ);
	LCD_WriteData(0x64);
	LCD_WriteData(0x03);
	LCD_WriteData(0X12);
	LCD_WriteData(0X81);

	LCD_WriteCommand(LCD_PRC);
	LCD_WriteData(0x20);

	LCD_WriteCommand(LCD_POWER1);   	//Power control
	LCD_WriteData(0x23);   				//VRH[5:0]

	LCD_WriteCommand(LCD_POWER2);   	//Power control
	LCD_WriteData(0x10);   				//SAP[2:0];BT[3:0]

	LCD_WriteCommand(LCD_VCOM1);    	//VCM control
	LCD_WriteData(0x3e);   				//Contrast
	LCD_WriteData(0x28);

	LCD_WriteCommand(LCD_VCOM2);    	//VCM control2
	LCD_WriteData(0x86);

	LCD_WriteCommand(LCD_MAC);    		//Memory Access Control
	LCD_WriteData(0x48);

	LCD_WriteCommand(LCD_PIXEL_FORMAT);
	LCD_WriteData(0x55);

	LCD_WriteCommand(LCD_FRMCTR1);
	LCD_WriteData(0x00);
	LCD_WriteData(0x18);

	LCD_WriteCommand(LCD_DFC);    		//Display Function Control
	LCD_WriteData(0x08);
	LCD_WriteData(0x82);
	LCD_WriteData(0x27);

	LCD_WriteCommand(LCD_SLEEP_OUT);    //Exit Sleep
	TIMER_delay_ms(120);

	LCD_WriteCommand(LCD_DISPLAY_ON);   //Display on

	LCD_ClearScr();
}
void LCD_DisplayOn(void) {
  LCD_WriteCommand(LCD_DISPLAY_ON);
}
void LCD_DisplayOff(void) {
  LCD_WriteCommand(LCD_DISPLAY_OFF);
}
void LCD_ClearScr(void) {
	if (_orientacion==LANDSCAPE)
		LCD_SetArea(0,0,LCD_PIXEL_HEIGHT,LCD_PIXEL_WIDTH);
	else
		LCD_SetArea(0,0,LCD_PIXEL_WIDTH,LCD_PIXEL_HEIGHT);

	LCD_FillArea(0,((LCD_PIXEL_WIDTH+1)*(LCD_PIXEL_HEIGHT+1)));
}
void LCD_SetArea(int x1, int y1, int x2, int y2) {
	if (_orientacion==LANDSCAPE)
	{
		swap(int, x1, y1);
		swap(int, x2, y2);
		y1=LCD_PIXEL_HEIGHT-y1;
		y2=LCD_PIXEL_HEIGHT-y2;
		swap(int, y1, y2);
	}

	LCD_WriteCommand(LCD_COLUMN_ADDR);
	LCD_WriteData((x1&0xFF00)>>8);
	LCD_WriteData((x1&0x00FF));
	LCD_WriteData((x2&0xFF00)>>8);
	LCD_WriteData((x2&0x00FF));

	LCD_WriteCommand(LCD_PAGE_ADDR);
	LCD_WriteData((y1&0xFF00)>>8);
	LCD_WriteData((y1&0x00FF));
	LCD_WriteData((y2&0xFF00)>>8);
	LCD_WriteData((y2&0x00FF));
}
void LCD_FillArea(uint16_t color, uint32_t pixels) {
	if(pixels > 0x13000) return;
	LCD_WriteCommand(LCD_GRAM);

	LCD_EnableDataWrite();
	LCD_SetDataValue(color);

	for(uint32_t i = 0; i < pixels; i++) LCD_Write();

	LCD_DisableWrite();
}

void LCD_WriteReg(uint16_t RegValue, bool command) {
	if(TFT_busy==1){
		//Si llega a este punto ocurrio un error en el ciclo de escritura debido al FreeRTOS
		return;
	}
	TFT_busy=1;
	if(command) LCD_EnableCommandWrite();
	else		LCD_EnableDataWrite();

	LCD_SetDataValue(RegValue);

	LCD_DisableWrite();
	TFT_busy=0;
}
void LCD_WriteCommand(uint8_t RegValue) {
	LCD_WriteReg(RegValue & 0xFF, true);
}
void LCD_WriteData(uint16_t RegValue) {
	LCD_WriteReg(RegValue & 0xFFFF, false);
}

uint16_t LCD_GetLcdPixelWidth(void) {
	if(_orientacion == PORTRAIT)
		return LCD_PIXEL_WIDTH;
	else
		return LCD_PIXEL_HEIGHT;
}
uint16_t LCD_GetLcdPixelHeight(void) {
	if(_orientacion == LANDSCAPE)
		return LCD_PIXEL_WIDTH;
	else
		return LCD_PIXEL_HEIGHT;
}

void LCD_SetColor(uint16_t hex) {
	_color = hex;
}
void LCD_SetColorRGB(uint16_t r, uint16_t g, uint16_t b) {
	_color = LCD_GetHexFromRGB(r, g, b);
}
uint16_t LCD_GetHexFromRGB(uint16_t r, uint16_t g, uint16_t b) {
	return ((g & 28) << 3 | b >> 3) | ((r & 248) | g >> 5) << 8;
}
void LCD_SetBorderWidth(uint8_t width) {
	if(width == 0) width = 1;
	_borderWidth = width - 1;
}

void LCD_DrawPixel(uint16_t x, uint16_t y) {
	uint16_t border = _borderWidth;
	_borderWidth = 0;
	LCD_DrawPoint(x, y);
	_borderWidth = border;
}
void LCD_DrawPoint(uint16_t x, uint16_t y) {
	uint16_t tmp_x1 = x;
	uint16_t tmp_y1 = y;
	uint16_t tmp_x2 = x + _borderWidth;
	uint16_t tmp_y2 = y + _borderWidth;

	LCD_SetArea(tmp_x1, tmp_y1, tmp_x2, tmp_y2);
	LCD_FillArea(_color, (((tmp_x2-tmp_x1)+1)*((tmp_y2-tmp_y1)+1)));
}
void LCD_DrawRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, bool fill) {
	uint16_t x1 = x;
	uint16_t y1 = y;
	uint16_t x2 = x + w - 1;
	uint16_t y2 = y + h - 1;

	if(fill) {
		LCD_SetArea(x1, y1, x2, y2);
		LCD_FillArea(_color, (((x2-x1)+1)*((y2-y1)+1)));
	} else {
		uint16_t tmp_x1 = 0;
		uint16_t tmp_y1 = 0;
		uint16_t tmp_x2 = 0;
		uint16_t tmp_y2 = 0;

		for(uint16_t i = y1; i <= y2 - _borderWidth; i++) {
			if(i == y1 || i == y2 - _borderWidth) {
				tmp_x1 = x1;
				tmp_y1 = i;
				tmp_x2 = x2;
				tmp_y2 = i + _borderWidth;

				LCD_SetArea(tmp_x1, tmp_y1, tmp_x2, tmp_y2);
				LCD_FillArea(_color, (((tmp_x2-tmp_x1)+1)*((tmp_y2-tmp_y1)+1)));
			} else {
				LCD_DrawPoint(x1, i);
				LCD_DrawPoint(x2 - _borderWidth, i);
			}
		}
	}
}
void LCD_DrawRectangleRadius(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t r, bool fill) {
	uint16_t x1 = x;
	uint16_t y1 = y;
	uint16_t x2 = x + w - 1;
	uint16_t y2 = y + h - 1;

	LCD_DrawRectangle(x + r, y, w - 2 * r, h, true);
	LCD_DrawRectangle(x, y + r, w, h - 2 * r, true);

	uint16_t cx = x1 + r - 1;
	uint16_t cy = y1 + r - 1;

	for(uint16_t x3 = cx - r; x3 < cx + 1; x3++) {
		for(uint16_t y3 = cy - r; y3 < cy + 1; y3++) {
			if(pow(x3 - cx, 2) + pow(y3 - cy, 2) <= pow(r, 2))
				if (x3 >= x && x3 <= x + w - 1 && y3 >= y && y3 <= y + h - 1) LCD_DrawPixel(x3, y3);
		}
	}

	cx = x2 - r + 1;
	cy = y1 + r - 1;

	for(uint16_t x3 = cx - 1; x3 < cx + r; x3++) {
		for(uint16_t y3 = cy - r; y3 < cy + 1; y3++) {
			if(pow(x3 - cx, 2) + pow(y3 - cy, 2) <= pow(r, 2))
				if (x3 >= x && x3 <= x + w - 1 && y3 >= y && y3 <= y + h - 1) LCD_DrawPixel(x3, y3);
		}
	}

	cx = x1 + r - 1;
	cy = y2 - r + 1;

	for(uint16_t x3 = cx - r; x3 < cx + 1; x3++) {
		for(uint16_t y3 = cy - 1; y3 < cy + r; y3++) {
			if(pow(x3 - cx, 2) + pow(y3 - cy, 2) <= pow(r, 2))
				if (x3 >= x && x3 <= x + w - 1 && y3 >= y && y3 <= y + h - 1) LCD_DrawPixel(x3, y3);
		}
	}

	cx = x2 - r + 1;
	cy = y2 - r + 1;

	for(uint16_t x3 = cx - 1; x3 < cx + r; x3++) {
		for(uint16_t y3 = cy - 1; y3 < cy + r; y3++) {
			if(pow(x3 - cx, 2) + pow(y3 - cy, 2) <= pow(r, 2))
				if (x3 >= x && x3 <= x + w - 1 && y3 >= y && y3 <= y + h - 1) LCD_DrawPixel(x3, y3);
		}
	}
}
void LCD_DrawCircle(uint16_t cx, uint16_t cy, uint16_t r) {
	for(uint16_t x = cx - r; x < cx + r; x++) {
		for(uint16_t y = cy - r; y < cy + r; y++) {
			if(pow(x - cx, 2) + pow(y - cy, 2) <= pow(r, 2)) LCD_DrawPixel(x, y);
		}
	}
}
void LCD_DrawChar(uint16_t x, uint16_t y, char c, uint8_t font_size) {
	extern char smallFonts[95][12];
	extern char largeFonts[95][32];

	if(c < 32 || c > 126) return;

	char *letra;
	uint8_t font_width = 0;
	uint8_t font_heigth = 0;

	switch(font_size) {
		case LCD_FONT_SIZE_SMALL:
			letra = smallFonts[c-32];
			font_width = 8;
			font_heigth = 12;
			break;
		case LCD_FONT_SIZE_LARGE:
			letra = largeFonts[c-32];
			font_width = 16;
			font_heigth = 16;
			break;
		default:
			letra = smallFonts[c-32];
			font_width = 8;
			font_heigth = 12;
			break;
	}

	for(uint8_t i = 0; i < font_width; i++) {
		for(uint8_t j = 0; j < font_heigth; j++) {
			uint16_t letra_nueva = 0;
			switch(font_size) {
				case LCD_FONT_SIZE_SMALL:
					letra_nueva = letra[j];
					break;
				case LCD_FONT_SIZE_LARGE:
					letra_nueva = (letra[j*2] << 8) | letra[j*2+1];
					break;
				default:
					letra_nueva = letra[j];
					break;
			}
			if((letra_nueva >> ((font_width - 1) - i)) & 0x01) {
				if(
						x + i >= 0 &&
						x + i < LCD_GetLcdPixelWidth() &&
						y + j >= 0 &&
						y + j < LCD_GetLcdPixelHeight()
				) LCD_DrawPixel(x + i, y + j);
			}
		}
	}
}
void LCD_DrawText(uint16_t x, uint16_t y, char *str, uint8_t font_size) {
	uint8_t font_width = 0;

	switch(font_size) {
		case LCD_FONT_SIZE_SMALL:
			font_width = 8;
			break;
		case LCD_FONT_SIZE_LARGE:
			font_width = 16;
			break;
		default:
			font_width = 8;
			break;
	}

	uint16_t len = strlen(str);
	for(uint16_t i = 0; i < len; i++) {
		if(str[i] == 0x0) break;
		LCD_DrawChar(x + (i * (font_width - 1)), y, str[i], font_size);
	}
}

void LCD_DrawSevenSeg(uint16_t x, uint16_t y, uint8_t number, bool dot) {
	LCD_ClearArea(x, y, 40, 80);

	//0
	if(number == 0 || number == 4 || number == 5 || number == 6 || number == 8 || number == 9) {
		LCD_DrawRectangle(x+5,y+15,6,20,true);
	}

	//1
	if(number == 0 || number == 2 || number == 3 || number == 5 || number == 6 || number == 7 || number == 8 || number == 9) {
		LCD_DrawRectangle(x+10,y+5,20,6,true);
	}

	//2
	if(number == 0 || number == 1 || number == 2 || number == 3 || number == 4 || number == 7 || number == 8 || number == 9) {
		LCD_DrawRectangle(x+29,y+15,6,20,true);
	}

	//3
	if(number == 0 || number == 1 || number == 3 || number == 4 || number == 5 || number == 6 || number == 7 || number == 8 || number == 9) {
		LCD_DrawRectangle(x+29,y+45,6,20,true);
	}

	//4
	if(number == 0 || number == 2 || number == 3 || number == 5 || number == 6 || number == 8 || number == 9) {
		LCD_DrawRectangle(x+10,y+69,20,6,true);
	}

	//5
	if(number == 0 || number == 2 || number == 6 || number == 8) {
		LCD_DrawRectangle(x+5,y+45,6,20,true);
	}

	//6
	if(number == 2 || number == 3 || number == 4 || number == 5 || number == 6 || number == 8 || number == 9) {
		LCD_DrawRectangle(x+10,y+37,20,6,true);
	}

	if(dot) {
		LCD_DrawRectangle(x+35,y+67,6,6,true);
	}
}
void LCD_DrawSignal(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t data[], uint16_t bg_color, uint16_t s_color) {
	uint32_t pixels = (uint32_t)w * (uint32_t)h;
	if(pixels > 0x13000) return;

	LCD_SetArea(x, y, w, h);

	LCD_WriteCommand(LCD_GRAM);

	uint16_t bkp_color = _color;

	LCD_EnableDataWrite();

	for(uint32_t i = 0; i < pixels; i++) {
		uint16_t x = i / w;
		uint16_t y = i % w;

		uint16_t val = h - x;

		if(val == data[y]) {
			LCD_SetDataValue(s_color);
			LCD_Write();
		} else {
			LCD_SetDataValue(bg_color);
			LCD_Write();
		}
	}

	LCD_DisableWrite();
	_color = bkp_color;
}

void LCD_ClearArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
	uint32_t bkp_color = _color;
	LCD_SetColor(0x0);
	LCD_DrawRectangle(x, y, w, h, true);
	LCD_SetColor(bkp_color);
}
