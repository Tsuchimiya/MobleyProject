/**
 * @file    us_sensors.h
 * @author  L.Senaneuch
 * @brief   Headers of functions to manage time
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _US_SENSORS_H
#define _US_SENSORS_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include "stm32f10x.h"
 
#define Rising_Edge 0x00 
#define Falling_Edge 0x02

#define IMPAIR 1
#define PAIR 0


#define Circular                  ((uint32_t)0x00000020)		// Circular Mode DMA
#define Calibration               ((uint32_t)0x00000000) // Normal Mode DMA



struct sensor {
	uint16_t RISING_EDGE;
	uint16_t FALLING_EDGE;
	uint16_t COUNTER_DIFF;
};

extern struct sensor sensors[6];

 void US_QuickInit(void);
 void US_StartAcq(void);
 void US_StopAcq(void);
 float US_CalcDistance(uint8_t sensor_position);
 

#endif // _US_SENSORS_H
