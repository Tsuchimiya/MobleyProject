/***********************************************************
 * Fonctions gérant le traitement des messages reçus sur la
 * Raspberry Pi depuis la STM32
 * Auteur(s) : Team Mobley
 * Date : 11/01/2018
 ********************************************************* */

#ifndef LISTEN_H
#define LISTEN_H

#include <stdio.h>
#include <pthread.h>
#include "../debug.h"
#include "../IHM/ihm_handler.h"
#include "can_var.h"

#define TH_NAME "[Listen]"



/***********************  Listen   **********************
 * Réception/traitement des messages provenant du CAN
 * INPUTS : socketCAN : socket can 
 *********************************************************/
void * listenCAN (void * socketCAN);


#endif
