/**
 * @file    tim.h
 * @author  Curtis Team
 * @brief   Headers of functions to handle Timers  
*/
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TIM_H
#define _TIM_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/** 
 * @brief  Timers remap type
*/
typedef enum {
    DefaultRemap,
    PartialRemap1,
    PartialRemap2,
    FullRemap, 
    ErrorRemap
} TIM_remap_TypeDef;

/* Exported constants --------------------------------------------------------*/
/**
 * @brief    Number of timers existing on this board
*/
#define TIM_MAX_NUMBER 4

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void TIM_QuickInit(TIM_TypeDef *TIMx, float period_us);

void TIM_Start(TIM_TypeDef *TIMx);
void TIM_Stop(TIM_TypeDef *TIMx);

void TIM_Callback(TIM_TypeDef TIMx);

int TIM_Remap(TIM_TypeDef *TIMx, TIM_remap_TypeDef RemapType);
TIM_remap_TypeDef TIM_RemapStatus(TIM_TypeDef *TIMx);

#endif // _TIM_H
