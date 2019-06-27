#include "user_stm32f1xx_clock.h"

void System_Clock_Configuration(void)
{
	/*-----------PLL source selection is PLL and Muliplier---------
	PLL source = HSE div 1 = 8MHz
	Mul				 = 8
	=> PLL clock = 64MHz
	--------------------------------------------------------*/
	RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_8);
	
	/*-------------System core clock selection--------------------------*/
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
}
void AHB_Clock_Configuration(void)
{
	/*-----------AHB speed-------------------*/
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
}
void APB2_Clock_Configuration(void)
{
	/*-----------APB2 speed--------------------*/
	RCC_PCLK2Config(RCC_HCLK_Div16);
}
void Clock_Configuration(void)
{
	APB2_Clock_Configuration(); 

	RCC_APB2PeriphClockCmd(RCC_APB2_PERIPH_ACTIVE, ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1_PERIPH_ACTIVE, ENABLE);
}
