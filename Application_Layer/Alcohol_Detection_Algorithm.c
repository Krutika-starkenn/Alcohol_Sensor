#include "main.h"

unsigned char g_uc_Alcohol_State_Machine = 0;
unsigned int g_ui_ADC_CH10_Data = 0;
unsigned int g_ui_ADC_CH11_Data = 0;
unsigned short g_us_Alcohol_Sensor_Raw_ADC_Data = 0;
unsigned char g_uc_Flag_Air_Sampling_Pump_State = 0;

unsigned char g_uc_Flag_Start_Alcohol_Test = 0;
unsigned char g_uc_Alcohol_Threshold_Mode = 0;

unsigned char g_uc_Alcohol_Test_Status = 0;
unsigned short g_us_Measured_Alcohol_Level = 0;

volatile unsigned int g_vui_Ticker_Alcohol_Test_Timeout_Timer = 0;
volatile unsigned int g_vui_Ticker_Alcohol_Sensor_Data_Sampling_Timer = 0;
volatile unsigned int g_vui_Ticker_Timeout_For_Pump_Activation_Timer = 0;

unsigned short g_a_us_1msec_Readings[20];
unsigned short g_a_us_10msec_Readings[1010];
volatile unsigned int g_vui_Ticker_Alcohol_Sensor_Sampling_Interval_Integration = 0;
volatile unsigned int g_v_ui_Ticker_Stop_Vibrations = 0;

unsigned short g_us_10ms_Index = 0;
unsigned int g_ui_Average_Val = 0;
unsigned short g_us_1msec_Reading_Index = 0;
unsigned char g_uc_Take_Initial_Readings = 1;
unsigned int g_ui_Base_Reading = 0;
float g_f_BAC = 0;
tdst_Temp_Calculated_Values gost_Temperature_Data;
tdst_Pressure_Calculated_Values gost_Pressure_Calculated_Values;



