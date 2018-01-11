/**
 * @file 	pwm.h
 * @author 	Curtis Team
 * @brief 	Headers of functions to handle PWM
*/
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _PWM_H
#define _PWM_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void PWM_QuickInit(TIM_TypeDef *TIMx, uint16_t Channelx, float frequencyPWMHz);
int PWM_QuickInit_Complementary(TIM_TypeDef *TIMx, uint16_t Channelx);
void PWM_SetDutyCycle(TIM_TypeDef *TIMx, uint16_t Channelx, float dutyCycle);
void PWM_Start(TIM_TypeDef *TIMx);
void PWM_Stop(TIM_TypeDef *TIMx);  

#endif // _PWM_H
