#ifndef SEGMENT_H
#define SEGMENT_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "codeRegulPos.h"
#include "../../API_raspi/debug.h"

#define NOT_INIT 0
#define INIT_POINT 2
#define ERROR_UPDATE_COORDS -12
#define SEUIL_ANGLE 45
#define SEUIL_ERREUR_CONSEQ 4
#define SEUIL_DISTANCE 0.00005 // ptêt que l'unité chie TODO check


#define VOITURE_STOPPED 0
#define VOITURE_FORWARD 1

#define ARRIVEE -12

#define PI 3.14159265


int nbErrors;
double previousAngle;
struct coordonnees{
  double latitude;
  double longitude;
};
struct coordonnees destination;
// Point de destination du segment a atteindre
void goToPoint(double longitude, double latitude);

// Fonction de suivi de trajectoire a appeler des qu'une nouvelle coord est echantillonnee
int update_coords(double long_vago,double lat_vago, double long_vago_before,double lat_vago_before);


#endif
