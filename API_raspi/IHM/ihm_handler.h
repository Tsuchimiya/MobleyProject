#ifndef IHM_HANDLER_H
#define IHM_HANDLER_H

#include <stdio.h>
#include "../debug.h"
#include <stdlib.h>
#include <gtk/gtk.h>

// thread de l'ihm
pthread_t IHM;

// widgets avec lesquels on va interragir NE PAS LES MODIFIER 
GtkWidget *batterie;


/*********************** initWindow **********************
Initialise et affiche une fenetre utilisateur
 *********************************************************/
void initWindow();

/*********************** majBatterie **********************
Mets à jour la valeur de la batterie affichée
            INPUTS : value = valeur de la batterie à afficher
 *********************************************************/
void majBatterie(int value);


#endif
