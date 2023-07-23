/******************* (C) COPYRIGHT 2013 SSPL **********************************
* File Name          : main.c
* Author             : MCD Application Team
* Version            : 
* Date               : 
* Description        : 
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "stm32f10x_it.h"

#include "stm32f10x_tim.h"




/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : NMIException
* Description    : This function handles NMI exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NMIException(void)
{}

/*******************************************************************************
* Function Name  : HardFaultException
* Description    : This function handles Hard Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void HardFaultException(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {}
}

/*******************************************************************************
* Function Name  : MemManageException
* Description    : This function handles Memory Manage exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MemManageException(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {}
}

/*******************************************************************************
* Function Name  : BusFaultException
* Description    : This function handles Bus Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BusFaultException(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {}
}

/*******************************************************************************
* Function Name  : UsageFaultException
* Description    : This function handles Usage Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UsageFaultException(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {}
}

/*******************************************************************************
* Function Name  : DebugMonitor
* Description    : This function handles Debug Monitor exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DebugMonitor(void)
{}

/*******************************************************************************
* Function Name  : SVCHandler
* Description    : This function handles SVCall exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SVCHandler(void)
{}

/*******************************************************************************
* Function Name  : PendSVC
* Description    : This function handles PendSVC exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PendSVC(void)
{}

/*******************************************************************************
* Function Name  : SysTickHandler
* Description    : This function handles SysTick Handler.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SysTickHandler(void)
{  
	if(g_vui_mSec)	g_vui_mSec--;
	if(g_vui_Ticker_Accessory_Board_Heartbeat) g_vui_Ticker_Accessory_Board_Heartbeat--;
	//if(g_vui_Ticker_Get_Alcohol_Test_Samples) g_vui_Ticker_Get_Alcohol_Test_Samples--;
    //if(g_vui_Ticker_Sampling_Timer) g_vui_Ticker_Sampling_Timer--;
	if(g_vui_Ticker_Heartbeat_LED) g_vui_Ticker_Heartbeat_LED--;
	//if(g_vui_Ticker_Buzzer_Handler) g_vui_Ticker_Buzzer_Handler--;
	
	if(g_vui_Ticker_Power_ON_Wait_Time) g_vui_Ticker_Power_ON_Wait_Time--;
	
	if(!g_vui_Ticker_Power_ON_Wait_Time)
	{
		g_uc_Power_ON_Flag = 0;
	}
	
	if(g_vui_Ticker_Get_Sensor_Data_Cmd_Interval) g_vui_Ticker_Get_Sensor_Data_Cmd_Interval--;
		
	if(g_vui_Ticker_Alcohol_Test_Timeout_Timer) g_vui_Ticker_Alcohol_Test_Timeout_Timer--;
	if(g_vui_Ticker_Alcohol_Sensor_Data_Sampling_Timer) g_vui_Ticker_Alcohol_Sensor_Data_Sampling_Timer--;
    
  if(g_vui_Ticker_Timeout_For_Pump_Activation_Timer)  g_vui_Ticker_Timeout_For_Pump_Activation_Timer--;
	if(g_vui_Ticker_Pump_Turn_On_Timeout)								g_vui_Ticker_Pump_Turn_On_Timeout--;
	  
  if(g_vui_Ticker_Alcohol_Sensor_Sampling_Interval_Integration)   g_vui_Ticker_Alcohol_Sensor_Sampling_Interval_Integration--;
}

/*******************************************************************************
* Function Name  : WWDG_IRQHandler
* Description    : This function handles WWDG interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void WWDG_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : PVD_IRQHandler
* Description    : This function handles PVD interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PVD_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : TAMPER_IRQHandler
* Description    : This function handles Tamper interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TAMPER_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : RTC_IRQHandler
* Description    : This function handles RTC global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RTC_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : FLASH_IRQHandler
* Description    : This function handles Flash interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void FLASH_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : RCC_IRQHandler
* Description    : This function handles RCC interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : EXTI0_IRQHandler
* Description    : This function handles External interrupt Line 0 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI0_IRQHandler(void)		/* tested on 29th May2017*/
{
  
    if(EXTI_GetITStatus(EXTI_Line0) != RESET)
	{
        
//		if(1 == g_uc_Power_ON_Flag)
//		{
//			//key detection within 5 sec
//            if(!CRUISE_BUTTON_STATUS)
//            {
//                if (!g_vui_Ticker_Time_Between_Two_Key_Press_Timer)
//                {
//                    g_uc_Key_Press_Counter = 0;
//                }
//                
//                g_uc_Key_Press_Counter++;
//                g_vui_Ticker_Time_Between_Two_Key_Press_Timer =  TIMEOUT_BETWEEN_TWO_KEY_PRESS;
//                
//                #if DEBUG_ON
//                    sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n KP Cnt:%d, %d, %d", g_uc_Key_Press_Counter, g_vui_Ticker_Power_ON_Key_Detection_Timer, g_uc_Power_ON_Flag);	
//                    fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);
//                #endif

//				if(g_uc_Key_Press_Counter == 3)
//				{
//					g_uc_Flag_Multiple_Times_Key_Pressed = 0;
//					//g_vui_Ticker_Power_ON_Key_Detection_Timer = 0;	
//                    g_uc_Flag_Multiple_Key_Pressed_For_Test_Mode = 1;
//				}
//                
//				if(g_uc_Key_Press_Counter == 5)
//				{
//					g_uc_Flag_Multiple_Times_Key_Pressed = 1;
//					//g_vui_Ticker_Power_ON_Key_Detection_Timer = 0;	
//                    g_uc_Flag_Multiple_Key_Pressed_For_Test_Mode = 0;
//				}
//				
//                if(g_uc_Key_Press_Counter != 5 && g_uc_Key_Press_Counter != 3)
//				{
////					g_uc_Key_Press_Counter = 0;
//					g_uc_Flag_Multiple_Times_Key_Pressed = 0;
//                    g_uc_Flag_Multiple_Key_Pressed_For_Test_Mode = 0;
//				}
//                
//				
//			}
//			
//		}
//		else
//		{

//			if(!CRUISE_BUTTON_STATUS)
//			{
//                #if 0
//                    fn_uc_Send_String_On_Debug_Port("\r\n Key press detected");
//                #endif
//                
//                Cruz_On_Off_Bit = BIT_HIGH;
//                
//                // change prev state
//                g_uc_Flag_Previous_State = KEY_PRESSED;
//			}
//			
//		}
//        
//        //EXTI_ClearITPendingBit(EXTI_Line0);
    }
	
	EXTI_ClearITPendingBit(EXTI_Line0);
}

