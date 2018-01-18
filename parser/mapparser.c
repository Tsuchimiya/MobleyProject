#include "mapparser.h"
#define MAXTRY 5


/********************** parsePoints ************************
 * Recupere les coordonnees GPS de points de reperes sur le
 * campus et les place dans le tableau tabpoints de world
 * INPUTS : fpoints : fichier contenant les coordonnees GPS
 *          world : structure contenant la carte du campus
 * OUTPUT : --
 *********************************************************/
void parsePoints(FILE *fpoints, map* world) {
  int size, id;
  int i=0;
  double x, y;
  char name[MAXSIZE];
  if (fpoints!=NULL) {
    fscanf(fpoints, "%d", &size);
    world->sizePoints=size;
    world->tabPoints=(point *)malloc(size*sizeof(point));
    while(fscanf(fpoints, "%d %s %lf %lf", &id, name, &x, &y) !=EOF) {
      strcpy(world->tabPoints[i].name, name);
      world->tabPoints[i].id=id;
      world->tabPoints[i].x=x;
      world->tabPoints[i].y=y;
      i++;
    }
  } else {
    printf("[PARSE] Error: points.map can't be parsed.\n");
  }
}


/********************** parseSteps ******************************
 * Recupere les identifiants des reperes des etapes appartenant
 * a un chemin donne et les place dans le tableau tabSteps 
 * de world
 * INPUTS : fsteps : fichier contenant les etapes d'un chemin
 *          world : structure contenant la carte du campus
 * OUTPUT : --
 ***************************************************************/
void parseSteps(FILE *fsteps, map* world) {
  int size, id;
  int nbPoints;
  int idPt;
  char src[MAXSIZE];
  char dest[MAXSIZE];
  int i=0;
  int j;
  point pnt;
  if (fsteps!=NULL) {
    fscanf(fsteps, "%d", &size);
    world->sizeSteps=size;
    world->tabSteps=(step *)malloc(size*sizeof(step));
    while(fscanf(fsteps, "%d %s %s %d", &id, src, dest, &nbPoints)!=EOF)
      {
	world->tabSteps[i].id=id;
	strcpy(world->tabSteps[i].dest, dest);
	strcpy(world->tabSteps[i].src, src);
	world->tabSteps[i].nbPoints=nbPoints;
	world->tabSteps[i].points=(point *)malloc(nbPoints*sizeof(point));
	for (j=0;j<nbPoints;j++)
	  {
	    fscanf(fsteps, "%d", &idPt);
	    pnt = getPoint(*world, idPt);
	    world->tabSteps[i].points[j]=pnt;
	  }
	i++;
      }
  }
}

/********************** printPoints ******************************
 * Affiche les coordonnees GPS des points de reperes appartenant
 * a la carte du campus 
 * INPUTS : world : structure contenant la carte du campus
 * OUTPUT : --
 ***************************************************************/
void printPoints(map world) {
  int i;
  int size=world.sizePoints;
  point *tab=world.tabPoints;
  if(tab==NULL) {
    printf("[PARSE] Can't display tabPoints: its value is NULL.\n");
  }
  else {
    printf("\n----ARRAY OF %d POINTS----\n\n", size);
    for(i=0;i<size;i++)
      {
	printf("Id %d : %s\n    x=%lf y=%lf\n", tab[i].id, tab[i].name, tab[i].x, tab[i].y);
      }
  }
}


/********************** printPoint ******************************
 * Affiche les coordonnees GPS d'UN point de reperes appartenant
 * a la carte du campus 
 * INPUTS : pt : le point à afficher
 * OUTPUT : --
 ***************************************************************/
void printPoint(point pt) {
  printf("Id %d : %s. x=%lf y=%lf\n", pt.id, pt.name, pt.x, pt.y);
}

/********************** printSteps ******************************
 * Affiche les identifiants des etapes (points repères)
 * appartenant a tous les trajets definis sur la carte 
 * INPUTS : world : structure contenant la carte du campus
 * OUTPUT : --
 ***************************************************************/
void printSteps(map world) {
  int i,j;
  int size=world.sizeSteps;
  step *tab=world.tabSteps;
  if(tab==NULL) {
    printf("[PARSE] Can't display tabSteps: its value is NULL.\n");
  }
  else {
    printf("\n----ARRAY OF %d STEPS----\n\n", size);
    for(i=0;i<size;i++)
      {
	printf("Id %d : %s to %s. %d points\n", tab[i].id, tab[i].src, tab[i].dest, tab[i].nbPoints);
	for(j=0;j<tab[i].nbPoints;j++)
	  {
	    printf("   -");
	    printPoint((tab[i].points[j]));
	  }
	printf("\n");
      }
  }
}

/********************** getPoint ******************************
 * Renvoie la structure point du point dont l'id est donne en
 *  entree
 * INPUTS : world : structure contenant la carte du campus
 *          id : identifiant du point concerne
 * OUTPUT : point : structure point correspondant a l'id
 ***************************************************************/
point getPoint(map world, int id)
{
  int i;
  for (i=0;i<world.sizePoints;i++)
    {
      if(world.tabPoints[i].id==id)
	{
	  return world.tabPoints[i];
	}
    }
  printf("[ERROR] : no point of the id %d\n", id);
  exit(-1);
}

