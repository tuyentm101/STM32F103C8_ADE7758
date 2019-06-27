#ifndef _USER_STM32F1XX_SYSTICK_H_
#define _USER_STM32F1XX_SYSTICK_H_

#include "stm32f10x_conf.h" 

/****************************************/
void SystemTick_Timer_Init(void);
void SystemTick_Delay_ms(uint32_t nTime_ms);
void SystemTick_Delay_Us(volatile uint32_t nTime_Us);
void TimingDelay_Decrement(void);
/****************************************/
#endif
