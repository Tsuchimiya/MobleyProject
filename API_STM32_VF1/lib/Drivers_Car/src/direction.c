/**
 * @file    direction.c
 * @author  L.Senaneuch
 * @brief   Functions to handle direction   
 */
 
/* Includes ------------------------------------------------------------------*/
#include "direction.h"
#include "modules_definitions.h"
#include "common_constants.h"
#include "adc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
/**
 * @brief   Inits the direction. 
 * @retval  None
*/
void Direction_QuickInit(void) {
    ADC_QuickInit(DIRECTION_ADC, DIRECTION_GPIO, DIRECTION_PIN, DIRECTION_RANK, DIRECTION_SAMPLING);
}

/**
 * @brief   Returns the direction value in degree
 * @retval  Charge of the battery (in percentage)
*/
uint8_t Direction_get(void) {
    uint16_t DirectionValue = ADC_QuickGet(DIRECTION_ADC, DIRECTION_RANK);
    //return PERCENTAGE*(BatteryValue - BATTERY_ADC_SCALE)/BATTERY_ADC_SCALE;
		return (DirectionValue>>4);
}

/* Private functions ---------------------------------------------------------*/
