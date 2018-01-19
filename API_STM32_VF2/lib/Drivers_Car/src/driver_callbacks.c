/**
 * @file    driver_callbacks.c
 * @author  Curtis Team
 * @brief   Functions to manage callbacks for Drivers_Car layer 
 */
 
/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stm32f10x.h>
#include "driver_callbacks.h"
#include "common_constants.h"
#include "modules_definitions.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

__weak void HallSensor_Handler(Sensor_Enum hall_identifier) {}
__weak void FrontMotor_Handler(side_TypeDef direction) {}
__weak void SPIComm_Rx_Data_Handler(void) {}
__weak void SPIComm_Tx_Data_Handler(void) {}

void EXTI_Callback(uint32_t EXTI_Line) {
    if (EXTI_Line == SENSOR_L_LINE) HallSensor_Handler(SENSOR_L);
    if (EXTI_Line == SENSOR_R_LINE) HallSensor_Handler(SENSOR_R);

/**
 * Commented by L.Senaneuch cause => sensors remplaced by adc value in new hwr
 */
//    if (EXTI_Line == FRONT_LINE_LEFT)   FrontMotor_Handler(LEFT);
//    if (EXTI_Line == FRONT_LINE_RIGHT)  FrontMotor_Handler(RIGHT);
}

//void DMA_Callback(DMA_Channel_TypeDef* DMAy_Channelx, uint8_t itstatus) {
//   if (DMAy_Channelx == SPICOMM_SPIx_DMA_Rx_Channel) {
//      if (itstatus & DMA_IT_TC) SPIComm_Rx_Data_Handler();
//   } else if (DMAy_Channelx == SPICOMM_SPIx_DMA_Tx_Channel) {
//      if (itstatus & DMA_IT_TC) SPIComm_Tx_Data_Handler();
//   }
//}
//    
/* Private functions ---------------------------------------------------------*/
