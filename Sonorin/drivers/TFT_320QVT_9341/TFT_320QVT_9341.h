#include "chip.h"
#include "TFT_PIN_CONNECTION.h"
#include "FW_Timer.h"
#include "string.h"
#include "math.h"

#define LCD_ID                  0x9341

#define LCD_PIXEL_WIDTH    		240
#define LCD_PIXEL_HEIGHT   		320

#define LCD_HSYNC            	((uint32_t)9)   /* Horizontal synchronization */
#define LCD_HBP              	((uint32_t)29)    /* Horizontal back porch      */
#define LCD_HFP              	((uint32_t)2)    /* Horizontal front porch     */
#define LCD_VSYNC            	((uint32_t)1)   /* Vertical synchronization   */
#define LCD_VBP              	((uint32_t)3)    /* Vertical back porch        */
#define LCD_VFP              	((uint32_t)2)    /* Vertical front porch       */

#define LCD_SWRESET             0x01   /* Software Reset */
#define LCD_READ_DISPLAY_ID     0x04   /* Read display identification information */
#define LCD_RDDST               0x09   /* Read Display Status */
#define LCD_RDDPM               0x0A   /* Read Display Power Mode */
#define LCD_RDDMADCTL           0x0B   /* Read Display MADCTL */
#define LCD_RDDCOLMOD           0x0C   /* Read Display Pixel Format */
#define LCD_RDDIM               0x0D   /* Read Display Image Format */
#define LCD_RDDSM               0x0E   /* Read Display Signal Mode */
#define LCD_RDDSDR              0x0F   /* Read Display Self-Diagnostic Result */
#define LCD_SPLIN               0x10   /* Enter Sleep Mode */
#define LCD_SLEEP_OUT           0x11   /* Sleep out register */
#define LCD_PTLON               0x12   /* Partial Mode ON */
#define LCD_NORMAL_MODE_ON      0x13   /* Normal Display Mode ON */
#define LCD_DINVOFF             0x20   /* Display Inversion OFF */
#define LCD_DINVON              0x21   /* Display Inversion ON */
#define LCD_GAMMA               0x26   /* Gamma register */
#define LCD_DISPLAY_OFF         0x28   /* Display off register */
#define LCD_DISPLAY_ON          0x29   /* Display on register */
#define LCD_COLUMN_ADDR         0x2A   /* Colomn address register */
#define LCD_PAGE_ADDR           0x2B   /* Page address register */
#define LCD_GRAM                0x2C   /* GRAM register */
#define LCD_RGBSET              0x2D   /* Color SET */
#define LCD_RAMRD               0x2E   /* Memory Read */
#define LCD_PLTAR               0x30   /* Partial Area */
#define LCD_VSCRDEF             0x33   /* Vertical Scrolling Definition */
#define LCD_TEOFF               0x34   /* Tearing Effect Line OFF */
#define LCD_TEON                0x35   /* Tearing Effect Line ON */
#define LCD_MAC                 0x36   /* Memory Access Control register*/
#define LCD_VSCRSADD            0x37   /* Vertical Scrolling Start Address */
#define LCD_IDMOFF              0x38   /* Idle Mode OFF */
#define LCD_IDMON               0x39   /* Idle Mode ON */
#define LCD_PIXEL_FORMAT        0x3A   /* Pixel Format register */
#define LCD_WRITE_MEM_CONTINUE  0x3C   /* Write Memory Continue */
#define LCD_READ_MEM_CONTINUE   0x3E   /* Read Memory Continue */
#define LCD_SET_TEAR_SCANLINE   0x44   /* Set Tear Scanline */
#define LCD_GET_SCANLINE        0x45   /* Get Scanline */
#define LCD_WDB                 0x51   /* Write Brightness Display register */
#define LCD_RDDISBV             0x52   /* Read Display Brightness */
#define LCD_WCD                 0x53   /* Write Control Display register*/
#define LCD_RDCTRLD             0x54   /* Read CTRL Display */
#define LCD_WRCABC              0x55   /* Write Content Adaptive Brightness Control */
#define LCD_RDCABC              0x56   /* Read Content Adaptive Brightness Control */
#define LCD_WRITE_CABC          0x5E   /* Write CABC Minimum Brightness */
#define LCD_READ_CABC           0x5F   /* Read CABC Minimum Brightness */
#define LCD_READ_ID1            0xDA   /* Read ID1 */
#define LCD_READ_ID2            0xDB   /* Read ID2 */
#define LCD_READ_ID3            0xDC   /* Read ID3 */

