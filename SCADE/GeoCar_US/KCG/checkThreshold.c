/* $********** SCADE Suite KCG 32-bit 6.6 (build i19) ***********
** Command: kcg66.exe -config U:/5A/Prog_synchrone/GeoCar_US/KCG/config.txt
** Generation date: 2018-01-18T13:27:06
*************************************************************$ */

#include "kcg_consts.h"
#include "kcg_sensors.h"
#include "checkThreshold.h"

/* checkThreshold/ */
kcg_bool checkThreshold(
  /* Sensor_value/, _L2/ */
  kcg_float64 Sensor_value,
  /* Threshold/, _L3/ */
  kcg_float64 Threshold)
{
  /* Alarm/, _L1/ */
  kcg_bool Alarm;

  Alarm = Sensor_value > Threshold;
  return Alarm;
}



/* $********** SCADE Suite KCG 32-bit 6.6 (build i19) ***********
** checkThreshold.c
** Generation date: 2018-01-18T13:27:06
*************************************************************$ */

