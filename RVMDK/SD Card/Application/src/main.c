/**
  ******************************************************************************
  * @file    sd/main.c 
  * @author  wangzhihai
  * @version V1.0
  * @date    04/15/2011
  * @brief   Main program body.
  ******************************************************************************
 */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "app.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;

/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
void Delay(__IO uint32_t nCount);
void SPI_SDMode(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
	/* System Clocks Configuration **********************************************/
	RCC_Configuration();
	   
	/* Configure all unused GPIO port pins in Analog Input mode (floating input
	 trigger OFF), this will reduce the power consumption and increase the device
	 immunity against EMI/EMC *************************************************/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
	                     RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
	                     RCC_APB2Periph_GPIOE, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
	                     RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
	                     RCC_APB2Periph_GPIOE, DISABLE); 
	/*configure SPI to SDCard mode */
	SPI_SDMode();

	App_Prog();

	while(1);
}

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void RCC_Configuration(void)
{   
  /* Setup the microcontroller system. Initialize the Embedded Flash Interface,  
     initialize the PLL and update the SystemFrequency variable. */
	SystemInit();

  	//SYSTICK分频--1ms的系统时钟中断
	if (SysTick_Config(SystemFrequency / 100))
  	{ 
  	  	/* Capture error */ 
    	while (1);
  	}
}

/**
  * @brief  Configures the SPI in high speed.
  * @param  None.
  * @retval None.
  */
void SPI_SDMode(void)
{
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA |
	        				RCC_APB2Periph_GPIOC |
	        				RCC_APB2Periph_AFIO  |
	        				RCC_APB2Periph_SPI1, ENABLE);
	
	/* PA5=CLK, PA7=MOSI alternate function push-pull output */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
		
	/* PA6=MISO pull-up input */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
		
	/* Configure PC7 as CS  open drain push-pull output */
	GPIO_SetBits(GPIOC, GPIO_Pin_5 | GPIO_Pin_7); //set high.
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure); 
	
	/* SPI1 configuration */
	SPI_Cmd(SPI1, DISABLE); //disable SPI1 for configuratio.
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;		//两线全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;							//主
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;						//8位
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;								//CPOL=1 时钟悬空高
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;							//CPHA=1 数据捕获第二个
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;								//软件NSS
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;	//128分频.
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;						//高位在前
	SPI_InitStructure.SPI_CRCPolynomial = 7;								//CRC7
	SPI_Init(SPI1, &SPI_InitStructure);

	//SPI_SSOutputCmd(SPI1, ENABLE); //使能NSS脚可用
		
	/* Enable SPI1  */
	SPI_Cmd(SPI1, ENABLE);
//--------------------------------------复位一下总线，这个比较重要	 
	GPIO_SetBits(GPIOC, GPIO_Pin_7);
		 	
    /* Loop while DR register in not emplty */
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    /* Send byte through the SPI1 peripheral */
    SPI_I2S_SendData(SPI1, 0xff);

    /* Wait to receive a byte */
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
    /* Return the byte read from the SPI bus */
    SPI_I2S_ReceiveData(SPI1);
//----------------------------------------------------end
}

/**
  * @brief  Inserts a delay time.
  * @param  nCount: specifies the delay time length.
  * @retval None
  */
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