/*******************************************************************************
* Function Name  : EXTI1_IRQHandler
* Description    : This function handles External interrupt Line 1 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXTI2_IRQHandler
* Description    : This function handles External interrupt Line 2 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXTI3_IRQHandler
* Description    : This function handles External interrupt Line 3 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXTI4_IRQHandler
* Description    : This function handles External interrupt Line 4 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI4_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line4);
}

/*******************************************************************************
* Function Name  : DMA1_Channel1_IRQHandler
* Description    : This function handles DMA1 Channel 1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel1_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : DMA1_Channel2_IRQHandler
* Description    : This function handles DMA1 Channel 2 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel2_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : DMA1_Channel3_IRQHandler
* Description    : This function handles DMA1 Channel 3 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel3_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : DMA1_Channel4_IRQHandler
* Description    : This function handles DMA1 Channel 4 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel4_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : DMA1_Channel5_IRQHandler
* Description    : This function handles DMA1 Channel 5 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel5_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : DMA1_Channel6_IRQHandler
* Description    : This function handles DMA1 Channel 6 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel6_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : DMA1_Channel7_IRQHandler
* Description    : This function handles DMA1 Channel 7 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel7_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : ADC1_2_IRQHandler
* Description    : This function handles ADC1 and ADC2 global interrupts requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ADC1_2_IRQHandler(void)
{}



/*******************************************************************************
* Function Name  : USB_HP_CAN_TX_IRQHandler
* Description    : This function handles USB High Priority or CAN TX interrupts 
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USB_HP_CAN_TX_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : USB_LP_CAN_RX0_IRQHandler
* Description    : This function handles USB Low Priority or CAN RX0 interrupts 
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USB_LP_CAN_RX0_IRQHandler(void)
{
	CanRxMsg Can_Rx_Msg;
    
//	u8 n=0;
	/* Reset all Identifier bytes to zero */
	Can_Rx_Msg.g_ul_Can_Rx_STD_ID = 0x00;
	Can_Rx_Msg.g_ul_Can_Rx_EXD_ID = 0x00;
	Can_Rx_Msg.g_uc_Can_Rx_IDE = 0;
	Can_Rx_Msg.g_uc_Can_Rx_DLC = 0;
	Can_Rx_Msg.g_uc_Can_Rx_RTR = 0;	
	Can_Rx_Msg.g_uc_Can_Rx_FMI = 0;
	
	// Reset all data bytes to zero
		Can_Rx_Msg.g_uc_Can_Rx_DATA[0] = 0x00;	// Byte0
		Can_Rx_Msg.g_uc_Can_Rx_DATA[1] = 0x00;
		Can_Rx_Msg.g_uc_Can_Rx_DATA[2] = 0x00;
		Can_Rx_Msg.g_uc_Can_Rx_DATA[3] = 0x00;
		
		Can_Rx_Msg.g_uc_Can_Rx_DATA[4] = 0x00;
		Can_Rx_Msg.g_uc_Can_Rx_DATA[5] = 0x00;
		Can_Rx_Msg.g_uc_Can_Rx_DATA[6] = 0x00;
		Can_Rx_Msg.g_uc_Can_Rx_DATA[7] = 0x00;	// Byte7	
	
		get_Received_CAN_Data(CAN_FIFO0, &Can_Rx_Msg);	//Receive
	
    g_uc_ECU_Data_Msg[0] = Can_Rx_Msg.g_uc_Can_Rx_DATA[0];
    g_uc_ECU_Data_Msg[1] = Can_Rx_Msg.g_uc_Can_Rx_DATA[1];
    g_uc_ECU_Data_Msg[2] = Can_Rx_Msg.g_uc_Can_Rx_DATA[2];
    g_uc_ECU_Data_Msg[3] = Can_Rx_Msg.g_uc_Can_Rx_DATA[3];
    g_uc_ECU_Data_Msg[4] = Can_Rx_Msg.g_uc_Can_Rx_DATA[4];
    g_uc_ECU_Data_Msg[5] = Can_Rx_Msg.g_uc_Can_Rx_DATA[5];
    g_uc_ECU_Data_Msg[6] = Can_Rx_Msg.g_uc_Can_Rx_DATA[6];
    g_uc_ECU_Data_Msg[7] = Can_Rx_Msg.g_uc_Can_Rx_DATA[7];
	
 
    switch(Can_Rx_Msg.g_ul_Can_Rx_STD_ID)
    {
				case CAN_RX_ID_OF_START_ALCOHOL_TEST:
        {
					g_uc_Flag_Start_Alcohol_Test = g_uc_ECU_Data_Msg[0];
					g_uc_Alcohol_Threshold_Mode = g_uc_ECU_Data_Msg[1];	
				}
				break;
		
				case CAN_RX_ID_OF_ALCOHOL_THRESHOLD:
        {
			
				}
				break;
        
        case CAN_RX_ID_OF_PERIPHERAL_RESET:
        {
            if (0xF1 == g_uc_ECU_Data_Msg[0])
            {
                //to  reset the system
                NVIC_GenerateSystemReset();
            }            
        }
        break;
		
    }// End of Switch
    
    CAN_ClearITPendingBit(CAN_IT_FMP0);	
}

