#ifndef CODEREGULPOS_H
#define CODEREGULPOS_H
#include "../../API_raspi/com_CAN/communicationSTM.h"

int Commande_Angle_I[2];
void initRegulPos(void);
void RegulationPos(int angleVersPoint_I);

#endif
