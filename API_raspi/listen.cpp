#include "listen.h"
extern "C"
static void * listen (void * data){
  
  int s = (int) *data;
  printf("[Listen] Socket numéro : %d",s);
  return 0;
}
