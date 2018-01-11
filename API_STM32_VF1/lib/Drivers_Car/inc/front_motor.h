/**
 * @file    front_motor.h
 * @author  Curtis Team
 * @brief   Headers of functions to handle front motor  
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _FRONT_MOTOR_H
#define _FRONT_MOTOR_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include "stm32f10x.h"
#include "common_constants.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void FrontMotor_QuickInit(void);
void FrontMotor_turn(side_TypeDef direction); 
void FrontMotor_Handler(side_TypeDef direction);

#endif // _FRONT_MOTOR_H
