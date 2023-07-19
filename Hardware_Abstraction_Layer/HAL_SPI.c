#include "main.h"

unsigned char *g_p_uc_Read_SPI_Value;
unsigned short g_uc_Clock_Cycles = 10;//20;
volatile unsigned int g_v_ui_Ticker_SPI_Write_Read_Timeout = 0;
unsigned short g_uc_Clock_Cycles_Read = 10;//50;


void fn_Init_SPI_Pins(void)
{
    
    //GPIOA, GPIO_Pin_4         : CHIP_SELECT
    //GPIOA, GPIO_Pin_5         : CLOCK
    //GPIOA, GPIO_Pin_6         : MISO
    //GPIOA, GPIO_Pin_7         : MOSI
    
    //SPI CHIP_SELECT, CLOCK & MOSI as output

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); 


    //SPI MISO as input
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); 

    RESET_SPI_MOSI;
    SET_SPI_CLOCK;
    fn_Select_Deselect_SPI_Device(DESELECT);
    
//    fn_uc_Device_Reset();
    
}

void fn_Read_Status_Reg(void)
{
    
    unsigned char l_uc_Data_Counter = 0;
    unsigned char l_uc_Received_Data = 0;
    unsigned short arg_us_Data_Byte = 0x05C0;
    
    
    fn_Select_Deselect_SPI_Device(SELECT);

    for( l_uc_Data_Counter = 0; l_uc_Data_Counter < 16; l_uc_Data_Counter++ )
    {

        DELAY(g_uc_Clock_Cycles);

        RESET_SPI_CLOCK;
        
        DELAY(g_uc_Clock_Cycles);
        
        //MSB first
        if(0x01 == ((arg_us_Data_Byte >> ((16 - 1) - l_uc_Data_Counter)) & 0x01))
        {
            SET_SPI_MOSI;
        }
        else //if(0x00 == ((arg_uc_Data_Byte >> ((MAX_SPI_DATA_BITS - 1) - l_uc_Data_Counter)) & 0x01))
        {
            RESET_SPI_MOSI;
        }

        //is any delay required or what if there is no data from slave ?
        //DELAY(g_uc_Clock_Cycles);
        
        DELAY(g_uc_Clock_Cycles);

//        l_uc_Temp_Data = READ_SPI_MISO;
//        
//        l_uc_Received_Data |= (l_uc_Temp_Data << ((MAX_SPI_DATA_BITS - 1) - l_uc_Data_Counter));
        
        SET_SPI_CLOCK;

//        DELAY(g_uc_Clock_Cycles);
    }
    
    l_uc_Received_Data = fn_uc_Read_Byte_On_SPI();
    
    DELAY(g_uc_Clock_Cycles);
    fn_Select_Deselect_SPI_Device(DESELECT);
    
    #if 1//DEBUG_NAND_FLASH
    sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n C Reg Recvd Data:%d",
    l_uc_Received_Data);
    fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);
    #endif


}

unsigned char fn_uc_Send_Byte_Over_SPI(unsigned char arg_uc_Data_Byte, void *arg_ptr_uc_Read_DataPointer)
{
    unsigned char *l_p_uc_Temp_Pointer;
    unsigned char l_uc_Data_Counter = 0;
    unsigned char l_uc_Received_Data = 0;
    
 	l_p_uc_Temp_Pointer = (unsigned char *) arg_ptr_uc_Read_DataPointer;
    #if DEBUG_SPI
    
        sprintf((char *)&g_uc_Transmit_Buffer[0],"\t Read PTR Addr: %d ",
        (unsigned char*)*l_p_uc_Temp_Pointer);
        fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);
   
    #endif

//    fn_Select_Deselect_SPI_Device(SELECT);

    for( l_uc_Data_Counter = 0; l_uc_Data_Counter < 8; l_uc_Data_Counter++ )
    {

        DELAY(g_uc_Clock_Cycles);

        RESET_SPI_CLOCK;
        
        DELAY(g_uc_Clock_Cycles);
        
        //MSB first
        if(0x01 == ((arg_uc_Data_Byte >> ((MAX_SPI_DATA_BITS - 1) - l_uc_Data_Counter)) & 0x01))
        {
            SET_SPI_MOSI;
        }
        else //if(0x00 == ((arg_uc_Data_Byte >> ((MAX_SPI_DATA_BITS - 1) - l_uc_Data_Counter)) & 0x01))
        {
            RESET_SPI_MOSI;
        }

        //is any delay required or what if there is no data from slave ?
        //DELAY(g_uc_Clock_Cycles);
        
        DELAY(g_uc_Clock_Cycles);

//        l_uc_Temp_Data = READ_SPI_MISO;
//        
//        l_uc_Received_Data |= (l_uc_Temp_Data << ((MAX_SPI_DATA_BITS - 1) - l_uc_Data_Counter));
        
        SET_SPI_CLOCK;

//        DELAY(g_uc_Clock_Cycles);
    }
    
