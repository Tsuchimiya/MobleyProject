#include "init_all.h"
pthread_t gps;



int init_filter(int *sock){
  idTab[0]=ANGLEVOLANTMESURE;
  idTab[1]=VITESSEMESUREGAUCHE;
  idTab[2]=VITESSEMESUREDROITE;
  idTab[3]=ULTRASONMESURE;
  idTab[4]=BATTERIE;
  idTab[5]=VITESSECMDDROITE;
  //idTab[6]=VITESSECMDGAUCHE;
  //idTab[7]= ANGLEVOLANTCMD;
  int i = 0;
  // defining filters for CAN :
  struct can_filter rfilter[NBVARFILTER];

  for (i=0;i<NBVARFILTER;i++){
    rfilter[i].can_mask=CAN_SFF_MASK;
    rfilter[i].can_id=idTab[i];
  }

   return setsockopt(*sock, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));

}



void test_maj(){
  double lt = 2.0;
  double lg  = 50.0;
  while(1){
    majCoords(lt,lg);
    lt=lt + 0.00000001;
    lg++;
    usleep(250000);
  }

}

void init_socket(int *s){
  	
	int nbytes;
	struct sockaddr_can addr;
	struct can_frame frame;
	struct ifreq ifr;

	const char *ifname = "can0";
	// opening socket CAN_RAW//SOCK_RAW or CAN_BCM // SOCK_DGRAM BCM = cyclique
	printf("[init_all] starting socket\n");
	if((*s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
		perror("Error while opening socket");
		//	return -1;
	}

	//finding dynamically the can0 interface (to bind to all can interface put 0 into the index)
	strcpy(ifr.ifr_name, ifname);
	ioctl(*s, SIOCGIFINDEX, &ifr);
	
	addr.can_family  = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	printf("%s at index %d\n", ifname, ifr.ifr_ifindex);

	// bind the socket to a can interface
	if(bind(*s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("Error in socket bind");
		//return -2;
	}

	init_filter(s);

	//setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));
}


void initVoiture(){
  continueSending();
  initializeGPS();
}

void stopVoiture(){
  int old;
  sendVitesse(0);
  sendAngle(0);
  stopSending();
  //pthread_setcancelstate( PTHREAD_CANCEL_ASYNCHRONOUS, &old);
  pthread_cancel(gps);
  pthread_join(gps,NULL);

  
  if(pthread_create(&gps,NULL,listenGPS,NULL) <0 ){
    perror("[Init_all] pthread failure with listen GPS ");
    }
  

}

int
main(void)
{
  pthread_t test;
  FILE *fpts;
  FILE *fsteps;


  // initialisation des variables de com can (A FAIRE AVANT LES THREADS)
  int sockSend;
  init_socket(&sockSend);
  Init();
  setSockSend(sockSend);


  // Init du parser ( A FAIRE AVANT LES THREADS ) 
  fpts=fopen("../parser/points.map", "r");
  printf("[Init_all] Parse : points file opened.\n");
  fsteps=fopen("../parser/steps.map","r");
  printf("[Init_all] Parse : steps file opened.\n");

  if (fpts==NULL || fsteps==NULL) {
    printf("[Init_all] Parse: Error: a map file can't be read.\n");
  } else {
    parsePoints(fpts, &world);
    printf("[Init_all] points file parsed.\n");
    parseSteps(fsteps, &world);
    printf("[Init_all] steps file parsed.\n");


//// TEST DECLOSEST POINT a effacer
   // closestPoint(1.4674500,43.5704470);


//    fclose(fpts);
  //  fclose(fsteps);
   
    // printSteps(world);
  }

  //  goToPoint(1.4668290317058563,43.571076884255085);
  
  int s;
  init_socket(&s);
  printf("[Init_all] starting listenCAN\n");

  // demarage thread de reception des msg can
  if(pthread_create(&test,NULL,listenCAN,&s) <0 ){
    perror("[Init_all] pthread failure with listen CAN");
  }

  printf("[Init_all] opening window\n");
  initWindow();


  
  // demarage thread gps

   if(pthread_create(&gps,NULL,listenGPS,NULL) <0 ){
    perror("[Init_all] pthread failure with listen GPS ");
    }
  //test_maj();

  
 printf("[Init_all] starting test\n");
 sleep(3);
 //Tests(&s);

  pthread_join(test,NULL);
  pthread_join(gps,NULL);

  return 0;
}