/*******************************************************************************
* Function Name  : CAN_RX1_IRQHandler
* Description    : This function handles CAN RX1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CAN_RX1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : CAN_SCE_IRQHandler
* Description    : This function handles CAN SCE interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CAN_SCE_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : EXTI9_5_IRQHandler
* Description    : This function handles External lines 9 to 5 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI9_5_IRQHandler(void)
{

//	if(!CRUISE_ON)
//	Cruz_On_Off_Bit=BIT_HIGH;
//	else
//	Cruz_On_Off_Bit=BIT_LOW;
	
//	if(!TEST_KEY)
//	Test_Ki_Bit=BIT_HIGH;
//	else
//	Test_Ki_Bit=BIT_LOW;	
	
 EXTI_ClearITPendingBit(EXTI_Line5);
 EXTI_ClearITPendingBit(EXTI_Line6);
 EXTI_ClearITPendingBit(EXTI_Line7);
 EXTI_ClearITPendingBit(EXTI_Line8);
}

/*******************************************************************************
* Function Name  : TIM1_BRK_IRQHandler
* Description    : This function handles TIM1 Break interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM1_BRK_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : TIM1_UP_IRQHandler
* Description    : This function handles TIM1 overflow and update interrupt
*                  request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM1_UP_IRQHandler(void)
{
  
}

/*******************************************************************************
* Function Name  : TIM1_TRG_COM_IRQHandler
* Description    : This function handles TIM1 Trigger and commutation interrupts
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM1_TRG_COM_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : TIM1_CC_IRQHandler
* Description    : This function handles TIM1 capture compare interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM1_CC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM2_IRQHandler
* Description    : This function handles TIM2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM2_IRQHandler(void)
{

}

/*******************************************************************************
* Function Name  : TIM3_IRQHandler
* Description    : This function handles TIM3 global interrupt request.
* Input          : Key inputs to Increment and Decrement Speed
* Output         : Speed Out ( Toggling of Pin)
* Return         : None
* Author         : Mr.Naresh S. Partole, 18th July 2017
*******************************************************************************/
void TIM3_IRQHandler(void)	// interrupt in 10uS // checked on 31st May 2017
{
	
  TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
}

