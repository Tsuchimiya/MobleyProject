/* $********** SCADE Suite KCG 32-bit 6.6 (build i19) ***********
** Command: kcg66.exe -config U:/5A/Prog_synchrone/GeoCar_US/Simulation/config.txt
** Generation date: 2018-01-18T09:58:59
*************************************************************$ */
#ifndef _US_handler_H_
#define _US_handler_H_

#include "kcg_types.h"
#include "checkThreshold.h"

/* ========================  input structure  ====================== */
typedef struct {
  kcg_float64 /* US_FL/ */ US_FL;
  kcg_float64 /* US_FM/ */ US_FM;
  kcg_float64 /* US_FR/ */ US_FR;
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
  kcg_bool /* Emergency_stop_SM: */ Emergency_stop_SM_reset_nxt;
  /* ---------------------  sub nodes' contexts  --------------------- */
  outC_checkThreshold /* _L1=(checkThreshold#3)/ */ Context_checkThreshold_3;
  outC_checkThreshold /* _L2=(checkThreshold#4)/ */ Context_checkThreshold_4;
  outC_checkThreshold /* _L3=(checkThreshold#5)/ */ Context_checkThreshold_5;
  /* ------------------ clocks of observable data -------------------- */
  SSM_ST_Emergency_stop_SM /* Emergency_stop_SM: */ Emergency_stop_SM_state_sel;
  SSM_ST_Emergency_stop_SM /* Emergency_stop_SM: */ Emergency_stop_SM_state_act;
  /* -------------------- (-debug) no assertions  -------------------- */
  /* ------------------- (-debug) local variables -------------------- */
  kcg_bool /* @1/_/o/ */ o_times_3_size;
  kcg_bool /* @1/_/c/ */ c_times_3_size;
  kcg_size /* @1/_/n/ */ n_times_3_size;
  kcg_size /* @1/_/v4/ */ v4_times_3_size;
  kcg_bool /* Emergency_stop_SM:IDLE:_L1/ */ _L1_IDLE_Emergency_stop_SM;
  kcg_bool /* Emergency_stop_SM:Stop:_L1/ */ _L1_Stop_Emergency_stop_SM;
  kcg_bool /* Emergency_stop_SM:WaitForConfirmation:_L2/ */ _L2_WaitForConfirmation_Emergency_stop_SM;
  SSM_TR_Emergency_stop_SM /* Emergency_stop_SM: */ Emergency_stop_SM_fired_strong;
  SSM_TR_Emergency_stop_SM /* Emergency_stop_SM: */ Emergency_stop_SM_fired;
  kcg_bool /* Obstacle_L/ */ Obstacle_L;
  kcg_bool /* Obstacle_M/ */ Obstacle_M;
  kcg_bool /* Obstacle_R/ */ Obstacle_R;
  kcg_bool /* _L1/ */ _L1;
  kcg_bool /* _L2/ */ _L2;
  kcg_bool /* _L3/ */ _L3;
  kcg_float64 /* _L4/ */ _L4;
  kcg_float64 /* _L5/ */ _L5;
  kcg_float64 /* _L6/ */ _L6;
  kcg_float64 /* _L7/ */ _L7;
  kcg_float64 /* _L8/ */ _L8;
  kcg_float64 /* _L9/ */ _L9;
  kcg_bool /* _L14/ */ _L14;
  kcg_bool /* _L15/ */ _L15;
  kcg_bool /* _L16/ */ _L16;
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
** Generation date: 2018-01-18T09:58:59
*************************************************************$ */

