/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : main.h
* Author             : MCD Application Team
* Version            : V2.0.2
* Date               : 07/11/2008
* Description        : Header for main.c module
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "macro_const.h"
#include "hardware_config.h"
#include "stm32f10x_lib.h"
#include "stm32f10x_type.h"
#include "string.h"
#include <stdio.h>
#include "math.h"
#include "HAL_ADC.h"
#include <time.h>
#include "HAL_I2C.h"

#include "Alcohol_Detection_Algorithm.h"
#include "HAL_SPI.h"
#include "Pressure_Sensor_XGPG6857D.h"

typedef enum
{
    enm_STATE_HANDLE_HEARTBEAT = 0,
    enm_STATE_HANDLE_ALCOHOL_DETECTION,
    enm_STATE_HANDLE_TEMPERATURE_SENSOR,
		enm_STATE_HANDLE_LED_BUZZER,
		enm_STATE_ERROR_HANDLING,
	
		enm_MAX_STATES
}tdenm_Main_State_Machine;

enum
{
	TEST_NOT_STARTED = 0,
	TEST_STARTED = 1,
	TEST_IN_PROGRESS = 2,
	TEST_COMPLETED = 3
};

enum
{
	SAMPLING_STARTED = 1,
	SAMPLING_COMPLETED = 0,
};

extern unsigned char g_uc_Transmit_Buffer[];

extern unsigned char g_uc_Power_ON_Flag;
extern unsigned char g_uc_Flag_Timer_State;

extern volatile unsigned int g_vui_mSec;
extern vuint8_t g_vuc_clock_stable;

//extern vuint16_t g_uc_Uart3_Wr_Data_Index;
//extern uint8_t 	g_uc_Rx3_Buf[UART_RX_BUF], g_uc_Uart3_Rx_Buf[UART_BUF_SIZE];

extern unsigned int g_ui_Previous_Data_Buffer_Index ;

extern volatile unsigned int g_vui_Ticker_Accessory_Board_Heartbeat;
extern volatile unsigned int g_vui_Ticker_Heartbeat_LED;
extern volatile unsigned int g_vui_Ticker_Power_ON_Wait_Time;
extern volatile unsigned int g_vui_Ticker_Get_Sensor_Data_Cmd_Interval;
extern volatile unsigned int g_vui_Ticker_ADC_Voltage_Level_Scanning_Time;
extern volatile unsigned int g_vui_Ticker_Pump_Turn_On_Timeout;
extern volatile unsigned int g_vui_Ticker_LED_Blink_Timeout;

extern unsigned char g_uc_Flag_LED_State;
extern unsigned char g_uc_Flag_Send_Data;
extern unsigned char g_uc_ECU_Data_Msg[];
extern CanTxMsg Can_Tx_Msg;
extern CAN_InitTypeDef        CAN_InitStructure;
extern CAN_FilterInitTypeDef  CAN_FilterInitStructure;
extern USART_InitTypeDef USART_InitStructure;
extern GPIO_InitTypeDef GPIO_InitStructure;
extern EXTI_InitTypeDef EXTI_InitStructure;
extern ErrorStatus HSEStartUpStatus;

extern uint8_t 	g_uc_Uart1_Rx_Buf[];
extern uint8_t 	g_uc_Uart2_Rx_Buf[];
//extern uint8_t 	g_uc_Uart3_Rx_Buf[];
extern vuint16_t g_uc_Uart1_Wr_Data_Index, g_uc_Uart1_Rd_Data_Index;
extern vuint16_t g_uc_Uart2_Wr_Data_Index, g_uc_Uart2_Rd_Data_Index;
extern vuint16_t g_uc_Uart3_Wr_Data_Index, g_uc_Uart3_Rd_Data_Index;
char* itoa(int num, char* str, int base);

// System Init Handler
void RCC_Configuration(void);
void NVIC_Configuration(void);
void InitSysTickTimer (void);
void Timer_Configuration(void);
void Delay(u16 nTime);
void USART_Configuration (void);
void TransmitData (u8 *str);
void GPIO_Configuration(void);
void EXTI_Configuration (void);
unsigned char fn_Handle_Heartbeat_LED(void);

// CAN Handler
void CAN_Config(void);
unsigned char fn_uc_Send_Heartbeat_To_ECU(void);
unsigned char fn_uc_Send_Cruise_Button_Status_To_ECU(void);

// UART Handler
void fn_uc_Send_Byte_On_Debug_Port(u8 byt);
void fn_uc_Send_String_On_Debug_Port (char *bytes);

void fn_uc_Send_Byte_On_UART2_Port(u8 byt);
void fn_uc_Send_String_On_UART2_Port (unsigned char *bytes);

void fn_uc_Send_Byte_On_UART3_Port(u8 byt);
void fn_uc_Send_String_On_UART3_Port (unsigned char *bytes);
unsigned char fn_uc_RGB_LED_Off(void);
unsigned char fn_uc_RGB_LED_On(void);
void fn_Handle_LED_BUZZER_Indication(void);

// Timers
void SetTimer3(void);
void SetTimer4(void);

#define I2C_DELAY	600

void XGPG6857D(void);
extern unsigned short g_uc_Clock_Cycles_Read;
//unsigned char l_uc_fn_Ret_Val;
#endif /* __MAIN_H */

/******************* (C) COPYRIGHT 2013 SSPL *****END OF FILE*****************/
