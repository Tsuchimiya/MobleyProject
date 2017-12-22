#include "segment.h"
int init= NOT_INIT;
int stateVoiture=VOITURE_STOPPED;

// calcule l'angle par rapport au nord des coordonnees
int computeCourseCoords(double long_before,double lat_before,double longitude, double latitude)
{
  double toDeg = 180.0/PI;
  int course;
  double x2=longitude;
  double x1=long_before;
  double y2=latitude;
  double y1=lat_before;
  double dx=x2-x1;
  double dy=y2-y1;

  if (dx==0 && dy==0) {
    course=0;
  } else if(dx==0 && dy>0) {
    course=0;
  } else if(dx>0 && dy!=0) {
    course=atan2(dx,dy)*toDeg;
  } else if(dx>0 && dy==0) { //atan2(dx,0) returns error
    course=90.0;
  } else if(dx==0 && dy<0) {
    course=180.0;
  } else if(dx<0 && dy!=0) {
    course=360.0+atan2(dx,dy)*toDeg;
  } else if(dx<0 && dy==0) {
    course=270.0;
  } else {
    printf("[GPS] course out of range\n");
  }

  return course;
}

struct angles{
  int angleVago;
  int angleToGo;
};

// On calcule l'angle vers lequel aller
struct angles computeAngleToGo ( double long_vago, double lat_vago, double long_vago_before, double lat_vago_before){
  struct angles A;
  int angleNordCoords = computeCourseCoords(long_vago,lat_vago, destination.longitude, destination.latitude);
  int angleVago = computeCourseCoords(long_vago_before,lat_vago_before, long_vago,lat_vago);
  ;
  printf("Angle nord coords = %d",angleNordCoords);
  printf("  Angle vago = %d \n",angleVago);
  A.angleToGo = angleNordCoords-angleVago;
  A.angleVago = angleVago;
  return A;

}

//initialisation du point vers lequel aller
void goToPoint(double longitude, double latitude){
  destination.longitude = longitude;
  destination.latitude = latitude;
  init = INIT_POINT;
  nbErrors = 0;
  previousAngle = 0;
  initRegulPos();
  sendAngle(0);
  
  
}

double distanceFromPoint (double long_vago, double lat_vago){
  if (init == INIT_POINT)
    return sqrt(pow((long_vago-destination.longitude),2) + pow((lat_vago-destination.latitude),2));
  else
    return -1;
}

struct coordonnees nextPoint(){
  struct coordonnees resu;
  resu.latitude = ARRIVEE;
  resu.longitude = ARRIVEE;
  return resu;
}

int update_coords(double long_vago,double lat_vago, double long_vago_before,double lat_vago_before){
  int angleToGo;
  struct angles A;
  switch (init){
    
  case NOT_INIT:
    printf("Erreur Initialiser le point de destination... \n");
    return ERROR_UPDATE_COORDS;
    break;
    
  case INIT_POINT:

    // si on est arrive au point, on va au point suivant s'il existe
    if (distanceFromPoint(long_vago,lat_vago) <= SEUIL_DISTANCE){
      destination = nextPoint();
    }

    // si on est arrive au point final, on arrete la voiture 
    if (destination.latitude == ARRIVEE && destination.longitude == ARRIVEE){
      if(DEBUG){
	printf("[Trajectoire] Arrivee a destination\n");
      }
      sendVitesse(0);
      stateVoiture = VOITURE_STOPPED;
    }
    else {
      // calcul de l'angle vers lequel aller
      A = computeAngleToGo (long_vago,lat_vago,long_vago_before,lat_vago_before);
      angleToGo = A.angleToGo;
   
      printf("[Trajectoire] Angle to GO = %d \n",angleToGo);
      // si l'angle parait correct on regule
      if (abs(A.angleVago - previousAngle) < SEUIL_ANGLE){
	printf("[Trajectoire] REGULATION SENT \n");
	if(RegulationPos(angleToGo))
	{
		A.angleVago = A.angleVago - 180;
		stateVoiture = VOITURE_STOPPED;
	}
	

	// on fait avancer la voiture si elle n'avancait pas deja
	if (stateVoiture == VOITURE_STOPPED){
	  sendVitesse(50);
	}
	previousAngle = A.angleVago;
      }
      

      // si l'angle est incorrect on ne fait rien , au bout d'un nombre d'erreur consecutives, STOP de la voiture car on est perdus
      else{
	sendAngle(0);
	if(nbErrors < SEUIL_ERREUR_CONSEQ){
	  nbErrors ++;
	  return 0;
	}else {
	  printf("[Trajectoires] ERREUR \n");
	  sendVitesse(0);
	  return ERROR_UPDATE_COORDS;
	}
      }
      
    }
    return 0;
    break;

  }
}
