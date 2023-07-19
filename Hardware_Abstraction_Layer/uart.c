#include "main.h"
#include "string.h"

	
	
/* Private function prototypes -----------------------------------------------*/
uint8_t 	g_uc_Uart1_Rx_Buf[UART_BUF_SIZE];
uint8_t 	g_uc_Uart2_Rx_Buf[UART_BUF_SIZE];
//uint8_t 	g_uc_Uart3_Rx_Buf[UART3_BUF_SIZE]; // UART3_BUF_SIZE

vuint16_t 	g_uc_Uart1_Wr_Data_Index = 0, g_uc_Uart1_Rd_Data_Index = 0;
vuint16_t 	g_uc_Uart2_Wr_Data_Index = 0, g_uc_Uart2_Rd_Data_Index = 0;
vuint16_t 	g_uc_Uart3_Wr_Data_Index = 0, g_uc_Uart3_Rd_Data_Index = 0;

/*******************************************************************************
* Function Name  : fn_uc_Send_String_On_Debug_Port
* Description    : Sends string (multiple bytes ) on uart port 
* Input          :  
* Output         : None
* Return         : None
*******************************************************************************/
void fn_uc_Send_String_On_Debug_Port (char *bytes)
{
	while(*bytes)
	{   
		/* Send one byte from USART1 to USART2 */    
		 USART_SendData(USART1, *bytes);
		/* Loop until the end of transmit */     
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
		{
			;
		}		
		bytes++;
	}
}
/*******************************************************************************
* Function Name  : fn_uc_Send_Byte_On_Debug_Port
* Description    : Sends single byte on uart port  
* Input          :  
* Output         : None
* Return         : None
*******************************************************************************/
void fn_uc_Send_Byte_On_Debug_Port(u8 byt)
{
	
     USART_SendData(USART1, byt);
    /* Loop until the end of transmit */ 
    while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);

}




/*******************************************************************************
* Function Name  : fn_uc_Send_String_On_UART3_Port
* Description    : Sends string (multiple bytes) on uart port 
* Input          :  
* Output         : None
* Return         : None
*******************************************************************************/
void fn_uc_Send_String_On_UART2_Port (unsigned char *bytes)
{
	while(0xFF != *bytes)
	{   
		/* Send one byte from USART1 to USART2 */    
		 USART_SendData(USART2, *bytes);
		/* Loop until the end of transmit */     
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
		{
			;
		}		
		bytes++;
	}
}
/*******************************************************************************
* Function Name  : fn_uc_Send_Byte_On_UART3_Port
* Description    : Sends single byte on uart port  
* Input          :  
* Output         : None
* Return         : None
*******************************************************************************/
void fn_uc_Send_Byte_On_UART2_Port(u8 byt)
{
	
     USART_SendData(USART2, byt);
    /* Loop until the end of transmit */ 
    while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);

}



/*******************************************************************************
* Function Name  : fn_uc_Send_String_On_UART3_Port
* Description    : Sends string (multiple bytes) on uart port 
* Input          :  
* Output         : None
* Return         : None
*******************************************************************************/
void fn_uc_Send_String_On_UART3_Port (unsigned char *bytes)
{
	while('@' != *bytes)
	{   
		/* Send one byte from USART1 to USART2 */    
		 USART_SendData(USART3, *bytes);
		/* Loop until the end of transmit */     
		while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
		{
			;
		}
		
		bytes++;
	}
}
/*******************************************************************************
* Function Name  : fn_uc_Send_Byte_On_UART3_Port
* Description    : Sends single byte on uart port  
* Input          :  
* Output         : None
* Return         : None
*******************************************************************************/
void fn_uc_Send_Byte_On_UART3_Port(u8 byt)
{
	
     USART_SendData(USART3, byt);
    /* Loop until the end of transmit */ 
    while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);

}