#define LCD_RGB_INTERFACE       0xB0   /* RGB Interface Signal Control */
#define LCD_FRMCTR1             0xB1   /* Frame Rate Control (In Normal Mode) */
#define LCD_FRMCTR2             0xB2   /* Frame Rate Control (In Idle Mode) */
#define LCD_FRMCTR3             0xB3   /* Frame Rate Control (In Partial Mode) */
#define LCD_INVTR               0xB4   /* Display Inversion Control */
#define LCD_BPC                 0xB5   /* Blanking Porch Control register */
#define LCD_DFC                 0xB6   /* Display Function Control register */
#define LCD_ETMOD               0xB7   /* Entry Mode Set */
#define LCD_BACKLIGHT1          0xB8   /* Backlight Control 1 */
#define LCD_BACKLIGHT2          0xB9   /* Backlight Control 2 */
#define LCD_BACKLIGHT3          0xBA   /* Backlight Control 3 */
#define LCD_BACKLIGHT4          0xBB   /* Backlight Control 4 */
#define LCD_BACKLIGHT5          0xBC   /* Backlight Control 5 */
#define LCD_BACKLIGHT7          0xBE   /* Backlight Control 7 */
#define LCD_BACKLIGHT8          0xBF   /* Backlight Control 8 */
#define LCD_POWER1              0xC0   /* Power Control 1 register */
#define LCD_POWER2              0xC1   /* Power Control 2 register */
#define LCD_VCOM1               0xC5   /* VCOM Control 1 register */
#define LCD_VCOM2               0xC7   /* VCOM Control 2 register */
#define LCD_NVMWR               0xD0   /* NV Memory Write */
#define LCD_NVMPKEY             0xD1   /* NV Memory Protection Key */
#define LCD_RDNVM               0xD2   /* NV Memory Status Read */
#define LCD_READ_ID4            0xD3   /* Read ID4 */
#define LCD_PGAMMA              0xE0   /* Positive Gamma Correction register */
#define LCD_NGAMMA              0xE1   /* Negative Gamma Correction register */
#define LCD_DGAMCTRL1           0xE2   /* Digital Gamma Control 1 */
#define LCD_DGAMCTRL2           0xE3   /* Digital Gamma Control 2 */
#define LCD_INTERFACE           0xF6   /* Interface control register */

#define LCD_POWERA              0xCB   /* Power control A register */
#define LCD_POWERB              0xCF   /* Power control B register */
#define LCD_DTCA                0xE8   /* Driver timing control A */
#define LCD_DTCB                0xEA   /* Driver timing control B */
#define LCD_POWER_SEQ           0xED   /* Power on sequence register */
#define LCD_3GAMMA_EN           0xF2   /* 3 Gamma enable register */
#define LCD_PRC                 0xF7   /* Pump ratio control register */

#define LCD_READ_ID4_SIZE       3      /* Size of Read ID4 */

#define PORTRAIT 0
#define LANDSCAPE 1

#define LCD_DATA_DIR			0
#define LCD_DATA_DIR_OUTPUT		1
#define LCD_DATA_DIR_INPUT		2

#define LCD_FONT_SIZE_SMALL		0
#define LCD_FONT_SIZE_MEDIUM	1
#define LCD_FONT_SIZE_LARGE		2

void LCD_Init_IO_Pins(void);
void LCD_Reset(void);
void LCD_SetDataDir(uint8_t dir);
void LCD_EnableDataWrite(void);
void LCD_EnableCommandWrite(void);
void LCD_DisableWrite(void);
void LCD_Write(void);
void LCD_SetDataValue(uint16_t data);

void LCD_Init(void);
void LCD_DisplayOn(void);
void LCD_DisplayOff(void);
void LCD_ClearScr(void);
void LCD_SetArea(int x1, int y1, int x2, int y2);
void LCD_FillArea(uint16_t color, uint32_t pixels);

void LCD_WriteReg(uint16_t RegValue, bool command);
void LCD_WriteCommand(uint8_t RegValue);
void LCD_WriteData(uint16_t RegValue);

uint16_t LCD_GetLcdPixelWidth(void);
uint16_t LCD_GetLcdPixelHeight(void);

void LCD_SetColor(uint16_t hex);
void LCD_SetColorRGB(uint16_t r, uint16_t g, uint16_t b);
uint16_t LCD_GetHexFromRGB(uint16_t r, uint16_t g, uint16_t b);
void LCD_SetBorderWidth(uint8_t width);

void LCD_DrawPixel(uint16_t x, uint16_t y);
void LCD_DrawPoint(uint16_t x, uint16_t y);
void LCD_DrawRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, bool fill);
void LCD_DrawRectangleRadius(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t r, bool fill);
void LCD_DrawCircle(uint16_t cx, uint16_t cy, uint16_t r);
void LCD_DrawChar(uint16_t x, uint16_t y, char c, uint8_t font_size);
void LCD_DrawText(uint16_t x, uint16_t y, char *str, uint8_t font_size);
void LCD_DrawSevenSeg(uint16_t x, uint16_t y, uint8_t number, bool dot);
void LCD_DrawSignal(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t data[], uint16_t bg_color, uint16_t s_color);

void LCD_ClearArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
