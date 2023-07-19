/* Includes ------------------------------------------------------------------*/
#include "main.h"

unsigned int clocks = 8;
void fn_ClockDelay(unsigned int l_ui_Time);


/********************************************************************************************************************************************
Function Name		: unsigned char fn_uc_Initialize_Simulated_I2C_Bus_Port_Pins(void)
Description			: This function can be used initialize GPIO Pins for I2C Bus Simulation
Input Parameters 	: None
Output Parameters	: SUCCESS - Function will return SUCCESS by default
Author				: Mr. Shreyas Apte
********************************************************************************************************************************************/
unsigned char fn_uc_Initialize_Simulated_I2C_Bus_Port_Pins(void)
{
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7 ; //	Port-B Pin6 - SCL, Port-B Pin7 - SDA
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;		 // Set GPIO Pins as output 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	return SUCCESS;
}


/********************************************************************************************************************************************
Function Name		: unsigned char fn_uc_Simulated_I2C_Bus_Send_Start_Bit(void)
Description			: This function can be used to generate Simulated I2C Bus Start condition
Input Parameters 	: None
Output Parameters	: SUCCESS - Function will return SUCCESS by default
Author				: Mr. Shreyas Apte
********************************************************************************************************************************************/
unsigned char fn_uc_Simulated_I2C_Bus_Send_Start_Bit(void)
{
	SET_I2C_DATA_PIN;			// Pull I2C Data Pin High
	SET_I2C_CLOCK_PIN;			// Pull I2C Clock pin Hig	
	fn_ClockDelay(clocks);	// Wait for 8 clock cycles
	CLEAR_I2C_DATA_PIN;			// Pull Down I2C Data Pin down for Start command
	fn_ClockDelay(clocks);	// Wait for 8 clock cycles
	CLEAR_I2C_CLOCK_PIN;

	return SUCCESS;
}

/********************************************************************************************************************************************
Function Name		: unsigned char fn_uc_Simulated_I2C_Bus_Send_Byte(unsigned char l_uc_Data_to_be_Send)
Description			: This function can be used to send a Byte data on Simulated I2C Bus
Input Parameters 	: Data to be sent needs to be pass to this function.
Output Parameters	: SUCCESS - Function will return SUCCESS in case of successful operation 
Author				: Mr. Shreyas Apte
********************************************************************************************************************************************/
unsigned char fn_uc_Simulated_I2C_Bus_Send_Byte(unsigned char l_uc_Data_to_be_Send)
{
	unsigned char l_uc_Masking_Variable = 0x80;	
	unsigned char l_uc_Loop_Counter = 0;
	
	for(l_uc_Loop_Counter = 0; l_uc_Loop_Counter <= 7; l_uc_Loop_Counter++)
	{
		// Verify MSB bit and drive I2C Lines accordingly
		if(l_uc_Data_to_be_Send & l_uc_Masking_Variable)	
		{
			SET_I2C_DATA_PIN;			// Pull up I2C Data Pin				
			fn_uc_Generate_I2C_Clock();		
			CLEAR_I2C_DATA_PIN;			// original position
		}
		else
		{
			CLEAR_I2C_DATA_PIN;			//	Pull Down I2C Data Pin			
			fn_uc_Generate_I2C_Clock();		
		}		
		
		if(l_uc_Loop_Counter < 7)
		{
			l_uc_Data_to_be_Send <<= 1;			// Left shift to send next bit
		}
		
	}// for loop
	
	return SUCCESS;
	
}

/********************************************************************************************************************************************
Function Name		: unsigned char fn_uc_Simulated_I2C_Bus_Wait_For_Ack_Bit(void)
Description			: This function generates Dummy clock signals to read Acknowledgement bit
Input Parameters 	: None					  
Output Parameters	: SUCCESS - Function will return SUCCESS in case of successful operation  
Author				: Mr. Shreyas Apte
********************************************************************************************************************************************/
unsigned char fn_uc_Simulated_I2C_Bus_Wait_For_Ack_Bit(void)
{
    unsigned char l_uc_SDA_Status = 0;
    
    
//	CLEAR_I2C_CLOCK_PIN;		// | 
//	fn_ClockDelay(clocks);				// | Generate Clock Pulse
//	SET_I2C_CLOCK_PIN;			// | to latch data
//	fn_ClockDelay(clocks);				// |
//	CLEAR_I2C_CLOCK_PIN;		// |
//	
//	return SUCCESS;
	SET_I2C_DATA_PIN;
	CLEAR_I2C_CLOCK_PIN;		// | 
	fn_ClockDelay(clocks);				// | Generate Clock Pulse
	SET_I2C_CLOCK_PIN;			// | to latch data

	fn_uc_Initialize_Simulated_I2C_Bus_Port_Pins_AS_Input();
	//fn_ClockDelay(clocks);
    l_uc_SDA_Status = READ_I2C_DATA_PIN;
	
    fn_uc_Initialize_Simulated_I2C_Bus_Port_Pins_AS_Output();	
    fn_ClockDelay(clocks);				// |
    CLEAR_I2C_CLOCK_PIN;		// |
    SET_I2C_DATA_PIN;
        
   if(1 == l_uc_SDA_Status)
    {
		#if 1//DEBUG_EEPROM_LAYER
			sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n SDA Status- %d",l_uc_SDA_Status);
			fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);
		#endif	
        return FAILURE;
    }
    else
    {
        return SUCCESS;
    }
    
}


