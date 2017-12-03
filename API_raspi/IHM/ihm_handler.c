#include "ihm_handler.h"
// Lance une fenetre 
void * launchWindow (void * p_data){
  gtk_main();
}

// fonction executee avant la fermeture de la fenetre
static gboolean delete_event( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data )
{

    g_print ("[ihm_handler] delete event occurred \n");

    return FALSE;
}

// fonction detruisant la fenetre
static void destroy( GtkWidget *widget,
                     gpointer   data )
{
    gtk_main_quit ();
}

void initWindow(){


  // widgets de la fenetre 
  GtkWidget *window;
  GtkWidget *button;

  int argc = 0;
  char *argv[]={"main"};

  // initialisation de gtk (ici avec des parametres par defaut vides)
  gtk_init(&argc,&argv);

  // Creation de la fenetre de l'IHM et parametrage
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "GeoCar");
  gtk_container_set_border_width (GTK_CONTAINER (window),200);

  // Definition du comportement a avoir si on quitte la fenetre
  g_signal_connect (window, "delete-event", G_CALLBACK (delete_event), NULL);
  g_signal_connect (window, "destroy", G_CALLBACK (destroy), NULL);

  // Creation du label batterie, parametrage
  batterie = gtk_label_new("-- %");
  gtk_container_add (GTK_CONTAINER (window), batterie);


  
  // affichage de tous les widgets (TODO recursif)
  gtk_widget_show (batterie);
  gtk_widget_show (window);


  if(pthread_create(&IHM,NULL,launchWindow,NULL)<0){
     perror("[ihm_handler] erreur de création du thread de l'ihm");
  }

}


void majBatterie(int value){
  if (DEBUG) {
    printf("[ihm_handler] maj batterie a %d \n", value);
  }
  char valueCasted [24];
  sprintf(valueCasted,"%d",value);

  gtk_label_set_text(GTK_LABEL(batterie), valueCasted);
}
