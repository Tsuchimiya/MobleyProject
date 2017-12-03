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

/*********************** InitMessage **********************
 * Initialisation d'un message à envoyer
 * INPUTS : frame : pointeur vers trame CAN à transmettre
 *          id : id du message à trasmettre
 *          taille : nb octets contenus dans le message
 *********************************************************/
void InitMessage (struct can_frame *frame, int id, int taille);

/*********************** Init ******************************
 * Initialisation globale des communications
 * INPUTS :
************************************************************/
void Init ();

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
