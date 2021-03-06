#ifndef IHM_HANDLER_H
#define IHM_HANDLER_H

#include <stdio.h>
#include "../debug.h"
#include <stdlib.h>
#include <gtk/gtk.h>
#include "../../GPS/Trajectoires/segment.h"
#include "../init_all.h"


#define MAX_BUFFER 50

// Definition de la status bar (ultrason / batterie ...) 
#define BATTERIE_FAIBLE 0
#define MSG_BAT_FAIBLE "Batterie faible: la voiture va bientot s'arreter\n"
#define BATTERIE_CRITIC 1
#define MSG_BAT_CRITIC "Plus de batterie: arret automatique de la voiture\n"




// thread de l'ihm
pthread_t IHM;

// widgets avec lesquels on va interragir NE PAS LES MODIFIER 
GtkWidget *batterie;
GtkWidget *longitude;
GtkWidget *lattitude;
GtkWidget *window;
GtkWidget *error;
GtkWidget *controlButton;

/*********************** initWindow **********************
Initialise et affiche une fenetre utilisateur
 *********************************************************/
void initWindow();

/*********************** majBatterie **********************
Mets à jour la valeur de la batterie affichée
            INPUTS : value = valeur de la batterie à afficher
 *********************************************************/
void majBatterie(int value);

void majCoords(double lat, double lon);

void alert(int type_error);


/*********************** Choix de la destination **********************
Gestion de la liste contenant les destinations
***********************************************************************/
enum {
  DESTINATIONS
};

// Fonction creant la liste de destinations
void CreerListe (GtkTreeStore *destinations, GtkWidget *liste_dest);

// Fonction de selection destination
void ChoixDestination (GtkTreeSelection *choix, gpointer donnee);

// Fonction de remplissage de la liste
void RemplirListe(GtkTreeStore *destinations);

#endif
