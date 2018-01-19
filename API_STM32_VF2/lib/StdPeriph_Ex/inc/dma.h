/**
 * @file    dma.h
 * @author  Curtis Team
 * @brief   Headers of functions to handle DMA  
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _DMA_H
#define _DMA_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void DMA_QuickInit_Periph2Buffer(DMA_Channel_TypeDef* DMAy_Channelx, uint32_t PeripheralBaseAddr, uint32_t PeripheralDataSize, uint32_t MemoryBaseAddr, uint32_t MemoryDataSize, uint32_t MemoryBufferSize);
void DMA_QuickInit_Buffer2Periph(DMA_Channel_TypeDef* DMAy_Channelx, uint32_t PeripheralBaseAddr, uint32_t PeripheralDataSize, uint32_t MemoryBaseAddr, uint32_t MemoryDataSize, uint32_t MemoryBufferSize);

void DMA_Callback(DMA_Channel_TypeDef* DMAy_Channelx, uint8_t itstatus);

#endif // _DMA_H
