/**
 * @file    spi.h
 * @author  Curtis Team
 * @brief   Headers of functions to handle SPI
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _SPI_H
#define _SPI_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/


/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void SPI_QuickInit(SPI_TypeDef* SPIx, uint16_t SPI_Mode);
void SPI_Start(SPI_TypeDef* SPIx);
void SPI_Stop(SPI_TypeDef* SPIx);

void SPI_Callback(SPI_TypeDef* SPIx);

#endif // _SPI_H
