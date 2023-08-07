#include "main.h"


tdenm_Function_Ret_Values fn_enm_XGZP6857D_Pressure_SensorSend_Reset_Cmd(void);
tdenm_Function_Ret_Values fn_enm_XGZP6857D_Pressure_SensorRead_Calibration_Coefficient_Data(unsigned char arg_Device_Cmd, unsigned short *arg_us_Coefficient_Value);
/********************************************************************************************************************************************
Function Name		: tdenm_Function_Ret_Values fn_enm_XGZP6857D_Pressure_SensorGet_Raw_ADC_Pressure_Data(unsigned int *arg_ptr_ui_Digital_Converted_Value)
Description			: This function can be used to read Raw ADC conversion values of pressure data from sensor
Input Parameters 	: 1. Pointer where the resultant data has to be stored
Output Parameters	: CMD_EXECUTION_FAILED - 0
					  CMD_EXECUTION_SUCCESS - 1
Author				: Nitin Gaikwad
********************************************************************************************************************************************/
tdenm_Function_Ret_Values fn_enm_XGZP6857D_Pressure_SensorGet_Raw_ADC_Pressure_Data(unsigned int *arg_ptr_ui_Digital_Converted_Value)
{
	unsigned char l_uc_Byte_Counter = 0;
	unsigned char l_uc_Bytes_To_Read = 3;	// as Response is of 3 bytes
	unsigned char l_uc_Data = 0;
	unsigned long int l_ui_Pressure_Data = 0;	
	unsigned long int l_ui_Pressure_Data_adc = 0;	
	unsigned int pressure_H = 0;
	unsigned int pressure_C = 0;
	unsigned int pressure_L = 0;
	
	fn_v_XGZP6857D_Pressure_Sensor_Generate_Dummy_Clock();
	
	// Initiate Pressure Conversion
	// Send Start bit
	fn_uc_Simulated_I2C_Bus_Send_Start_Bit();
		
	//********* Send 7 bit Device address + 1 Write bit *************
	fn_uc_Simulated_I2C_Bus_Send_Byte(SENSOR_XGZP6857D_DEVICE_ADDRESS_FOR_WRITE_SEQUENCE);
	
	if (SUCCESS != fn_uc_Simulated_I2C_Bus_Wait_For_Ack_Bit())
	{
		return CMD_EXECUTION_FAILED;
	}
		
	//**************** Send Command ************************
	fn_uc_Simulated_I2C_Bus_Send_Byte(CMD_XGZP6857D_CMD);
	
	if (SUCCESS != fn_uc_Simulated_I2C_Bus_Wait_For_Ack_Bit())
	{
		return CMD_EXECUTION_FAILED;	
	}
	
	//**************** Send Command ************************
	fn_uc_Simulated_I2C_Bus_Send_Byte(CMD_XGZP6857D_TEMP_DATA_LSB);
	
	if (SUCCESS != fn_uc_Simulated_I2C_Bus_Wait_For_Ack_Bit())
	{
		return CMD_EXECUTION_FAILED;	
	}
	
	// *************** Send stop bit ****************************
	fn_uc_Simulated_I2C_Bus_Send_Stop_Bit();
	
	// Wait for 10 ms for sending next command
	Delay(10);
	
	fn_v_XGZP6857D_Pressure_Sensor_Generate_Dummy_Clock();
	
	
		
	// Send Start bit
	fn_uc_Simulated_I2C_Bus_Send_Start_Bit();
		
	//********* Send 7 bit Device address + 1 Write bit *************
	fn_uc_Simulated_I2C_Bus_Send_Byte(SENSOR_XGZP6857D_DEVICE_ADDRESS_FOR_WRITE_SEQUENCE);
	
	if (SUCCESS != fn_uc_Simulated_I2C_Bus_Wait_For_Ack_Bit())
	{
		return CMD_EXECUTION_FAILED;
	}
		
	//**************** Send Command ************************
	fn_uc_Simulated_I2C_Bus_Send_Byte(CMD_XGZP6857D_PRESSURE_DATA_MSB);
	
	if (SUCCESS != fn_uc_Simulated_I2C_Bus_Wait_For_Ack_Bit())
	{
		return CMD_EXECUTION_FAILED;	
	}	
	
	// *************** Send stop bit ****************************
	fn_uc_Simulated_I2C_Bus_Send_Stop_Bit();
	
	fn_v_XGZP6857D_Pressure_Sensor_Generate_Dummy_Clock();
	
	// Read Converted Data
	// Again send Start bit
	fn_uc_Simulated_I2C_Bus_Send_Start_Bit();
		
	//********* Send 7 bit Device address + 1 Read bit *************
	fn_uc_Simulated_I2C_Bus_Send_Byte(SENSOR_XGZP6857D_DEVICE_ADDRESS_FOR_READ_SEQUENCE);
	
	if (SUCCESS != fn_uc_Simulated_I2C_Bus_Wait_For_Ack_Bit())
	{
		return CMD_EXECUTION_FAILED;
	}
	
//		//**************** Send Command ************************
//	fn_uc_Simulated_I2C_Bus_Send_Byte(CMD_XGZP6857D_TEMP_DATA_LSB);
//	
//	if (SUCCESS != fn_uc_Simulated_I2C_Bus_Wait_For_Ack_Bit())
//	{
//		return CMD_EXECUTION_FAILED;	
//	}	
	
	// Read Data from Device
	for(l_uc_Byte_Counter = 0; l_uc_Byte_Counter < l_uc_Bytes_To_Read; l_uc_Byte_Counter++)
	{			
		//Read Byte from memory
		l_uc_Data = fn_uc_Read_I2C_Byte_From_XGZP6857D_Pressure_Sensor();
	
		if(0 == l_uc_Byte_Counter)
		{
			pressure_H = l_uc_Data;	
			
		}	else if	(1 == l_uc_Byte_Counter)	
		{
			pressure_C = l_uc_Data;
			
		}else if	(2 == l_uc_Byte_Counter)	
		{
			pressure_L = l_uc_Data;
//			l_ui_Pressure_Data = pressure_L ;
//			l_ui_Pressure_Data = (pressure_C << 8);
//			l_ui_Pressure_Data = (pressure_H << 16);
			
		}
		
		#if 0
//		sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n Byte No: %d,Raw ADC Byte: %d, Left8: %d", l_uc_Byte_Counter,l_uc_Data, l_ui_Pressure_Data);
			sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n Byte No: %d, Raw ADC Byte: %d,   MSB: %d, CSB: %d, LSB: %d, pressure Data %lu",l_uc_Byte_Counter,l_uc_Data,pressure_H, pressure_C,pressure_L,l_ui_Pressure_Data);
			fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);
		#endif
		// Send ACK signal
		if (l_uc_Byte_Counter < (l_uc_Bytes_To_Read - 1 ))
		{
			l_ui_Pressure_Data = (l_ui_Pressure_Data << 8);
			fn_uc_Send_I2C_ACK_Signal();
		}
	
		#if 0
//		sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n Byte No: %d,Raw ADC Byte: %d, Left8: %d", l_uc_Byte_Counter,l_uc_Data, l_ui_Pressure_Data);
		  sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n Byte No: %d,Raw ADC Byte: %d", l_uc_Byte_Counter,l_uc_Data);
			fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);
		#endif
					
	}// for loop to count number of bytes to be written in a page
	
	
	// ************* Send NACK command to terminate read operation **************
	fn_uc_Generate_I2C_NAK_Signal();
		
	// *************** Send stop bit ****************************
	fn_uc_Simulated_I2C_Bus_Send_Stop_Bit();
	
	fn_v_XGZP6857D_Pressure_Sensor_Generate_Dummy_Clock();
	l_ui_Pressure_Data = 0;
	l_ui_Pressure_Data = pressure_H * 65536 + pressure_C * 256 + pressure_L;
	
	if(l_ui_Pressure_Data > 8388608)
	{
		l_ui_Pressure_Data_adc = (l_ui_Pressure_Data - 16777216) / 64;
		l_ui_Pressure_Data_adc = 0;
	}
	else
	{
		l_ui_Pressure_Data_adc = l_ui_Pressure_Data/64;
	}
	#if 0
