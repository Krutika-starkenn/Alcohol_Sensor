/******************** (C) COPYRIGHT 2017 SST ***********************************
* File Name          : Port_Pin_Config.h
* Author             : Mr. Naresh S. Partole
* Version            : V1.0.1
* Date               : 18/07/2017
* Description        : LED cum Alarm card.
********************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HARDWARE_CONFIG_H
#define __HARDWARE_CONFIG_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

//#define	HEARTBEAT_LED_ON							GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_SET)
//#define	HEARTBEAT_LED_OFF							GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_RESET)
#define	HEARTBEAT_LED_ON							GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET)
#define	HEARTBEAT_LED_OFF							GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET)

#define RFID_LED_ON									GPIO_WriteBit(GPIOB, GPIO_Pin_4, Bit_SET)
#define RFID_LED_OFF								GPIO_WriteBit(GPIOB, GPIO_Pin_4, Bit_RESET)

//#define BUZZER_ON									GPIO_WriteBit(GPIOB, GPIO_Pin_4, Bit_SET)
//#define BUZZER_OFF									GPIO_WriteBit(GPIOB, GPIO_Pin_4, Bit_RESET)

#define BUZZER_ON									GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_SET)
#define BUZZER_OFF									GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_RESET)

#define RED_LED_ON									GPIO_WriteBit(GPIOB, GPIO_Pin_15, Bit_SET)
#define RED_LED_OFF									GPIO_WriteBit(GPIOB, GPIO_Pin_15, Bit_RESET)

#define GREEN_LED_ON								GPIO_WriteBit(GPIOB, GPIO_Pin_14, Bit_SET)
#define GREEN_LED_OFF								GPIO_WriteBit(GPIOB, GPIO_Pin_14, Bit_RESET)

#define BLUE_LED_ON									GPIO_WriteBit(GPIOB, GPIO_Pin_13, Bit_SET)
#define BLUE_LED_OFF								GPIO_WriteBit(GPIOB, GPIO_Pin_13, Bit_RESET)


		

//#define ALCOHOL_TEST_BUTTON_STATUS					GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)


#endif /* __HARDWARE_CONFIG_H */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
