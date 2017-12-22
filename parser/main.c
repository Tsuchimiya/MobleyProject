#include "mapparser.h"

void main()
{
  FILE *fpts;
  FILE *fsteps;
  map world;

  fpts=fopen("points.map", "r");
  printf("[PARSE] points file opened.\n");
  fsteps=fopen("steps.map","r");
  printf("[PARSE] steps file opened.\n");
  if (fpts==NULL || fsteps==NULL) {
    printf("[PARSE] Error: a map file can't be read.\n");
  } else {
    parsePoints(fpts, &world);
    printf("[PARSE] points file parsed.\n");
    parseSteps(fsteps, &world);
    printf("[PARSE] steps file parsed.\n");
    //printPoints(world);
    //point test=getPoint(world, 4);
    //printf("%d, %s, %lf, %lf\n", test.id, test.name, test.x, test.y);
    printSteps(world);
  }
}
