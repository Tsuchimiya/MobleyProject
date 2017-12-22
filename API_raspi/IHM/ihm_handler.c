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

// Fonction creant la liste de destinations
void CreerListe (GtkTreeStore *destinations, GtkWidget *liste_dest) {
  
  GtkTreeViewColumn *colonne;
  GtkCellRenderer *renderer;

  // Creation du modele de la liste contenant les destinations
  destinations = gtk_tree_store_new (1, G_TYPE_STRING);

  // Remplissage de la liste
  RemplirListe(destinations);
  printf("liste remplie \n");

  // Creation de la vue
  liste_dest = gtk_tree_view_new_with_model(GTK_TREE_MODEL(destinations));
  printf("vue creee\n");
  g_object_unref (G_OBJECT (destinations));

  // Creation d'un "cell renderer"
  renderer = gtk_cell_renderer_text_new ();
  g_object_set (G_OBJECT (renderer),"foreground", "blue", NULL);

  // Creation d'une colonne
  colonne =  gtk_tree_view_column_new_with_attributes ("Destinations", renderer, "text", DESTINATIONS,NULL);

  // Ajout de la colonne à la vue
  gtk_tree_view_append_column (GTK_TREE_VIEW (liste_dest), colonne);

}

// Fonction de selection destination
void ChoixDestination (GtkTreeSelection *choix, gpointer donnee) {

  GtkTreeIter iterateur;
  GtkTreeModel *model;
  gchar *dest;

  if (gtk_tree_selection_get_selected (choix, &model, &iterateur)) 
    {
      gtk_tree_model_get (model, &iterateur, DESTINATIONS, &dest, -1);

      // Affichage dans le terminal
      g_print ("[ihm_handler] Vous souhaitez aller au %s\n", dest);

      // Affichage dans un popup
      GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
      GtkWidget * dialog;
      dialog = gtk_message_dialog_new (window,flags, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,"Vous souhaitez aller au %s\n", dest);
      gtk_dialog_run (GTK_DIALOG (dialog));
      gtk_widget_destroy (dialog);

      g_free (dest);
      }
}

// Fonction de remplissage de la liste
void RemplirListe(GtkTreeStore *destinations) {
  
  // Creation de l'iterateur
  GtkTreeIter iterateur;
  gtk_tree_store_append (destinations, &iterateur, NULL);

  // Remplissage de la liste
  gtk_tree_store_set (destinations, &iterateur, DESTINATIONS, "GB",-1);
  gtk_tree_store_append (destinations, &iterateur, NULL);
  gtk_tree_store_set (destinations, &iterateur, DESTINATIONS, "GC",-1);
  gtk_tree_store_append (destinations, &iterateur, NULL);
  gtk_tree_store_set (destinations, &iterateur, DESTINATIONS, "GEI",-1);
  gtk_tree_store_append (destinations, &iterateur, NULL);
  gtk_tree_store_set (destinations, &iterateur, DESTINATIONS, "GMM",-1);
  gtk_tree_store_append (destinations, &iterateur, NULL);
  gtk_tree_store_set (destinations, &iterateur, DESTINATIONS, "GM",-1);
  gtk_tree_store_append (destinations, &iterateur, NULL);
  gtk_tree_store_set (destinations, &iterateur, DESTINATIONS, "GP",-1);
  gtk_tree_store_append (destinations, &iterateur, NULL);
  gtk_tree_store_set (destinations, &iterateur, DESTINATIONS, "GPE",-1);
  gtk_tree_store_append (destinations, &iterateur, NULL);
  gtk_tree_store_set (destinations, &iterateur, DESTINATIONS, "RU",-1);  
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

// Fonction initialisant la fenetre
void initWindow(){


  // widgets de la fenetre 

  GtkWidget *table;
  GtkWidget *logo;
  GtkWidget *map;
  GtkTreeStore *destinations;
  GtkWidget *liste_dest;

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
  gtk_container_set_border_width (GTK_CONTAINER (window),100);

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
  GtkWidget * destTitre;

  const char *format = "<span underline='double' font_weight='bold' color=\"black\" > %s </span>";
  gpsTitre = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(gpsTitre),g_markup_printf_escaped(format,"Données GPS"));
  batTitre = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(batTitre),g_markup_printf_escaped(format,"Batterie"));
  statusTitre = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(statusTitre),g_markup_printf_escaped(format,"Informations voiture"));
  destTitre = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(destTitre),g_markup_printf_escaped(format,"Où voulez-vous aller ?"));

  gtk_grid_attach (GTK_GRID (table), gpsTitre,0,0,2,1);
  gtk_grid_attach (GTK_GRID (table), batTitre,2,0,1,1);
  gtk_grid_attach (GTK_GRID (table), statusTitre,0,4,3,1);
  gtk_grid_attach (GTK_GRID (table), destTitre,0,5,3,8);


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
  majCoords(43.570600,1.466499);
  
  gtk_grid_attach (GTK_GRID (table), lattitude,0,1,1,1);
  gtk_grid_attach (GTK_GRID (table), longitude,1,1,1,1);

  /************************************************* DESTINATIONS ***********************************************/
 /*********************************************************************************************************/

// Creation de la liste
  //CreerListe (destinations, liste_dest);
  GtkTreeViewColumn *colonne;
  GtkCellRenderer *renderer;

  // Creation du modele de la liste contenant les destinations
  destinations = gtk_tree_store_new (1, G_TYPE_STRING);

  // Remplissage de la liste
  RemplirListe(destinations);

  // Creation de la vue
  liste_dest = gtk_tree_view_new_with_model(GTK_TREE_MODEL(destinations));
  g_object_unref (G_OBJECT (destinations));

  // Creation d'un "cell renderer"
  renderer = gtk_cell_renderer_text_new ();
  g_object_set (G_OBJECT (renderer),"foreground", "blue", NULL);

  // Creation d'une colonne
  colonne =  gtk_tree_view_column_new_with_attributes ("Destinations", renderer, "text", DESTINATIONS,NULL);

  // Ajout de la colonne à la vue
  gtk_tree_view_append_column (GTK_TREE_VIEW (liste_dest), colonne);

  gtk_grid_attach (GTK_GRID (table), liste_dest,0,10,4,4);

  // Bouton valider
  GtkWidget * Valider_btn;
  Valider_btn=gtk_button_new_with_label ("Confirmer");
  gtk_grid_attach (GTK_GRID (table),Valider_btn ,0,15,1,1);


  // Choix de la destination
  GtkTreeSelection *choix;
  gpointer donnee;
  
  choix = gtk_tree_view_get_selection (GTK_TREE_VIEW (liste_dest));
  gtk_tree_selection_set_mode (choix, GTK_SELECTION_SINGLE);
  g_signal_connect_swapped (Valider_btn, "clicked",G_CALLBACK (ChoixDestination), G_OBJECT (choix));
  ChoixDestination (choix, donnee);

 /*********************************************************************************************************/
  /*********************************************************************************************************/
  
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