/*******************************************************************************
* Function Name  : TIM4_IRQHandler
* Description    : This function handles TIM4 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM4_IRQHandler(void)
{
  TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
}

/*******************************************************************************
* Function Name  : I2C1_EV_IRQHandler
* Description    : This function handles I2C1 Event interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C1_EV_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : I2C1_ER_IRQHandler
* Description    : This function handles I2C1 Error interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C1_ER_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : I2C2_EV_IRQHandler
* Description    : This function handles I2C2 Event interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C2_EV_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : I2C2_ER_IRQHandler
* Description    : This function handles I2C2 Error interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C2_ER_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : SPI1_IRQHandler
* Description    : This function handles SPI1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI1_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : SPI2_IRQHandler
* Description    : This function handles SPI2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI2_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : USART1_IRQHandler
* Description    : This function handles USART1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART1_IRQHandler(void)
{
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{   	
		/* Read one byte from the receive data register */
	    g_uc_Uart1_Rx_Buf[g_uc_Uart1_Wr_Data_Index]  = (USART_ReceiveData(USART1) & 0xFF); 
         		
        g_uc_Uart1_Wr_Data_Index++;
		
		if(g_uc_Uart1_Wr_Data_Index == UART_BUF_SIZE) g_uc_Uart1_Wr_Data_Index=0;
	}
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);	
}

/*******************************************************************************
* Function Name  : USART2_IRQHandler
* Description    : This function handles USART2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
			/* Read one byte from the receive data register */
			g_uc_Uart2_Rx_Buf[g_uc_Uart2_Wr_Data_Index]  = (USART_ReceiveData(USART2) & 0xFF);
			
			g_uc_Uart2_Wr_Data_Index ++;
					
			if(g_uc_Uart2_Wr_Data_Index >= UART_BUF_SIZE) 
			{
				g_uc_Uart2_Wr_Data_Index = 0;
			}
	}
	
	USART_ClearITPendingBit(USART2, USART_IT_RXNE);	
}