void fn_uc_Handle_Alcohol_Test(void)
{
	switch(g_uc_Alcohol_State_Machine)
	{
		case STATE_WAIT_FOR_TEST_START:
		{
			// if Start Alcohol test Msg received from DMS then start timer
			if(1 == g_uc_Flag_Start_Alcohol_Test)
			{
				// Go to Next state and wait for User to blow on sensor
				g_vui_Ticker_Alcohol_Test_Timeout_Timer = ALCOHOL_TEST_TIMEOUT_TIMER;
			}
			
			g_uc_Alcohol_State_Machine++;
		}
		break;
		
		case STATE_MONITOR_AIRFLOW:
		{
					// Monitor air flow on pressure sensor
					//fn_v_Monitor_Pressure_And_Temperature();
		
          /*  if(0 == g_uc_Take_Initial_Readings)
            {
                gost_Pressure_Calculated_Values.i_Temp_Compensated_Pressure = AIR_FLOW_DETECTION_THRESHOLD;
                sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n Kindly wait initializing the Breathalyzer....");
                fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);
            }*/
			// if Pressure exceeds threshold then go to next state to turn ON Pump
            
			if(gost_Pressure_Calculated_Values.i_Temp_Compensated_Pressure >= AIR_FLOW_DETECTION_THRESHOLD)
			{
				// Send Alcohol Test Started Message to ECU or user
				//fn_uc_Send_Alcohol_Test_Start_Status_To_ECU(ALCOHOL_TEST_STARTED);
				if(1 == g_uc_Take_Initial_Readings)
				{
						fn_uc_Send_String_On_Debug_Port("\r\n Blow detected");
				}
				// Go to Next State to Start collecting Air Sample
				g_uc_Flag_Air_Sampling_Pump_State = 1;
				g_uc_Alcohol_State_Machine = STATE_HANDLE_AIR_SUCTION_PUMP;
				g_vui_Ticker_Timeout_For_Pump_Activation_Timer = PUMP_ACTIVATION_TIMEOUT;
				
				GPIO_WriteBit(GPIOC, GPIO_Pin_1, Bit_RESET);
				break;
			}
			
			if(1 == g_uc_Flag_Start_Alcohol_Test)
			{
				if(!g_vui_Ticker_Alcohol_Test_Timeout_Timer)
				{
					// Send Alcohol Test Timeout Message to ECU to display on HMI
					//fn_uc_Send_Alcohol_Test_Start_Status_To_ECU(ALCOHOL_TEST_TIMEOUT);
					
					// Restart Test
					g_uc_Alcohol_Test_Status = TEST_TIMEOUT;
					g_us_Measured_Alcohol_Level = 0;
					g_uc_Alcohol_State_Machine = STATE_SEND_RESULT_TO_ECU;
				}
			}
			else			
			{
				g_uc_Alcohol_State_Machine = STATE_WAIT_FOR_TEST_START;
			}
		}
		break;
		
		case STATE_HANDLE_AIR_SUCTION_PUMP:
		{
			if(0 == g_uc_Flag_Air_Sampling_Pump_State)
			{
				// Turn Off Pump
//                TURN_OFF_AIR_SAMPLING_PUMP;
//                GPIO_WriteBit(GPIOC, GPIO_Pin_1, Bit_RESET);
				// Go to Pressure monitoring state
				g_uc_Alcohol_State_Machine = STATE_PROCESS_SAMPLES;
			}
			else if((1 == g_uc_Flag_Air_Sampling_Pump_State) && (0 == g_vui_Ticker_Timeout_For_Pump_Activation_Timer))
			{
//                if(1 == g_uc_Take_Initial_Readings)
//                {
//                    fn_uc_Send_String_On_Debug_Port("\r\n Capturing data");
//                }
//                else
//                {
//                    fn_uc_Send_String_On_Debug_Port("\r\n Processing....");
//                }
                GPIO_WriteBit(GPIOC, GPIO_Pin_1, Bit_SET);
				// start AIR Sampling pump and start timer for 
				TURN_ON_AIR_SAMPLING_PUMP;
				
				// Start sampling timer
				g_vui_Ticker_Alcohol_Sensor_Data_Sampling_Timer = ALCOHOL_SENSOR_DATA_SAMPLING_TIME;
                g_vui_Ticker_Timeout_For_Pump_Activation_Timer = PUMP_ON_TIMEOUT;
				
				// Go for Sampling
				g_uc_Alcohol_State_Machine = STATE_START_ALCOHOL_SENSOR_DATA_SAMPLING;
				
				#if DEBUG_ALCOHOL_SENSOR_RAW_ADC_DATA
					sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n Alc ADC Raw Data:");
					fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);
				#endif
			}
			else
			{
				
			}
		}
		break;
		
		case STATE_START_ALCOHOL_SENSOR_DATA_SAMPLING:
		{
            
			if(g_vui_Ticker_Alcohol_Sensor_Data_Sampling_Timer)
//			while(g_vui_Ticker_Alcohol_Sensor_Data_Sampling_Timer)
			{
                
                if(0 == g_uc_Take_Initial_Readings)
                {
                    if((g_vui_Ticker_Alcohol_Sensor_Data_Sampling_Timer%1000) == 0)
                    {
                        sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n %d... ",g_vui_Ticker_Alcohol_Sensor_Data_Sampling_Timer/1000);
                        fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);
                    }
                }
                
                if(!g_vui_Ticker_Alcohol_Sensor_Sampling_Interval_Integration)
                {
                    g_vui_Ticker_Alcohol_Sensor_Sampling_Interval_Integration = 1;
                    if(SUCCESS != fn_uc_Get_Alcohol_Sensor_Raw_ADC_Data(&g_us_Alcohol_Sensor_Raw_ADC_Data))
                    {
                        
                    }
                    
                    g_a_us_1msec_Readings[g_us_1msec_Reading_Index] = g_us_Alcohol_Sensor_Raw_ADC_Data;

                    g_ui_Average_Val += g_a_us_1msec_Readings[g_us_1msec_Reading_Index];
                    g_us_1msec_Reading_Index++;
                    if(g_us_1msec_Reading_Index >= 10)
                    {
                        g_ui_Average_Val /= 10;
                        g_a_us_10msec_Readings[g_us_10ms_Index] = g_ui_Average_Val;
                        g_us_10ms_Index ++;
                        g_us_1msec_Reading_Index = 0;
                        g_ui_Average_Val = 0;
                    }
                }
			
			#if DEBUG_ALCOHOL_SENSOR_RAW_ADC_DATA
				sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n %d", g_us_Alcohol_Sensor_Raw_ADC_Data);
				fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);
			#endif
						
                if(!g_vui_Ticker_Timeout_For_Pump_Activation_Timer)
                {
                    g_vui_Ticker_Timeout_For_Pump_Activation_Timer = 20000;
                    TURN_OFF_AIR_SAMPLING_PUMP;
                }
			
            }
            else
            {
                g_uc_Flag_Air_Sampling_Pump_State = 0;
                g_uc_Alcohol_State_Machine = STATE_HANDLE_AIR_SUCTION_PUMP;
                GPIO_WriteBit(GPIOC, GPIO_Pin_1, Bit_RESET);
            }
            
            
		}
		break;
		
		case STATE_PROCESS_SAMPLES:
		{			
            unsigned short l_us_Process_Result_Index = 0;
            //float l_f_Rel_Voltage = 0;
            g_ui_Average_Val = 0;
			// Process captured data
            for(l_us_Process_Result_Index = 0; l_us_Process_Result_Index < g_us_10ms_Index; l_us_Process_Result_Index++)
            {
                g_ui_Average_Val += g_a_us_10msec_Readings[l_us_Process_Result_Index];
                //l_f_Rel_Voltage = g_a_us_10msec_Readings[l_us_Process_Result_Index] * 0.000811;
//				sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n %d \t, %.3f", g_a_us_10msec_Readings[l_us_Process_Result_Index], l_f_Rel_Voltage);
//				fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);
                
                g_a_us_10msec_Readings[l_us_Process_Result_Index] = 0;
            }

            g_us_10ms_Index = 0;
            g_us_1msec_Reading_Index = 0;
			
			// clear start test flag
			g_uc_Flag_Start_Alcohol_Test = 0;
			
			g_uc_Alcohol_State_Machine = STATE_SEND_RESULT_TO_ECU;
		}
		break;
		
		case STATE_SEND_RESULT_TO_ECU:
		{
			// Send Result to ECU
            signed int l_si_Temp_Val = 0;
            float l_f_BAC = 0;
            
			//fn_uc_Send_Alcohol_Test_Result_To_ECU(g_uc_Alcohol_Test_Status, g_us_Measured_Alcohol_Level);
			g_uc_Alcohol_State_Machine = STATE_MONITOR_AIRFLOW;
            
            if(0 == g_uc_Take_Initial_Readings)
            {
                g_uc_Take_Initial_Readings = 1;
                g_ui_Base_Reading = g_ui_Average_Val;
                sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n Breathalyzer can now be used");
                fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);
                
                l_si_Temp_Val = g_ui_Average_Val - g_ui_Base_Reading;
                l_f_BAC = l_si_Temp_Val * 0.000007495164;
                
            }
            else
            {
                l_si_Temp_Val = g_ui_Average_Val - 1030000;
                l_f_BAC = l_si_Temp_Val * 0.000007495164;
                
                if(l_f_BAC < 0)
                {
                    l_f_BAC = 0;
                }
                
            }
            g_f_BAC = l_f_BAC;
