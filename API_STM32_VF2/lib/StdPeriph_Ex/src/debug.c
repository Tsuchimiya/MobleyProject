/**
 * @file    debug.c
 * @author  Curtis Team
 * @brief   Functions to help debugging  
 */
 
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stm32f10x.h>
#include "debug.h"

/* Private typedef -----------------------------------------------------------*/
struct __FILE {int handle;/* Add whatever you need here */};

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
FILE __stdout;
FILE __stdin;

/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
/**
 * @brief   Function used by printf to put a char in the Debug Viewer.
 * @param   ch Character to send.
 * @param   f  Output stream.
 * @return  The character sent.
*/
int fputc(int ch, FILE *f) {
  ITM_SendChar(ch);
  return(ch);
}

/**
 * @brief   For-loop sleep
 * @param   ms Number of milliseconds.
*/
void dbg_sleep(uint32_t ms) {
    uint32_t i;
    uint32_t ticks = ms * (SystemCoreClock/1000);
    for(i = 29; i < ticks; i+=5);
}

/* Private functions ---------------------------------------------------------*/
