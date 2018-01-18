#include "ihm_handler.h"
#define CAR_NOT_INIT -1
#define CAR_INIT 2
int etat;
point destPoint;
int batterieLvl = 100;
int onceFaible =0;
gboolean  alertBatterie( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data )
{
  GtkDialogFlags flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;
  GtkWidget * dialog2;
  // printf("SIGNAL \n");
  // METTRE MUTEX SUR BATTERIE TODO
  if(batterieLvl <= 8){
    if (batterieLvl <= 2){
      dialog2  = gtk_message_dialog_new (GTK_WINDOW(window),flags, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE,MSG_BAT_CRITIC);
      gtk_dialog_run (GTK_DIALOG (dialog2));
      gtk_widget_destroy (dialog2);
    }else{
      if(!onceFaible){
       dialog2  = gtk_message_dialog_new (GTK_WINDOW(window),flags, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,MSG_BAT_FAIBLE);
      gtk_dialog_run (GTK_DIALOG (dialog2));
      gtk_widget_destroy (dialog2);
      onceFaible = 1;
      }
    
    }
  }
     
    return TRUE;
}



// Controle la voiture depuis l'ihm
void control(){

  // soit on lance l'initialisation pour demarrer une regulation apres
  if (etat == CAR_NOT_INIT){
    etat = CAR_INIT;
    printf("init en cours\n");
    initVoiture();
    gtk_button_set_label(GTK_BUTTON(controlButton),"STOP");
  }

  // soit on stoppe la voiture
  else {
    printf("stopping the car\n");
    gtk_button_set_label(GTK_BUTTON(controlButton),"Demarrer");
    etat = CAR_NOT_INIT;
    stopVoiture();
  }
}

// Lance une fenetre

void majBatterie(int value){
  if (DEBUG) {
    printf("[ihm_handler] maj batterie a %d %%\n", value);
  }
  char valueCasted [7];
  sprintf(valueCasted,"%d %%",value);
  batterieLvl = value;
  gtk_progress_bar_set_text (GTK_PROGRESS_BAR(batterie), valueCasted);
  gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(batterie),(gdouble)(value/100.0));
  /*if(value <= 8){
    if (value <= 2){
      alert(BATTERIE_CRITIC);
    }else{
      alert(BATTERIE_FAIBLE);
    }
    }*/
  
}
 char valLatCast [13];
 char valLongCast [13];
double longitude_coord;
double latitude_coord;

