#include "codeRegulPos.h"
//Variable de commande.
float Commande_Angle_I[2];
float Ki_I;
float Kp_I;


//Initialisation des valeurs pour la régulation.
void initRegulPos(void)
{
	//Init des coefficients de correction pour réguler l'angle vers la destination.
	Kp_I = 0.44; //45° d'erreur => 40° d'angle roue => Sature à 20° sur la Raspy
	//Ki_I = 0;
	desespoir = 0;
	Commande_Angle_I[1] = 0;
	Commande_Angle_I[0] = 0;
}

//Régulation d'angle.
int RegulationPos(int angleVersPoint_I)
{	
  int angle_I;

  //Erreur Lukko
  angle_I = -angleVersPoint_I;
    
  //Cas3: 180+Seuil<=Abs(Erreur)<360
  //Inversion de l'erreur via le 360-Erreur
  if(abs(angle_I) >= 180+SEUIL_DEMITOUR && abs(angle_I) < 359)
    {
      angle_I = 360 + angle_I;
    }
  //Cas2: 180-Seuil<=Abs(Erreur)<180+Seuil
  //Demi-tour
  else if(desespoir == 0 && abs(angle_I) < 180+SEUIL_DEMITOUR && abs(angle_I) >= 180-SEUIL_DEMITOUR)
    {
      desespoir=1;
      demi_tour();
	  return 1;
    }
    
  //Cas1: 0<=Abs(Erreur)<180-Seuil
  //Tourner droite ou gauche selon l'erreur.
  if(abs(angle_I) >= 0 && abs(angle_I) <= 180 - SEUIL_DEMITOUR)
    {
	Commande_Angle_I[0] = (float)angle_I * Kp_I;
    }

  //MAJ de la valeur ancienne, pour le prochain passage.
  Commande_Angle_I[1] = Commande_Angle_I[0];
  printf("[Regulation] %f\n", Commande_Angle_I[0]);
  //Envoit de la commande d'angle.
  sendAngle((int)Commande_Angle_I[0]);
  return 0;
}
