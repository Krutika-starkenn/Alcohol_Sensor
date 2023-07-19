/*************** (C) COPYRIGHT 2019, Sixth Sensor Technology *******************
* File Name          : HAL_SPI.h
* Author             : Krutika Sawant
* Version            : -
* Date               : 29/Jan/2019
* Description        : Header for HAL_SPI.c module
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_SPI_H
#define __HAL_SPI_H

#define MAX_SPI_DATA_BITS                               8

#define RESET_SPI_CHIP_SELECT                           GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET)
#define SET_SPI_CHIP_SELECT                             GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET)

#define READ_SPI_MISO                                   GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6)

#define RESET_SPI_CLOCK                                 GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_RESET)
#define SET_SPI_CLOCK                                   GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_SET)

#define RESET_SPI_MOSI                                  GPIO_WriteBit(GPIOA, GPIO_Pin_7, Bit_RESET)
#define SET_SPI_MOSI                                    GPIO_WriteBit(GPIOA, GPIO_Pin_7, Bit_SET)
 
#define SELECT                                          1
#define DESELECT                                        0

#define SPI_CLOCK_INTERVAL                              10          //cycles

#define RESET_SPI_MISO                                  GPIO_WriteBit(GPIOA, GPIO_Pin_6, Bit_RESET)
#define SET_SPI_MISO                                    GPIO_WriteBit(GPIOA, GPIO_Pin_6, Bit_SET)

extern volatile unsigned int g_v_ui_Ticker_SPI_Write_Read_Timeout;


void fn_Init_SPI_Pins(void);
void fn_Select_Deselect_SPI_Device(unsigned char arg_uc_SD_Card_Select_Status);
unsigned char fn_uc_Send_Byte_Over_SPI(unsigned char arg_uc_Data_Byte,void *arg_ptr_uc_Read_DataPointer);
unsigned char fn_uc_Send_Read_Data_Over_SPI(void *arg_p_ucData_Over_SPI, unsigned char arg_uc_Data_Length_In_Bits);//, void *arg_Void_Pointer);
unsigned char fn_uc_Read_Byte_On_SPI(void);


#endif


