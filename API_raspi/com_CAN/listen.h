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
