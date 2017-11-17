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

#define NBVARFILTER 5
#define ANGLEVOLANTMESURE 2
#define ANGLEVOLANTCMD 5
#define VITESSECMDGAUCHE 4
#define VITESSECMDDROITE 3
#define VITESSEMESUREGAUCHE 1
#define VITESSEMESUREDROITE 0
#define ULTRASONMESURE 6
#define BATTERIE 7



unsigned char angleVolantMesure_c;
unsigned char batterie_c;
unsigned char vitesseMesureDroite_c;
unsigned char vitesseMesureGauche_c;
unsigned char ultrasonMesure_c;


pthread_mutex_t batterie_mutex;
pthread_mutex_t vitesseMesureDroite_mutex;
pthread_mutex_t vitesseMesureGauche_mutex;
pthread_mutex_t ultrasonMesure_mutex;
pthread_mutex_t angleVolantMesure_mutex;


#endif
