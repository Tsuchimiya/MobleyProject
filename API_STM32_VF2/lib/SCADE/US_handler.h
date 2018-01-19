/* $********** SCADE Suite KCG 32-bit 6.6 (build i19) ***********
** Command: kcg66.exe -config U:/5A/Prog_synchrone/GeoCar_US/KCG/config.txt
** Generation date: 2018-01-18T13:27:06
*************************************************************$ */
#ifndef _US_handler_H_
#define _US_handler_H_

#include "kcg_types.h"
#include "checkThreshold.h"

/* ========================  input structure  ====================== */
typedef struct {
  kcg_float64 /* Left_Sensor/, _L7/ */ Left_Sensor;
  kcg_float64 /* Middle_Sensor/, _L8/ */ Middle_Sensor;
  kcg_float64 /* Right_Sensor/, _L9/ */ Right_Sensor;
} inC_US_handler;

/* =====================  no output structure  ====================== */

/* ========================  context type  ========================= */
typedef struct {
  /* ---------------------------  outputs  --------------------------- */
  kcg_bool /* Emergency_stop/ */ Emergency_stop;
  /* -----------------------  no local probes  ----------------------- */
  /* ----------------------- local memories  ------------------------- */
  kcg_bool init;
  kcg_size /* @1/_/v3/ */ v3_times_3_size;
  SSM_ST_Emergency_stop_SM /* Emergency_stop_SM: */ Emergency_stop_SM_state_nxt;
  kcg_bool /* Emergency_stop_SM: */ Emergency_stop_SM_reset_act;
  /* -------------------- no sub nodes' contexts  -------------------- */
  /* ----------------- no clocks of observable data ------------------ */
} outC_US_handler;

/* ===========  node initialization and cycle functions  =========== */
/* US_handler/ */
extern void US_handler(inC_US_handler *inC, outC_US_handler *outC);

#ifndef KCG_NO_EXTERN_CALL_TO_RESET
extern void US_handler_reset(outC_US_handler *outC);
#endif /* KCG_NO_EXTERN_CALL_TO_RESET */

#ifndef KCG_USER_DEFINED_INIT
extern void US_handler_init(outC_US_handler *outC);
#endif /* KCG_USER_DEFINED_INIT */

/*
  Expanded instances for: US_handler/
  @1: (times#3)
*/

#endif /* _US_handler_H_ */
/* $********** SCADE Suite KCG 32-bit 6.6 (build i19) ***********
** US_handler.h
** Generation date: 2018-01-18T13:27:06
*************************************************************$ */

