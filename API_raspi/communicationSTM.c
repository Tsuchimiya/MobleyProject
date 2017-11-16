#include "communicationSTM.h"

// to set a virtual socket on your pc : modprobe vcan, flexcan, mcp251x, can-raw, can-dev, can
// ip link set vcan0 up type vcan
// cansend vcan0 7DF#0201050000000000, 7df: id variable, le reste = valeur

// http://copperhilltech.com/what-is-socketcan/

/*********************** InitMessage **********************
 * Initialisation d'un message à envoyer
 * INPUTS : frame : pointeur vers trame CAN à transmettre
 *          id : id du message à trasmettre
 *          taille : nb octets contenus dans le message
 *********************************************************/

void InitMessage (struct can_frame *frame, int id, int taille)
{
  *frame.can_id  = id;
  *frame.can_dlc = taille;
}

/*********************** Init ******************************
 * Initialisation globale des communications
 * INPUTS :
************************************************************/
void Init ()
{
  // Création message AngleVolantCommande
  InitMessage (&AngleVolantCommande, 5, 1);

  // Création message VitesseCommandeGauche
  InitMessage (VitesseCommandeGauche&, 4, 1);

  // Création message VitesseCommandeDroite
  InitMessage (&VitesseCommandeDroite, 3, 1);
  
}

/********************** SendMessage ************************
 * Envoi d'un message
 * INPUTS : frame : pointeur vers trame CAN à transmettre
 *          data : donnée à transmettre
 *          socket : id socket 
 * OUTPUT : nbytes : retour de la fonction write
 *********************************************************/

int SendMessage (struct can_frame *frame, char data, int socket)
{
  *frame.data[0]=data;
  nbytes = write(socket, frame, sizeof(struct can_frame));
  return nbytes;
}

// Messages à envoyer
struct can_frame AngleVolantCommande, VitesseCommandeGauche, VitesseCommandeDroite;

int main(void)
{
	int s;
	int nbytes;
	struct sockaddr_can addr;

	struct ifreq ifr;

	const char *ifname = "can0";
	
	// opening socket CAN_RAW//SOCK_RAW or CAN_BCM // SOCK_DGRAM BCM = cyclique
	if((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
		perror("Error while opening socket");
		return -1;
	}

	//finding dynamically the can0 interface (to bind to all can interface put 0 into the index)
	strcpy(ifr.ifr_name, ifname);
	ioctl(s, SIOCGIFINDEX, &ifr);
	
	addr.can_family  = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	printf("%s at index %d\n", ifname, ifr.ifr_ifindex);

	// bind the socket to a can interface
	if(bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("Error in socket bind");
		return -2;
	}

	// ************** filtres réception ****************************
	// 5 messages en réception = 5 filtres dans rfilter
	struct can_filter rfilter[5];

	// Batterie
	rfilter[0].can_id   = 7;
	rfilter[0].can_mask = CAN_SFF_MASK;

	// Anglevolantmesure
	rfilter[1].can_id   = 2;
	rfilter[1].can_mask = CAN_SFF_MASK;

	// VitesseMesureDroite
	rfilter[2].can_id   = 0;
	rfilter[2].can_mask = CAN_SFF_MASK;

	// VitesseMesureGauche
	rfilter[3].can_id   = 1;
	rfilter[3].can_mask = CAN_SFF_MASK;

	// UltrasonMesure
	rfilter[4].can_id   = 6;
	rfilter[4].can_mask = CAN_SFF_MASK;

	/*
	 // pour recevoir les erreurs du bus can 
	  can_err_mask_t err_mask = ( CAN_ERR_TX_TIMEOUT | CAN_ERR_BUSOFF );
	  setsockopt(s, SOL_CAN_RAW, CAN_RAW_ERR_FILTER,
	  	  &err_mask, sizeof(err_mask));
	*/

	setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));


	// Creation des messages avec taille et id
	Init;

       	// ******************* Envoi des messages *********************************
	nbytes=SendMessage ( &AngleVolantCommande, 0x11, s);
	nbytes=SendMessage ( &VitesseCommandeGauche, 0x11, s);
	nbytes=SendMessage ( &VitesseCommandeDroite, 0x11, s);
		
	printf("Wrote %d bytes\n", nbytes);
	
	return 0;
}
