/**
 * @file    mirroring.h
 * @author  Curtis Team
 * @brief   Headers of functions to perform mirroring between STM32 and master
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _MIRRORING_H
#define _MIRRORING_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Mirroring_Init(void);
void Mirroring_Start(void);
void Mirroring_Stop(void);

#endif // _MIRRORING_H
