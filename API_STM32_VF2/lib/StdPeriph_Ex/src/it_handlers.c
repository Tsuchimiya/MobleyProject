/**
 * @file    it_handlers.c
 * @author  Curtis Team
 * @brief   Main Interrupt Service Routines
*/

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stm32f10x.h>
#include "it_handlers.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/**
* @brief IRQ Handler Macro for ADC: call ITHandler and clear interrupt
*/
#define ADC_IRQ_HANDLER(adc) \
   if ( (ADC_GetITStatus(ADC##adc, ADC_IT_AWD ) == SET) || \
        (ADC_GetITStatus(ADC##adc, ADC_IT_EOC ) == SET) || \
        (ADC_GetITStatus(ADC##adc, ADC_IT_JEOC) == SET) ) \
   { \
       ADC_ITHandler(ADC##adc); \
       ADC_ClearITPendingBit(ADC##adc, ADC_IT_AWD | ADC_IT_EOC | ADC_IT_JEOC); \
   }

/**
* @brief IRQ Handler Macro for TIM: call ITHandler and clear interrupt
*/
#define TIM_IRQ_HANDLER(tim) \
   TIM_ITHandler(TIM##tim); \
   TIM_ClearITPendingBit(TIM##tim, TIM_IT_Update | TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4 | TIM_IT_COM | TIM_IT_Trigger | TIM_IT_Break); \

/**
* @brief IRQ Handler Macro for DMA: call ITHandler and clear interrupt
*/
#define DMA_IRQ_HANDLER(dma, channel) \
   DMA_ITHandler(DMA##dma##_Channel##channel,   ((uint8_t)DMA_GetITStatus(DMA##dma##_IT_TC##channel) << 1) + \
                                                ((uint8_t)DMA_GetITStatus(DMA##dma##_IT_HT##channel) << 2) + \
                                                ((uint8_t)DMA_GetITStatus(DMA##dma##_IT_TE##channel) << 3)); \
   DMA_ClearITPendingBit(DMA##dma##_IT_GL##channel);

/**
* @brief IRQ Handler Macro for EXTI: call ITHandler and clear interrupt
*/
#define EXTI_IRQ_HANDLER(exti) \
    if (EXTI_GetITStatus(EXTI_Line##exti) == SET) { \
        EXTI_ITHandler(EXTI_Line##exti); \
        EXTI_ClearITPendingBit(EXTI_Line##exti); \
    }

/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

__weak void EXTI_ITHandler(uint32_t EXTI_Line) {}
__weak void DMA_ITHandler(DMA_Channel_TypeDef* DMAy_Channelx, uint8_t itstatus) {}
__weak void ADC_ITHandler(ADC_TypeDef* ADCx) {}
__weak void TIM_ITHandler(TIM_TypeDef* TIMx) {}
__weak void SPI_ITHandler(SPI_TypeDef* SPIx) {}
__weak void SysTick_ITHandler(void) {}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/******************************************************************************/
/**
 * @brief  Handles EXTI0_IRQHandler interrupt request.
 * @param  None
 * @retval None
*/
void EXTI0_IRQHandler(void) {
    EXTI_IRQ_HANDLER(0);
}

/**
 * @brief  Handles EXTI1_IRQHandler interrupt request.
 * @param  None
 * @retval None
*/
void EXTI1_IRQHandler(void) {
    EXTI_IRQ_HANDLER(1);
}

/**
 * @brief  Handles EXTI2_IRQHandler interrupt request.
 * @param  None
 * @retval None
*/
void EXTI2_IRQHandler(void) {
    EXTI_IRQ_HANDLER(2);
}

/**
 * @brief  Handles EXTI3_IRQHandler interrupt request.
 * @param  None
 * @retval None
*/
void EXTI3_IRQHandler(void) {
    EXTI_IRQ_HANDLER(3);
}

/**
 * @brief  Handles EXTI4_IRQHandler interrupt request.
 * @param  None
 * @retval None
*/
void EXTI4_IRQHandler(void) {
    EXTI_IRQ_HANDLER(4);
}

/**
 * @brief  Handles EXTI9_5_IRQHandler interrupt request.
 * @param  None
 * @retval None
*/
void EXTI9_5_IRQHandler(void) {
    EXTI_IRQ_HANDLER(5);
    EXTI_IRQ_HANDLER(6);
    EXTI_IRQ_HANDLER(7);
    EXTI_IRQ_HANDLER(8);
    EXTI_IRQ_HANDLER(9);
}

/**
 * @brief  Handles EXTI9_5_IRQHandler interrupt request.
 * @param  None
 * @retval None
*/
void EXTI15_10_IRQHandler(void) {
    EXTI_IRQ_HANDLER(10);
    EXTI_IRQ_HANDLER(11);
    EXTI_IRQ_HANDLER(12);
    EXTI_IRQ_HANDLER(13);
    EXTI_IRQ_HANDLER(14);
    EXTI_IRQ_HANDLER(15);
}


/**
 * @brief  Handles ADC1_2_IRQHandler interrupt request.
 * @param  None
 * @retval None
*/
void ADC1_2_IRQHandler(void) {
    ADC_IRQ_HANDLER(1)
    ADC_IRQ_HANDLER(2)
}


///**
// * @brief  Handles DMA1_Channel1 interrupt request.
// * @param  None
// * @retval None
//*/
//void DMA1_Channel1_IRQHandler(void) {
//   DMA_IRQ_HANDLER(1, 1)
//}

///**
// * @brief  Handles DMA1_Channel2 interrupt request.
// * @param  None
// * @retval None
//*/
//void DMA1_Channel2_IRQHandler(void) {
//   DMA_IRQ_HANDLER(1, 2)
//}

///**
// * @brief  Handles DMA1_Channel3 interrupt request.
// * @param  None
// * @retval None
//*/
//void DMA1_Channel3_IRQHandler(void) {
//   DMA_IRQ_HANDLER(1, 3)
//}

///**
// * @brief  Handles DMA1_Channel4 interrupt request.
// * @param  None
// * @retval None
//*/
//void DMA1_Channel4_IRQHandler(void) {
//   DMA_IRQ_HANDLER(1, 4)
//}

///**
// * @brief  Handles DMA1_Channel5 interrupt request.
// * @param  None
// * @retval None
//*/
//void DMA1_Channel5_IRQHandler(void) {
//   DMA_IRQ_HANDLER(1, 5)
//}

///**
// * @brief  Handles DMA1_Channel6 interrupt request.
// * @param  None
// * @retval None
//*/
//void DMA1_Channel6_IRQHandler(void) {
//   DMA_IRQ_HANDLER(1, 6)
//}

///**
// * @brief  Handles DMA1_Channel7 interrupt request.
// * @param  None
// * @retval None
//*/
//void DMA1_Channel7_IRQHandler(void) {
//   DMA_IRQ_HANDLER(1, 7)
//}

/**
 * @brief  Handles TIM1 up interrupt request.
 * @param  None
 * @retval None
*/
void TIM1_UP_IRQHandler(void) {
    TIM_ITHandler(TIM1);
}

/**
 * @brief  Handles TIM2 interrupt request.
 * @param  None
 * @retval None
*/
void TIM2_IRQHandler(void) {
    TIM_ITHandler(TIM2);
}

/**
 * @brief  Handles TIM3 interrupt request.
 * @param  None
 * @retval None
*/

void TIM3_IRQHandler(void) {
    TIM_ITHandler(TIM3);
}


/**
 * @brief  Handles TIM4 interrupt request.
 * @param  None
 * @retval None
*/

/*void TIM4_IRQHandler(void) {
    TIM_ITHandler(TIM4);
}*/

/**
 * @brief  Handles SPI1 interrupt request.
 * @param  None
 * @retval None
*/
void SPI1_IRQHandler(void) {
    SPI_ITHandler(SPI1);
}

/**
 * @brief  Handles SPI2 interrupt request.
 * @param  None
 * @retval None
*/
void SPI2_IRQHandler(void) {
    SPI_ITHandler(SPI2);
}

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  Handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void) {}

/**
  * @brief  Handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void) {
  // Go to infinite loop when Hard Fault exception occurs
  while(1) {}
}

/**
  * @brief  Handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void) {
  // Go to infinite loop when Memory Manage exception occurs
  while(1) {}
}

/**
  * @brief  Handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void) {
  // Go to infinite loop when Bus Fault exception occurs
  while(1) {}
}

/**
  * @brief  Handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void) {
  // Go to infinite loop when Usage Fault exception occurs
  while(1) {}
}

/**
  * @brief  Handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void) {}

/**
  * @brief  Handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void) {}

/**
  * @brief  Handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void) {}

/**
  * @brief  Handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void) {
    SysTick_ITHandler();
}
