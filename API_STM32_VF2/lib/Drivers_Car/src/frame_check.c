/**
 * @file    frame_check.c
 * @author  Curtis Team
 * @brief   Functions to ensure frame checking
 */
 
/* Includes ------------------------------------------------------------------*/
#include "frame_check.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/**
 * @brief   Canary used for data transmissions
 */
#define CANARY  ((uint8_t)0xCA)
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
/**
 * @brief   Calculates the Checksum
 * @param   *pdata Pointer on the data whose CRC is beeing calculated.
 * @param   len Data lenght
 * @return  uint8_t The CRC
 */
uint8_t FrameCheck_computeCRC(uint8_t *pdata, size_t len) {
    int i;
    uint8_t CRC_ = 0;
    for (i = 0 ; i < len ; i++) CRC_ ^= pdata[i];
    return CRC_;
}

/**
 * @brief   Checks if the CRC is correct
 * @param   *pdata Pointer on the data whose CRC is beeing checked.
 * @param   len Data lenght
 * @param   crc CRC to check
 * @retval  uint8_t 0 if successful, something else if error
 */
uint8_t FrameCheck_checkCRC(uint8_t *pdata, size_t len, uint8_t crc) {
    return crc ^ FrameCheck_computeCRC(pdata, len);
}

/**
 * @brief puts the value of the canary
 * @retval the value of the canary
 */
uint8_t FrameCheck_computeCanary(void) {
    return CANARY;
}

/**
 * @brief   checks if the canary is empty
 * @param   canary Canary to check
 * @retval  0 if empty something else if error
 */
uint8_t FrameCheck_checkCanary(uint8_t canary) {
    return CANARY ^ canary;
}

/**
 * @brief   Frame correction based on Hamming code
 * @param   *pdata Pointer on the data whose CRC is beeing checked.
 * @param   len Data lenght
 * @param   crc CRC to check
 * @return  ???
 */
uint8_t FrameCheck_frameCorrection(uint8_t *pdata, size_t len, uint8_t crc) {
    return (uint8_t) 0x00;
}
/* Private functions ---------------------------------------------------------*/
