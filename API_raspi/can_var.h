#ifndef CAN_VAR
#define CAN_VAR

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
#include <pthread.h>

#define NBVARFILTER 6
#define ANGLEVOLANTMESURE 5
#define ANGLEVOLANTCMD 1
#define VITESSECMDGAUCHE 3
#define VITESSECMDDROITE 12
#define VITESSEMESUREGAUCHE 10
#define VITESSEMESUREDROITE 4
#define ULTRASONMESURE 6
#define BATTERIE 7



char angleVolantMesure_c;
char batterie_c;
char vitesseMesureDroite_c;
char vitesseMesureGauche_c;
char ultrasonMesure_c;


pthread_mutex_t batterie_mutex;
pthread_mutex_t vitesseMesureDroite_mutex;
pthread_mutex_t vitesseMesureGauche_mutex;
pthread_mutex_t ultrasonMesure_mutex;
pthread_mutex_t angleVolantMesure_mutex;

int idTab[NBVARFILTER];

#endif
