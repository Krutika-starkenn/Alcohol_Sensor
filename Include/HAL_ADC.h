#ifndef __HAL_ADC_H
#define __HAL_ADC_H

#define ADC_1											   		1
#define ADC_2											   		2
#define NUMBER_OF_ADC_SAMPLES_FOR_AVERAGING_DATA		 	    100

#define CHANNEL_A												0
#define CHANNEL_B												1
#define CHANNEL_C												2
#define CHANNEL_D												3

#define INPUT_1												    ADC_Channel_0
#define INPUT_2												    ADC_Channel_1
#define INPUT_3									                ADC_Channel_2
#define INPUT_4										            ADC_Channel_3


extern unsigned int g_ui_ADC_CH0_Data;
extern unsigned int g_ui_ADC_CH1_Data;
extern unsigned int g_ui_ADC_CH2_Data;
extern unsigned int g_ui_ADC_CH3_Data;


unsigned char fn_uc_Initialize_ADC1_Module(void);
unsigned char fn_Get_ADC_Channel_Data(unsigned char l_uc_ADC_Number, unsigned char l_uc_ADC_Channel_Number, unsigned int *l_ui_Instanteneous_Data);
unsigned char fn_Get_ADC_Sampled_Data(unsigned char l_uc_ADC_Number, unsigned char l_uc_ADC_Channel_Number, unsigned int *l_ui_Sampled_Data);
unsigned char fn_Get_ADC_Sampled_Data_Of_Both_APS_Channels(unsigned int *l_p_ui_APS_1_Input_Sampled_Data, unsigned int *l_p_ui_APS_2_Input_Sampled_Data);
unsigned char fn_Get_ADC_Sampled_Data_Of_Both_ECU_Channels(unsigned int *l_p_ui_DAC_APS_1_Output_Sampled_Data, unsigned int *l_p_ui_DAC_APS_2_Output_Sampled_Data);

#endif
