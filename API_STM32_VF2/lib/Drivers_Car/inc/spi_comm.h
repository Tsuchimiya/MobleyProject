/**
 * @file    spi_comm.h
 * @author  Curtis Team
 * @brief   Headers of functions to handle communication threw SPI  
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _SPI_COMM_H
#define _SPI_COMM_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include <stm32f10x.h>

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported defines ------------------------------------------------------------*/

#ifndef SPICOMM_BUFFER_SIZE_MAX
/**
 * @brief   Default size of the buffer used for SPI communication.
 */
#define SPICOMM_BUFFER_SIZE_MAX     256

#endif // SPICOMM_BUFFER_SIZE_MAX

/* Exported functions ------------------------------------------------------- */
void SPIComm_QuickInit(uint8_t * buffer_Rx, uint8_t * buffer_Tx, size_t buffer_Rx_size, size_t buffer_Tx_size);

void SPIComm_Start(void);
void SPIComm_Stop(void);

#endif // _SPI_COMM_H
