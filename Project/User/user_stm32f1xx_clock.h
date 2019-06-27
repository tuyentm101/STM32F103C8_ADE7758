#ifndef _USER_STM32F1XX_CLOCK_H_
#define _USER_STM32F1XX_CLOCK_H_
#include "stm32f10x_conf.h"   
#include "user_stm32f1xx_spi.h"
/*----------------------------------------------------------------------------*/
#define RCC_APB2_PERIPH_ACTIVE		RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB | SPIy_GPIO_CLK | SPIy_CLK | RCC_APB2Periph_AFIO
#define RCC_APB1_PERIPH_ACTIVE		RCC_APB1Periph_TIM2
/*----------------------------------------------------------------------------*/
void Clock_Configuration(void);
#endif
