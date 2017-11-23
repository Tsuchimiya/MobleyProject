/**
 * @file    data_interface.c
 * @author  Curtis Team
 * @brief   Functions for initialization of sensors and actuators
 */
 
/* Includes ------------------------------------------------------------------*/
#include "data_interface.h"

#include "common_constants.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/**
 * @brief   STM32 data
 */
volatile DataITF_STM_TypeDef *pDataITF_STM;
/**
 * @brief   PI data
 */
volatile DataITF_PI_TypeDef *pDataITF_PI;

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void DataITF_PI_Init(void);
void DataITF_STM_Init(void);

/* Public functions ----------------------------------------------------------*/
/**
 * @brief   Initializes the DataITF_STM and DataITF_STM structures
 * @retval  None
 */
void DataITF_Init(void) {
   DataITF_PI_Init();
   DataITF_STM_Init();
}

/* Private functions ---------------------------------------------------------*/

/**
 * @brief   Initializes the DataITF_PI structure with bytes of zeros
 * @retval  None
 */
void DataITF_PI_Init(void) {
   pDataITF_PI->motor_prop            = 0;
   pDataITF_PI->motor_dir             = NONE;
   pDataITF_PI->enable_motors_control = 0;
   pDataITF_PI->errors_SPI            = 0;
}
/**
 * @brief   Initializes the DataITF_STM structure with bytes of zeros
 * @retval  None
 */
void DataITF_STM_Init(void) {
    int i;

    for(i = 0; i < US_NUM; i++)
        pDataITF_STM->ultrasonic_sensors[i] = 0;

    pDataITF_STM->wheel_SENSOR_R = 0;
    pDataITF_STM->wheel_SENSOR_L = 0;
    pDataITF_STM->steering_stop_sensor_R  = 0;
    pDataITF_STM->steering_stop_sensor_L  = 0;
    pDataITF_STM->motor_current_R         = 0;
    pDataITF_STM->motor_current_L         = 0;
    pDataITF_STM->errors_SPI              = 0;

    pDataITF_STM->wheel_speed_R          = 0.0;
    pDataITF_STM->wheel_speed_L          = 0.0;
	  pDataITF_STM->travelled_distance_R   = 0.0;
    pDataITF_STM->travelled_distance_L   = 0.0;
    pDataITF_STM->battery_level          = 0;
}
