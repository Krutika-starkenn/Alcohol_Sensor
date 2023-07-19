#ifndef __HAL_EEPROM_H
#define __HAL_EEPROM_H


#define EEPROM_DEVICE_ADDRESS_TO_WRITE_DATA										0xA0
#define EEPROM_DEVICE_ADDRESS_TO_READ_DATA										0xA1

#define EEPROM_PAGE_SIZE														64

#define EEPROM_START_ADDRESS													0
#define EEPROM_END_ADDRESS														16383
#define EEPROM_DEFAULT_LOAD_DATA												0x00

#define MEMORY_CRC_KEY															0xFFFF;

#define DEBUG_EEPROM_LAYER														0

typedef enum
{
    enmWRITE_FAIL = 0,
    enmWRITE_SUCCESS = 1,
    enmREAD_FAIL = 2,
    enmREAD_SUCCESS = 3,
    enmCOMPARE_FAIL = 4,
    enmCOMPARE_SUCCESS = 5,
    enmNULL_POINTER = 6,
    enmMAX_RETURN_TYPE
}tden_EEPROM_Ret;



extern unsigned int clocks;


tden_EEPROM_Ret fn_enm_EEPROM_Write_Read_Compare_Data_Block_with_CRC(unsigned short arg_us_Base_Address,char *arg_Structure_In_Action, unsigned short arg_us_Data_Length);
tden_EEPROM_Ret fn_enm_Write_Data_IN_EEPROM_Memory(unsigned short l_us_Base_Address, void *l_ptr_v_Data, unsigned int l_ui_Data_Length);
tden_EEPROM_Ret fn_enm_Read_Data_From_EEPROM_Memory(unsigned short l_us_Base_Address, void *l_ptr_v_Data, unsigned int l_ui_Data_Length);
unsigned char fn_uc_Read_Simulated_I2C_Byte_From_EEPROM_Memory(void);
tden_EEPROM_Ret fn_enm_Write_Byte_In_EEPROM_Memory(const unsigned short l_us_Base_Address, unsigned char *l_p_uc_Data);
tden_EEPROM_Ret fn_enm_Read_Byte_From_EEPROM_Memory(const unsigned short l_us_Base_Address, unsigned char *l_p_uc_Data);
void Fn_EEPROM_Delay(unsigned int l_ui_Time);
unsigned int Calculate_CRC(unsigned char *l_p_uc_Data, unsigned int l_ui_length);
unsigned char fn_uc_Clear_EEPROM_Memory(void);



#endif

