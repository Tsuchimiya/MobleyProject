/**
 * @file    hall_sensors.h
 * @author  Curtis Team
 * @brief   Headers of functions to handle hall sensors
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _HALL_SENSORS_H
#define _HALL_SENSORS_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include "stm32f10x.h"
#include "modules_definitions.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/**
 * @brief   Way to trigg interrupts to detect forward movement
*/
#define HALLSENSOR_TRIGG_FW                    EXTI_Trigger_Rising

/**
 * @brief   Way to trigg interrupts to detect backward movement
*/
#define HALLSENSOR_TRIGG_BW                    EXTI_Trigger_Falling

/**
 * @brief   EXTI preemption priority
*/
#define HALLSENSOR_PRIO                        1

/**
 * @brief   Number of date of interrupt saved. Must be inferior to 0xFFFFFFFF
*/
#define HALLSENSOR_MAX_SAVED_POP 			    36

/**
 * @brief   An error occured : current sector if superior to number of sectors 
*/ 
#define ERROR_SENSOR_OUT_OF_RANGE 	            (uint16_t)(-1)

/**
 * @brief   An error occured : this value was not computed (too few pops are kept in memory)
*/ 
#define ERROR_VALUE_NOT_FOUND 	                (uint64_t)(-1)

/**
 * @brief   Time corresponding to a hall sensor period : meaning time between two changes of speed. Expressed in ms. 
*/
#define HALLSENSOR_TIME_BETWEEN_TWO_UPDATES     1000

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void HallSensor_QuickInit(Sensor_Enum hall_identifier);
void HallSensor_Callback(Sensor_Enum hall_identifier);
uint16_t HallSensor_getSector(Sensor_Enum hall_identifier);
int32_t HallSensor_getLap(Sensor_Enum hall_identifier);
uint64_t HallSensor_getLastPop(uint8_t n, Sensor_Enum hall_identifier);
int8_t HallSensor_getNumberTicksInPeriod(Sensor_Enum hall_identifier);
void HallSensor_Handler(Sensor_Enum hall_identifier);
void HallSensor_TimeCallback(void);
#endif // _HALL_SENSORS_H
