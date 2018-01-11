#ifndef INIT_ALL
#define INIT_ALL
#include "com_CAN/can_var.h"
#include "com_CAN/listen.h"
#include "IHM/ihm_handler.h"
#include <pthread.h>
#include "com_CAN/communicationSTM.h"
#include "../GPS/gps_comm.h"
#include "../parser/mapparser.h"


/***********************  init_socket   *******************
 * Initialise et configure un socket conformément aux variables
 * qu'on veut recevoir
 * INPUTS : s : socket à initialiser
 *********************************************************/
void init_socket(int *s);
#endif
