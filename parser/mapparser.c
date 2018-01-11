#include "mapparser.h"
#define MAXTRY 5
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

void printPoint(point pt) {
  printf("Id %d : %s. x=%lf y=%lf\n", pt.id, pt.name, pt.x, pt.y);
}

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

tab findSeqStep (map world, char * src, char *dest){

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
    resuFinal.size = tailleIndex;
    resuFinal.data = malloc (sizeof(int)*(resuFinal.size));
    int i = 0;
    int j = 0;
    for (i=(tailleIndex-1);i>=0;i--){
      resuFinal.data[j] = resu[i];
      j ++;
    }
    
    return resuFinal;
  }
}



step getStep(map world, int id){
  return world.tabSteps[id];
}
