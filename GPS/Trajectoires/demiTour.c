#include "demiTour.h"


void demi_tour()
{
	printf("[demi_tour]debut demitour\n");
	sendAngle(20);
	printf("[demi_tour]go left\n");
	sleep(1);
	sendVitesse(60);
	usleep(3500000);
	sendVitesse(0);
	sendAngle(-20);
	sleep(1);
	sendVitesse(-60);
	usleep(4500000);
	sendVitesse(0);
	sendAngle(20);
	sleep(1);
	sendVitesse(60);
	sleep(3);
	printf("[demi_tour]presque findemitour tmtc jupp bbq\n");
	sendVitesse(0);
}