/********************************************************************************************************************************************
Function Name		: unsigned char fn_uc_Simulated_I2C_Bus_Send_Stop_Bit(void)
Description			: This function can be used to generate STOP condition on I2C Bus
Input Parameters 	: None					 
Output Parameters	: SUCCESS - Function will return SUCCESS in case of successful operation
Author				: Mr. Shreyas Apte
********************************************************************************************************************************************/
unsigned char fn_uc_Simulated_I2C_Bus_Send_Stop_Bit(void)
{
	CLEAR_I2C_CLOCK_PIN;
	CLEAR_I2C_DATA_PIN;
	fn_ClockDelay(clocks);
	SET_I2C_CLOCK_PIN;
	fn_ClockDelay(clocks);	
	SET_I2C_DATA_PIN;
	fn_ClockDelay(clocks);
	CLEAR_I2C_DATA_PIN;
	CLEAR_I2C_CLOCK_PIN;
	
	return SUCCESS;
}



unsigned char fn_uc_Generate_I2C_Clock(void)
{
	//unsigned char l_uc_Local_Clock = 100;
	CLEAR_I2C_CLOCK_PIN;		// | 
	fn_ClockDelay(clocks);				// | Generate Clock Pulse
	SET_I2C_CLOCK_PIN;			// | to latch data
	fn_ClockDelay(clocks);				// |
	CLEAR_I2C_CLOCK_PIN;		// |
	
	return SUCCESS;
}


unsigned char fn_uc_Generate_I2C_NAK_Signal(void)
{
	CLEAR_I2C_CLOCK_PIN;																									 //CLEAR SCL LINE
	SET_I2C_DATA_PIN;
    fn_ClockDelay(clocks);	
	SET_I2C_CLOCK_PIN;    																						//SET SCL LINE
    fn_ClockDelay(clocks);
	CLEAR_I2C_CLOCK_PIN;																										//CLEAR SCL LINE
	SET_I2C_DATA_PIN;
	
	return SUCCESS;
}


unsigned char fn_uc_Send_I2C_ACK_Signal(void)
{
	
	CLEAR_I2C_CLOCK_PIN;																										//CLEAR SCL LINE	
	CLEAR_I2C_DATA_PIN;
    fn_ClockDelay(clocks);	
	SET_I2C_CLOCK_PIN;     																							//SET SCL LINE
    fn_ClockDelay(clocks);
	CLEAR_I2C_CLOCK_PIN;																									//CLEAR SCL LINE	
	SET_I2C_DATA_PIN;
	
	return SUCCESS;
}


unsigned char fn_uc_Initialize_Simulated_I2C_Bus_Port_Pins_AS_Input(void)
{
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;			
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	return SUCCESS;
}


unsigned char fn_uc_Initialize_Simulated_I2C_Bus_Port_Pins_AS_Output(void)
{
	// Set Port Pins as Output
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;			
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;//GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	return SUCCESS;
}


unsigned int fn_uc_Simulated_I2C_Bus_Read_Byte(void)
{
	unsigned char l_received_data = 0;	
	unsigned char l_uc_Loop_Counter = 0;
	
	SET_I2C_DATA_PIN;
	CLEAR_I2C_CLOCK_PIN;		// | 
	fn_ClockDelay(clocks);				// | Generate Clock Pulse
	SET_I2C_CLOCK_PIN;			// | to latch data

	fn_uc_Initialize_Simulated_I2C_Bus_Port_Pins_AS_Input();
	
	for(l_uc_Loop_Counter = 0; l_uc_Loop_Counter <= 7; l_uc_Loop_Counter++)
	{
			sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\r data Read = %d",READ_I2C_DATA_PIN);
			fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);
		if(READ_I2C_DATA_PIN)
		{
			l_received_data |= 0x01;
		}
		else
		{
			l_received_data &= 0xFE;
		}
		if(l_uc_Loop_Counter < 7)
		{
			l_received_data = (l_received_data << 1);
		}
	}
	
	
	  fn_uc_Initialize_Simulated_I2C_Bus_Port_Pins_AS_Output();	
	fn_ClockDelay(clocks);				// |
    CLEAR_I2C_CLOCK_PIN;		// |
    SET_I2C_DATA_PIN;
//	unsigned int data;
//	fn_uc_Initialize_Simulated_I2C_Bus_Port_Pins_AS_Input();
//	fn_uc_Generate_I2C_Clock();
//	data = I2C_ReceiveData(I2C1);
	
	return l_received_data;
}

void fn_ClockDelay(unsigned int l_ui_Time)
{
	unsigned int l_ui_Counter = 0;
	
	for(l_ui_Counter = 0; l_ui_Counter < l_ui_Time; l_ui_Counter++);
}

