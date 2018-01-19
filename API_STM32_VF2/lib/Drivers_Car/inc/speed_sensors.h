/**
 * @file    speed_sensors.h
 * @author  Curtis Team
 * @brief   Headers of functions to handle speed sensors   
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _SPEED_SENSOR_H
#define _SPEED_SENSOR_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include "stm32f10x.h"
#include "modules_definitions.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/        
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void SpeedSensor_QuickInit(Sensor_Enum SpeedSensor_identifier);
float SpeedSensor_get(float unit, Sensor_Enum SpeedSensor_identifier);

#endif // _SPEED_SENSOR_H
