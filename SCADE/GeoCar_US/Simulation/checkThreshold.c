/* $********** SCADE Suite KCG 32-bit 6.6 (build i19) ***********
** Command: kcg66.exe -config U:/5A/Prog_synchrone/GeoCar_US/Simulation/config.txt
** Generation date: 2018-01-18T09:58:59
*************************************************************$ */

#include "kcg_consts.h"
#include "kcg_sensors.h"
#include "checkThreshold.h"

/* checkThreshold/ */
void checkThreshold(
  /* Sensor_value/ */
  kcg_float64 Sensor_value,
  /* Threshold/ */
  kcg_float64 Threshold,
  outC_checkThreshold *outC)
{
  outC->_L3 = Threshold;
  outC->_L2 = Sensor_value;
  outC->_L1 = outC->_L2 > outC->_L3;
  outC->Alarm = outC->_L1;
}

#ifndef KCG_USER_DEFINED_INIT
void checkThreshold_init(outC_checkThreshold *outC)
{
  outC->_L3 = kcg_lit_float64(0.0);
  outC->_L2 = kcg_lit_float64(0.0);
  outC->_L1 = kcg_true;
  outC->Alarm = kcg_true;
}
#endif /* KCG_USER_DEFINED_INIT */


#ifndef KCG_NO_EXTERN_CALL_TO_RESET
void checkThreshold_reset(outC_checkThreshold *outC)
{
}
#endif /* KCG_NO_EXTERN_CALL_TO_RESET */



/* $********** SCADE Suite KCG 32-bit 6.6 (build i19) ***********
** checkThreshold.c
** Generation date: 2018-01-18T09:58:59
*************************************************************$ */

