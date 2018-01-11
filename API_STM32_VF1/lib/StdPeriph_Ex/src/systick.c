/**
 * @file    systick.c
 * @author  Curtis Team
 * @brief   Functions to handle systick (STM internal time)  
 */

/* Includes ------------------------------------------------------------------*/
#include "systick.h"
#include "nvic.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

__weak void SysTick_Callback(void) {}

/**
 * @brief   Makes the initialization of the systick system 
*/
void SysTick_QuickInit(void) {
    while (SysTick_Config(SystemCoreClock / SYSTICK_FREQ - 1) != 0);
    NVIC_QuickInit(SysTick_IRQn, 1);
}

/**
 * @brief Handler associated to SysTick.  
*/
void SysTick_ITHandler(void) {
    SysTick_Callback();
}

/* Private functions ---------------------------------------------------------*/
