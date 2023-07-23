
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "string.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/ 
unsigned int g_ui_ADC_CH0_Data;
unsigned int g_ui_ADC_CH1_Data;
unsigned int g_ui_ADC_CH2_Data;
unsigned int g_ui_ADC_CH3_Data;

/********************************************************************************************************************************************
Function Name		: void Initialize_ADC1_Module(void)
Description			: This function can be used initialize ADC1 module of STM32F105xx
Input Parameters 	: None
Output Parameters	: None
Author				: Mr. Shreyas Apte
********************************************************************************************************************************************/
unsigned char fn_uc_Initialize_ADC1_Module(void)
{
	// Initilize ADC Module
	ADC_InitTypeDef ADC_InitStructure; 
	
	/* Configure GPIOC Pin0,1,2,3 as input function pull-up */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;// | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;					 					
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//	GPIO_Init(GPIOC, &GPIO_InitStructure);	
  
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1 ;//| GPIO_Pin_2 | GPIO_Pin_3;					 					
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//GPIO_Mode_IPU;//GPIO_Mode_IN_FLOATING;//GPIO_Mode_IN_FLOATING;//GPIO_Mode_IPU;//GPIO_Mode_IN_FLOATING;//GPIO_Mode_IPU;//GPIO_Mode_IN_FLOATING;//GPIO_Mode_IN_FLOATING;//GPIO_Mode_IPU;//GPIO_Mode_IN_FLOATING;//;//;//;//GPIO_Mode_IPD;//GPIO_Mode_IN_FLOATING;//GPIO_Mode_IN_FLOATING;//GPIO_Mode_Out_PP;//GPIO_Mode_Out_OD;//GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
    //PC0 : ADC Ch 10
    //PC1 : ADC Ch 11
    //PC2 : ADC Ch 12
    //PC3 : ADC Ch 13
    
    //PA0 : ADC Ch 0
    //PA1 : ADC Ch 1
    //PA2 : ADC Ch 2
    //PA3 : ADC Ch 3
 
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);  
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	//ADC_DeInit(ADC1); 
	ADC_DeInit(ADC1);
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	//ADC_Init(ADC1, &ADC_InitStructure);	   
	ADC_Init(ADC1, &ADC_InitStructure);	
	//ADC_RegularChannelConfig(ADC1,ADC_Channel_1, 1,ADC_SampleTime_28Cycles5); // define regular conversion config
	//ADC_Init(ADC1, &ADC_InitStructure); //set config of ADC1
//	ADC_Cmd(ADC1, ENABLE);	
	ADC_Cmd(ADC1, ENABLE);	
	
//	ADC_ResetCalibration(ADC1);
	ADC_ResetCalibration(ADC1);

	
//	while(ADC_GetResetCalibrationStatus(ADC1));	
	while(ADC_GetResetCalibrationStatus(ADC1));	
//	ADC_StartCalibration(ADC1);	 
 	ADC_StartCalibration(ADC1);	
	//while(ADC_GetCalibrationStatus(ADC1));
	while(ADC_GetCalibrationStatus(ADC1));
	// start conversion
	//ADC_Cmd (ADC1,ENABLE);                   //enable ADC1
	ADC_Cmd (ADC1,ENABLE);
	ADC_Cmd (ADC1,ENABLE);
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);	
	return SUCCESS;
}				  



