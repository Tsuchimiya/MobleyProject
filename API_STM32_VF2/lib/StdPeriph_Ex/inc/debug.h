/**
 * @file    debug.h
 * @author  Curtis Team
 * @brief   Headers of functions to help debugging  
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _DEBUG_H
#define _DEBUG_H

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
int fputc(int ch, FILE *f);
void dbg_sleep(uint32_t ms);

#endif // _DEBUG_H