//            sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n Integral: %d\t Estimated BAC: %.3f",g_ui_Average_Val, l_f_BAC);
            sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n%.3f", l_f_BAC);
            fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);
            
            g_ui_Average_Val = 0;
            
		}
		break;
	}
	
}


unsigned char fn_uc_Get_Alcohol_Sensor_Raw_ADC_Data(unsigned short *arg_ptr_Result)
{
	unsigned short l_us_Sampling_Counter = 0;
	unsigned int l_ui_Instanteneous_Data = 0;
	unsigned int l_ui_Sample_Addition = 0;
		
	*arg_ptr_Result = 0;

	for(l_us_Sampling_Counter = 0 ; l_us_Sampling_Counter < ALCOHOL_SENSOR_ADC_SAMPLING_COUNTS; l_us_Sampling_Counter++)
	{
	
		if(SUCCESS == fn_Get_ADC_Channel_Data(ADC_1, ALCOHOL_SENSOR_ANALOG_INPUT_READ_CHANNEL, &l_ui_Instanteneous_Data))
		{		
			//sprintf(&g_uc_Transmit_Buffer[0],"\r\n Inst data - %d", l_ui_Instanteneous_Data);
			//fn_UART_Send_String(g_uc_Transmit_Buffer);
			#if ALCOHOL_ADC_DEBUG	
			sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n Inst data - %d", l_ui_Instanteneous_Data);
			fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);
			#endif
			l_ui_Sample_Addition = l_ui_Sample_Addition + l_ui_Instanteneous_Data;

			#if ALCOHOL_ADC_DEBUG			
				sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n Sampling data - %d", l_ui_Sample_Addition);
//				fn_UART_Send_String(g_uc_Transmit_Buffer);		
				fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);			
			#endif			
			
			l_ui_Instanteneous_Data = 0;
		}
		else
		{
			
			sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n ADC Read Fail");
			//fn_UART_Send_String(g_uc_Transmit_Buffer);
			fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);
			
			return FAILURE;
		}
	}
    
    l_ui_Sample_Addition = (l_ui_Sample_Addition / ALCOHOL_SENSOR_ADC_SAMPLING_COUNTS);
	
	*arg_ptr_Result = (unsigned short)l_ui_Sample_Addition ;
    
		
	