/********************************************************************************************************************************************
Function Name		: unsigned char fn_Get_ADC_Channel_Data(unsigned char ADC_Number, unsigned char l_uc_ADC_Channel_Number, unsigned int *l_ui_Instanteneous_Data)
Description			: This function is used for reading ADC data from selected ADC Module and ADC Channel
Input Parameters 	: l_uc_ADC_Number 		   - ADC1 or ADC1 
					  l_uc_ADC_Channel_Number  - Channel 1 to Channel 17
					  *l_ui_Instanteneous_Data - pointer of the variable where result will get stored
Output Parameters	: SUCCESS	- Function will return SUCCESS in case of successful operation
					  FAILURE	- Function will return FAILURE in case of wrong input parameter
Author				: Mr. Shreyas Apte
********************************************************************************************************************************************/
unsigned char fn_Get_ADC_Channel_Data(unsigned char l_uc_ADC_Number, unsigned char l_uc_ADC_Channel_Number, unsigned int *l_ui_Instanteneous_Data)
{
	
	ADC_TypeDef *l_p_struct_ADC_Base_Address;
	*l_ui_Instanteneous_Data = 0;
//	fn_uc_Send_String_On_Debug_Port("\r\n Inside fn_Get_ADC_Channel_Data");
//	sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n ADC number - %d", l_uc_ADC_Number);
//			fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);
//	sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n ADC channel number - %d", l_uc_ADC_Channel_Number);
//			fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);
//	sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\nData - %d", *l_ui_Instanteneous_Data);
//			fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);
	if(ADC_1 == l_uc_ADC_Number)
	{
		l_p_struct_ADC_Base_Address = ADC1;		
	}
	else if(ADC_2 == l_uc_ADC_Number)
	{
		l_p_struct_ADC_Base_Address = ADC2;
	}
	else
	{		
		return FAILURE;
	}
	
	if(l_uc_ADC_Channel_Number <= ADC_Channel_17)
	{
		// Valid channel
	}
	else
	{
		return FAILURE;
	}
	
	ADC_ClearFlag(l_p_struct_ADC_Base_Address, ADC_FLAG_EOC);

	ADC_RegularChannelConfig(l_p_struct_ADC_Base_Address, l_uc_ADC_Channel_Number, 1, ADC_SampleTime_55Cycles5);//ADC_SampleTime_55Cycles5);
	
	ADC_SoftwareStartConvCmd(l_p_struct_ADC_Base_Address, ENABLE);		
	 
  	while(!ADC_GetFlagStatus(l_p_struct_ADC_Base_Address, ADC_FLAG_EOC ))
	{
		// Wait till ADC Conversion complete1s
		
	}

	*l_ui_Instanteneous_Data = ADC_GetConversionValue(l_p_struct_ADC_Base_Address);
//	sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n ADC_OUT: %d", *l_ui_Instanteneous_Data);
	sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n %d", *l_ui_Instanteneous_Data);
                   fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);
//	#if  DEBUG_BATTERY_LEVEL_RAW_ADC_DATA
//                    sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n ADC counts: %d", *l_ui_Instanteneous_Data);
//                    fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);
//    #endif
		
	//sprintf(&g_uc_Transmit_Buffer[0],"\r\n Inst Data from 1st fn - %d", *l_ui_Instanteneous_Data);
	//fn_UART_Send_String(g_uc_Transmit_Buffer);
	
	return SUCCESS;
}





