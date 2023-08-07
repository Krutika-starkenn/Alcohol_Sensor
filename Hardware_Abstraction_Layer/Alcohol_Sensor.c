
#include "main.h"

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
    
	return SUCCESS;
}