//		sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n Byte No: %d,Raw ADC Byte: %d, Left8: %d", l_uc_Byte_Counter,l_uc_Data, l_ui_Pressure_Data);
			sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n Byte No: %d, Raw ADC Byte: %d,   MSB: %d, CSB: %d, LSB: %d, pressure Data %lu",l_uc_Byte_Counter,l_uc_Data,pressure_H, pressure_C,pressure_L,l_ui_Pressure_Data_adc);
			fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);
		#endif
	
//	*arg_ptr_ui_Digital_Converted_Value = l_ui_Pressure_Data;
	
	#if 1//DEBUG_XGZP6857DPRESSURE_SENSOR_GET_RAW_ADC_PRESSURE_DATA_FUNCTION
		sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n Raw Pressure ADC Value: %lu",l_ui_Pressure_Data_adc);
		fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);
	#endif
	
	return CMD_EXECUTION_SUCCESS;
}



/********************************************************************************************************************************************
Function Name		: tdenm_Function_Ret_Values fn_enm_XGZP6857D_Pressure_SensorGet_Raw_ADC_Temperature_Data(unsigned int *arg_ptr_ui_Digital_Converted_Value)
Description			: This function can be used to read Raw ADC conversion values of Temperature data from sensor
Input Parameters 	: 1. Pointer where the resultant data has to be stored
Output Parameters	: CMD_EXECUTION_FAILED - 0
										CMD_EXECUTION_SUCCESS - 1
Author						: 
********************************************************************************************************************************************/
tdenm_Function_Ret_Values fn_enm_XGZP6857D_Pressure_SensorGet_Raw_ADC_Temperature_Data(unsigned int *arg_ptr_ui_Digital_Converted_Value)
{
	unsigned char l_uc_Byte_Counter = 0;
	unsigned char l_uc_Bytes_To_Read = 2;	// as Response is of 2 bytes
	unsigned char l_uc_Data = 0;
	unsigned long int l_ui_Temp_Data = 0;	
	unsigned long int l_ui_Temp_Data_adc = 0;	
	unsigned int Temp_H = 0;
	unsigned int Temp_L = 0;
	
	fn_v_XGZP6857D_Pressure_Sensor_Generate_Dummy_Clock();
	
	// Initiate Pressure Conversion
	// Send Start bit
	fn_uc_Simulated_I2C_Bus_Send_Start_Bit();
		
	//********* Send 7 bit Device address + 1 Write bit *************
	fn_uc_Simulated_I2C_Bus_Send_Byte(SENSOR_XGZP6857D_DEVICE_ADDRESS_FOR_WRITE_SEQUENCE);
	
	if (SUCCESS != fn_uc_Simulated_I2C_Bus_Wait_For_Ack_Bit())
	{
		return CMD_EXECUTION_FAILED;
	}
		
	//**************** Send Command ************************
	fn_uc_Simulated_I2C_Bus_Send_Byte(CMD_XGZP6857D_CMD);
	
	if (SUCCESS != fn_uc_Simulated_I2C_Bus_Wait_For_Ack_Bit())
	{
		return CMD_EXECUTION_FAILED;	
	}
	
	//**************** Send Command ************************
	fn_uc_Simulated_I2C_Bus_Send_Byte(CMD_XGZP6857D_TEMP_DATA_LSB);
	
	if (SUCCESS != fn_uc_Simulated_I2C_Bus_Wait_For_Ack_Bit())
	{
		return CMD_EXECUTION_FAILED;	
	}
	
	// *************** Send stop bit ****************************
	fn_uc_Simulated_I2C_Bus_Send_Stop_Bit();
	
	// Wait for 10 ms for sending next command
	Delay(10);
	
	fn_v_XGZP6857D_Pressure_Sensor_Generate_Dummy_Clock();
	
	
		
	// Send Start bit
	fn_uc_Simulated_I2C_Bus_Send_Start_Bit();
		
	//********* Send 7 bit Device address + 1 Write bit *************
	fn_uc_Simulated_I2C_Bus_Send_Byte(SENSOR_XGZP6857D_DEVICE_ADDRESS_FOR_WRITE_SEQUENCE);
	
	if (SUCCESS != fn_uc_Simulated_I2C_Bus_Wait_For_Ack_Bit())
	{
		return CMD_EXECUTION_FAILED;
	}
		
	//**************** Send Command ************************
	fn_uc_Simulated_I2C_Bus_Send_Byte(CMD_XGZP6857D_TEMP_DATA_MSB);
	
	if (SUCCESS != fn_uc_Simulated_I2C_Bus_Wait_For_Ack_Bit())
	{
		return CMD_EXECUTION_FAILED;	
	}	
	
	// *************** Send stop bit ****************************
	fn_uc_Simulated_I2C_Bus_Send_Stop_Bit();
	
	fn_v_XGZP6857D_Pressure_Sensor_Generate_Dummy_Clock();
	
	// Read Converted Data
	// Again send Start bit
	fn_uc_Simulated_I2C_Bus_Send_Start_Bit();
		
	//********* Send 7 bit Device address + 1 Read bit *************
	fn_uc_Simulated_I2C_Bus_Send_Byte(SENSOR_XGZP6857D_DEVICE_ADDRESS_FOR_READ_SEQUENCE);
	
	if (SUCCESS != fn_uc_Simulated_I2C_Bus_Wait_For_Ack_Bit())
	{
		return CMD_EXECUTION_FAILED;
	}
	
//		//**************** Send Command ************************
//	fn_uc_Simulated_I2C_Bus_Send_Byte(CMD_XGZP6857D_TEMP_DATA_LSB);
//	
//	if (SUCCESS != fn_uc_Simulated_I2C_Bus_Wait_For_Ack_Bit())
//	{
//		return CMD_EXECUTION_FAILED;	
//	}	
	
	// Read Data from Device
	for(l_uc_Byte_Counter = 0; l_uc_Byte_Counter < l_uc_Bytes_To_Read; l_uc_Byte_Counter++)
	{			
		//Read Byte from memory
		l_uc_Data = fn_uc_Read_I2C_Byte_From_XGZP6857D_Pressure_Sensor();
	
		if(0 == l_uc_Byte_Counter)
		{
			Temp_H = l_uc_Data;	
			
		}	else 
		{
			Temp_L = l_uc_Data;
			
		}
		
		#if 0
//		sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n Byte No: %d,Raw ADC Byte: %d, Left8: %d", l_uc_Byte_Counter,l_uc_Data, l_ui_Pressure_Data);
		sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n Byte No: %d, Raw ADC Byte: %d,   MSB: %d, CSB: %d, LSB: %d, pressure Data %lu\r\n ",l_uc_Byte_Counter,l_uc_Data,pressure_H, pressure_C,pressure_L,l_ui_Pressure_Data);
			fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);
		#endif
		// Send ACK signal
		if (l_uc_Byte_Counter < (l_uc_Bytes_To_Read - 1 ))
		{
			l_ui_Temp_Data = (l_ui_Temp_Data << 8);
			fn_uc_Send_I2C_ACK_Signal();
		}
	
		#if 0
//		sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n Byte No: %d,Raw ADC Byte: %d, Left8: %d", l_uc_Byte_Counter,l_uc_Data, l_ui_Pressure_Data);
		sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n Byte No: %d,Raw ADC Byte: %d", l_uc_Byte_Counter,l_uc_Data);
			fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);
		#endif
					
	}// for loop to count number of bytes to be written in a page
	
	
	// ************* Send NACK command to terminate read operation **************
	fn_uc_Generate_I2C_NAK_Signal();
		
	// *************** Send stop bit ****************************
	fn_uc_Simulated_I2C_Bus_Send_Stop_Bit();
	
	fn_v_XGZP6857D_Pressure_Sensor_Generate_Dummy_Clock();
	l_ui_Temp_Data = 0;
	l_ui_Temp_Data =  Temp_H * 256 + Temp_L;
	if(l_ui_Temp_Data < 32768)
	{
//	l_ui_Pressure_Data_adc= (l_ui_Pressure_Data -  16777216) / 64;
		l_ui_Temp_Data_adc = l_ui_Temp_Data / 256;
//	l_ui_Temp_Data= 0;
	}
	else if(l_ui_Temp_Data > 32768)
	{
		l_ui_Temp_Data_adc = (l_ui_Temp_Data - 65536) / 256;
	}
		#if 1
