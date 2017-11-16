/*----------------------------------------------------------------------------
 * Name:    CanDemo.c
 * Purpose: CAN example for MCBSTM32
 * Note(s): possible defines set in "options for target - C/C++ - Define"
 *            __USE_LCD   - enable Output on LCD
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2009-2013 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include "USER.h"


char text[17];

/*----------------------------------------------------------------------------
	System variables 
	----------------------------------------------------------------------------*/
	//Signal de commande
	uint8_t vitesseCommandeGauche_I = 0;
	uint8_t vitesseCommandeDroite_I = 0;	
	uint8_t angleVolantCommande_I = 0;
	
	//Signal d'information
	uint8_t batterie_I = 100;	
	uint8_t angleVolantMesure_I = 0;	
	uint8_t vitesseMesureGauche_I = 0;	
	uint8_t vitesseMesureDroite_I = 0;	
	uint8_t ultrasonMesure_I = 0;	
	
	//Lecture
	uint8_t val_Rx;

/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void)  {

  SysTick_Config(SystemCoreClock / 1000);         /* SysTick 1 msec IRQ       */


  can_Init ();                                    /* initialize CAN interface */

	//Test
	batterie_I = 255;	
	angleVolantMesure_I = 0;	
	vitesseMesureGauche_I = 150;	
	vitesseMesureDroite_I = 100;	
	ultrasonMesure_I = 50;	
	
	
	
  while (1) {
		
		//Ordonnancement des messages CAN    
		
		
			/*----------------------------------------------------*/
//		if (CAN_TxRdy) {                              /* tx msg on CAN Ctrl       */
//      CAN_TxRdy = 0;
//      CAN_TxMsg.data[0] = val_Tx;                 /* data[0] = ADC value      */
//      CAN_wrMsg (&CAN_TxMsg);                     /* transmit message         */
//    }

		Envoie_CAN(batterie_I,angleVolantMesure_I,vitesseMesureGauche_I,vitesseMesureDroite_I,ultrasonMesure_I);
		
    if (CAN_RxRdy) {                              /* rx msg on CAN Ctrl       */
      CAN_RxRdy = 0;
																									/* checking msg id and attributing value to corresponding variable */
			switch (CAN_RxMsg.id)
				{
				case 3 :
					vitesseCommandeDroite_I = CAN_RxMsg.data[0];
					break;
				case 4 :
					vitesseCommandeGauche_I = CAN_RxMsg.data[0];
					break;
				case 5 : 
					angleVolantCommande_I = CAN_RxMsg.data[0];
					break;
				default : 
					break;
				}
      val_Rx = CAN_RxMsg.data[0];
    }
		//Fin de l'ordonnancement du CAN

  }
}