/********************************************************************************************************************************************
Function Name		: unsigned char fn_Get_ADC_Sampled_Data(unsigned char l_uc_ADC_Number, unsigned char l_uc_ADC_Channel_Number, unsigned int *l_ui_Sampled_Data)
Description			: This function takes number of Samples from ADC and gives out the average value of samples for processing
Input Parameters 	: l_uc_ADC_Number 		   - ADC1 or ADC1 
					  l_uc_ADC_Channel_Number  - Channel 1 to Channel 17
					  *l_ui_Instanteneous_Data - pointer of the variable where result will get stored
Output Parameters	: SUCCESS	- Function will return SUCCESS in case of successful operation
					  FAILURE	- Function will return FAILURE in case of wrong input parameter  
Author				: Mr. Shreyas Apte
********************************************************************************************************************************************/
unsigned char fn_Get_ADC_Sampled_Data(unsigned char l_uc_ADC_Number, unsigned char l_uc_ADC_Channel_Number, unsigned int *l_ui_Sampled_Data)
{
	unsigned short l_us_Sampling_Counter = 0;
	unsigned int l_ui_Instanteneous_Data = 0;
	
	
	*l_ui_Sampled_Data = 0;
	
	for(l_us_Sampling_Counter = 0 ; l_us_Sampling_Counter <= NUMBER_OF_ADC_SAMPLES_FOR_AVERAGING_DATA; l_us_Sampling_Counter++)
	{
		if(SUCCESS == fn_Get_ADC_Channel_Data(l_uc_ADC_Number, l_uc_ADC_Channel_Number, &l_ui_Instanteneous_Data))
		{		
			//sprintf(&g_uc_Transmit_Buffer[0],"\r\n Inst data - %d", l_ui_Instanteneous_Data);
			//fn_UART_Send_String(g_uc_Transmit_Buffer);
			
			*l_ui_Sampled_Data = *l_ui_Sampled_Data + l_ui_Instanteneous_Data;

//			#if 0			
//				sprintf(&g_uc_Transmit_Buffer[0],"\r\n Sampling data - %d", *l_ui_Sampled_Data);
//				fn_UART_Send_String(g_uc_Transmit_Buffer);			
//			#endif
       			
			
			l_ui_Instanteneous_Data = 0;
		}
		else
		{
			//sprintf(&g_uc_Transmit_Buffer[0],"\r\n ADC Read Fail");
			//fn_UART_Send_String(g_uc_Transmit_Buffer);
			
			return FAILURE;
		}
	}
	
	*l_ui_Sampled_Data = *l_ui_Sampled_Data / NUMBER_OF_ADC_SAMPLES_FOR_AVERAGING_DATA;
	
//	sprintf(&g_uc_Transmit_Buffer[0],"\r\n final Sampled data - %d", *l_ui_Sampled_Data);
//	fn_UART_Send_String(g_uc_Transmit_Buffer);
	 #if  DEBUG_BATTERY_LEVEL_RAW_ADC_DATA
                    sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n ADC Sample Data: %d",*l_ui_Sampled_Data);
                    fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);
	#endif	
	return SUCCESS;
}





/********************************************************************************************************************************************
Function Name		: unsigned char fn_Get_ADC_Sampled_Data_Of_Both_Channels(unsigned int *l_p_ui_Channel_10_Sampled_Data, unsigned int *l_p_ui_Channel_11_Sampled_Data)
Description			: This function can be used to get 2 ADC channels averaged sample data simultaneously
Input Parameters 	: l_p_ui_Channel_10_Sampled_Data - Integer pointer of Channel 10 data where data needs to be store
					  l_p_ui_Channel_11_Sampled_Data - Integer pointer of Channel 11 data where data needs to be store
Output Parameters	: SUCCESS	- Function will return SUCCESS in case of successful operation
					  FAILURE	- Function will return FAILURE in case of wrong input parameter  
Author				: Mr. Shreyas Apte
********************************************************************************************************************************************/
unsigned char fn_Get_ADC_Sampled_Data_Of_Both_APS_Channels(unsigned int *l_p_ui_APS_1_Input_Sampled_Data, unsigned int *l_p_ui_APS_2_Input_Sampled_Data)
{
	
	unsigned short l_us_Sampling_Counter = 0;
	unsigned int l_ui_Instanteneous_Data_APS_1_Input = 0;
	unsigned int l_ui_Instanteneous_Data_APS_2_Input = 0;
	
	*l_p_ui_APS_1_Input_Sampled_Data = 0;
	*l_p_ui_APS_2_Input_Sampled_Data = 0;
	
	for(l_us_Sampling_Counter = 0 ; l_us_Sampling_Counter <= NUMBER_OF_ADC_SAMPLES_FOR_AVERAGING_DATA; l_us_Sampling_Counter++)
	{
		if(SUCCESS == fn_Get_ADC_Channel_Data(ADC_1, INPUT_1, &l_ui_Instanteneous_Data_APS_1_Input))
		{			
			if(SUCCESS == fn_Get_ADC_Channel_Data(ADC_1, INPUT_2, &l_ui_Instanteneous_Data_APS_2_Input))
			{			
				*l_p_ui_APS_1_Input_Sampled_Data = *l_p_ui_APS_1_Input_Sampled_Data + l_ui_Instanteneous_Data_APS_1_Input;
				*l_p_ui_APS_2_Input_Sampled_Data = *l_p_ui_APS_2_Input_Sampled_Data + l_ui_Instanteneous_Data_APS_2_Input;							
				
				l_ui_Instanteneous_Data_APS_1_Input = 0;
				l_ui_Instanteneous_Data_APS_2_Input = 0;
			}
			else
			{
				return FAILURE;
			}
		}
		else
		{
			return FAILURE;
		}
	}
	
	*l_p_ui_APS_1_Input_Sampled_Data = *l_p_ui_APS_1_Input_Sampled_Data / NUMBER_OF_ADC_SAMPLES_FOR_AVERAGING_DATA;
	*l_p_ui_APS_2_Input_Sampled_Data = *l_p_ui_APS_2_Input_Sampled_Data / NUMBER_OF_ADC_SAMPLES_FOR_AVERAGING_DATA;	

	return SUCCESS;
}




