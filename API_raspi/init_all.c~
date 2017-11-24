#include "init_all.h"

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


int
main(void)
{
  pthread_t test;


  int s;
  init_socket(&s);
  printf("[Init_all] starting listenCAN\n");

  if(pthread_create(&test,NULL,listenCAN,&s) <0 ){
    perror("[Init_all] pthread failure with listen");
  }
 printf("[Init_all] starting test\n");
 sleep(5);
 Tests(&s);

  pthread_join(test,NULL);
  return 0;
}
