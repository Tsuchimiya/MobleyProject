
#include "listen.h"

// to set a virtual socket on your pc : modprobe vcan, flexcan, mcp251x, can-raw, can-dev, can
// ip link set vcan0 up type vcan
// cansend vcan0 7DF#0201050000000000, 7df: id variable, le reste = valeur


// http://copperhilltech.com/what-is-socketcan/

/*********************  treatMsg   **********************
 * traitement des messages reçus: 
 * mise à jour des variables globale selon le type de trame reçu
 * INPUTS : canFrame : trame CAN à traiter 
 *********************************************************/
void * treatMsg(struct can_frame canFrame){

  switch (canFrame.can_id){

    // Mise à jour de la variable globale correspondant à l'id reçu
  case ANGLEVOLANTMESURE: 
    if (DEBUG){
      printf("%s angle volant mesure= %d\n",TH_NAME,canFrame.data[0]);
    }
    
    // mise à jour de la variable angle volant mesuré
    pthread_mutex_lock(&angleVolantMesure_mutex);
    angleVolantMesure_c = (unsigned char)canFrame.data[0];
    pthread_mutex_unlock(&angleVolantMesure_mutex);
    break;

  case BATTERIE:
    if(DEBUG){
      printf("%s batterie= %d\n",TH_NAME,canFrame.data[0]);
    }
     // mise à jour de la variable batterie
    pthread_mutex_lock(&batterie_mutex);
    batterie_c = (unsigned char)canFrame.data[0];
    pthread_mutex_unlock(&batterie_mutex);

    // affichage sur l'ihm
    int value = (int)canFrame.data[0];
    if(value >=0 && value < 100){

      if (value <= 54){
	if (value <= 51){

	  if (DEBUG)
	    
	    printf("%s PLUS DE BATTERIE \n",TH_NAME);
	}else{
	  if (DEBUG)
	    printf("%s BATTERIE FAIBLE \n",TH_NAME);
	  
	}
      }
      value = (value - 50) *2;
      majBatterie(value);
    }
    else{
      printf ("%s erreur data batterie > 100 ou < 0 %d \n",TH_NAME ,value);
    }
    break;

  case VITESSEMESUREDROITE:
    if(DEBUG){
      printf("%s vitesse mesure droite= %d\n",TH_NAME,canFrame.data[0]);
    }
     // mise à jour de la variable vitesse mesure gauche
    pthread_mutex_lock(&vitesseMesureDroite_mutex);
    vitesseMesureDroite_c = (unsigned char)canFrame.data[0];
    pthread_mutex_unlock(&vitesseMesureDroite_mutex);
    break;
    
  case VITESSEMESUREGAUCHE:
    if(DEBUG){
      printf("%s vitesse mesure gauche= %d\n",TH_NAME,canFrame.data[0]);
    }
     // mise à jour de la variable vitesse mesure gauche
    pthread_mutex_lock(&vitesseMesureGauche_mutex);
    vitesseMesureGauche_c = (unsigned char)canFrame.data[0];
    pthread_mutex_unlock(&vitesseMesureGauche_mutex);
    break;

  case ULTRASONMESURE:
    if(DEBUG){
      printf("%s mesure ultrason= %d\n",TH_NAME,canFrame.data[0]);
    }
     // mise à jour de la variable mesure ultrason
    pthread_mutex_lock(&ultrasonMesure_mutex);
    ultrasonMesure_c = (unsigned char)canFrame.data[0];
    pthread_mutex_unlock(&ultrasonMesure_mutex);
    break;
  default:
    printf("%s Erreur variable reçue inconnue numéro = %d\n",TH_NAME,canFrame.can_id);



  }

}

/*********************  ListenCAN   **********************
 * Réception/traitement des messages provenant du CAN
 * INPUTS : socketCAN : socket can 
 *********************************************************/
void * listenCAN (void * socketCAN){
  printf("%s Starting thread\n",TH_NAME);
  int *s = (int*) socketCAN;
  struct can_frame canFrame;
  printf("%s Socket number : %d\n",TH_NAME,(*s));
  int nbytes;
  

  while (1){
   
    nbytes = read(*s,&canFrame,sizeof(struct can_frame));

    // Checking that there are no errors raised by read
    if (nbytes < 0){
      perror ("[Listen] can raw socket read \n");
    }

    // Checking that the frame received is complete 
    if (nbytes < sizeof(struct can_frame)){
      perror("[Listen] read: incomplete CAN frame");
    }

    // affichage du paquet reçu
    if(DEBUG){
      printf("%s Received var number %d = %d \n",TH_NAME,canFrame.can_id,canFrame.data[0]);
    }
    // TODO rajouter une sécurité sur la data
    if (sizeof(canFrame.data[0])>0){
      treatMsg(canFrame);
    }

  }
  
}
