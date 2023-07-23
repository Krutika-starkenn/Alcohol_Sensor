#ifndef __HAL_PRESSURE_SENSOR_XGZP6857D_H
#define __HAL_PRESSURE_SENSOR_XGZP6857D_H
/* I2C for presure sensor Pressure_Sensor_XGZP6857D */
#define SLAVE_ADDRESS_XGZP6857D			0x6D

void fn_uc_XGZP6857D_Pressure_Sensor_start(void);
void fn_uc_XGZP6857D_Pressure_Sensor_stop(void);
void fn_uc_XGZP6857D_Pressure_Sensor_Send_0(void);
void fn_uc_XGZP6857D_Pressure_Sensor_Send_1(void);
char fn_uc_XGZP6857D_Pressure_Sensor_ACK(void);



#endif
