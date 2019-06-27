#include "user_stm32f1xx_spi.h"

void SPI_Configuration(uint16_t SPI_mode)
{
	SPI_InitTypeDef SPI_InitStructure;
	/*---------------- Config SPI pin-------------------------------------------- */
	GPIO_SPI_Configuration(SPI_mode);
	/*---------------- Config SPI parameters-------------------------------------------- */
	SPI_InitStructure.SPI_Mode = SPI_mode; 
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;   //only 8 LSB of DR used in transmission/reception
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; 				//bit SSM = 1 in CR1
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;  //Baudrate = PCLK2 / 256
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
	
	SPI_Init(SPIy, &SPI_InitStructure);
	SPI_NSSInternalSoftwareConfig(SPIy, SPI_NSSInternalSoft_Set); //Bit SSI = 1 in CR1 
	SPI_Cmd(SPIy, ENABLE); 
}
void SPI_LCD5110_Configuration(void)
{
	SPI_InitTypeDef SPI_InitStructure;
	
	GPIO_SPI_Configuration(SPI_Mode_Master);
	
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;   //only 8 LSB of DR used in transmission/reception
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; 				//bit SSM = 1 in CR1
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4; 
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
	
	SPI_Init(SPIy, &SPI_InitStructure);
	SPI_NSSInternalSoftwareConfig(SPIy, SPI_NSSInternalSoft_Set); //Bit SSI = 1 in CR1 
	SPI_Cmd(SPIy, ENABLE); 
	
}
uint8_t SPI_WriteRead8(uint8_t Data)
{
	uint8_t rx_data;
	
	SPI_I2S_SendData(SPIy,(uint16_t)Data);
	while (RESET == SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_TXE));		//waiting for TxBuffer is empty, means data is sent
	while (RESET == SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_RXNE));
	rx_data = SPI_I2S_ReceiveData(SPIy);
	
	return rx_data;
}
uint16_t SPI_WriteRead16(uint16_t Data)
{
	uint16_t rx_data;
	
	SPI_I2S_SendData(SPIy, Data);
	while (RESET == SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_TXE));		//waiting for TxBuffer is empty, means data is sent
	while (RESET == SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_RXNE));
	rx_data = SPI_I2S_ReceiveData(SPIy);
	
	return rx_data;
}
uint8_t SPI_WriteByte(uint8_t Data)
{
	return SPI_WriteRead8(Data); 
}
uint16_t SPI_Write2Byte(uint16_t Data)
{
	return SPI_WriteRead16(Data); 
}
uint8_t SPI_ReadByte(void)
{
	return SPI_WriteRead8(SPI_DUMMY_BYTE); 
}
void SPI_Send_Byte(uint8_t Data)
{
	SPI_I2S_SendData(SPIy,(uint16_t)Data);
	while (RESET == SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_TXE));		//waiting for TxBuffer is empty, means data is sent
}
