/**
 * @file    gpio.c
 * @author  Curtis Team
 * @brief   Functions to handle GPIO
 */

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stm32f10x.h>
#include "gpio.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void GPIO_ClockEnable(GPIO_TypeDef *GPIOx);

/* Public functions ----------------------------------------------------------*/
/**
 * @brief   Makes the initialization of the given Pin with the parameters specified
 * @param   GPIOx: where x can be (A..G) to select the GPIO peripheral.
 * @param   GPIO_Pin: specifies the port bit to read. This parameter can be GPIO_Pin_x where x can be (0..15).
 * @param   GPIO_Mode: mode of GPIO
 *      @arg GPIO_Mode_AIN
 *      @arg GPIO_Mode_IN_FLOATING
 *      @arg GPIO_Mode_IPD
 *      @arg GPIO_Mode_IPU
 *      @arg GPIO_Mode_Out_OD
 *      @arg GPIO_Mode_Out_PP
 *      @arg GPIO_Mode_AF_OD
 *      @arg GPIO_Mode_AF_PP
 * @retval  None
 */
void GPIO_QuickInit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode) {
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_ClockEnable(GPIOx);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode;

    GPIO_Init(GPIOx, &GPIO_InitStruct);
}

/* Private functions ---------------------------------------------------------*/
/**
 * @brief   Enables clock on the adequate GPIO
 * @param   GPIOx: where x can be (A..G) to select the GPIO peripheral.
 * @retval  None
 */
void GPIO_ClockEnable(GPIO_TypeDef* GPIOx) {
        if (GPIOx == GPIOA) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
   else if (GPIOx == GPIOB) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
   else if (GPIOx == GPIOC) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
   else if (GPIOx == GPIOD) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
   else if (GPIOx == GPIOE) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
   else if (GPIOx == GPIOF) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
   else if (GPIOx == GPIOG) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
   else {}
}



