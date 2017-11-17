#include <stdio.h>
#include <pthread.h>

#define TH_NAME "[Listen]"
#define DEBUG 1

/***********************  Listen   **********************
 * Réception/traitement des messages provenant du CAN
 * INPUTS : socketCAN : socket can 
 *********************************************************/
void * listenCAN (void * socketCAN);
