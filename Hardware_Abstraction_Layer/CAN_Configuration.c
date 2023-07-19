#include "main.h"




/*******************************************************************************
* Function Name  : CAN_Config
* Description    : Configures the CAN, transmit and receive using interrupt.
* Input          : None
* Output         : None
* Return         : PASSED if the reception is well done, FAILED in other case
*******************************************************************************/
void CAN_Config(void)
{
	/* CAN register init */																																			// understand CAN module correctly 
	CAN_DeInit();
	CAN_StructInit(&CAN_InitStructure);

	/* CAN cell init */
	CAN_InitStructure.CAN_TTCM = DISABLE;
	CAN_InitStructure.CAN_ABOM = DISABLE;
	CAN_InitStructure.CAN_AWUM = DISABLE;
	CAN_InitStructure.CAN_NART = DISABLE;//ENABLE;
	CAN_InitStructure.CAN_RFLM = ENABLE;
	CAN_InitStructure.CAN_TXFP = DISABLE;
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;	/*	CAN_Mode_LoopBack;	*/ 	
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
	CAN_InitStructure.CAN_BS1 = CAN_BS1_12tq;
	CAN_InitStructure.CAN_BS2 = CAN_BS2_5tq;
	CAN_InitStructure.CAN_Prescaler = 2;
	CAN_Init(&CAN_InitStructure);   
    
	/* CAN filter init */
	CAN_FilterInitStructure.CAN_FilterNumber = 0;
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdList;
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_16bit;
	/*For a SID the numbers for the Filter/Mask IDs need to be shifted to the left by 5 bits.*/
    CAN_FilterInitStructure.CAN_FilterIdHigh = (CAN_RX_ID_OF_START_ALCOHOL_TEST << 5);
    CAN_FilterInitStructure.CAN_FilterIdLow = (CAN_RX_ID_OF_ALCOHOL_THRESHOLD << 5);
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = (CAN_RX_ID_OF_PERIPHERAL_RESET << 5);
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO0;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);	
	
	
	/* CAN filter init */
	CAN_FilterInitStructure.CAN_FilterNumber = 1;
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdList;
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_16bit;
	/*For a SID the numbers for the Filter/Mask IDs need to be shifted to the left by 5 bits.*/
    CAN_FilterInitStructure.CAN_FilterIdHigh = (CAN_RX_ID_OF_TPMS_THRESHOLDS_MESSAGE << 5);
    CAN_FilterInitStructure.CAN_FilterIdLow = (CAN_RX_ID_OF_TPMS_TYRE_CONFIGURATION_MESSAGE << 5);
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = (CAN_RX_ID_OF_DRIVER_DROWSINESS_SPEED_MESSAGE << 5);
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = (CAN_RX_ID_OF_DATE_TIME_BROADCAST << 5);
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO0;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);
	
	
	CAN_FilterInitStructure.CAN_FilterNumber = 2;
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdList;
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_16bit;
	/*For a SID the numbers for the Filter/Mask IDs need to be shifted to the left by 5 bits.*/
    CAN_FilterInitStructure.CAN_FilterIdHigh = (CAN_RX_ID_OF_IMAGE_TRANSFER_REQUEST_REPLY << 5);
    CAN_FilterInitStructure.CAN_FilterIdLow = (CAN_RX_ID_OF_IMAGE_TRANSFER_STATUS << 5);
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO0;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);
	/* CAN FIFO0 message pending interrupt enable */ 
	CAN_ITConfig(CAN_IT_FMP0, ENABLE);
}