//    fn_Select_Deselect_SPI_Device(DESELECT);
   
    #if DEBUG_SPI
    
        sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n Sent Data: %d \t Recvd Data:%d",
        arg_uc_Data_Byte,
        l_uc_Received_Data);
        fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);
   
    #endif

    *l_p_uc_Temp_Pointer = l_uc_Received_Data;

    #if DEBUG_SPI
    
        sprintf((char *)&g_uc_Transmit_Buffer[0],"\t Ptr Data: %d ",
        *l_p_uc_Temp_Pointer);
        fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);
   
    #endif
   
    return SUCCESS;
}


//add delay for consecutive clock cycles
//receive interrupt to be configured
//cpol & cpha i.e. clock polarity & clock phase
//function for select sd card & deselect sd card

void fn_Select_Deselect_SPI_Device(unsigned char arg_uc_SD_Card_Select_Status)
{
    SET_SPI_CLOCK;

    if (SELECT == arg_uc_SD_Card_Select_Status)
    {
        RESET_SPI_CHIP_SELECT;
    }
    else if (DESELECT == arg_uc_SD_Card_Select_Status)
    {
        SET_SPI_CHIP_SELECT;
    }

//    DELAY(g_uc_Clock_Cycles);
}


unsigned char fn_uc_Read_Byte_On_SPI(void)
{
    unsigned char l_uc_Received_Data = 0;
    unsigned char l_uc_Data_Counter = 0;

    
    DELAY(g_uc_Clock_Cycles_Read);
    for( l_uc_Data_Counter = 0; l_uc_Data_Counter < 8; l_uc_Data_Counter++ )
    {
        
//        RESET_SPI_MOSI;
//        DELAY(g_uc_Clock_Cycles_Read);
        
        RESET_SPI_CLOCK;

        if(READ_SPI_MISO)
		{
			l_uc_Received_Data |= 0x01;
		}
		else
		{
			l_uc_Received_Data &= 0xFE;
		}
        
//        l_uc_Temp_Data = READ_SPI_MISO;
//        l_uc_Received_Data |= (l_uc_Temp_Data << ((MAX_SPI_DATA_BITS - 1) - l_uc_Data_Counter));
        
        SET_SPI_CLOCK;
        DELAY(g_uc_Clock_Cycles_Read);
        
//        SET_SPI_MOSI;
//        DELAY(g_uc_Clock_Cycles_Read);
        
		if(l_uc_Data_Counter < 7)
		{
			l_uc_Received_Data = (l_uc_Received_Data << 1);
		}

    }
    
//    RESET_SPI_CLOCK;

    return l_uc_Received_Data;
}


//unsigned char fn_uc_Send_Read_Data_Over_SPI(void *arg_p_ucData_Over_SPI, unsigned char arg_uc_Data_Length_In_Bits)//, void *arg_Void_Pointer)
//{

//    unsigned char l_uc_Temp_Data_Counter = 0;
//	unsigned char *l_ptr_uc_DataPointer;
//	unsigned char *l_ptr_uc_Read_DataPointer;

//    tdst_Firmware_Build_Number l_ost_Firmware_Build_Number;

//    l_ptr_uc_DataPointer = (unsigned char *) arg_p_ucData_Over_SPI;
//    l_ptr_uc_Read_DataPointer = (unsigned char *) (&l_ost_Firmware_Build_Number);

//    while (l_uc_Temp_Data_Counter < arg_uc_Data_Length_In_Bits)
//    {
//        fn_uc_Send_Byte_Over_SPI(*l_ptr_uc_DataPointer, l_ptr_uc_Read_DataPointer);

//        #if DEBUG_SPI

//            sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n Sent: %d Read: %d",
//            *l_ptr_uc_DataPointer,
//            *l_ptr_uc_Read_DataPointer);
//            fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);

//        #endif

//        l_ptr_uc_DataPointer++;
//        l_ptr_uc_Read_DataPointer++;
//        l_uc_Temp_Data_Counter += MAX_SPI_DATA_BITS;

//    }

//    #if DEBUG_SPI
//        sprintf((char *)&g_uc_Transmit_Buffer[0],"\r\n\r\n");
//        fn_uc_Send_String_On_Debug_Port((char *)g_uc_Transmit_Buffer);
//    #endif

//    //CRC check to be added

//    return SUCCESS;
//}

/******************************************File ends here********************************************************/
