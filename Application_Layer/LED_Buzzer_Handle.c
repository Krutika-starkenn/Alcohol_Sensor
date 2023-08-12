/***********************************LED_Buzzer_Handle.c**********************************/

#include "main.h"

#define LED_BLINK_TIMEOUT								500
#define BUZZER_ON_TIMEOUT								500


volatile unsigned int g_vui_Ticker_LED_Blink_Timeout = 0;


void fn_Handle_LED_BUZZER_Indication(void)
{
	unsigned char l_uc_Current_State = 0;
	static unsigned char s_l_uc_Toggle = 0;
	static unsigned char s_l_uc_Prev_State = 0;
	
	l_uc_Current_State = Get_Current_Alcohol_State();
	if(l_uc_Current_State != s_l_uc_Prev_State)
	{
		s_l_uc_Prev_State = l_uc_Current_State;
		g_vui_Ticker_LED_Blink_Timeout = LED_BLINK_TIMEOUT;
		s_l_uc_Toggle = 0;
		
	}
	
	switch(l_uc_Current_State)
	{		
		case STATE_WAIT_FOR_TEST_START:
		{
			//blink yellow LED
			if(TEST_STARTED == fn_Get_Alcohol_Test_Start_Status())
			{
				if(!g_vui_Ticker_LED_Blink_Timeout)
				{
					g_vui_Ticker_LED_Blink_Timeout = LED_BLINK_TIMEOUT;
					if(RESET == s_l_uc_Toggle)
					{
						RED_LED_ON;
					}
					else
					{
						RED_LED_OFF;
					}
					s_l_uc_Toggle ^= 1;
					//toggle yellow LED
				}
			}
		}
		break;
		
		case STATE_MONITOR_AIRFLOW:
		{
			GREEN_LED_ON;
				//Turn On green LED solid
		}
		break;
		
		case STATE_HANDLE_AIR_SUCTION_PUMP:
		{
				if(!g_vui_Ticker_LED_Blink_Timeout)
				{
					g_vui_Ticker_LED_Blink_Timeout = LED_BLINK_TIMEOUT;
					if(RESET == s_l_uc_Toggle)
					{
						BLUE_LED_ON;
					}
					else
					{
						BLUE_LED_OFF;
					}
					s_l_uc_Toggle ^= 1;
					
					//toggle blue LED
				}
				
		}
		break;
		
		case STATE_START_ALCOHOL_SENSOR_DATA_SAMPLING:
		{
			
		}
		break;
		
		case STATE_PROCESS_SAMPLES:
		{
			BUZZER_ON;
			g_vui_Ticker_LED_Blink_Timeout = BUZZER_ON_TIMEOUT;
			while(g_vui_Ticker_LED_Blink_Timeout);
			BUZZER_OFF;					
			
			//play buzzer
		}
		break;
		
		case STATE_SEND_RESULT_TO_ECU:
		{
			
		}
		break;		
	}
}





















/***********************************End of LED_Buzzer_Handle.c**********************************/
