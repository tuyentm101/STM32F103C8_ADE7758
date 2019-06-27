#ifndef _ADE7758_H_
#define _ADE7758_H_
#include "user_stm32f1xx_spi.h"
#include "user_stm32f1xx_exti.h"
/*------------ADE7758 register-----------------------*/
#define  RESERVED    	 0x00

#define  AWATTHR    	 0x01
#define  BWATTHR     	 0x02
#define  CWATTHR     	 0x03

#define  AVARHR      	 0x04
#define  BVARHR      	 0x05
#define  CVARHR      	 0x06

#define  AVAHR       	 0x07
#define  BVAHR       	 0x08
#define  CVAHR       	 0x09

#define  AIRMS      	 0x0A
#define  BIRMS      	 0x0B
#define  CIRMS      	 0x0C

#define  AVRMS      	 0x0D
#define  BVRMS      	 0x0E
#define  CVRMS         0x0F

#define  FREQUECNY   	 0x10
#define	 TEMP 			   0x11

#define	 WFORM 		 	   0x12
#define	 OPMODE 		   0x13
#define	 MMODE			   0x14
#define	 WAVMODE	     0x15

#define  COMPMODE		   0x16
#define  LCYCMODE 		 0x17
#define  MASK 			   0x18

#define  STATUS 		   0x19
#define  RSTATUS		   0x1A
#define  ZXTOUT        0x1B

#define  LINECYC       0x1C
#define  SAGCYC        0x1D 
#define  SAGLVL        0x1E

#define  VPINTLVL 		 0x1F
#define  IPINTLVL		   0x20 
#define  VPEAK 			   0x21

#define  IPEAK 			   0x22
#define  GAIN 			   0x23

#define  VRMSGAIN      0x24
#define  BVRMSGAIN     0x25
#define  CVRMSGAIN     0x26 

#define  AIGAIN 		   0x27 
#define  BIGAIN 		   0x28 
#define  CIGAIN 		   0x29 

#define	 AWG           0x2A
#define	 BWG			     0x2B
#define	 CWG			     0x2C

#define	AVARG 			   0x2D
#define	BVARG 			   0x2E
#define	CVARG 			   0x2F

#define	AVAG 			     0x30
#define	BVAG 			     0x31
#define	CVAG 			     0x32

#define	AVRMSOS			   0x33
#define	BVRMSOS 		   0x34
#define	CVRMSOS				 0x35

#define	AIRMSOS			   0x36
#define	BIRMSOS 		   0x37
#define	CIRMSOS			   0x38

#define	AWATTOS 		   0x39
#define	BWATTOS 		   0x3A
#define	CWATTOS 		   0x3B

#define	AVAROS				 0x3C
#define	BVAROS				 0x3D
#define	CVAROS 				 0x3E

#define	APHCAL 			   0x3F 
#define	BPHCAL 		     0x40 
#define	CPHCAL 	  	   0x41 

#define	WDIV 					 0x42 
#define	VARDIV 				 0x43
#define	VADIV					 0x44

#define	APCFNUM 			 0x45 
#define	APCFDEN 	     0x46 
#define VARCFNUM 	     0x47 
#define	VARCFDEN	     0x48 
// 0x49 to 0x7D
#define	CHKSUM 		     0x7E
#define	VERSION		     0x7F
/*-----------RESET STATUS register mask bit------------------------*/
#define RSTATUS_ZXA_BIT_MASK			((uint32_t)0x00000200)
#define RSTATUS_ZXB_BIT_MASK			((uint32_t)0x00000400)
#define RSTATUS_ZXC_BIT_MASK			((uint32_t)0x00000800)
#define RSTATUS_LENERGY_BIT_MASK	((uint32_t)0x00001000)									
/*-------------Determine IT source------------------*/
#define ZXA					(ADE7758_Read_24bit(RSTATUS) & RSTATUS_ZXA_BIT_MASK)
#define ZXB					(ADE7758_Read_24bit(RSTATUS) & RSTATUS_ZXB_BIT_MASK)
#define ZXC					(ADE7758_Read_24bit(RSTATUS) & RSTATUS_ZXC_BIT_MASK)
#define LENERGY     (ADE7758_Read_24bit(RSTATUS) & RSTATUS_LENERGY_BIT_MASK)
/*----------------------------------------------------------------*/
#define WRITE_CMD					((uint8_t)0x80)
#define READ_CMD					((uint8_t)0x00)
#define PHASE_A						0
#define PHASE_B						1
#define PHASE_C						2
#define V_MIN							25			// V_min = V_full-scale / 20, V_full-scale = 500 V
#define V_NOM							220	
#define I_MIN							260/1000	//I_min = I_full-scale / 500, I_full-scale = 130 A
#define I_TEST					  10
#define cosphi						1 //tai thuan tro
/*#define VRMS_VMIN					11111
#define VRMS_VNOM					22222
#define IRMS_IMIN					11111
#define IRMS_ITEST					22222

#define VRMS_RATIO				353.55/1639101  //??
#define IRMS_RATIO				91.92/1921472		//??
*/
/*-------------EXTERN VARIABLES----------------------*/
extern float wh_lsb[3], varh_lsb[3], vah_lsb[3];
extern volatile uint32_t get_data_v[100],get_data_i[100],v_data[3], i_data[3],watthr[3],vahr[3],varhr[3];
extern volatile uint8_t check;
extern uint8_t calib_flag, phase_flag;
/*---------------------------------------------------*/
uint8_t ADE7758_Read_8bit(uint8_t add_reg);
uint16_t ADE7758_Read_16bit(uint8_t add_reg);
uint32_t ADE7758_Read_24bit(uint8_t add_reg);
void ADE7758_Write_8bit(uint8_t add_reg, uint8_t content);
void ADE7758_Write_16bit(uint8_t add_reg, uint16_t content);
void ADE7758_Write_24bit(uint8_t add_reg, uint32_t content);
uint32_t Vrms_Read(uint8_t phase);
uint32_t Irms_Read(uint8_t phase);
void ADE7758_ZX_VI_Read(volatile uint32_t *data1,volatile uint32_t *data2, uint8_t phase);
void ADE7758_ZX_Pwr_Read(volatile uint32_t *data1, volatile uint32_t *data2, volatile uint32_t *data3, uint8_t phase);
void Get_Sequence_Data(uint8_t phase);
void ADE7758_RMS_Offset_Calib_Init(void);
void ADE7758_RMS_Offset_Calibration(uint8_t phase);
void ADE7758_Gain_Calib_Init(void);
void ADE7758_Gain_Calib(uint8_t phase);

#endif
