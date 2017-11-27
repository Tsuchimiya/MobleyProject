#include "init_all.h"
#include "communicationSTM.h"

// Messages à envoyer
struct can_frame AngleVolantCommande, VitesseCommandeGauche, VitesseCommandeDroite;
// Filtre de réception
struct can_filter rfilter[NBVARFILTER];
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
  (*frame).can_id  = id;
  (*frame).can_dlc = taille;
}

/*********************** CreerFiltre **********************
Crée un filtre pour autoriser un message en réception
INPUTS : id : id du message
         indice : emplacement dans le tableau des filtres
         tabFiltre : tableau contenant les filtres
 *********************************************************/
void CreerFiltre (int id, int indice, struct can_filter *tabFiltre)
{
  tabFiltre[indice].can_id   = id;
  tabFiltre[indice].can_mask = CAN_SFF_MASK;
}

/*********************** Init ******************************
 * Initialisation globale des communications
 * INPUTS :
************************************************************/
void Init ()
{
  // ********************* Creer messages **************************
  
  // Création message AngleVolantCommande
  InitMessage (&AngleVolantCommande, ANGLEVOLANTCMD, 1);

  // Création message VitesseCommandeGauche
  InitMessage (&VitesseCommandeGauche, VITESSECMDGAUCHE, 1);

  // Création message VitesseCommandeDroite
  InitMessage (&VitesseCommandeDroite, VITESSECMDDROITE, 1);



}

/********************** EnvoiMessage ************************
 * Envoi d'un message
 * INPUTS : frame : pointeur vers trame CAN à transmettre
 *          data : donnée à transmettre
 *          socket : id socket 
 * OUTPUT : nbytes : retour de la fonction write
 *********************************************************/

int EnvoiMessage (struct can_frame *frame, char data, int socket)
{
  (*frame).data[0]=data;
  int nbytes;
  nbytes = write(socket, frame, sizeof(struct can_frame));
  return nbytes;
}



/**************************** Tests *****************************
Teste les envois de messages
INPUTS : socket : 
 ****************************************************************/

void Tests (int *s)
{
  int nbytes;
  int sock;
  init_socket(&sock);
  Init();
  

  nbytes=EnvoiMessage ( &VitesseCommandeGauche, (char)25, sock);
  printf("[Test] envoi cmd vitesse : avancer  %d\n",nbytes);
  sleep(3);

  nbytes=EnvoiMessage ( &VitesseCommandeGauche, (char)0, sock);
  printf("[Test] envoi cmd vitesse : arrêt %d\n",nbytes);
  sleep(1);

  nbytes=EnvoiMessage ( &VitesseCommandeGauche, (char)-25, sock);
  printf("[Test] envoi cmd vitesse : reculer %d\n",nbytes);
  sleep(3);

  nbytes=EnvoiMessage ( &VitesseCommandeGauche, (char)0, sock);
  printf("[Test] envoi cmd vitesse : arrêt %d\n",nbytes);
  sleep(1);

  nbytes=EnvoiMessage ( &AngleVolantCommande, (char)-20, sock);
  printf("[Test] envoi angle volant: tourner droite %d\n",nbytes);
  sleep(1);

  nbytes=EnvoiMessage ( &VitesseCommandeGauche, (char)25, sock);
  printf("[Test] envoi cmd vitesse: avancer %d\n",nbytes);
  sleep(2);

  nbytes=EnvoiMessage ( &AngleVolantCommande, (char)0, sock);
  printf("[Test] envoi angle volant: redresser %d\n",nbytes);
  sleep(1);

  nbytes=EnvoiMessage ( &AngleVolantCommande, (char)20, sock);
  printf("[Test] envoi angle volant: tourner gauche %d\n",nbytes);
  sleep(2);

  nbytes=EnvoiMessage ( &AngleVolantCommande, (char)0, sock);
  printf("[Test] envoi angle volant: redresser %d\n",nbytes);
  sleep(2);

  nbytes=EnvoiMessage ( &VitesseCommandeGauche, (char)0, sock);
  printf("[Test] envoi cmd vitesse: arrêter %d\n",nbytes);

}
