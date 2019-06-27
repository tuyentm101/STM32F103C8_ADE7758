#include "user_stm32f1xx_exti.h"

EXTI_InitTypeDef   EXTI_InitStructure;
NVIC_InitTypeDef   NVIC_InitStructure;

void EXTI0_Configuration(void)
{
	GPIO_EXTI0_Configuration();
	
	/* Clears the EXTI line 0 interrupt pending bit */
	EXTI_ClearITPendingBit(EXTI_Line0);
	
  /* Configure EXTI0 line */
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}
void NVIC_Configuration(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	/* Enable and set EXTI0 Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;					//Interrupt vector
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
  NVIC_Init(&NVIC_InitStructure);
}	
void NVIC_EXTI_Enable(void)
{
	NVIC_EnableIRQ(EXTI0_IRQn);
}
void NVIC_EXTI_Disable(void)
{
	NVIC_DisableIRQ(EXTI0_IRQn);
}