//    if(SUCCESS == fn_Get_ADC_Channel_Data(ADC_1, ADC_Channel_10, &l_ui_Instanteneous_Data))
//    {		
//        sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n 1 : %d", l_ui_Instanteneous_Data);
//			fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);
//    }
//    
//    if(SUCCESS == fn_Get_ADC_Channel_Data(ADC_1, ADC_Channel_11, &l_ui_Instanteneous_Data))
//    {		
//        sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n 2 : %d", l_ui_Instanteneous_Data);
//			fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);
//    }
//    
//    if(SUCCESS == fn_Get_ADC_Channel_Data(ADC_1, ADC_Channel_12, &l_ui_Instanteneous_Data))
//    {		
//			sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n 3 : %d", l_ui_Instanteneous_Data);
//			fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);
//    }
//    
//    if(SUCCESS == fn_Get_ADC_Channel_Data(ADC_1, ADC_Channel_13, &l_ui_Instanteneous_Data))
//    {		
//			sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n 4 : %d", l_ui_Instanteneous_Data);
//			fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);
//    }

	return SUCCESS;
}


unsigned char fn_uc_Send_Alcohol_Test_Start_Status_To_ECU(unsigned char arg_uc_Status)
{
	unsigned char l_uc_Mailbox_No = 0;
    unsigned short l_us_CAN_Msg_Send_Attempts = 0;
	
	Can_Tx_Msg.g_ul_Can_Tx_STD_ID = CAN_TX_ID_OF_ALCOHOL_TEST_START_STATUS;
	Can_Tx_Msg.g_ul_Can_Tx_EXD_ID = 0x00;
	Can_Tx_Msg.g_uc_Can_Tx_IDE = CAN_ID_STD;
	Can_Tx_Msg.g_uc_Can_Tx_DLC = 8;
	Can_Tx_Msg.g_uc_Can_Tx_RTR = CAN_RTR_DATA;
	
	Can_Tx_Msg.g_uc_Can_Tx_DATA[0] = arg_uc_Status;
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
            fn_uc_Send_String_On_Debug_Port("\r\n No mailbox: fn_uc_Send_Alcohol_Test_Start_Status_To_ECU");
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
				fn_uc_Send_String_On_Debug_Port("\r\n CAN tx pending: fn_uc_Send_Alcohol_Test_Start_Status_To_ECU");
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
            fn_uc_Send_String_On_Debug_Port("\r\n CAN tx pending: fn_uc_Send_Alcohol_Test_Start_Status_To_ECU");
        }
    }  
    s_l_uc_Once_Sent = 0;
    
    #endif
    
    #endif
    
    if(CANTXFAILED == CAN_TransmitStatus(l_uc_Mailbox_No))
    {
        fn_uc_Send_String_On_Debug_Port("\r\n CAN tx failed: fn_uc_Send_Alcohol_Test_Start_Status_To_ECU");
        return FAILURE;
    }
	
	return SUCCESS;
}

