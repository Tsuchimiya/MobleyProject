#include "ihm_handler.h"


void alert(int type_error){
  if (DEBUG)
    printf("ALERT \n");
  switch (type_error){
    
  case BATTERIE_CRITIC:
    gtk_statusbar_push(GTK_STATUSBAR(error),BATTERIE_CRITIC,MSG_BAT_CRITIC);
    break;
  case BATTERIE_FAIBLE:
    gtk_statusbar_push(GTK_STATUSBAR(error),BATTERIE_FAIBLE,MSG_BAT_FAIBLE);
    break;
  default:
    printf("Erreur alerte de type inconnue\n");
    break;

  }

}

// Lance une fenetre

void majBatterie(int value){
  if (DEBUG) {
    printf("[ihm_handler] maj batterie a %d %%\n", value);
  }
  char valueCasted [7];
  sprintf(valueCasted,"%d %%",value);

  gtk_progress_bar_set_text (GTK_PROGRESS_BAR(batterie), valueCasted);
  gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(batterie),(gdouble)(value/100.0));
  
}

// todo check lat/lon
void majCoords(double lat, double lon){

 char valLatCast [14];
 char valLongCast [14];
 sprintf(valLatCast, "Lat: %lf",lat);
 sprintf(valLongCast, "Lon: %lf",lon);
 if (DEBUG) {
   printf("[ihm_handler] maj coords a %lf, %lf \n", lat,lon);
   printf("[ihm_handler] %s %s  \n", valLatCast,valLongCast);
  }

 gtk_label_set_text (GTK_LABEL(lattitude), valLatCast);
 gtk_label_set_text (GTK_LABEL(longitude), valLongCast);

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

  GtkWidget *table;
  GtkWidget *logo;
  GtkWidget *map;
  int argc = 0;
  char *argv[]={"main"};

  // initialisation de gtk (ici avec des parametres par defaut vides)
  gtk_init(&argc,&argv);
  /* if (gtk_clutter_init (&argc, &argv) != CLUTTER_INIT_SUCCESS)
    return 1;
  */
  // Creation de la fenetre de l'IHM et parametrage
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "GeoCar");
  gtk_container_set_border_width (GTK_CONTAINER (window),200);

  // Definition du comportement a avoir si on quitte la fenetre
  g_signal_connect (window, "delete-event", G_CALLBACK (delete_event), NULL);
  g_signal_connect (window, "destroy", G_CALLBACK (destroy), NULL);

  // Creation de la table allant contenir tous les widgets
  table = gtk_grid_new ();
 
 //ecartement des colonnes
  gtk_grid_set_row_homogeneous(GTK_GRID(table),TRUE);
  gtk_grid_set_column_spacing(GTK_GRID (table),50);
  gtk_container_add (GTK_CONTAINER (window), table);

  // Creation des labels de titre
  GtkWidget * gpsTitre;
  GtkWidget * batTitre;
  GtkWidget * statusTitre;

  const char *format = "<span underline='double' font_weight='bold' color=\"black\" > %s </span>";
  gpsTitre = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(gpsTitre),g_markup_printf_escaped(format,"Données GPS"));
  batTitre = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(batTitre),g_markup_printf_escaped(format,"Batterie"));
  statusTitre = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(statusTitre),g_markup_printf_escaped(format,"Informations voiture"));

  gtk_grid_attach (GTK_GRID (table), gpsTitre,0,0,2,1);
  gtk_grid_attach (GTK_GRID (table), batTitre,2,0,1,1);
  gtk_grid_attach (GTK_GRID (table), statusTitre,0,4,3,1);

  /*label#title-label {
  font: 15px Sans
  }*/
 

  // Creation du label batterie, parametrage
  batterie = gtk_progress_bar_new();
  gtk_progress_bar_set_show_text (GTK_PROGRESS_BAR(batterie),TRUE);
  GdkColor col;
  majBatterie(100);
  gtk_grid_attach (GTK_GRID (table), batterie,2,1,1,1);


  // Creation du label d'erreur attaché à la batterie
  error = gtk_statusbar_new();
  gtk_grid_attach(GTK_GRID(table), error, 0,5,3,1);


  // Creation des labels coord
  lattitude = gtk_label_new(NULL);
  longitude = gtk_label_new(NULL);
  majCoords(0.0,0.0);
  
  gtk_grid_attach (GTK_GRID (table), lattitude,0,1,1,1);
  gtk_grid_attach (GTK_GRID (table), longitude,1,1,1,1);
  
  
  // Création de la map
 
  //GdkPixbuf * img = gdk_pixbuf_new_from_file("IHM/map.svg",NULL);
  //map = gtk_image_new_from_pixbuf(img);

  //map = gtk_champlain_embed_new ();
  //gtk_widget_set_size_request (map, 200, 280);
  // gtk_image_set_pixel_size(GTK_IMAGE(map),200);

  //gtk_container_add (GTK_CONTAINER (window), map);

  
  //gtk_grid_attach(GTK_GRID (table), map, 2,0,300,300);
  // affichage de tous les widgets (TODO recursif)
  gtk_grid_set_column_homogeneous(GTK_GRID(table),TRUE);

  gtk_widget_show_all (window);
  

  if(pthread_create(&IHM,NULL,launchWindow,NULL)<0){
     perror("[ihm_handler] erreur de création du thread de l'ihm");
  }

}


