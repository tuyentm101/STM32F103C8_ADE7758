#ifndef _LCD5110_H_
#define _LCD5110_H_
/* Includes ------------------------------------------------------------------*/
#include "user_stm32f1xx_spi.h"
#include "user_stm32f1xx_SysTick.h"
/* Exported constants --------------------------------------------------------*/
#define LCD_DATA_PORT			GPIOA
#define LCD_CTRL_PORT		  GPIOB
#define LCD_RS				GPIO_Pin_14		//RS Pin: PB14
#define LCD_EN				GPIO_Pin_15		//EN Pin: PB15
#define LCD_D4				GPIO_Pin_9		// D4 Pin: PA9
#define LCD_D5				GPIO_Pin_10		// D5 Pin: PA10
#define LCD_D6				GPIO_Pin_11		// D6 Pin: PA11
#define LCD_D7				GPIO_Pin_12    // D7 Pin: PA12
#define LCD5110_PORT    GPIOA
#define RST_PIN         GPIO_Pin_2
#define CE_PIN          SPIy_PIN_NSS
#define DC_PIN          GPIO_Pin_3
#define DIN_PIN         SPIy_PIN_MOSI
#define CLK_PIN         SPIy_PIN_SCK
#define LCD5110_CMD     0       /* DC = 0 bits nhan duoc la command*/
#define LCD5110_DATA    1      /* DC =1 bits nhan duoc la data */
#define LCD_X     84
#define LCD_Y     48
/* Exported macro ------------------------------------------------------------*/
#define EnableLCD		GPIO_ResetBits(LCD5110_PORT, CE_PIN)
#define DisableLCD		GPIO_SetBits(LCD5110_PORT, CE_PIN)
/* Exported function ------------------------------------------------------------*/
void LCD5110_ShiftOut(uint8_t TxData);
void LCD5110_Write(uint8_t DC, uint8_t Data_Transfer);
void LCD5110_GotoXY(uint8_t x,uint8_t y);  //x:0->5  y:0->83
void LCD5110_Clr(void);
void LCD5110_write_char(uint8_t c);
void LCD5110_write_sring(uint8_t *str);
void LCD5110_Bitmap(unsigned char arr[]);
void LCD5110_Init(void);
//void error_program(void);

#endif
