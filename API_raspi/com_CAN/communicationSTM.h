/***************************************************
* Une Description brève mais claire de la fonction *
* Une Description brève mais claire de la fonction *
* Une Description brève mais claire de la fonction *
****************************************************/

#ifndef COMMUNICATIONSTM
#define COMMUNICATIONSTM

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>

//#include <wiringPi.h>

#include "can_var.h"


#define INITIALIZED_VAR 1

/*********************** Init ******************************
 * Initialisation globale des communications
 * INPUTS :
************************************************************/
void Init ();

/*********************** setSockSend ******************************
 * Initialisation du socket de communication
 * INPUTS : socket: valeur du socket CAN à set
 ***************************************************************/
void setSockSend(int socket);

/*********************** sendAngle******************************
 * Envoi d'un ordre d'angle au STM 
 * INPUTS : angle: valeur de l'angle a envoyer
 ***************************************************************/
void sendAngle(int angle);

/*********************** sendVitesse ******************************
 * Envoi d'un ordre de vitesse à la voiture
 * INPUTS : vitesse: valeur de la vitesse a envoyer
 ***************************************************************/
void sendVitesse(int vitesse);

/********************** EnvoiMessage ************************
 * Envoi d'un message
 * INPUTS : frame : pointeur vers trame CAN à transmettre
 *          data : donnée à transmettre
 *          socket : id socket 
 * OUTPUT : nbytes : retour de la fonction write
 *********************************************************/

int EnvoiMessage (struct can_frame *frame, char data, int socket);

/*********************** CreerFiltre **********************
Crée un filtre pour autoriser un message en réception
INPUTS : id : id du message
         indice : emplacement dans le tableau des filtres
         tabFiltre : tableau contenant les filtres
 *********************************************************/
void CreerFiltre (int id, int indice, struct can_filter *tabFiltre);

/**************************** Tests *****************************
Teste les envois de messages
INPUTS : socket : 
 ****************************************************************/
void Tests (int *s);
  
#endif
