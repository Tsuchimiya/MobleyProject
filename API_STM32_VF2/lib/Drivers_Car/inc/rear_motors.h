/**
 * @file    rear_motors.h
 * @author  Curtis team
 * @brief   Headers of functions to handle rear motors
 */




/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _REAR_MOTORS_H_
#define _REAR_MOTORS_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include <stm32f10x_conf.h>
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/**
 * @brief   Time corresponding to a rear motor period : meaning time between two changes of command. Expressed in ms. 
*/
#define MOTORS_COMMAND_TIME_BETWEEN_TWO_UPDATES 10

/* Exported macro ------------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/
extern volatile int16_t speed_cmd;

/* Exported functions ------------------------------------------------------- */
void RearMotors_QuickInit(void);
void RearMotors_Enable(void);
void RearMotors_Disable(void);
void RearMotors_setSpeed(int16_t speed);

#endif // _REAR_MOTORS_H_