unsigned char fn_uc_Send_Alcohol_Test_Result_To_ECU(unsigned char arg_uc_Alcohol_Test_Result_Status, unsigned short arg_us_Measured_Alcohol_Level)
{
	unsigned char l_uc_Mailbox_No = 0;
    unsigned short l_us_CAN_Msg_Send_Attempts = 0;
	
	Can_Tx_Msg.g_ul_Can_Tx_STD_ID = CAN_TX_ID_OF_ALCOHOL_TEST_START_STATUS;
	Can_Tx_Msg.g_ul_Can_Tx_EXD_ID = 0x00;
	Can_Tx_Msg.g_uc_Can_Tx_IDE = CAN_ID_STD;
	Can_Tx_Msg.g_uc_Can_Tx_DLC = 8;
	Can_Tx_Msg.g_uc_Can_Tx_RTR = CAN_RTR_DATA;
	
	Can_Tx_Msg.g_uc_Can_Tx_DATA[0] = arg_uc_Alcohol_Test_Result_Status;
	Can_Tx_Msg.g_uc_Can_Tx_DATA[1] = (arg_us_Measured_Alcohol_Level >> 8) ;
	Can_Tx_Msg.g_uc_Can_Tx_DATA[2] = (arg_us_Measured_Alcohol_Level & 0xFF);
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
            fn_uc_Send_String_On_Debug_Port("\r\n No mailbox: fn_uc_Send_Alcohol_Test_Result_To_ECU");
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
				fn_uc_Send_String_On_Debug_Port("\r\n CAN tx pending: fn_uc_Send_Alcohol_Test_Result_To_ECU");
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
            fn_uc_Send_String_On_Debug_Port("\r\n CAN tx pending: fn_uc_Send_Alcohol_Test_Result_To_ECU");
        }
    }  
    s_l_uc_Once_Sent = 0;
    
    #endif
    
    #endif
    
    if(CANTXFAILED == CAN_TransmitStatus(l_uc_Mailbox_No))
    {
        fn_uc_Send_String_On_Debug_Port("\r\n CAN tx failed: fn_uc_Send_Alcohol_Test_Result_To_ECU");
        return FAILURE;
    }
	return SUCCESS;


}



unsigned char fn_uc_Calculate_Integral(unsigned short *arg_ptr_us_Data_To_Be_Integrated, unsigned short arg_us_Number_Of_Bytes)
{
    
    return SUCCESS;
}


void fn_Calculate_Time_Period_Using_Port_Pin(void)
{
    static unsigned char l_s_uc_Toggle = 0;
    if(l_s_uc_Toggle)
    {
        GPIO_WriteBit(GPIOC, GPIO_Pin_2, Bit_SET);
    }
    else
    {
        GPIO_WriteBit(GPIOC, GPIO_Pin_2, Bit_RESET);
    }
    l_s_uc_Toggle = l_s_uc_Toggle ^ 1;

}

unsigned fn_uc_Handle_Cap_Vibrations(void)
{
    static unsigned char l_s_uc_Start_Vibrations = 0;
    
    if(g_f_BAC > 0.03)
//    if(g_f_BAC > 0)
    {
        if(0 == l_s_uc_Start_Vibrations)
        {
            l_s_uc_Start_Vibrations = 1;
            START_VIBRATION;
            g_v_ui_Ticker_Stop_Vibrations = 5000;
        }
    }
    
    if((1 == l_s_uc_Start_Vibrations) && (!g_v_ui_Ticker_Stop_Vibrations))
    {
        STOP_VIBRATION;
        l_s_uc_Start_Vibrations = 0;
        g_f_BAC = 0;
    }
    return SUCCESS;
}