// todo check lat/lon
void majCoords(double lat, double lon){

 if (DEBUG) {
   printf("[ihm_handler] maj coords a %lf, %lf \n", lat,lon);
   printf("[ihm_handler] %s %s  \n", valLatCast,valLongCast);
  }
 longitude_coord = lon;
 latitude_coord = lat;
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
// cherche le point final le plus proche de notre position actuelle
int  closestPoint(double lon, double lat){
  int size = world.sizePoints;
  int i;
  point *tab = world.tabPoints;
  double minDist;
  int save;
  double tmp;

  if(tab==NULL) {
    printf("[ihm_handler] tab null, can't find the closest point\n");
  }
  else {
    minDist = sqrt(pow(100*(tab[0].x-lon),2)+pow(100*(tab[0].y-lat),2));
    save = 0;
    for(i=1;i<7;i++)
      {
	tmp = sqrt(pow(100*(tab[i].x-lon),2)+pow(100*(tab[i].y-lat),2)) ;
	printf("[ihm_handler] min = %lf \n",tmp);
	if (tmp <= minDist){
	  save = i;
	  minDist = tmp;
	}
      }

  }
	printf("[ihm_handler] parser : closest point id = %d\n",save);
  return save;
}
// Fonction de selection destination
void ChoixDestination (GtkTreeSelection *choix, gpointer donnee) {
  point departPoint;

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

      int depart = closestPoint(longitude_coord,latitude_coord);
      departPoint = world.tabPoints[depart];
      findSeqStep(world,departPoint.name,dest,0);
      if (resuFinal.inverse > 0 ){
	destPoint = getStep(world,resuFinal.data[0]).points[1];
	currentDest.idPoint = 1;
      }
      else {
	currentDest.idPoint = getStep(world,resuFinal.data[0]).nbPoints - 2;
	destPoint =   getStep(world,resuFinal.data[0]).points[currentDest.idPoint];
      }
     
      currentDest.idStep = 0;
      printf("[ihm_handler] going to point %f , %f\n",destPoint.x,destPoint.y);
      goToPoint(destPoint.x,destPoint.y);
      
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
  etat = CAR_NOT_INIT;


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
  gtk_grid_set_column_spacing(GTK_GRID (table),0);
  gtk_grid_set_row_spacing(GTK_GRID (table),10);
  gtk_container_add (GTK_CONTAINER (window), table);

  // Creation des labels de titre
  GtkWidget * gpsTitre;
  GtkWidget * batTitre;
  GtkWidget * statusTitre;
  GtkWidget * destTitre;

  const char *format = "<span underline='double' font_weight='bold' color=\"black\" > %s </span>";
  batTitre = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(batTitre),g_markup_printf_escaped(format,"Batterie"));

//  gtk_grid_attach (GTK_GRID (table), batTitre,2,0,1,1);


  // Creation du label batterie, parametrage
  batterie = gtk_progress_bar_new();
  gtk_progress_bar_set_show_text (GTK_PROGRESS_BAR(batterie),TRUE);
  GdkColor col;
  majBatterie(100);
  gtk_grid_attach (GTK_GRID (table), batterie,2,0,1,1);


  // Creation des labels coord
  lattitude = gtk_label_new(NULL);
  longitude = gtk_label_new(NULL);
  majCoords(43.570600,1.466499);
  
  //gtk_grid_attach (GTK_GRID (table), lattitude,0,7,1,1);
  //gtk_grid_attach (GTK_GRID (table), longitude,1,8,1,1);

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

  gtk_grid_attach (GTK_GRID (table), liste_dest,2,1,1,1);

  // Bouton valider
  GtkWidget * Valider_btn;
  Valider_btn=gtk_button_new_with_label ("Confirmer");
  gtk_grid_attach (GTK_GRID (table),Valider_btn ,2,2,1,1);


  // Bouton de controle init puis arret d'urgence
  controlButton = gtk_button_new_with_label ("Demarrer");
  gtk_grid_attach (GTK_GRID (table),controlButton ,0,3,3,1);
  g_signal_connect (controlButton, "clicked",G_CALLBACK(control),NULL);


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
 
  // GdkPixbuf * img = gdk_pixbuf_new_from_file("IHM/map.svg",NULL);
  GdkPixbuf * img = gdk_pixbuf_new_from_file("IHM/index.png",NULL);
   map = gtk_image_new_from_pixbuf(img);

  //map = gtk_champlain_embed_new ();
  //gtk_widget_set_size_request (map, 200, 280);
  // gtk_image_set_pixel_size(GTK_IMAGE(map),200);

  //gtk_container_add (GTK_CONTAINER (window), map);

  
   gtk_grid_attach(GTK_GRID (table), map, 0,1,2,2);
   


   gtk_grid_set_column_homogeneous(GTK_GRID(table),TRUE);
   gtk_window_fullscreen(GTK_WINDOW(window));
   gtk_widget_show_all (window);


   // init du signal de la batterie


  g_signal_new("batterie_critique",
             G_TYPE_OBJECT, G_SIGNAL_RUN_FIRST,
             0, NULL, NULL,
             g_cclosure_marshal_VOID__POINTER,
             G_TYPE_NONE, 1, G_TYPE_POINTER);

 g_signal_new("batterie_faible",
             G_TYPE_OBJECT, G_SIGNAL_RUN_FIRST,
             0, NULL, NULL,
             g_cclosure_marshal_VOID__POINTER,
             G_TYPE_NONE, 1, G_TYPE_POINTER);

// ajout du watchdog surveillant le niveau de batterie dans l'ihm
  g_idle_add((GSourceFunc ) (alertBatterie),NULL);


  if(pthread_create(&IHM,NULL,launchWindow,NULL)<0){
     perror("[ihm_handler] erreur de création du thread de l'ihm");
  }

}


