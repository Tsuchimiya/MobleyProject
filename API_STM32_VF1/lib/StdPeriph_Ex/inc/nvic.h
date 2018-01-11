/**
 * @file    nvic.h
 * @author  Curtis Team
 * @brief   Headers of functions to handle NVIC  
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _NVIC_H
#define _NVIC_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void NVIC_QuickInit(int8_t IRQChannel, uint8_t Priority);

#endif // _NVIC_H