//		sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n Byte No: %d,Raw ADC Byte: %d, Left8: %d", l_uc_Byte_Counter,l_uc_Data, l_ui_Pressure_Data);
			sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n Byte No: %d, Raw ADC Byte: %lu,   Temp_H: %d, Temp_L: %d, Temperature: %lu ",l_uc_Byte_Counter,l_ui_Temp_Data,Temp_H,Temp_L,l_ui_Temp_Data_adc);
			fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);
		#endif
		
//	#if 1
////		sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n Byte No: %d,Raw ADC Byte: %d, Left8: %d", l_uc_Byte_Counter,l_uc_Data, l_ui_Pressure_Data);
//		sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n Byte No: %d, Raw ADC Byte: %d,   MSB: %d, CSB: %d, LSB: %d, pressure Data %lu kpa",l_uc_Byte_Counter,l_uc_Data,pressure_H, pressure_C,pressure_L,l_ui_Pressure_Data_adc);
//			fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);
//		#endif
	
//	*arg_ptr_ui_Digital_Converted_Value = l_ui_Pressure_Data;
	
	#if DEBUG_XGZP6857DPRESSURE_SENSOR_GET_RAW_ADC_PRESSURE_DATA_FUNCTION
	sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n Byte No: %d, Raw Pressure ADC Value: %d", l_uc_Byte_Counter,l_ui_Pressure_Data);
		fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);
	#endif
	
	return CMD_EXECUTION_SUCCESS;
}
tdst_Temp_Calculated_Values fn_XGZP6857D_Pressure_Sensorstr_Calculate_Temperature(unsigned int arg_ui_Raw_ADC_Temp_Data, unsigned short arg_Calibration_Coefficient_C5, unsigned short arg_Calibration_Coefficient_C6, unsigned char arg_uc_Q5_Coefficient_Value, unsigned char arg_uc_Q6_Coefficient_Value);
tdst_Pressure_Calculated_Values fn_XGZP6857D_Pressure_Sensorstr_Calculate_Pressure(unsigned int arg_ui_Raw_ADC_Pressure_Data, int arg_i_Temp_Difference, unsigned short arg_us_Calibration_Coefficient_C1, unsigned short arg_us_Calibration_Coefficient_C2, unsigned short arg_us_Calibration_Coefficient_C3, unsigned short arg_us_Calibration_Coefficient_C4, unsigned char arg_uc_Q1_Coefficient_Value, unsigned char arg_uc_Q2_Coefficient_Value, unsigned char arg_uc_Q3_Coefficient_Value, unsigned char arg_uc_Q4_Coefficient_Value);
void fn_v_XGZP6857D_Pressure_SensorMonitor_Pressure_And_Temperature(void);
void fn_v_XGZP6857D_Pressure_Sensor_Generate_Dummy_Clock(void)
{
	unsigned char l_uc_Loop_Counter = 0;
	
	for(l_uc_Loop_Counter = 0; l_uc_Loop_Counter < 1; l_uc_Loop_Counter++)
	{
		fn_uc_Generate_I2C_Clock();
	}
}

