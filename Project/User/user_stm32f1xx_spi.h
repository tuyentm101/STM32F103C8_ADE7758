#ifndef _USER_STM32F1XX_SPI_H_
#define _USER_STM32F1XX_SPI_H_
#include "stm32f10x_conf.h"   
#include "user_stm32f1xx_gpio.h"
/*----------------------------------------------------------------------------*/
#define SPIy                   SPI1   
#define SPIy_CLK               RCC_APB2Periph_SPI1
#define SPIy_GPIO              GPIOA
#define SPIy_GPIO_CLK          RCC_APB2Periph_GPIOA  
#define SPIy_PIN_NSS					 GPIO_Pin_4
#define SPIy_PIN_SCK           GPIO_Pin_5
#define SPIy_PIN_MISO          GPIO_Pin_6
#define SPIy_PIN_MOSI          GPIO_Pin_7	
#define SPI_DUMMY_BYTE 0x00
#define EnableChip							GPIO_ResetBits(SPIy_GPIO, SPIy_PIN_NSS)
#define DisableChip							GPIO_SetBits(SPIy_GPIO, SPIy_PIN_NSS)
/*-----------------------------------------*/
void SPI_Configuration(uint16_t SPI_mode);
void SPI_LCD5110_Configuration(void);
uint8_t SPI_WriteByte(uint8_t Data);
uint16_t SPI_Write2Byte(uint16_t Data);
uint8_t SPI_ReadByte(void);
void SPI_Send_Byte(uint8_t Data);
#endif
