
#ifndef __PRESSURE_SENSOR_XGPG6857D_H
#define __PRESSURE_SENSOR_XGPG6857D__H
#include "main.h"

#define DEBUG_PRESSURE_SENSOR_DEBUG			1

#define SENSOR_XGZP6857D_DEVICE_ADDRESS_FOR_WRITE_SEQUENCE	0xDA    // 0x6D
#define SENSOR_XGZP6857D_DEVICE_ADDRESS_FOR_READ_SEQUENCE		0xDB    // 0x6D


#define CMD_XGZP6857D_PRESSURE_DATA_MSB			0x06					//	Pressure Data out<23:16>
#define CMD_XGZP6857D_PRESSURE_DATA_CSB			0x07					//	Pressure Data out<15:8>
#define CMD_XGZP6857D_PRESSURE_DATA_LSB			0x08					//	Pressure Data out<7:0>
#define CMD_XGZP6857D_TEMP_DATA_MSB					0x09					//	Temp Data out<15:8>
#define CMD_XGZP6857D_TEMP_DATA_LSB					0x0A					//	Temp Data out<7:0>
#define CMD_XGZP6857D_CMD										0x30					//	Measurement Command Register
#define CMD_XGZP6857D_CMD_Write							0x60					//	Measurement Command Register

//*********************** Debug Macros *****************************
#define DEBUG_XGZP6857DPRESSURE_SENSOR_READ_CALIBRATION_COEFFICIENT_FUNCTION		0
#define DEBUG_XGZP6857DPRESSURE_SENSOR_GET_RAW_ADC_PRESSURE_DATA_FUNCTION				0
#define DEBUG_XGZP6857DPRESSURE_SENSOR_GET_RAW_ADC_TEMPERATURE_DATA_FUNCTION		0
#define DEBUG_XGZP6857DPRESSURE_SENSOR_CALCULATE_TEMPERATURE_FUNCTION						0
#define DEBUG_XGZP6857DPRESSURE_SENSOR_CALCULATE_PRESSURE_FUNCTION							0
#define DEBUG_XGZP6857DMONITOR_PRESSURE_AND_TEMPERATURE_FUNCTION								0
//******************************************************************

//void fn_uc_write_one_byte_XGZP6857D(unsigned char addr, unsigned char data);
//unsigned char fn_uc_read_one_byte_XGZP6857D(unsigned char addr);
//tdenm_Function_Ret_Values check_ack_bit(void);
//void Write_I2C_Byte(unsigned char byte);
//unsigned char Read_I2c_Byte(void);

//void fn_uc_XGZP6857D_Pressure_Sensor_start(void);
//void fn_uc_XGZP6857D_Pressure_Sensor_stop(void);
//void fn_uc_XGZP6857D_Pressure_Sensor_Send_0(void);
//void fn_uc_XGZP6857D_Pressure_Sensor_Send_1(void);
//char fn_uc_XGZP6857D_Pressure_Sensor_ACK(void);
//void fn_uc_XGZP6857D_Pressure_Sensor_Write_I2C_Byte(unsigned char byte);
//unsigned char fn_uc_XGZP6857D_Pressure_Sensor_Read_I2C_Byte(void);
//void fn_uc_XGZP6857D_Pressure_Sensor_Write_One_Byte(unsigned char addr, unsigned char data);
//unsigned char fn_uc_XGZP6857D_Pressure_Sensor_Read_One_Byte(void);


typedef enum
{
	CMD_EXECUTION_FAILED = 0,
	CMD_EXECUTION_SUCCESS	
	
}tdenm_Function_Ret_Values;


typedef struct
{
	signed int i_Temp_Difference;
	signed int i_Calculated_Temperature;
	
}tdst_Temp_Calculated_Values;


typedef struct
{
	long long ll_Offset;
	long long ll_Sensitivity;
	signed int i_Temp_Compensated_Pressure;
	
}tdst_Pressure_Calculated_Values;


tdenm_Function_Ret_Values fn_enm_XGZP6857D_Pressure_SensorSend_Reset_Cmd(void);
tdenm_Function_Ret_Values fn_enm_XGZP6857D_Pressure_SensorRead_Calibration_Coefficient_Data(unsigned char arg_Device_Cmd, unsigned short *arg_us_Coefficient_Value);
tdenm_Function_Ret_Values fn_enm_XGZP6857D_Pressure_SensorGet_Raw_ADC_Pressure_Data(unsigned int *arg_ptr_ui_Digital_Converted_Value);
tdenm_Function_Ret_Values fn_enm_XGZP6857D_Pressure_SensorGet_Raw_ADC_Temperature_Data(unsigned int *arg_ptr_ui_Digital_Converted_Value);
tdst_Temp_Calculated_Values fn_XGZP6857D_Pressure_Sensor_str_Calculate_Temperature(unsigned int arg_ui_Raw_ADC_Temp_Data, unsigned short arg_Calibration_Coefficient_C5, unsigned short arg_Calibration_Coefficient_C6, unsigned char arg_uc_Q5_Coefficient_Value, unsigned char arg_uc_Q6_Coefficient_Value);
tdst_Pressure_Calculated_Values fn_XGZP6857D_Pressure_Sensor_str_Calculate_Pressure(unsigned int arg_ui_Raw_ADC_Pressure_Data, int arg_i_Temp_Difference, unsigned short arg_us_Calibration_Coefficient_C1, unsigned short arg_us_Calibration_Coefficient_C2, unsigned short arg_us_Calibration_Coefficient_C3, unsigned short arg_us_Calibration_Coefficient_C4, unsigned char arg_uc_Q1_Coefficient_Value, unsigned char arg_uc_Q2_Coefficient_Value, unsigned char arg_uc_Q3_Coefficient_Value, unsigned char arg_uc_Q4_Coefficient_Value);
void fn_v_XGZP6857D_Pressure_SensorMonitor_Pressure_And_Temperature(void);
void fn_v_XGZP6857D_Pressure_Sensor_Generate_Dummy_Clock(void);

unsigned char fn_uc_Read_I2C_Byte_From_XGZP6857D_Pressure_Sensor(void);

#endif
