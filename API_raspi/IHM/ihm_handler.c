#include "ihm_handler.h"
// Lance une fenetre

void majBatterie(int value){
  if (DEBUG) {
    printf("[ihm_handler] maj batterie a %d %%\n", value);
  }
  char valueCasted [24];
  sprintf(valueCasted,"%d %%",value);

  gtk_progress_bar_set_text (GTK_PROGRESS(batterie), valueCasted);
  gtk_progress_bar_set_fraction(GTK_PROGRESS(batterie),(gdouble)(value/100.0));
  
}


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
  GtkWidget *table;
  GtkWidget *logo;

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

  // Creation de la table allant contenir tous les widgets
  table = gtk_table_new (2, 3, TRUE);
  gtk_container_add (GTK_CONTAINER (window), table);

  // Creation du label batterie, parametrage
  batterie = gtk_progress_bar_new();
  GdkColor col;
  majBatterie(100);
  gtk_table_attach_defaults (GTK_TABLE (table), batterie,2,3,0,1);


  
  // affichage de tous les widgets (TODO recursif)
  gtk_widget_show (batterie);
  gtk_widget_show(table);
  gtk_widget_show (window);


  if(pthread_create(&IHM,NULL,launchWindow,NULL)<0){
     perror("[ihm_handler] erreur de création du thread de l'ihm");
  }

}


