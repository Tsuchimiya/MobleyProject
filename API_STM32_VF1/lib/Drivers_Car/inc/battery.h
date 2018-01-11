/**
 * @file    battery.h
 * @author  Curtis Team
 * @brief   Headers of functions to handle battery 
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _BATTERY_H
#define _BATTERY_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Battery_QuickInit(void);
uint8_t Battery_get(void);

#endif // _BATTERY_H
