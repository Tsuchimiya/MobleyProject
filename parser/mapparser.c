#include "mapparser.h"

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
  char name[MAXSIZE];
  int i=0;
  int j;
  point pnt;
  if (fsteps!=NULL) {
    fscanf(fsteps, "%d", &size);
    world->sizeSteps=size;
    world->tabSteps=(step *)malloc(size*sizeof(step));
    while(fscanf(fsteps, "%d %s %d", &id, name, &nbPoints)!=EOF)
    {
      world->tabSteps[i].id=id;
      strcpy(world->tabSteps[i].name, name);
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
      printf("Id %d : %s. %d points\n", tab[i].id, tab[i].name, tab[i].nbPoints);
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
