#ifndef CODEREGULPOS_H
#define CODEREGULPOS_H
#include "../../API_raspi/com_CAN/communicationSTM.h"
#include "math.h"
#include "demiTour.h"

#define SEUIL_DEMITOUR 45
void initRegulPos(void);
int RegulationPos(int angleVersPoint_I);

#endif
