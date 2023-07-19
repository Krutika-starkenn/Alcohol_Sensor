#ifndef __HAL_I2C_H
#define __HAL_I2C_H

#define SET_I2C_CLOCK_PIN				GPIO_WriteBit(GPIOB, GPIO_Pin_6, Bit_SET)	//PB.6
#define CLEAR_I2C_CLOCK_PIN				GPIO_WriteBit(GPIOB, GPIO_Pin_6, Bit_RESET)	//PB.6

#define SET_I2C_DATA_PIN				GPIO_WriteBit(GPIOB, GPIO_Pin_7, Bit_SET)	//PB.7	 
#define CLEAR_I2C_DATA_PIN				GPIO_WriteBit(GPIOB, GPIO_Pin_7, Bit_RESET)	//PB.7

#define READ_I2C_DATA_PIN				GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)




unsigned char fn_uc_Initialize_Simulated_I2C_Bus_Port_Pins(void);
unsigned char fn_uc_Simulated_I2C_Bus_Send_Start_Bit(void);
unsigned char fn_uc_Simulated_I2C_Bus_Send_Byte(unsigned char l_uc_Data_to_be_Send);
unsigned char fn_uc_Simulated_I2C_Bus_Wait_For_Ack_Bit(void);
unsigned char fn_uc_Simulated_I2C_Bus_Send_Stop_Bit(void);
unsigned char fn_uc_Generate_I2C_Clock(void);
unsigned char fn_uc_Generate_I2C_NAK_Signal(void);
unsigned char fn_uc_Send_I2C_ACK_Signal(void);
unsigned char fn_uc_Initialize_Simulated_I2C_Bus_Port_Pins_AS_Input(void);
unsigned char fn_uc_Initialize_Simulated_I2C_Bus_Port_Pins_AS_Output(void);
unsigned int fn_uc_Simulated_I2C_Bus_Read_Byte(void);
extern void fn_ClockDelay(unsigned int l_ui_Time);


extern unsigned int clocks ;
#endif
