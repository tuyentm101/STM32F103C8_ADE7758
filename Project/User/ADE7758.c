#include "ADE7758.h"

volatile uint32_t get_data_v[100],get_data_i[100],v_data[3], i_data[3],watthr[3],varhr[3], vahr[3];
uint32_t Vrms_avg = 0, Irms_avg = 0;
uint8_t calib_flag = 0, phase_flag;
volatile uint8_t k, check;
float wh_lsb[3], varh_lsb[3], vah_lsb[3];

uint8_t ADE7758_Read_8bit(uint8_t add_reg)
{ 
	uint8_t rx_data;
	
	EnableChip;
	SPI_WriteByte(READ_CMD | add_reg);
	rx_data = SPI_ReadByte(); 
	DisableChip;
	
  return rx_data; 
}
uint16_t ADE7758_Read_16bit(uint8_t add_reg)
{
	uint16_t rx_data;
	
	EnableChip;
	SPI_WriteByte(READ_CMD | add_reg);
	rx_data = SPI_ReadByte();
	rx_data = (rx_data << 8) | SPI_ReadByte();
	DisableChip;
	
	return rx_data;
}
uint32_t ADE7758_Read_24bit(uint8_t add_reg)
{
	uint32_t rx_data;
	
	EnableChip;
	SPI_WriteByte(READ_CMD | add_reg);
	rx_data = SPI_ReadByte();
	rx_data =(rx_data << 16) | SPI_ReadByte();
	rx_data = (rx_data << 8) | SPI_ReadByte();
	DisableChip;
	
	return rx_data;
}	

void ADE7758_Write_8bit(uint8_t add_reg, uint8_t content)
{
	EnableChip;
	SPI_WriteByte(WRITE_CMD | add_reg);
	SPI_WriteByte(content);
	DisableChip;
}	

void ADE7758_Write_16bit(uint8_t add_reg, uint16_t content)
{
	EnableChip;
	SPI_WriteByte(WRITE_CMD | add_reg);
	SPI_Write2Byte(content);
	DisableChip;
}	

void ADE7758_Write_24bit(uint8_t add_reg, uint32_t content)
{
	EnableChip;
	SPI_WriteByte(WRITE_CMD | add_reg);
	
	/*--------Send 16 bit MSB----------*/
	SPI_Write2Byte((content & 0x00FFFF00) >> 8);
	/*--------Send 8 bit LSB----------*/
	SPI_WriteByte(content & 0x000000FF);
	DisableChip;
}	

