/*-----------------------------------------------------
Description: 
1. SPI1
	- NSS: 	PA4
	- CLK: 	PA5
	- MISO: PA6
	- MOSI: PA7
2. External interrupt EXTI0: PB0
3. Project using ADE7758 to calculate, calibrate 
	 and display the voltage, active power, reactive power, active energy (kWhr)
-----------------------------------------------------*/
#include "main.h"
																			
void General_Configuration(void);

uint8_t get_data;
int main(void)
{
//	uint32_t voltage, I_rms_test_1[3], I_rms_test_2[3], V_rms_test_1[3], V_rms_test_2[3];
//	uint16_t V_rmsos_value, I_rmsos_value;
	
	General_Configuration();
//	LCD_Init(); 
//	NVIC_EXTI_Enable();
	
//	/***These following functions used when RMS offset calibrating ********/
//	/******* Stage 0: Init ******/
//	ADE7758_RMS_Offset_Calib_Init();
//	/******* Stage 1: Set up test condition number 1: V_nom and I_test *******/
//	ADE7758_RMS_Offset_Calibration(PHASE_A);
//	I_rms_test_1[PHASE_A] = Irms_avg;
//	V_rms_test_1[PHASE_A] = Vrms_avg;
//	
//	ADE7758_RMS_Offset_Calibration(PHASE_B);
//	I_rms_test_1[PHASE_B] = Irms_avg;
//	V_rms_test_1[PHASE_B] = Vrms_avg;
//	
//	ADE7758_RMS_Offset_Calibration(PHASE_C);
//	I_rms_test_1[PHASE_C] = Irms_avg;
//	V_rms_test_1[PHASE_C] = Vrms_avg;
//	
//	/******** Stage 2: Set up test condition number 2: V_full scale / 20 and I_full scale / 500 */
//	ADE7758_RMS_Offset_Calibration(PHASE_A);
//	I_rms_test_2[PHASE_A] = Irms_avg;
//	V_rms_test_2[PHASE_A] = Vrms_avg;
//	
//	ADE7758_RMS_Offset_Calibration(PHASE_B);
//	I_rms_test_2[PHASE_B] = Irms_avg;
//	V_rms_test_2[PHASE_B] = Vrms_avg;
//	
//	ADE7758_RMS_Offset_Calibration(PHASE_C);
//	I_rms_test_2[PHASE_C] = Irms_avg;
//	V_rms_test_2[PHASE_C] = Vrms_avg;
//	
//	/********** Stage 3:**********************************************/
//				/*
//					Sub - routine to store 12 values I_rms_test_1,2[phase] and V_rms_test_1,2[phase] into FLASH,
//				  using it to write to calculate xVRMSOS and xIRMSOS registers 
//				*/
//      Following these equations to get 6 offset value: xVRMSOS, xIRMSOS. Store these 6 values into FLASH.
//				/*
//					Sub - routine to store 6 values xVRMSOS and xIRMSOS registers 
//				*/
//      Use these 6 values in FLASH to write in 6 OFFSET register before calculating,
//			then add OFFSET register following equation:
//				xIRMS = sqrt(xIRMS^2 + 16384 * xIRMSOS)
//				xVRMS = xVRMS + 64 * xVRMSOS */

//        /*
//					Sub - routine to store the conversion ratio	to FLASH, 
//					using it to get the real - world values of voltage and current
//				*/
// /*****************************END OF RMS OFFSET CALIBRATION***************************************/
/*---------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------*/
//	/**********These following functions using when Gain calibration using Line Accmulation**********/
//	/******* Stage 0: Init ******/
//	ADE7758_Gain_Calib_Init(); 
//	/******* Stage 1: Set up test condition number 1: V_nom, I_test, cosphi = 1 to get Wh/LSB *******/
//	ADE7758_Gain_Calib(PHASE_A);
//	/*
//		Sub - routine to store the Wh/LSB of phase A to FLASH
//		using it to calculate the real - world value later
//	*/	
//	ADE7758_Gain_Calib(PHASE_B);
//	/*
//		Sub - routine to store the Wh/LSB of phase B to FLASH
//		using it to calculate the real - world value later
//	*/	
//		ADE7758_Gain_Calib(PHASE_C);
//	/*
//		Sub - routine to store the Wh/LSB of phase C to FLASH
//		using it to calculate the real - world value later
//	*/	
//	/******* Stage 2: Set up test condition number 1: V_nom, I_test, cosphi = 0 (inductive load) to get Varh/LSB *******/
//	ADE7758_Gain_Calib(PHASE_A);
//	/*
//		Sub - routine to store the Varh/LSB of phase A to FLASH
//		using it to calculate the real - world value later
//	*/	
//	ADE7758_Gain_Calib(PHASE_B);
//	/*
//		Sub - routine to store the Varh/LSB of phase B to FLASH
//		using it to calculate the real - world value later
//	*/	
//		ADE7758_Gain_Calib(PHASE_C);
//	/*
//		Sub - routine to store the Varh/LSB of phase C to FLASH
//		using it to calculate the real - world value later
//	*/	
//	/*****************************END OF GAIN CALIBRATION***********************************************/
	while (1)
	{
//		ADE7758_Write_8bit(OPMODE, 7); 
		get_data = ADE7758_Read_8bit(OPMODE);
//		GPIO_WriteBit(ON_BOARD_LED_PORT, ON_BOARD_LED_PIN, led_val ? Bit_SET : Bit_RESET); 
//		led_val = 1 - led_val;
//		SystemTick_Delay_ms(1000); 
	}
}

void General_Configuration(void)
{
	Clock_Configuration();
	GPIO_Configuration();
	SystemTick_Timer_Init(); 
	SPI_Configuration(SPI_Mode_Master); 
//	EXTI0_Configuration();
//	NVIC_Configuration();
}	
