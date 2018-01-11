#ifndef MAPPARSER_H
#define MAPPARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 40

typedef struct str_point {
  int id;
  char name[MAXSIZE];
  double x; //longitude
  double y; //latitude
} point;

typedef struct str_step {
  int id;
  char src[MAXSIZE];
  char dest[MAXSIZE];
  int nbPoints;
  point* points;
} step;

typedef struct str_map {
  int sizePoints;
  int sizeSteps;
  point* tabPoints;
  step* tabSteps;

} map;

typedef struct str_tab {
  int * data;
  int size;
} tab;

tab resuFinal; 
map world;

void parsePoints(FILE *fpoints, map* world);
void parseSteps(FILE *fsteps, map* world);
void printPoints(map world);
void printPoint(point pnt);
point getPoint(map world, int id);
step getStep(map world, int id);
tab findSeqStep (map world, char * src, char *dest);
#endif
