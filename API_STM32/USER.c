#include "USER.h"

volatile uint32_t msTicks = 0;                        /* counts 1ms timeTicks     */
	
//Flag pour l'envoie sur le CAN
int batterieEnvoye_I = 0;
int angleVolantMesureEnvoye_I = 0;
int vitesseMesureGaucheEnvoye_I = 0;
int vitesseMesureDroiteEnvoye_I = 0;
int ultrasonMesureEnvoye_I = 0;
	

/*----------------------------------------------------------------------------
  SysTick_Handler
	Horloge de notre système qui compte les ms dans la variable globale 
	associées. On peut ainsi ordonnancer notre CAN et les autres periphs.
 *----------------------------------------------------------------------------*/
void SysTick_Handler(void) {
  if(msTicks >= 500)
	{
		msTicks = 0;
	}
	else 
	{
		msTicks++;                        
	}
}

/*----------------------------------------------------------------------------
  delays number of tick Systicks (happens every 1 ms)
	Permets de faire un delais bloquant en comptant simplement la valeur en ms.
 *----------------------------------------------------------------------------*/
void Delay (uint32_t dlyTicks) {
  uint32_t curTicks;

  curTicks = msTicks;
  while ((msTicks - curTicks) < dlyTicks);
}

/*----------------------------------------------------------------------------
  initialize CAN interface
 *----------------------------------------------------------------------------*/
void can_Init (void) {
	int i = 0;
	
  CAN_setup ();                                   /* setup CAN Controller  */
	/* Enable reception of msgs with ids going from 0 to 7*/
	CAN_wrFilter (0, STANDARD_FORMAT);
	CAN_wrFilter (1, STANDARD_FORMAT);
  CAN_wrFilter (2, STANDARD_FORMAT);
	CAN_wrFilter (3, STANDARD_FORMAT);
	CAN_wrFilter (4, STANDARD_FORMAT);
	CAN_wrFilter (5, STANDARD_FORMAT);
	CAN_wrFilter (6, STANDARD_FORMAT);
	CAN_wrFilter (7, STANDARD_FORMAT);
	
	/* ! COMMENT LINE BELOW TO ENABLE DEVICE TO PARTICIPATE IN CAN NETWORK !    */
  //CAN_testmode(CAN_BTR_SILM | CAN_BTR_LBKM);      // Loopback, Silent Mode (self-test)

  CAN_start ();                                   /* start CAN Controller   */

  CAN_waitReady ();                               /* wait til tx mbx is empty */
	
	//CAN_TxMsg.id = 33;                              /* initialize msg to send   */
  for (i = 0; i < 8; i++) CAN_TxMsg.data[i] = 0;
  CAN_TxMsg.len = 1;
  CAN_TxMsg.format = STANDARD_FORMAT;
  CAN_TxMsg.type = DATA_FRAME;

}


/*----------------------------------------------------------------------------
  Transmisson CAN
 *----------------------------------------------------------------------------*/
void Envoie_CAN(uint8_t batterie_I,uint8_t angleVolantMesure_I,uint8_t vitesseMesureGauche_I,
	uint8_t vitesseMesureDroite_I,uint8_t ultrasonMesure_I) 
{
	
	if(msTicks >= 5 && msTicks <= 7) 
		{											/* Gestion envoi de la batterie */
			if (batterieEnvoye_I == 0)
			{
				if (CAN_TxRdy)
				{
					CAN_TxRdy = 0;
					CAN_TxMsg.id = 7;
					CAN_TxMsg.data[0] = batterie_I;
					CAN_wrMsg (&CAN_TxMsg); 
					batterieEnvoye_I = 1;
				}
			}
		} 
		else
		{
			batterieEnvoye_I = 0;
		}
	
		
	/*----------------------------------------------------*/
			
		if(msTicks%50 <= 2)											/* Gestion envoi de l'ultrason */
		{
			if (ultrasonMesureEnvoye_I == 0)
			{
				if (CAN_TxRdy)
				{
					CAN_TxRdy = 0;
					CAN_TxMsg.id = 6;
					CAN_TxMsg.data[0] = ultrasonMesure_I;
					CAN_wrMsg (&CAN_TxMsg); 
					ultrasonMesureEnvoye_I = 1;
				}
			}
		} 
		else 
		{
			ultrasonMesureEnvoye_I = 0;
		}
		
			/*----------------------------------------------------*/
		if(msTicks%50 >= 10 &&msTicks%50 <= 12)											/* Gestion envoi de vitesseMesureDroite*/
		{
			if (vitesseMesureDroiteEnvoye_I == 0)
			{
				if (CAN_TxRdy)
				{
					CAN_TxRdy = 0;
					CAN_TxMsg.id = 0;
					CAN_TxMsg.data[0] = vitesseMesureDroite_I;
					CAN_wrMsg (&CAN_TxMsg); 
					vitesseMesureDroiteEnvoye_I = 1;
				}
			}
		} 
		else 
		{
			vitesseMesureDroiteEnvoye_I = 0;
		}
		
			/*----------------------------------------------------*/
		
				if(msTicks%50 >= 20 &&msTicks%50 <= 22)											/* Gestion envoi de vitesseMesureGauche*/
		{
			if (vitesseMesureGaucheEnvoye_I == 0)
			{
				if (CAN_TxRdy)
				{
					CAN_TxRdy = 0;
					CAN_TxMsg.id = 1;
					CAN_TxMsg.data[0] = vitesseMesureGauche_I;
					CAN_wrMsg (&CAN_TxMsg); 
					vitesseMesureGaucheEnvoye_I = 1;
				}
			}
		} 
		else 
		{
			vitesseMesureGaucheEnvoye_I = 0;
		}
		
		
		/*----------------------------------------------------*/
		
				if(msTicks%100 >= 15 &&msTicks%100 <= 17)											/* Gestion envoi de angleVolantMesure*/
		{
			if (angleVolantMesureEnvoye_I == 0)
			{
				if (CAN_TxRdy)
				{
					CAN_TxRdy = 0;
					CAN_TxMsg.id = 2;
					CAN_TxMsg.data[0] = angleVolantMesure_I;
					CAN_wrMsg (&CAN_TxMsg); 
					angleVolantMesureEnvoye_I = 1;
				}
			}
		} 
		else 
		{
			angleVolantMesureEnvoye_I = 0;
		}
}
	