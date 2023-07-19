
/******************** (C) COPYRIGHT 2017 SST ***********************************
* File Name          : macro_const.h
* Author             : Mr. Naresh S. Partole
* Version            : V1.0.1
* Date               : 19/07/2017
* Description        : Main program body.
********************************************************************************/

#include "main.h"

#define UART_RX_BUF		                            1500
#define UART_TX_BUF		                            1500
#define UART_BUF_SIZE	                            1500
#define UART3_BUF_SIZE								5000

#define	PWR_ON_CYC_DLY					            250


// CAN TX Messages from LED Card
#define CAN_TX_ID_OF_ACCESSORY_BOARD_HEARTEAT       0x200
#define CAN_RX_ID_OF_PERIPHERAL_RESET				0x0B0
//CAN Constants
#define REMOVE_WAITING_FOR_CAN_NODE                                     1
#define CAN_MESSAGE_PENDING_COUNT                                       1000
#define NO_MAILBOX_ATTEMPT_COUNTER                                      50
#define DONT_WAIT_FOR_CAN_MSG_TRANSMIT_STATUS                           1

#define SEND_CAN_DEBUG                                                  0


#define WAIT(x)				                        sec=x;while(sec);	

#define	ON					                        1
#define	OFF					                        0


#define DELAY(x)					 	            while(x) x--;

#define FAILURE                             	   	0
#define SUCESS									   	1

#define ELAPSED								        0
#define STARTED								        1


#define ECU_HEARTBEAT_TIMER                         500
#define ACC_BOARD_HEARTBEAT_SEND_TIME				1000
#define POWER_ON_WAIT_TIME							10000
					
#define ALCOHOL_ADC_DEBUG		0


