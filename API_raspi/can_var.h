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



char angleVolantMesure_c;
char batterie_c;
char vitesseMesureDroite_c;
char vitesseMesureGauche_c;
char ultrasonMesure_c;



#endif