/********************************************************************************************************************************************
Function Name		: unsigned char fn_Get_ADC_Sampled_Data_Of_Both_ECU_Channels(unsigned int *l_p_ui_Channel_12_Sampled_Data, unsigned int *l_p_ui_Channel_13_Sampled_Data)
Description			: This function can be used to get 2 ADC channels averaged sample data simultaneously
Input Parameters 	: l_p_ui_Channel_12_Sampled_Data - Integer pointer of Channel 12 data where data needs to be store
					  l_p_ui_Channel_13_Sampled_Data - Integer pointer of Channel 13 data where data needs to be store
Output Parameters	: SUCCESS	- Function will return SUCCESS in case of successful operation
					  FAILURE	- Function will return FAILURE in case of wrong input parameter  
Author				: Mr. Shreyas Apte
********************************************************************************************************************************************/
unsigned char fn_Get_ADC_Sampled_Data_Of_Both_ECU_Channels(unsigned int *l_p_ui_DAC_APS_1_Output_Sampled_Data, unsigned int *l_p_ui_DAC_APS_2_Output_Sampled_Data)
{
	
	unsigned short l_us_Sampling_Counter = 0;
	unsigned int l_ui_Instanteneous_Data_DAC_APS_1_Output = 0;
	unsigned int l_ui_Instanteneous_Data_DAC_APS_2_Output = 0;
	
	*l_p_ui_DAC_APS_1_Output_Sampled_Data = 0;
	*l_p_ui_DAC_APS_2_Output_Sampled_Data = 0;
	
	for(l_us_Sampling_Counter = 0 ; l_us_Sampling_Counter <= NUMBER_OF_ADC_SAMPLES_FOR_AVERAGING_DATA; l_us_Sampling_Counter++)
	{
		if(SUCCESS == fn_Get_ADC_Channel_Data(ADC_1, INPUT_3, &l_ui_Instanteneous_Data_DAC_APS_1_Output))
		{			
			if(SUCCESS == fn_Get_ADC_Channel_Data(ADC_1, INPUT_4, &l_ui_Instanteneous_Data_DAC_APS_2_Output))
			{			
				*l_p_ui_DAC_APS_1_Output_Sampled_Data = *l_p_ui_DAC_APS_1_Output_Sampled_Data + l_ui_Instanteneous_Data_DAC_APS_1_Output;
				*l_p_ui_DAC_APS_2_Output_Sampled_Data = *l_p_ui_DAC_APS_2_Output_Sampled_Data + l_ui_Instanteneous_Data_DAC_APS_2_Output;							
				
				l_ui_Instanteneous_Data_DAC_APS_1_Output = 0;
				l_ui_Instanteneous_Data_DAC_APS_2_Output = 0;
			}
			else
			{
				return FAILURE;
			}
		}
		else
		{
			return FAILURE;
		}
	}
	
	*l_p_ui_DAC_APS_1_Output_Sampled_Data = *l_p_ui_DAC_APS_1_Output_Sampled_Data / NUMBER_OF_ADC_SAMPLES_FOR_AVERAGING_DATA;
	*l_p_ui_DAC_APS_2_Output_Sampled_Data = *l_p_ui_DAC_APS_2_Output_Sampled_Data / NUMBER_OF_ADC_SAMPLES_FOR_AVERAGING_DATA;	

	return SUCCESS;
}

