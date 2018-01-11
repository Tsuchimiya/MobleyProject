/**
 * @file    driver_callbacks.h
 * @author  Curtis Team
 * @brief   Headers of functions to manage callbacks for Drivers_Car layer 
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _DRIVER_CALLBACKS_H
#define _DRIVER_CALLBACKS_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include <stm32f10x.h>
#include "common_constants.h"
#include "modules_definitions.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void HallSensor_Handler(Sensor_Enum hall_identifier);
void FrontMotor_Handler(side_TypeDef direction);
void SPIComm_Rx_Data_Handler(void);
void SPIComm_Tx_Data_Handler(void);

#endif // _DRIVER_CALLBACKS_H
