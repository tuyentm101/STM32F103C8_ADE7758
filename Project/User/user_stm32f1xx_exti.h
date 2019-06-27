#ifndef _USER_STM32F1XX_EXTI_H_
#define _USER_STM32F1XX_EXTI_H_
/*----------------------------------------*/
#include "stm32f10x_conf.h"   
#include "user_stm32f1xx_gpio.h"

void EXTI0_Configuration(void);
void NVIC_Configuration(void);
void NVIC_EXTI_Enable(void);
void NVIC_EXTI_Disable(void);
#endif
