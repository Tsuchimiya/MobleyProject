/**
 * @file 	tim_ic.h
 * @author 	Curtis Team
 * @brief 	Headers of functions to handle TIM_IC
*/
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TIM_IC_H
#define _TIM_IC_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "gpio.h"
#include "tim.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void TIM_IC_QuickInit(TIM_TypeDef *TIMx, uint16_t Channelx, float FrequencyCompareHz);

void TIM_IC_Start(TIM_TypeDef *TIMx);
void TIM_IC_Stop(TIM_TypeDef *TIMx);

#endif // _TIM_IC_H
