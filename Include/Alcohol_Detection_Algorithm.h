#ifndef __ALCOHOL_DETECTION_ALGORITHM_H
#define __ALCOHOL_DETECTION_ALGORITHM_H

#define TURN_ON_AIR_SAMPLING_PUMP                           GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_SET)
#define TURN_OFF_AIR_SAMPLING_PUMP                          GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_RESET)

#define START_VIBRATION                                    GPIO_WriteBit(GPIOB, GPIO_Pin_1, Bit_SET)
#define STOP_VIBRATION                                     GPIO_WriteBit(GPIOB, GPIO_Pin_1, Bit_RESET)

#define ALCOHOL_SENSOR_ADC_SAMPLING_COUNTS									1000  //200
#define AIR_FLOW_DETECTION_THRESHOLD												2000//200       0.2 psi

//#define ALCOHOL_SENSOR_ANALOG_INPUT_READ_CHANNEL			    ADC_Channel_10
#define ALCOHOL_SENSOR_ANALOG_INPUT_READ_CHANNEL		ADC_Channel_0
#define BATTERY_LEVEL_READ_CHANNEL								ADC_Channel_1

#define MAX_ALCOHOL_SAMPLES													10


#define ALCOHOL_SENSOR_DATA_SAMPLING_TIME								3000		//	3 Sec
#define ALCOHOL_TEST_TIMEOUT_TIMER											30000		    // 30 Sec
#define PUMP_ACTIVATION_TIMEOUT                         2000
#define PUMP_ON_TIMEOUT                                 200

#define DEBUG_ALCOHOL_SENSOR_RAW_ADC_DATA				0
#define DEBUG_BATTERY_LEVEL_RAW_ADC_DATA				0

// ****************** CAN ID's ******************************
#define CAN_TX_ID_OF_ALCOHOL_TEST_START_STATUS				0x223
#define CAN_TX_ID_OF_ALCOHOL_TEST_RESULT							0x224
#define CAN_TX_ID_OF_ALCOHOL_HB												0x227

 // CAN RX messages from ECU
#define	CAN_RX_ID_OF_START_ALCOHOL_TEST             	0x222
#define	CAN_RX_ID_OF_ALCOHOL_THRESHOLD             		0x221
#define	CAN_RX_ID_OF_SPEED_FROM_DMS										0x225
#define	CAN_RX_ID_OF_DMS_HB														0x226
// **********************************************************


#define ALCOHOL_TEST_STARTED							1
#define ALCOHOL_TEST_TIMEOUT							2

// **********************************************************




enum
{
	STATE_WAIT_FOR_TEST_START = 0,
	STATE_MONITOR_AIRFLOW,
	STATE_HANDLE_AIR_SUCTION_PUMP,
	STATE_START_ALCOHOL_SENSOR_DATA_SAMPLING,
	STATE_PROCESS_SAMPLES,
	STATE_SEND_RESULT_TO_ECU
};

enum
{
	TEST_FAIL = 0,
	TEST_PASS,
	TEST_TIMEOUT	
};
extern unsigned char g_uc_Alcohol_State_Machine;
extern unsigned int g_ui_ADC_CH10_Data;
extern unsigned int g_ui_ADC_CH11_Data;
extern unsigned short g_us_Alcohol_Sensor_Raw_ADC_Data;
extern unsigned char g_uc_Flag_Air_Sampling_Pump_State;
extern unsigned char g_uc_Flag_Start_Alcohol_Test;
extern unsigned char g_uc_Alcohol_Threshold_Mode;

extern unsigned char g_uc_Alcohol_Test_Status;
extern unsigned short g_us_Measured_Alcohol_Level;

extern volatile unsigned int g_vui_Ticker_Alcohol_Test_Timeout_Timer;
extern volatile unsigned int g_vui_Ticker_Alcohol_Sensor_Data_Sampling_Timer;
extern volatile unsigned int g_vui_Ticker_Timeout_For_Pump_Activation_Timer;
extern volatile unsigned int g_vui_Ticker_Alcohol_Sensor_Sampling_Interval_Integration;
extern volatile unsigned int g_v_ui_Ticker_Stop_Vibrations;

void fn_uc_Handle_Alcohol_Test(void);
unsigned char fn_uc_Get_Alcohol_Sensor_Raw_ADC_Data(unsigned short *arg_ptr_Result);
unsigned char fn_uc_Send_Alcohol_Test_Start_Status_To_ECU(unsigned char arg_uc_Status);
unsigned char fn_uc_Send_Alcohol_Test_Result_To_ECU(unsigned char arg_uc_Alcohol_Test_Result_Status, unsigned short arg_us_Measured_Alcohol_Level);
void fn_Calculate_Time_Period_Using_Port_Pin(void);
unsigned char fn_uc_Handle_Cap_Vibrations(void);
unsigned char Get_Current_Alcohol_State(void);
unsigned char fn_Get_Alcohol_Test_Start_Status(void);


#endif