uint32_t Vrms_Read(uint8_t phase)
{
	if (PHASE_A == phase)
		return ADE7758_Read_24bit(AVRMS); 
	if (PHASE_B == phase)
		return ADE7758_Read_24bit(BVRMS); 
	if (PHASE_C == phase)
		return ADE7758_Read_24bit(CVRMS); 
	return 0;
}
uint32_t Irms_Read(uint8_t phase)
{
	if (PHASE_A == phase)
		return ADE7758_Read_24bit(AIRMS); 
	if (PHASE_B == phase)
		return ADE7758_Read_24bit(BIRMS); 
	if (PHASE_C == phase)
		return ADE7758_Read_24bit(CIRMS); 
	return 0;
}
uint16_t Active_Pwr_Read(uint8_t phase)
{
	if (PHASE_A == phase)
		return ADE7758_Read_16bit(AWATTHR); 
	if (PHASE_B == phase)
		return ADE7758_Read_16bit(BWATTHR);  
	if (PHASE_C == phase)
		return ADE7758_Read_16bit(CWATTHR);  
	return 0;
}
uint16_t Reactive_Pwr_Read(uint8_t phase)
{
	if (PHASE_A == phase)
		return ADE7758_Read_16bit(AVARHR); 
	if (PHASE_B == phase)
		return ADE7758_Read_16bit(BVARHR);  
	if (PHASE_C == phase)
		return ADE7758_Read_16bit(CVARHR);  
	return 0;
}
uint16_t Apparent_Pwr_Read(uint8_t phase)
{
	if (PHASE_A == phase)
		return ADE7758_Read_16bit(AVAHR); 
	if (PHASE_B == phase)
		return ADE7758_Read_16bit(BVAHR);  
	if (PHASE_C == phase)
		return ADE7758_Read_16bit(CVAHR);  
	return 0;
}
void ADE7758_ZX_VI_Read(volatile uint32_t *data1,volatile uint32_t *data2, uint8_t phase)
{
	data1[phase] = Vrms_Read(phase);
	data2[phase] = Irms_Read(phase);
}
void ADE7758_ZX_Pwr_Read(volatile uint32_t *data1, volatile uint32_t *data2, volatile uint32_t *data3, uint8_t phase)
{
	data1[phase] = Active_Pwr_Read(phase);
	data2[phase] = Reactive_Pwr_Read(phase);
	data3[phase] = Apparent_Pwr_Read(phase);
}
void Get_Sequence_Data(uint8_t phase)
{
	if (k <= 50)
	{
		get_data_v[k] =  v_data[phase];
		get_data_i[k++] = i_data[phase]; 
	}
}	
/*
	Gain calibration using Line Accumulation
*/
void ADE7758_Gain_Calib_Init(void)
{
	/* Additional step: Set WDIV,VARDIV register*/
	ADE7758_Write_8bit(WDIV, 100); 				//divided by 100 before adding to WATTHR
	ADE7758_Write_8bit(VARDIV, 100); 			//divided by 100 before adding to VARHR
	/* Additional step: Set APCFDEN, APCFNUM register*/
	ADE7758_Write_16bit(APCFDEN, 277); 
	ADE7758_Write_16bit(APCFNUM, 1); 
	/* Step 1: Clear xWG, xVARG reigster*/
	ADE7758_Write_16bit(AWG,0); 
	ADE7758_Write_16bit(BWG,0);
	ADE7758_Write_16bit(CWG,0);
	ADE7758_Write_16bit(AVARG,0); 
	ADE7758_Write_16bit(BVARG,0);
	ADE7758_Write_16bit(CVAG,0);
	/* Step 2: Phase A selection for line period mesurement */
	ADE7758_Write_8bit(MMODE, 0xFC);
  /* Step 3: Set value for LCYCMODE register, set bit FREQSEL = LVA = LVAR = LWATT = 1 */	
	ADE7758_Write_8bit(LCYCMODE, 0x87);
	/* Step 4: Set number of zero - crossing*/
	ADE7758_Write_16bit(LINECYC,200); 	// 200 zero crossing times each phase
	/* Step 5: Set LENERGY bit = 1 */
	ADE7758_Write_24bit(MASK, 0x00001000); 
}
/*
	Test condition for Gain calibration I_test = 10 A, V_nom = 220V.
  Only one phase should be selected at a time in zero crossing during calibration
*/
void ADE7758_Gain_Calib(uint8_t phase)
{
	if (PHASE_A == phase)
	{
		phase_flag = phase;
		check = 0;
		ADE7758_Write_8bit(LCYCMODE, 0x8F); //Phasse A selected
		while (!check);											//waiting for LENERGY interrupt occured
		/****Step 1: Set value in APCFDEN reigster and APCFNUM register, done in init*/
		/****Step 2: Calculate value to write into xWG register and Accumulation Time*/
		/*
		Following equations: 
			WATTHR expected = (4*MC*I_test*V_nom*cosphi*AccumTime)/(1000*3600) = 44
			AccumTime = (LINECYC)/(2*line_frequency*Number of phase selected)
			xWG = (WATTHR expected / WATTHR - 1)*4096
		*/
		ADE7758_Write_16bit(AWG,(uint16_t)((44/watthr[PHASE_A] - 1)*4096)); 
		/*****Step 3: Calculate the Wh/LSB and store into FLASH*/
		/*
		Following equations:
			Wh/LSB = (I_test * V_nom * cosphi * AccumTime)/(3600 * WATTHR)
		*/
		wh_lsb[PHASE_A] =  (4400)/(3600*watthr[PHASE_A]);
	}
	if (PHASE_B == phase)
	{
		phase_flag = phase;
		check = 0;
		ADE7758_Write_8bit(LCYCMODE, 0x97); //Phasse B selected
		while (!check);											//waiting for LENERGY interrupt occured
		/****Step 1: Set value in APCFDEN reigster and APCFNUM register, done in init*/
		/****Step 2: Calculate value to write into xWG register and Accumulation Time*/
		/*
		Following equations: 
			WATTHR expected = (4*MC*I_test*V_nom*cosphi*AccumTime)/(1000*3600) = 44
			AccumTime = (LINECYC)/(2*line_frequency*Number of phase selected)
			xWG = (WATTHR expected / WATTHR - 1)*4096
		*/
		ADE7758_Write_16bit(BWG,(uint16_t)((44/watthr[PHASE_B] - 1)*4096)); 
		/*****Step 3: Calculate the Wh/LSB and store into FLASH*/
		/*
		Following equations:
			Wh/LSB = (I_test * V_nom * cosphi * AccumTime)/(3600 * WATTHR)
		*/
		wh_lsb[PHASE_B] =  (4400)/(3600*watthr[PHASE_B]);	
	}
	if (PHASE_C == phase)
	{
		phase_flag = phase;
		check = 0;
		ADE7758_Write_8bit(LCYCMODE, 0xA7); //Phasse C selected
		while (!check);											//waiting for LENERGY interrupt occured
		/****Step 1: Set value in APCFDEN reigster and APCFNUM register, done in init*/
		/****Step 2: Calculate value to write into xWG register and Accumulation Time*/
		/*
		Following equations: 
			WATTHR expected = (4*MC*I_test*V_nom*cosphi*AccumTime)/(1000*3600) = 44
			AccumTime = (LINECYC)/(2*line_frequency*Number of phase selected)
			xWG = (WATTHR expected / WATTHR - 1)*4096
		*/
		ADE7758_Write_16bit(CWG,(uint16_t)((44/watthr[PHASE_C] - 1)*4096)); 
		/*****Step 3: Calculate the Wh/LSB and store into FLASH*/
		/*
		Following equations:
			Wh/LSB = (I_test * V_nom * cosphi * AccumTime)/(3600 * WATTHR)
		*/
		wh_lsb[PHASE_C] =  (4400)/(3600*watthr[PHASE_C]);	
	}
}	
void ADE7758_RMS_Offset_Calib_Init(void)
{
	/* Enable zero - crossing on all phases + active/reactive 
	power register into line accumulation mode*/
	ADE7758_Write_8bit(LCYCMODE, 0x3B);			
  /* Set interrupt mask for zero crossing on all phases	*/
	ADE7758_Write_24bit(MASK, 0x00000E00);	
}
/*		step 0: set up test condition:
			step 1: Enable zero - crossing on all phases  
			step 2: SET INTERRUPT MASK FOR ZERO CROSSING ON ALL PHASES	
			step 3: SET UP SYSTEM FOR IFULLSCALE/500, VFULLSCALE/20																					
			step 4: READ RMS REGISTERS 
			step 5: write to RMS OFFSET REGISTER
*/
void ADE7758_RMS_Offset_Calibration(uint8_t phase)
{
	uint8_t i;
	
	calib_flag = 1;
	phase_flag = phase;
	k = 1;
	if (PHASE_A == phase)
	{
		//Cho doc het 50 gia tri lay mau
		while (k <= 50);	
		//Lay TB cong		
		for (i = 1; i <= 50; i++)
		{
			Vrms_avg += get_data_v[i];
			Irms_avg += get_data_i[i]; 
		}
		Vrms_avg = (uint32_t)(Vrms_avg / 50);
		Irms_avg = (uint32_t)(Irms_avg / 50);
		calib_flag = 0;
	}
	if (PHASE_B == phase)
	{
		//Cho doc het 50 gia tri lay mau
		while (k <= 50);	
		//Lay TB cong		
		for (i = 1; i <= 50; i++)
		{
			Vrms_avg += get_data_v[i];
			Irms_avg += get_data_i[i]; 
		}
		Vrms_avg = (uint32_t)(Vrms_avg / 50);
		Irms_avg = (uint32_t)(Irms_avg / 50);
		calib_flag = 0;
	}
	if (PHASE_C == phase)
	{
		//Cho doc het 50 gia tri lay mau
		while (k <= 50);	
		//Lay TB cong		
		for (i = 1; i <= 50; i++)
		{
			Vrms_avg += get_data_v[i];
			Irms_avg += get_data_i[i]; 
		}
		Vrms_avg = (uint32_t)(Vrms_avg / 50);
		Irms_avg = (uint32_t)(Irms_avg / 50);
		calib_flag = 0;
	}
}
