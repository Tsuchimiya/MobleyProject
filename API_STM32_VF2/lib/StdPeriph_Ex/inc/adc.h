/**
 * @file    adc.h
 * @author  Curtis Team
 * @brief   Headers of functions to handle ADCs  
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _ADC_H
#define _ADC_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stm32f10x.h>

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/**
 * @brief Given pin was succesfully initialized as analogic input
*/
#define ADC_NO_ERROR    0

/**
* @brief Given pin couldn't be initialized: port is unreachable
*/ 
#define ADC_ERROR_PORT  (-1)

/**
 * @brief Given pin couldn't be initialized: pin is unreachable
*/ 
#define ADC_ERROR_PIN   (-2)

/**
 * @brief Given rank couldn't be initialized: rank is out of range
*/ 
#define ADC_ERROR_RANK  (-3)

/**
 * @brief Maximum number of channels for one ADC
*/ 
#define ADC_NB_CHANNELS_MAX  5

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
int ADC_QuickInit(ADC_TypeDef* ADCx, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin_x, uint8_t Rank, uint8_t SampleTime);
uint16_t ADC_QuickGet(ADC_TypeDef* ADCx, uint8_t Rank);
void ADC_Callback(void);

#endif // _ADC_H