/*******************************************************************************
* Function Name  : USART3_IRQHandler
* Description    : This function handles USART3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART3_IRQHandler(void)
{
    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
//		if(1 == g_uc_Flag_DD_Warning_Status)
//		{
//			g_uc_DD_Image_Data_Buffer[g_ui_DD_Image_Data_Wr_Index]  = (USART_ReceiveData(USART3) & 0xFF); 
//			
//			g_ui_DD_Image_Data_Wr_Index ++;
//				
//			// Check for index roll over
//			if(g_ui_DD_Image_Data_Wr_Index >= DD_IMAGE_DATA_BUFFER_SIZE) 
//			{
//				g_ui_DD_Image_Data_Wr_Index = 0;
//			}
//		}
//		else
//		{
//			/* Read one byte from the receive data register */
//			g_uc_Uart3_Rx_Buf[g_uc_Uart3_Wr_Data_Index]  = (USART_ReceiveData(USART3) & 0xFF); 
//			
//			g_uc_Uart3_Wr_Data_Index ++;
//				
//			// Check for index roll over
//			if(g_uc_Uart3_Wr_Data_Index >= UART_BUF_SIZE) 
//			{
//				g_uc_Uart3_Wr_Data_Index = 0;
//			}
//		}
	}
	
	USART_ClearITPendingBit(USART3, USART_IT_RXNE);	
}

/*******************************************************************************
* Function Name  : EXTI15_10_IRQHandler
* Description    : This function handles External lines 15 to 10 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line12) != RESET)
	{
		if(1 == g_uc_Power_ON_Flag)
		{
			
			
		}
		else
		{

//			if(STATE_CHECK_START_TEST_SWITCH_PRESS == g_uc_Alcohol_Test_State_Machine)
//			{
//				if(!ALCOHOL_TEST_BUTTON_STATUS)
//				{
//					#if 0
//						fn_uc_Send_String_On_Debug_Port("\r\n Key press detected");
//					#endif
//					
//					Alcohol_Test_On_Off_Bit = BIT_HIGH;				
//				}
//			}
			
		}
		
		EXTI_ClearITPendingBit(EXTI_Line12);
	}
}

/*******************************************************************************
* Function Name  : RTCAlarm_IRQHandler
* Description    : This function handles RTC Alarm interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RTCAlarm_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : USBWakeUp_IRQHandler
* Description    : This function handles USB WakeUp interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USBWakeUp_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : TIM8_BRK_IRQHandler
* Description    : This function handles TIM8 Break interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM8_BRK_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : TIM8_UP_IRQHandler
* Description    : This function handles TIM8 overflow and update interrupt
*                  request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM8_UP_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : TIM8_TRG_COM_IRQHandler
* Description    : This function handles TIM8 Trigger and commutation interrupts
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM8_TRG_COM_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : TIM8_CC_IRQHandler
* Description    : This function handles TIM8 capture compare interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM8_CC_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : ADC3_IRQHandler
* Description    : This function handles ADC3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ADC3_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : FSMC_IRQHandler
* Description    : This function handles FSMC global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void FSMC_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : SDIO_IRQHandler
* Description    : This function handles SDIO global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SDIO_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : TIM5_IRQHandler
* Description    : This function handles TIM5 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM5_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : SPI3_IRQHandler
* Description    : This function handles SPI3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI3_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : UART4_IRQHandler
* Description    : This function handles UART4 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UART4_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : UART5_IRQHandler
* Description    : This function handles UART5 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UART5_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : TIM6_IRQHandler
* Description    : This function handles TIM6 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM6_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : TIM7_IRQHandler
* Description    : This function handles TIM7 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM7_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : DMA2_Channel1_IRQHandler
* Description    : This function handles DMA2 Channel 1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA2_Channel1_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : DMA2_Channel2_IRQHandler
* Description    : This function handles DMA2 Channel 2 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA2_Channel2_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : DMA2_Channel3_IRQHandler
* Description    : This function handles DMA2 Channel 3 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA2_Channel3_IRQHandler(void)
{}

/*******************************************************************************
* Function Name  : DMA2_Channel4_5_IRQHandler
* Description    : This function handles DMA2 Channel 4 and DMA2 Channel 5
*                  interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA2_Channel4_5_IRQHandler(void)
{}
	

/******************* (C) COPYRIGHT 2013 SSPL *****END OF FILE*****************/
	
