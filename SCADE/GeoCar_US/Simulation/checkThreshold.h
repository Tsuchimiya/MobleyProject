/* $********** SCADE Suite KCG 32-bit 6.6 (build i19) ***********
** Command: kcg66.exe -config U:/5A/Prog_synchrone/GeoCar_US/Simulation/config.txt
** Generation date: 2018-01-18T09:58:59
*************************************************************$ */
#ifndef _checkThreshold_H_
#define _checkThreshold_H_

#include "kcg_types.h"

/* =====================  no input structure  ====================== */

/* =====================  no output structure  ====================== */

/* ========================  context type  ========================= */
typedef struct {
  /* ---------------------------  outputs  --------------------------- */
  kcg_bool /* Alarm/ */ Alarm;
  /* -----------------------  no local probes  ----------------------- */
  /* -----------------------  no local memory  ----------------------- */
  /* -------------------- no sub nodes' contexts  -------------------- */
  /* ----------------- no clocks of observable data ------------------ */
  /* -------------------- (-debug) no assertions  -------------------- */
  /* ------------------- (-debug) local variables -------------------- */
  kcg_bool /* _L1/ */ _L1;
  kcg_float64 /* _L2/ */ _L2;
  kcg_float64 /* _L3/ */ _L3;
} outC_checkThreshold;

/* ===========  node initialization and cycle functions  =========== */
/* checkThreshold/ */
extern void checkThreshold(
  /* Sensor_value/ */
  kcg_float64 Sensor_value,
  /* Threshold/ */
  kcg_float64 Threshold,
  outC_checkThreshold *outC);

#ifndef KCG_NO_EXTERN_CALL_TO_RESET
extern void checkThreshold_reset(outC_checkThreshold *outC);
#endif /* KCG_NO_EXTERN_CALL_TO_RESET */

#ifndef KCG_USER_DEFINED_INIT
extern void checkThreshold_init(outC_checkThreshold *outC);
#endif /* KCG_USER_DEFINED_INIT */



#endif /* _checkThreshold_H_ */
/* $********** SCADE Suite KCG 32-bit 6.6 (build i19) ***********
** checkThreshold.h
** Generation date: 2018-01-18T09:58:59
*************************************************************$ */

