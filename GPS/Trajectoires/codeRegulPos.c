#include "codeRegulPos.h"
//Variable de commande.
float Commande_Angle_I[2];
float Ki_I;
float Kp_I;

//Initialisation des valeurs pour la régulation.
void initRegulPos(void)
{
	//Init des coefficients de correction pour réguler l'angle vers la destination.
	Kp_I = 0.22; //90° d'erreur => 20° d'angle roue
	//Ki_I = 0;
}

//Régulation d'angle.
void RegulationPos(int angleVersPoint_I)
{	
	//Choix d'une régulation selon l'orientation de la voiture.
	//Droite donc tourne à gauche.
	if(angleVersPoint_I >= 0 && angleVersPoint_I <= 90)
	{
		Commande_Angle[0] = -angleVersPoint_I * Kp_I;
	}
	else if(angleVersPoint_I > 90 && angleVersPoint_I <= 180)
	{
		//Dans le cas d'une erreur trop grande, on sature.
		Commande_Angle_I[0] = -20;
	}
	//Gauche donc tourne à droite.
	else if(angleVersPoint_I > 180 && angleVersPoint_I <= 270)
	{
		Commande_Angle_I[0] = (angleVersPoint_I-180) * Kp_I;
	}
	else if(angleVersPoint_I > 270)
	{
		//Dans le cas d'une erreur trop grande, on sature.
		Commande_Angle_I[0] = 20;
	}
	else
	{
		Commande_Angle_I[0] = 0;
	}
	
	//MAJ de la valeur ancienne, pour le prochain passage.
	Commande_Angle_I[1] = Commande_Angle_I[0];
	//Envoit de la commande d'angle.
	
}