unsigned char fn_uc_Read_I2C_Byte_From_XGZP6857D_Pressure_Sensor(void)
{
	unsigned char l_uc_Loop_Counter = 0;
	unsigned char l_uc_Byte_Read_From_Memory = 0;
	
	// Set Port Pins as Input
	fn_uc_Initialize_Simulated_I2C_Bus_Port_Pins_AS_Input();
	// delay
	fn_ClockDelay(clocks);
	
	for(l_uc_Loop_Counter=0; l_uc_Loop_Counter<=7; l_uc_Loop_Counter++)
	{
		// Set SCL Pin High
		SET_I2C_CLOCK_PIN;
		
		if(READ_I2C_DATA_PIN)
		{
			l_uc_Byte_Read_From_Memory |= 0x01;
		}
		else
		{
			l_uc_Byte_Read_From_Memory &= 0xFE;
		}
		
		// Clear SCL Pin
		CLEAR_I2C_CLOCK_PIN;
		fn_ClockDelay(clocks);
		
		if(l_uc_Loop_Counter < 7)
		{
			l_uc_Byte_Read_From_Memory = (l_uc_Byte_Read_From_Memory << 1);
		}
	}
	
	// Set Port Pins as Output
	fn_uc_Initialize_Simulated_I2C_Bus_Port_Pins_AS_Output();
	// delay
	DELAY(clocks);
	
	return (l_uc_Byte_Read_From_Memory);
}

unsigned int Get_Pressure_Val(void)
{
	unsigned int l_ui_Raw_ADC_Val = 0;
	fn_enm_XGZP6857D_Pressure_SensorGet_Raw_ADC_Temperature_Data(&l_ui_Raw_ADC_Val);
	return l_ui_Raw_ADC_Val;
}
