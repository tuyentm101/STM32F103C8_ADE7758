#ifndef _USER_STM32F1XX_LCD_TEXT_H_
#define _USER_STM32F1XX_LCD_TEXT_H_  
#include "user_stm32f1xx_gpio.h"
#include "user_stm32f1xx_SysTick.h"
/*----------------------------------------------------------------------------*/
#define LCD_CMD_CLR					        						 0x01
#define LCD_CMD_RETURN_HOME			    						 0x02
#define LCD_CMD_DEC_CURSOR											 0x04
#define LCD_CMD_INC_CURSOR											 0x06
#define LCD_CMD_ENTRY_MODE_SET		  						 0x06		/* I/D = 1 : Increment, S = 0: no shift display*/
#define LCD_CMD_DISPLAY_OFF_CTRL_NO_BLINK   	   0x0C   /* on display, off cursor, no blink */
#define LCD_CMD_DISPLAY_ON_CTRL_NO_BLINK 				 0x0E		/* on display, on cursor, no blink */
#define LCD_CMD_DISPLAY_OFF_CTRL_BLINK   	   		 0x0D 	/* on display, off cursor, blink */
#define LCD_CMD_DISPLAY_ON_CTRL_BLINK 				   0x0F		/* on display, on cursor, blink */
#define LCD_CMD_CURSOR_SHIFT_LEFT								 0x10
#define LCD_CMD_CURSOR_SHIFT_RIGHT							 0x14
#define LCD_CMD_DISPLAY_SHIFT_LEFT							 0x18
#define LCD_CMD_DISPLAY_SHIFT_RIGHT							 0x1C
#define LCD_CMD_ADD_L1_HOME				 						   0x80
#define LCD_CMD_ADD_L2_HOME				 							 0xC0
#define LCD_CMD_8BIT_FONT5X8_2LINE	 						 0x38
#define LCD_CMD_4BIT_FONT5X8_2LINE	 						 0x28
#define LCD_TYPE_CMD						 		 0
#define LCD_TYPE_DATA						     1
/*----------------------------------------------------------------------------*/
void LCD_Init(void);
void LCD_Write_Char(uint8_t ch);
void LCD_Write_String(uint8_t* text);
void LCD_Write_Decimal_Number(uint32_t num_int);
void LCD_Clear(void);
void LCD_GotoXY(uint8_t x, uint8_t y);

#endif
