/**************************************************
* Version Module - Project Tatsuno
*
* Copyright 2012 Leo Integrated Technologies Pvt Ltd.
* All Rights Reserved
*
* The information contained herein is confidential
* property of Company. The use, copying, transfer or 
* disclosure of such information is prohibited except
* by express written agreement with Company.
*
* File Name          : stm32f10x_wwdg.h
* Author             : Sanish P H
* Version            : Beta V.0
* Date               : 
* Author             : MCD Application Team
* Version            : V2.0.2
* Date               : 07/11/2008
* Description        : This file contains all the functions prototypes for the
*                      WWDG firmware library.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_WWDG_H
#define __STM32F10x_WWDG_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_map.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* WWDG Prescaler */
#define WWDG_Prescaler_1    ((u32)0x00000000)
#define WWDG_Prescaler_2    ((u32)0x00000080)
#define WWDG_Prescaler_4    ((u32)0x00000100)
#define WWDG_Prescaler_8    ((u32)0x00000180)

#define IS_WWDG_PRESCALER(PRESCALER) (((PRESCALER) == WWDG_Prescaler_1) || \
                                      ((PRESCALER) == WWDG_Prescaler_2) || \
                                      ((PRESCALER) == WWDG_Prescaler_4) || \
                                      ((PRESCALER) == WWDG_Prescaler_8))

#define IS_WWDG_WINDOW_VALUE(VALUE) ((VALUE) <= 0x7F)

#define IS_WWDG_COUNTER(COUNTER) (((COUNTER) >= 0x40) && ((COUNTER) <= 0x7F))

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void WWDG_DeInit(void);
void WWDG_SetPrescaler(u32 WWDG_Prescaler);
void WWDG_SetWindowValue(u8 WindowValue);
void WWDG_EnableIT(void);
void WWDG_SetCounter(u8 Counter);
void WWDG_Enable(u8 Counter);
FlagStatus WWDG_GetFlagStatus(void);
void WWDG_ClearFlag(void);

#endif /* __STM32F10x_WWDG_H */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