/******************** searchDirectStep **************************
 * Renvoie l'id du chemin correspondant au point de depart et a 
 * la destination specifiee
 * INPUTS : world : structure contenant la carte du campus
 *          dest : nom de la destination
 *          src : nom du point de depart
 * OUTPUT : identifiant du chemin
 ***************************************************************/
int searchDirectStep(map world, char * dest, char * src){
  int trouve= 0;
  int i=0;
  step *tab=world.tabSteps; 
  if(tab==NULL) {
    printf("[PARSE] Can't display tabSteps: its value is NULL.\n");
  }else{
    while (!trouve && i<world.sizeSteps){
      if (strcmp(tab[i].dest,dest)==0 && strcmp(tab[i].src,src) == 0){
	trouve = 1;
	return tab[i].id;

      }
      i++;
    }
    return -1;
  }
}

/********************** searchIntermPoint ******************************
 * Renvoie l'id du premier chemin trouve menant a la destination (permet
 * de calculer des points intermediaires si pas de chemin direct trouve)
 * INPUTS : world : structure contenant la carte du campus
 *          dest : nom de la destination
 * OUTPUT : id d'un chemin arrivant a la destination specifie
 *************************************************************************/
int searchIntermPoint(map world, char * dest){
  int trouve= 0;
  int i=0;
  step *tab=world.tabSteps; 
  if(tab==NULL) {
    printf("[PARSE] Can't display tabSteps: its value is NULL.\n");
  }else{
    while (!trouve && i<world.sizeSteps){
      if (strcmp(tab[i].dest,dest)==0){
	trouve = 1;
	return tab[i].id;

      }
      i++;
    }
    return -1;
  }
}


/************************** findSeqStep *********************************
 * Renvoie le nombre de chemins "directs" (size) et identifiants des chemins
 * "directs" (data)  pour aller du point de depart au point
 * d'arrivee
 * INPUTS : world : structure contenant la carte du campus
 *          src : nom du point de depart
 *          dest : nom de la destination
 * OUTPUT : tableau contenant "size" et "data"
 *************************************************************************/
tab findSeqStep (map world, char * src, char *dest, int nbRec){


  if (nbRec <= 1) {
    int trouve = 0;
    int i = 0;
    step *tab=world.tabSteps; 
    int resu [20];
 
    int tmp;
    int indexResu = 0;
    int tailleIndex = 0;
    int try =0;
  
    char dest1[10];
    if(tab==NULL) {
      printf("[PARSE] Can't display tabSteps: its value is NULL.\n");
    }
    else {
  
      // cherche un chemin direct vers la destination s'il existe
      tmp = searchDirectStep(world, dest,src);
      if (tmp >= 0){
	printf("[PARSER] found 1 direct path \n");
	resuFinal.size = 1;
	resuFinal.data = malloc (sizeof(int));
	*(resuFinal.data)=tmp;
	return resuFinal;
      }
      printf("[PARSER] direct path not found searching interm \n");

      strcpy(dest1,dest);
      while (!trouve && try < MAXTRY){
      
	tmp = searchIntermPoint(world,dest1);
	printf("[PARSER] tmp = %d \n",tmp);
	if (tmp >= 0){
	  resu[tailleIndex]=tmp;
	  tailleIndex ++;
	  //	printf("[PARSER] found 1 interm point %d \n",tmp);
	}
	if (strcmp(tab[tmp].src,src)==0){
	  trouve = 1;
	}

	strcpy(dest1,tab[tmp].src);
	try ++;
      }


      // recherche de chemin inverse
      if (! trouve){
	printf("[PARSE] looking for a reverse path \n");
	resuFinal = findSeqStep(world,dest,src,(nbRec+1));
	// recherche de chemin normal
      } else {
	printf("nbRec = %d\n",nbRec);
	if(nbRec){
	  resuFinal.size = tailleIndex;
	  resuFinal.data = malloc (sizeof(int)*(resuFinal.size));
	  int i = 0;
	  int j = 0;
	  resuFinal.inverse = -1;
	  for (i=0;i<tailleIndex;i++){
	    resuFinal.data[j] = resu[i];
	    j ++;
	  }
	}else{
	  resuFinal.size = tailleIndex;
	  resuFinal.data = malloc (sizeof(int)*(resuFinal.size));
	  int i = 0;
	  int j = 0;
	  resuFinal.inverse = 1;
	  for (i=(tailleIndex-1);i>=0;i--){
	    resuFinal.data[j] = resu[i];
	    j ++;
	  }
	}
      }
    
      return resuFinal;
    }
  }else {
    perror("Can't find a path to the destination, stopping everything\n");
  }
}


/********************** getStep ******************************
 * Renvoie la structure Step du chemin dont l'id est donne en
 *  entree
 * INPUTS : world : structure contenant la carte du campus
 *          id : identifiant du step concerne
 * OUTPUT : structure Step correspondant a l'id
 ***************************************************************/
step getStep(map world, int id){
  return world.tabSteps[id];
}
