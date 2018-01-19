/**
 * @file    spi_comm.c
 * @author  Curtis Team
 * @brief   Functions to handle communication threw SPI  
 */
 
/* Includes ------------------------------------------------------------------*/
#include "spi_comm.h"

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stm32f10x.h>

#include "modules_definitions.h"
#include "frame_check.h"
#include "nvic.h"
#include "gpio.h"
#include "spi.h"
#include "dma.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/**
 * @brief   Canary position in the frame.
 */
#define FRAME_CANARY_POS(length)    ((length) + 0)

/**
 * @brief   CRC position in the frame.
 */
#define FRAME_CRC_POS(length)       (FRAME_CANARY_POS(length) + FRAME_CANARY_SIZE)

/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
size_t data_buffer_Rx_size;
size_t data_buffer_Tx_size;
uint8_t *data_buffer_Rx;
uint8_t *data_buffer_Tx;

uint8_t frame_buffer_Rx[SPICOMM_BUFFER_SIZE_MAX + FRAME_CHECK_SIZE];
uint8_t frame_buffer_Tx[SPICOMM_BUFFER_SIZE_MAX + FRAME_CHECK_SIZE];

unsigned int error_canary_num = 0;
unsigned int error_crc_num = 0;

/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
/**
 * @brief   Initializes the SPI device with circular DMA on the given buffers.
 * @param   buffer_Rx Pointer to the buffer where the received data is stored
 * @param   buffer_Tx Pointer to the buffer where the data to send is stored
 * @param   buffer_Rx_size Size of buffer_Rx in bytes
 * @param   buffer_Tx_size Size of buffer_Tx in bytes
 * @retval  None
 */
//void SPIComm_QuickInit(uint8_t * buffer_Rx, uint8_t * buffer_Tx, size_t buffer_Rx_size, size_t buffer_Tx_size) {
//    // Save buffers' adress and size
//    data_buffer_Rx_size = buffer_Rx_size;
//    data_buffer_Tx_size = buffer_Tx_size;
//    data_buffer_Rx = buffer_Rx;
//    data_buffer_Tx = buffer_Tx;

//   // Configure and enable DMA_Rx interrupt
//    NVIC_QuickInit(SPICOMM_SPIx_DMA_Rx_Channel_IRQn, SPICOMM_SPIx_DMA_PRIO);
//   // Configure and enable DMA_Tx interrupt
//    NVIC_QuickInit(SPICOMM_SPIx_DMA_Tx_Channel_IRQn, SPICOMM_SPIx_DMA_PRIO);
//    
//    // DMA configuration 
//    DMA_QuickInit_Buffer2Periph(SPICOMM_SPIx_DMA_Tx_Channel, 
//        (uint32_t)&SPICOMM_SPIx->DR,    DMA_PeripheralDataSize_Byte, 
//        (uint32_t)frame_buffer_Tx,      DMA_MemoryDataSize_Byte, 
//        data_buffer_Tx_size + FRAME_CHECK_SIZE
//    );
//    DMA_QuickInit_Periph2Buffer(SPICOMM_SPIx_DMA_Rx_Channel, 
//        (uint32_t)&SPICOMM_SPIx->DR,    DMA_PeripheralDataSize_Byte, 
//        (uint32_t)frame_buffer_Rx,      DMA_MemoryDataSize_Byte, 
//        data_buffer_Rx_size + FRAME_CHECK_SIZE
//    );

//    // SPI configuration
//    SPI_QuickInit(SPICOMM_SPIx, SPI_Mode_Slave);
//    
//    // Enable SPIx Rx and Tx request
//    SPI_I2S_DMACmd(SPICOMM_SPIx, SPI_I2S_DMAReq_Rx | SPI_I2S_DMAReq_Tx, ENABLE);

//    // Enable SPIx Rx and Tx DMA channels interrupt
//    DMA_ITConfig(SPICOMM_SPIx_DMA_Rx_Channel, DMA_IT_HT | DMA_IT_TC | DMA_IT_TE, ENABLE);
//    DMA_ITConfig(SPICOMM_SPIx_DMA_Tx_Channel, DMA_IT_HT | DMA_IT_TC | DMA_IT_TE, ENABLE);
//}


/**
 * @brief   Starts the SPI communication.
 * @retval  None
 */
void SPIComm_Start(void) {
  // SPI_Start(SPICOMM_SPIx);
}

/**
 * @brief   Stops the SPI communication.
 * @retval  None
 */
void SPIComm_Stop(void) {
//   SPI_Stop(SPICOMM_SPIx);
}
    
/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Handles the DMA_Rx interrupts of SPIComm.
 * @param  status Status of the DMA transfert
 * @retval void
 */
void SPIComm_Rx_Data_Handler(void) {
   uint8_t canary, crc, error_canary, error_crc;

   // extract canary and crc
   canary = frame_buffer_Rx[FRAME_CANARY_POS(data_buffer_Rx_size)];
   crc = frame_buffer_Rx[FRAME_CRC_POS(data_buffer_Rx_size)];

   // check canary
   error_canary = (FrameCheck_checkCanary(canary) != 0);
   error_canary_num += error_canary;

   // check crc
   error_crc = (FrameCheck_checkCRC(frame_buffer_Rx, data_buffer_Rx_size + FRAME_CANARY_SIZE, crc) != 0);
   error_crc_num += error_crc;

   // copy frame to data if no error
   if(!error_canary && !error_crc) memcpy(data_buffer_Rx, frame_buffer_Rx, data_buffer_Rx_size);
}

/**
 * @brief  Handles the DMA_Tx interrupts of SPIComm.
 * @param  status Status of the DMA transfert
 * @retval void
 */
void SPIComm_Tx_Data_Handler(void) {
   // copy data to frame
   memcpy(frame_buffer_Tx, data_buffer_Tx, data_buffer_Tx_size);
   // add canary
   frame_buffer_Tx[FRAME_CANARY_POS(data_buffer_Tx_size)] = FrameCheck_computeCanary();
   // add crc
   frame_buffer_Tx[FRAME_CRC_POS(data_buffer_Tx_size)] = FrameCheck_computeCRC(frame_buffer_Tx, data_buffer_Tx_size + FRAME_CANARY_SIZE);
}
