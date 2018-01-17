#ifndef GPS_COMM_H
#define GPS_COMM_H
#include <gps.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../API_raspi/IHM/ihm_handler.h"
#include "../API_raspi/debug.h"
#include "Trajectoires/segment.h"
#include <pthread.h>

void *listenGPS(void * arg);
void initializeGPS();
#endif