/*******************************************************************************
* Function Name  : fn_uc_Send_Heartbit_To_ECU
* Description    : This function Sends Heartbit to ECU Board
* Input          : none
* Output         : Send CAN Message
* Return         : SUCCESS/FAILURE
* Author         : Mr.Shreyas Apte
*******************************************************************************/
unsigned char fn_uc_Send_Heartbeat_To_ECU(void)
{

	unsigned char l_uc_Mailbox_No = 0;
    unsigned short l_us_CAN_Msg_Send_Attempts = 0;
	
	if(!g_vui_Ticker_Accessory_Board_Heartbeat)
	{
		Can_Tx_Msg.g_ul_Can_Tx_STD_ID = CAN_TX_ID_OF_ACCESSORY_BOARD_HEARTEAT;
		Can_Tx_Msg.g_ul_Can_Tx_EXD_ID = 0x00;
		Can_Tx_Msg.g_uc_Can_Tx_IDE = CAN_ID_STD;
		Can_Tx_Msg.g_uc_Can_Tx_DLC = 8;
		Can_Tx_Msg.g_uc_Can_Tx_RTR = CAN_RTR_DATA;
	 
		// Set Alarm number in Byte 0
		Can_Tx_Msg.g_uc_Can_Tx_DATA[0] = 0x22;
		
		/* Reset all data bytes to zero */
		Can_Tx_Msg.g_uc_Can_Tx_DATA[1] = 0;	
		Can_Tx_Msg.g_uc_Can_Tx_DATA[2] = 0;
		Can_Tx_Msg.g_uc_Can_Tx_DATA[3] = 0;
		Can_Tx_Msg.g_uc_Can_Tx_DATA[4] = 0;
		Can_Tx_Msg.g_uc_Can_Tx_DATA[5] = 0;
		Can_Tx_Msg.g_uc_Can_Tx_DATA[6] = 0;
		Can_Tx_Msg.g_uc_Can_Tx_DATA[7] = 0;
        
           
    lbl_Resend_CAN_Msg:
     l_uc_Mailbox_No = CAN_Transmit(&Can_Tx_Msg);

    #if REMOVE_WAITING_FOR_CAN_NODE
    while (CAN_NO_MB == l_uc_Mailbox_No)
    {
        l_us_CAN_Msg_Send_Attempts++;
        if(l_us_CAN_Msg_Send_Attempts > NO_MAILBOX_ATTEMPT_COUNTER)
        {
            #if SEND_CAN_DEBUG
            fn_uc_Send_String_On_Debug_Port("\r\n No mailbox: fn_uc_Send_Heartbeat_To_ECU");
            #endif
            return FAILURE;
        }
        goto lbl_Resend_CAN_Msg;
    }


#if DONT_WAIT_FOR_CAN_MSG_TRANSMIT_STATUS

    l_us_CAN_Msg_Send_Attempts = 0;
    while (CANTXPENDING == CAN_TransmitStatus(l_uc_Mailbox_No))
    {
        l_us_CAN_Msg_Send_Attempts++;
        if(l_us_CAN_Msg_Send_Attempts > CAN_MESSAGE_PENDING_COUNT)
        {
            #if SEND_CAN_DEBUG
				fn_uc_Send_String_On_Debug_Port("\r\n CAN tx pending: fn_uc_Send_Heartbeat_To_ECU");
            #endif
            return FAILURE;
        }
    } 
    
    #else
    
    while (CANTXPENDING == CAN_TransmitStatus(l_uc_Mailbox_No))// || g_vui_Ticker_mSec > 0)
    {
        if(s_l_uc_Once_Sent == 0)
        {
            s_l_uc_Once_Sent = 1;
            fn_uc_Send_String_On_Debug_Port("\r\n CAN tx pending: fn_uc_Send_Heartbeat_To_ECU");
        }
    }  
    s_l_uc_Once_Sent = 0;
    
    #endif
    
    #endif
    
    if(CANTXFAILED == CAN_TransmitStatus(l_uc_Mailbox_No))
    {
        fn_uc_Send_String_On_Debug_Port("\r\n CAN tx failed: fn_uc_Send_Heartbeat_To_ECU");
        return FAILURE;
    }
		
		g_vui_Ticker_Accessory_Board_Heartbeat = ACC_BOARD_HEARTBEAT_SEND_TIME;
       
	}
	
	return SUCCESS;
}





/******************* (C) COPYRIGHT 2013 SSPL *****END OF FILE*****************/

