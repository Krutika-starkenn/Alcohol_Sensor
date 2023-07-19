/* Includes ------------------------------------------------------------------*/
#include "main.h"

/*******************************************************************************
* Function Name  : USART_Configuration
* Description    : UART Configuration
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART_Configuration(void)
{
	USART_InitStructure.USART_BaudRate = 19200;	/*	115200;	*/
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = 0;				/*	USART_Parity_No	*/
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* Configure the USART1 */
	USART_Init(USART1, &USART_InitStructure);	
	/* Enable the USART Receive interrupt: this interrupt is generated when the 
	 USART1 receive data register is not empty */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	 
	/* Enable USART1 */
	USART_Cmd(USART1, ENABLE);

	
	
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = 0;//USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
	/* Configure the USART2 */
	USART_Init(USART2, &USART_InitStructure);	
	/* Enable the USART Receive interrupt: this interrupt is generated when the 
	 USART1 receive data register is not empty */
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);	 
	/* Enable USART2 */
	USART_Cmd(USART2, ENABLE);		  
	

	
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = 0;
	USART_InitStructure.USART_HardwareFlowControl =USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
	/* Configure the USART3 */
	USART_Init(USART3, &USART_InitStructure);
	/* Enable the USART Receive interrupt: this interrupt is generated when the 
	USART3 receive data register is not empty */
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	 
	/* Enable USART3 */
	USART_Cmd(USART3, ENABLE);

}


/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_Configuration(void)
{
  /* RCC system reset(for debug purpose) */
  RCC_DeInit();

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if (HSEStartUpStatus == SUCCESS)
  {
		g_vuc_clock_stable = 1;
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);

    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1);

    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1);

    /* PCLK1 = HCLK/4 */
    RCC_PCLK1Config(RCC_HCLK_Div4);

    /* PLLCLK = 8MHz * 9 = 72 MHz */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    /* Enable PLL */
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {}

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while (RCC_GetSYSCLKSource() != 0x08)
    {}
  }
  else g_vuc_clock_stable = 0;
  /* TIM4 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4 | RCC_APB1Periph_USART2 | RCC_APB1Periph_USART3, ENABLE);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 , ENABLE);

  /* GPIOA and GPIOB clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 |RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO, ENABLE);	

  
  /* Enable ADC1, ADC2, ADC3 and GPIOC clocks */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
  /* CAN Periph clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN, ENABLE);

}

/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configure the TIM4 Ouput Channels.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_Configuration(void)
{
	/* Disable the Serial Wire Jtag Debug Port SWJ-DP */
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE); 

	// ******* Configure USART1 & UART 2 Tx Pin *************
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	// ******************************************************

	// ******* Configure USART1 & UART2 RX Pin **************
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	// ******************************************************
	
	// ************* Confifure UART 3 RX & TX ***************
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);						

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	// ******************************************************

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; /* CAN1Tx ,Alternate function push pull */
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; /* CAN1Rx ,Alternate function push pull */
	GPIO_Init(GPIOA, &GPIO_InitStructure);


	/* Heartbeat LED*/
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;			
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    /* output push pull type */
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;			
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    /* output push pull type */
	GPIO_Init(GPIOC, &GPIO_InitStructure);

/* Alcohol Sensor ADC Input */		
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0  | GPIO_Pin_1;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/* Alcohol Sensor ADC Input */		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* Battery level ADC Input	*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	  /* Alcohol Test Switch*/
	/*GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	*/
		
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
 
	/* Alcohol pump*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;			
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    /* output push pull type */
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
    /* Alcohol Vibrator*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;			
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    /* output push pull type */
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
	
	
    //Test the timeout of pump
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;			
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;    /* output push pull type */
	GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    //buzzer
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;			
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    /* output push pull type */
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//RED LED
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;			
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    /* output push pull type */
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//GREEN LED	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;			
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//GPIO_Mode_AIN;//GPIO_Mode_Out_PP;//GPIO_Mode_AF_PP;//GPIO_Mode_IPD;// GPIO_Mode_IPU;//GPIO_Mode_AF_PP;//GPIO_Mode_Out_PP;    /* output push pull type */
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//BLUE LED
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;			
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    /* output push pull type */
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
   
   
   
 
}
/*******************************************************************************
* Function Name  : InitSysTickTimer
* Description    : This function Configures Systick timer to generate 1 ms interrupt
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void InitSysTickTimer (void)
{
	/* Clear SysTick Counter */
  SysTick_CounterCmd(SysTick_Counter_Clear);

    /* SysTick end of count event each 1ms with input clock equal to 9MHz (HCLK/8, default) */
  SysTick_SetReload(9000);		 // 1.3ms time base	at 56/8 = 7 MHz, 1ms at 9 MHz
//  SysTick_SetReload(11250);	 // 1.25ms time base

  /* Enable SysTick interrupt */
  SysTick_ITConfig(ENABLE);

  /* Enable the SysTick Counter */
  SysTick_CounterCmd(SysTick_Counter_Enable);
}
/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures Vector Table base location.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
#ifdef  VECT_TAB_RAM
  /* Set the Vector Table base location at 0x20000000 */
  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
#else  /* VECT_TAB_FLASH  */
  /* Set the Vector Table base location at 0x08000000 */
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
#endif

 /* Enable the USART1 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	
	 // Enable the USART2 Interrupt 
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	
	 // Enable the USART3 Interrupt 
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	
  /* Enable CAN RX0 interrupt IRQ channel */
  NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN_RX0_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
  /* Enable the TIM3 gloabal Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	/* Enable the TIM3 gloabal Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	/* Enable the EXTI0 Interrupt */  // 26 May 2017
  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

}

/*******************************************************************************
* Function Name  : EXTI_Configuration
* Description    : Configures EXTI Line4.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI_Configuration (void)
{
	/* Connect EXTI Line4 to PA4 */
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB , GPIO_PinSource12);		
    
  EXTI_InitStructure.EXTI_Line = EXTI_Line12;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}

void SetTimer3(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  
  TIM_Cmd(TIM3,DISABLE);
  TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE); 
  
  TIM_TimeBaseStructure.TIM_Period = 360;	/*	may be the autoreload counter */
	
  TIM_TimeBaseStructure.TIM_Prescaler = 0;	/*//3;//5;//if t3ps increment by one Timer interrupt increments by 10uS*/
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;	/* Repetition counter */
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
  TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
  
  TIM_ARRPreloadConfig(TIM3, ENABLE);
  
  /* TIM IT enable */
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
  
  /* TIM2 enable counter */ 
  TIM_Cmd(TIM3, ENABLE); 
	
	/* for e.g TIM_Prescalar=9 then it 1+9=10 */
	
}

void SetTimer4(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  
  TIM_Cmd(TIM4,DISABLE);
  TIM_ITConfig(TIM4, TIM_IT_Update, DISABLE); 
  
   TIM_TimeBaseStructure.TIM_Period =720;	/*	may be the autoreload counter */
	
  TIM_TimeBaseStructure.TIM_Prescaler = 50000; /*//3;//5;//if t3ps increment by one Timer interrupt increments by 10uS */
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;	/* Repetition counter */
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
  TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
  
  TIM_ARRPreloadConfig(TIM4, ENABLE);
  
  /* TIM IT enable */
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
  
  /* TIM2 enable counter */ 
  TIM_Cmd(TIM4, ENABLE); 
	
	/* for e.g TIM_Prescalar=9 then it 1+9=10m */
}


/******************* (C) COPYRIGHT 2013 SSPL *****END OF FILE*****************/

