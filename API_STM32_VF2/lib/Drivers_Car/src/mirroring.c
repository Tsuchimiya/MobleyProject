/**
 * @file    mirroring.c
 * @author  Curtis Team
 * @brief   Functions to perform mirroring between STM32 and master
 */
 
/* Includes ------------------------------------------------------------------*/
#include "mirroring.h"
#include "spi_comm.h"
#include "can.h"
#include "data_interface.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define BUFFER_RX_SIZE (DATA_SIZE_MAX)
#define BUFFER_TX_SIZE (DATA_SIZE_MAX)

uint8_t buffer_Rx[BUFFER_RX_SIZE];
uint8_t buffer_Tx[BUFFER_TX_SIZE];
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
/**
 * @brief   Initialize the mirroring for both data_STM (sent) and data_PI (received).
 * @retval  None
 */
void Mirroring_Init(void) {
   pDataITF_PI  = (DataITF_PI_TypeDef  *)buffer_Rx;
   pDataITF_STM = (DataITF_STM_TypeDef *)buffer_Tx;
   DataITF_Init();
   //SPIComm_QuickInit((uint8_t *)buffer_Rx, (uint8_t *)buffer_Tx, BUFFER_RX_SIZE, BUFFER_TX_SIZE);
}

/**
 * @brief Starts the mirroring.
 * @retval  None
 */
void Mirroring_Start(void) {
   SPIComm_Start();
}

/**
 * @brief   Stops the mirroring.
 * @retval  None
 */
void Mirroring_Stop(void) {
   SPIComm_Stop();
}

/* Private functions ---------------------------------------------------------*/
