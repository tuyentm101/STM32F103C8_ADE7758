#ifndef _USER_STM32F1XX_GPIO_H_
#define _USER_STM32F1XX_GPIO_H_ 
#include "stm32f10x_conf.h"   
#include "user_stm32f1xx_spi.h"
#include "user_stm32f1xx_lcd_text.h"
#include "lcd5110.h"
/*----------------------------------------------------------------------------*/
#define GPIO_PORT_A									GPIOA								// GPIO port = A													
#define GPIO_PORT_C 								GPIOC								// GPIO port = C
#define GPIO_PORT_B	 								GPIOB								// GPIO port = B		
#define ON_BOARD_LED_PORT						GPIOC		
#define USER_LED_PORT								GPIOB
#define USER_BUTTON_PORT						GPIOB
#define LCD_DATA_PIN								LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7	
#define LCD_CTRL_PIN								LCD_EN | LCD_RS
#define USER_LED_PIN								GPIO_Pin_7
#define ON_BOARD_LED_PIN						GPIO_Pin_13	
#define USER_BUTTON_PIN							GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6
#define GPIO_MODE_ALTERNATE_FUNCTION_PUSH_PULL										  GPIO_Mode_AF_PP				
#define GPIO_MODE_OUTPUT_PUSH_PULL												          GPIO_Mode_Out_PP
#define GPIO_MODE_INPUT_FLOATING																	  GPIO_Mode_IN_FLOATING
#define GPIO_MODE_INPUT_PULL_UP																			GPIO_Mode_IPU
#define GPIO_MODE_INPUT_PULL_DOWN																		GPIO_Mode_IPD 
#define GPIO_SPEED_USER																							GPIO_Speed_50MHz	
/*----------------------------------------------------------------------------*/
void GPIO_Configuration(void);
void GPIO_SPI_Configuration(uint16_t SPI_mode);
void GPIO_EXTI0_Configuration(void);
#endif
