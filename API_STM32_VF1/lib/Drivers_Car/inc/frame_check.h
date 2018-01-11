/**
 * @file    frame_check.h
 * @author  Curtis Team
 * @brief   Headers of functions to ensure frame checking
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _FRAME_CHECK_H
#define _FRAME_CHECK_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/**
 * @brief   Canary length (expressed in bytes)
 */
#define FRAME_CANARY_SIZE   1

/**
 * @brief   CRC length (expressed in bytes)
 */
#define FRAME_CRC_SIZE      1

/**
 * @brief   Total size added to payload for communication checking
 */
#define FRAME_CHECK_SIZE    (FRAME_CANARY_SIZE + FRAME_CRC_SIZE)

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
uint8_t FrameCheck_computeCRC(uint8_t *pdata, size_t len);
uint8_t FrameCheck_checkCRC(uint8_t *pdata, size_t len, uint8_t crc);
uint8_t FrameCheck_computeCanary(void);
uint8_t FrameCheck_checkCanary(uint8_t canary);
uint8_t FrameCheck_frameCorrection(uint8_t *pdata, size_t len, uint8_t crc);

#endif // _FRAME_CHECK_H
