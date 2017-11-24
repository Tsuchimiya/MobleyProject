/**
 * @file    battery.c
 * @author  Curtis Team
 * @brief   Functions to handle battery   
 */
 
/* Includes ------------------------------------------------------------------*/
#include "battery.h"
#include "modules_definitions.h"
#include "common_constants.h"
#include "adc.h"
#include "data_interface.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
/**
 * @brief   Inits the battery. 
 * @retval  None
*/
void Battery_QuickInit(void) {
    ADC_QuickInit(BATTERY_ADC, BATTERY_GPIO, BATTERY_PIN, BATTERY_RANK, BATTERY_SAMPLING);
}

/**
 * @brief   Returns the charge of the battery
 * @retval  Charge of the battery (in percentage)
*/
uint8_t Battery_get(void) {
    uint16_t BatteryValue = ADC_QuickGet(BATTERY_ADC, BATTERY_RANK);
    return PERCENTAGE*(BatteryValue - BATTERY_ADC_SCALE)/BATTERY_ADC_SCALE;
}

/* Private functions ---------------------------------------------------------*/
