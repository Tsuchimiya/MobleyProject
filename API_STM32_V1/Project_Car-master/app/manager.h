/**
 * @file	manager.h
 * @author	Curtis Team
 * @brief	Header template for all the files of the project  
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _MANAGER_H
#define _MANAGER_H

#include <stdint.h>

#include "system_time.h"
#include "position_sensors.h"
#include "speed_sensors.h"

#include "motors.h"
#include "front_motor.h"
#include "rear_motors.h"

#include "us_sensors.h"
#include "direction.h"
#include "can.h"

#include "data_interface.h"
#include "mirroring.h"

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/


void Manager_Init(void);
void Manager_Callback(void);

#endif // _MANAGER_H
