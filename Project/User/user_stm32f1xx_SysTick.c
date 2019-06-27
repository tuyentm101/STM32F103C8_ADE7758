#include "user_stm32f1xx_SysTick.h"

volatile uint32_t Us_Ticks;
/* 
	Setup SysTick Timer for 1 Usec interrupts
	- Reload Value is the parameter to be passed for SysTick_Config() function
		Reload Value = SysTick Counter Clock (Hz) x  Desired Time base (s)  
	- Initialise value of timer interval and start System Tick Timer 
	- Interruption occurs between two microseconds
	- Note: Formula using clock frequency is AHB, not AHB / 8
*/
void SystemTick_Timer_Init(void)
{
	if (SysTick_Config(SystemCoreClock / 1000000)) //72 is numer of pulses at frequency of 72 MHz to create interval of 1 Us
		while (1);
}
void SystemTick_Delay_Us(volatile uint32_t nTime_Us)
{
	Us_Ticks = nTime_Us;
	while (Us_Ticks != 0);
}
void SystemTick_Delay_ms(uint32_t nTime_ms)
{
	uint32_t i;
	for (i = 0; i < nTime_ms; i++)
		SystemTick_Delay_Us(1000);
}
void TimingDelay_Decrement(void)
{
	if (Us_Ticks != 0)
		Us_Ticks--;
}
