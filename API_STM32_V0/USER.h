#include <stdio.h>
#include "stm32f10x.h"                            /* STM32F10x Definitions    */
#include "LCD.h"                                  /* LCD function prototypes  */
#include "ADC.h"                                  /* LCD function prototypes  */
#include "CAN.h"                                  /* STM32 CAN adaption layer */

//Variables

//Fonctions

void SysTick_Handler(void);
void Delay (uint32_t dlyTicks);
void can_Init (void);
void Envoie_CAN(uint8_t batterie_I,uint8_t angleVolantMesure_I,uint8_t vitesseMesureGauche_I,
	uint8_t vitesseMesureDroite_I,uint8_t ultrasonMesure_I);
