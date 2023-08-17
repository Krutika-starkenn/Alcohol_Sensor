/******************* (C) COPYRIGHT 2013 SSPL **********************************
* File Name          : main.c
* Author             : MCD Application Team
* Version            : 
* Date               : 
* Description        : 
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include <math.h>

void XGPG6857D_write(void);
void XGPG6857D_read(void);
unsigned char g_uc_Transmit_Buffer[100];
unsigned char g_uc_ECU_Data_Msg[8];	
unsigned char g_uc_Power_ON_Flag = 0;

volatile unsigned int g_vui_mSec = 0;
//unsigned int l_uc_fn_Ret_Val = 0;

vuint8_t g_vuc_clock_stable;
CanTxMsg Can_Tx_Msg;
CAN_InitTypeDef        CAN_InitStructure;
CAN_FilterInitTypeDef  CAN_FilterInitStructure;
USART_InitTypeDef USART_InitStructure;
GPIO_InitTypeDef GPIO_InitStructure;
EXTI_InitTypeDef EXTI_InitStructure;
ErrorStatus HSEStartUpStatus;

unsigned char g_bln_UART_Interrupt = 0;

tdenm_Main_State_Machine enm_Main_State_Machine;
unsigned char g_uc_Main_State_Machine = 0;
volatile unsigned int g_vui_Ticker_Accessory_Board_Heartbeat = 0;
volatile unsigned int g_vui_Ticker_Heartbeat_LED = 0;
volatile unsigned int g_vui_Ticker_Get_Sensor_Data_Cmd_Interval = 0;
volatile unsigned int g_vui_Ticker_Power_ON_Wait_Time = 0;
volatile unsigned int g_vui_Ticker_ADC_Voltage_Level_Scanning_Time = 0;

unsigned char g_uc_Flag_LED_State = 0;
unsigned char g_uc_Flag_Send_Data = 0;
unsigned short g_us_Factory_Data = 0;
I2C_InitTypeDef I2C_pressure_Struct;


/*******************************************************************************
* Function Name  : main
* Description    : Main program
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int main(void)
{
	
		RCC_Configuration();	/* System Clocks Configuration */
		NVIC_Configuration();	/* NVIC Configuration  interrupt*/
		EXTI_Configuration();	/* EXTI Configuration */
		InitSysTickTimer();		/* SysTickTimer Configuration */
		GPIO_Configuration();	/* GPIO Configuration */
		USART_Configuration();	/*USART Configurastion*/
		CAN_Config();
		fn_uc_Initialize_ADC1_Module(); /* Initialize ADC1 for analog input */
		fn_uc_Initialize_Simulated_I2C_Bus_Port_Pins();
		fn_Init_SPI_Pins();
		fn_uc_RGB_LED_Off();
		
		g_uc_Power_ON_Flag = 1;
		g_vui_Ticker_Power_ON_Wait_Time = POWER_ON_WAIT_TIME;
	
		g_uc_Main_State_Machine = enm_STATE_HANDLE_HEARTBEAT;

		#if 1//DEBUG_ON
					sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n Welcome to Starkenn Technologies \r\n Build Version: AB_01_00_D01.hex");	
			fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);
		#endif


		     
		while(1)
		{
        switch(g_uc_Main_State_Machine)
        {
            case enm_STATE_HANDLE_HEARTBEAT:
            {
                fn_Handle_Heartbeat_LED();
                fn_uc_Send_Heartbeat_To_ECU();
                
                g_uc_Main_State_Machine ++;
            }
            break;
            
            case enm_STATE_HANDLE_ALCOHOL_DETECTION:
            {
              	fn_uc_Handle_Alcohol_Test();
								g_uc_Main_State_Machine ++;
						}
            break;
            
            case enm_STATE_HANDLE_TEMPERATURE_SENSOR:
            {				
							g_uc_Main_State_Machine = enm_STATE_HANDLE_LED_BUZZER;
						}
						break;
						
						case enm_STATE_HANDLE_LED_BUZZER:
						{
							fn_Handle_LED_BUZZER_Indication();
							g_uc_Main_State_Machine = enm_STATE_ERROR_HANDLING;
						}
						break;
						
						case enm_STATE_ERROR_HANDLING:
						{
							fn_Handle_Error();
							g_uc_Main_State_Machine = enm_STATE_HANDLE_HEARTBEAT;						
						}
						break;
        }
		}

}

void Delay(u16 nTime)
{
    g_vui_mSec = nTime;
    while(g_vui_mSec);
}



unsigned char fn_Handle_Heartbeat_LED(void)
{
	if(! g_vui_Ticker_Heartbeat_LED)
	{
		if(g_uc_Flag_LED_State)
		{						
			HEARTBEAT_LED_ON;	
			g_uc_Flag_LED_State ^= 1;            
		}
		else
		{
			HEARTBEAT_LED_OFF;
			g_uc_Flag_LED_State ^= 1;            
		}
		
		#if 0//DEBUG_CAS_ALGO_FUNCTION
			fn_uc_Send_String_On_Debug_Port("\r\n HB\r\n");
		#endif
		
		g_vui_Ticker_Heartbeat_LED = ECU_HEARTBEAT_TIMER;
	}
	
	return SUCCESS;
}

unsigned char fn_uc_RGB_LED_Off(void)
{
	
	RED_LED_OFF;
	GREEN_LED_OFF;	
	BLUE_LED_OFF;
	return SUCCESS;
}


unsigned char fn_uc_RGB_LED_On(void)
{
	RED_LED_ON;//Common Cathode LED
	GREEN_LED_ON;
	BLUE_LED_ON;
	return SUCCESS;
}


