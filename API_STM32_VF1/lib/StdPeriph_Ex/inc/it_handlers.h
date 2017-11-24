/**
 * @file    it_handlers.h
 * @author  Curtis Team
 * @brief   Header of Main Interrupt Service Routines
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _IT_HANDLERS_H
#define _IT_HANDLERS_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stm32f10x.h>

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void EXTI_ITHandler(uint32_t EXTI_Line);
    
/**
 * @brief  Handles DMA interrupt requests.
 * @param  DMAy_Channelx DMA Channel of the interrupt
 * @param  flags Any combination of DMA_IT_TC, DMA_IT_HT, DMA_IT_TE
 * @retval None
*/
void DMA_ITHandler(DMA_Channel_TypeDef* DMAy_Channelx, uint8_t itstatus);

void ADC_ITHandler(ADC_TypeDef* ADCx);

void TIM_ITHandler(TIM_TypeDef* TIMx);

void SPI_ITHandler(SPI_TypeDef* SPIx);

void SysTick_ITHandler(void);

#endif // _IT_HANDLERS_H
