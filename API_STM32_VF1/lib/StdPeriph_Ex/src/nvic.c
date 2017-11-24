/**
 * @file    nvic.c
 * @author  Curtis Team
 * @brief   Functions to handle NVIC
 */

 /* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stm32f10x.h>
#include "nvic.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
/**
 * @brief   Makes the initialization of the given NVIC with the parameters specified
 * @param   IRQChannel: Number of the Interrupt Request to init
 * @param   Priority: Priority of the interruption initialized
 * @retval  None
*/
void NVIC_QuickInit(int8_t IRQChannel, uint8_t Priority) {
    NVIC_InitTypeDef NVIC_InitStruct;
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

    NVIC_InitStruct.NVIC_IRQChannel = IRQChannel;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = Priority;

    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStruct);
}
