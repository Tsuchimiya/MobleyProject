/**
 * @file    data_interface.h
 * @author  Curtis Team
 * @brief   Headers of functions for initialization of sensors and actuators
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _DATA_INTERFACE_H
#define _DATA_INTERFACE_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include "stm32f10x.h"
#include "common_constants.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/**
* @brief    Data alignment for Rapberry Pi : alignment is done at 4 bytes.
*/
#define DATA_ALIGNMENT_PI           4

/**
* @brief    Max payload size betweeen STM and Raspi
*/
#define DATA_SIZE_MAX_RAW           ((sizeof(DataITF_STM_TypeDef) > sizeof(DataITF_PI_TypeDef)) ? sizeof(DataITF_STM_TypeDef) : sizeof(DataITF_PI_TypeDef))

/**
* @brief    Max payload size taking into account the byte alignment
*/
#define DATA_SIZE_MAX               (DATA_SIZE_MAX_RAW - (DATA_ALIGNMENT_PI - DATA_SIZE_MAX_RAW % DATA_ALIGNMENT_PI) % DATA_ALIGNMENT_PI)

/**
 * @brief data updated by the STM32
 * size: 19 bytes
 */
typedef struct {
   uint16_t ultrasonic_sensors[US_NUM]; /*!< Ultrasonic sensors data */

   uint8_t wheel_SENSOR_R;     /*!< position sensor data of right motor */
   uint8_t wheel_SENSOR_L;     /*!< position sensor data of left motor */

   float travelled_distance_R;          /*!< Travelled distance by right wheel */
   float travelled_distance_L;          /*!< Travelled distance by left wheel */

   float wheel_speed_R;                 /*!< Right wheel speed */
   float wheel_speed_L;                 /*!< Left wheel speed */    

   uint8_t steering_stop_sensor_R;      /*!< Steering position data */
   uint8_t steering_stop_sensor_L;      /*!< Steering position data */

   uint16_t motor_current_R;            /*!< Right motor current data */
   uint16_t motor_current_L;            /*!<  Left motor current data */
	 uint16_t motor_current_F;
    
   uint8_t battery_level;               /*!<  Battery level data (in %)*/

   uint8_t errors_SPI;                  /*!< Errors of communication data */
	 uint8_t US_sensors_emergency;
} DataITF_STM_TypeDef;


/**
 * @brief data updated by the Raspberry Pi
 * size: 4 bytes
 */
typedef struct {
  int16_t motor_prop;                   /*!< Propulsion motors data */
  side_TypeDef motor_dir;               /*!< Direction motor data */
  uint8_t enable_motors_control;        /*!< To enable or not a PI controller on the car speed */

  uint8_t errors_SPI;                   /*!< Errors of communication data */
} DataITF_PI_TypeDef;

/**
 * @brief STM32 data
 */
extern volatile DataITF_STM_TypeDef *pDataITF_STM;

/**
 * @brief PI data
 */
extern volatile DataITF_PI_TypeDef *pDataITF_PI;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void DataITF_Init(void);

#endif // _DATA_INTERFACE_H
