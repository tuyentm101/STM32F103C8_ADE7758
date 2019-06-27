#include "user_stm32f1xx_gpio.h"

GPIO_InitTypeDef GPIO_InitStructure;

void GPIO_Configuration(void)
{
	/*---------Init LCD data pin--------*/
	GPIO_InitStructure.GPIO_Pin = LCD_DATA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUTPUT_PUSH_PULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_USER;
	GPIO_Init(LCD_DATA_PORT, &GPIO_InitStructure); 
	
	
	/*---------Init LCD control pin--------*/
	GPIO_InitStructure.GPIO_Pin =  LCD_CTRL_PIN; 
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUTPUT_PUSH_PULL;
	GPIO_Init(LCD_CTRL_PORT, &GPIO_InitStructure); 
	
	/*---------Init LED pin--------*/
	GPIO_InitStructure.GPIO_Pin = USER_LED_PIN ; 
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUTPUT_PUSH_PULL;
	GPIO_Init(USER_LED_PORT, &GPIO_InitStructure);
	
	
	/*---------Init button--------*/
	GPIO_InitStructure.GPIO_Pin =  USER_BUTTON_PIN; 
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_INPUT_FLOATING;
	GPIO_Init(USER_BUTTON_PORT, &GPIO_InitStructure);
	
//	GPIO_InitStructure.GPIO_Pin = RST_PIN | DC_PIN;
//	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUTPUT_PUSH_PULL;
//	GPIO_Init(GPIO_PORT_A, &GPIO_InitStructure);
//	
//	GPIO_InitStructure.GPIO_Pin =  ON_BOARD_LED_PIN; 
//	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUTPUT_PUSH_PULL;
//	GPIO_Init(ON_BOARD_LED_PORT, &GPIO_InitStructure); 
}
/*
	Khoi tao chan SPI1
	- Chan NSS cau hinh la AF chi khi SPI su dung NSS Hardware mode
	- Chan NSS cau hinh la GPIO output thong thuong khi SPI cau hinh la NSS Software mode
*/
void GPIO_SPI_Configuration(uint16_t SPI_mode)
{
  GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_USER;
	if (SPI_Mode_Master == SPI_mode)
	{
		/*---------Config MOSI and SCLK pin----------------------------*/
		GPIO_InitStructure.GPIO_Pin = SPIy_PIN_SCK | SPIy_PIN_MOSI;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_ALTERNATE_FUNCTION_PUSH_PULL;
		GPIO_Init(SPIy_GPIO, &GPIO_InitStructure);
		/*---------Config MISO pin-------------------------------------*/
		GPIO_InitStructure.GPIO_Pin = SPIy_PIN_MISO;
		GPIO_InitStructure.GPIO_Mode = GPIO_MODE_INPUT_FLOATING;
		GPIO_Init(SPIy_GPIO, &GPIO_InitStructure);
		/*---------Config NSS pin--------------------------------------*/
		GPIO_InitStructure.GPIO_Pin = SPIy_PIN_NSS;
		GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUTPUT_PUSH_PULL;
		GPIO_Init(SPIy_GPIO, &GPIO_InitStructure);
	}
	else	// if device is slave
	{
		/*---------Config MOSI and SCLK pin----------------------------*/
		GPIO_InitStructure.GPIO_Pin = SPIy_PIN_SCK | SPIy_PIN_MOSI;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_INPUT_FLOATING;
		GPIO_Init(SPIy_GPIO, &GPIO_InitStructure);
		/*---------Config MISO pin-------------------------------------*/
		GPIO_InitStructure.GPIO_Pin = SPIy_PIN_MISO;
		GPIO_InitStructure.GPIO_Mode = GPIO_MODE_ALTERNATE_FUNCTION_PUSH_PULL;
		GPIO_Init(SPIy_GPIO, &GPIO_InitStructure);
		/*---------Config NSS pin--------------------------------------*/
		GPIO_InitStructure.GPIO_Pin = SPIy_PIN_NSS;
		GPIO_InitStructure.GPIO_Mode = GPIO_MODE_ALTERNATE_FUNCTION_PUSH_PULL;
		GPIO_Init(SPIy_GPIO, &GPIO_InitStructure);
	}
}
/*
	Khoi tao chan ngat ngoai EXTI0
*/
void GPIO_EXTI0_Configuration(void)
{
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	  /* Connect EXTI0 Line to PB0 pin (mapping) */
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
}	
