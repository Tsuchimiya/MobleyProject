/* $********** SCADE Suite KCG 32-bit 6.6 (build i19) ***********
** Command: kcg66.exe -config U:/5A/Prog_synchrone/GeoCar_US/KCG/config.txt
** Generation date: 2018-01-18T13:27:06
*************************************************************$ */

#include "kcg_consts.h"
#include "kcg_sensors.h"
#include "US_handler.h"

/* US_handler/ */
void US_handler(inC_US_handler *inC, outC_US_handler *outC)
{
  /* @1/_/v4/ */
  kcg_size v4_times_3_size;
  /* @1/_/o/, Emergency_stop_SM:WaitForConfirmation:<2> */
  kcg_bool tr_2_guard_WaitForConfirmation_Emergency_stop_SM;
  /* Emergency_stop_SM:WaitForConfirmation:<1> */
  kcg_bool tr_1_guard_WaitForConfirmation_Emergency_stop_SM;
  /* Emergency_stop_SM: */
  SSM_ST_Emergency_stop_SM Emergency_stop_SM_state_act;
  /* Obstacle_L/, _L14/ */
  kcg_bool Obstacle_L;
  /* Obstacle_M/, _L15/ */
  kcg_bool Obstacle_M;
  /* Obstacle_R/, _L16/ */
  kcg_bool Obstacle_R;

  Obstacle_R = !/* _L3=(checkThreshold#5)/ */
    checkThreshold(inC->Right_Sensor, kcg_lit_float64(50.0));
  Obstacle_M = !/* _L2=(checkThreshold#4)/ */
    checkThreshold(inC->Middle_Sensor, kcg_lit_float64(100.0));
  Obstacle_L = !/* _L1=(checkThreshold#3)/ */
    checkThreshold(inC->Left_Sensor, kcg_lit_float64(50.0));
  /* Emergency_stop_SM: */
  switch (outC->Emergency_stop_SM_state_nxt) {
    case SSM_st_WaitForConfirmation_Emergency_stop_SM :
      if (outC->Emergency_stop_SM_reset_act) {
        outC->init = kcg_true;
      }
      /* @1/_/v4= */
      if (outC->init) {
        v4_times_3_size = 50;
      }
      else {
        v4_times_3_size = outC->v3_times_3_size;
      }
      /* @1/_/v3= */
      if (v4_times_3_size < 0) {
        outC->v3_times_3_size = v4_times_3_size;
      }
      else {
        outC->v3_times_3_size = v4_times_3_size - 1;
      }
      tr_2_guard_WaitForConfirmation_Emergency_stop_SM = outC->v3_times_3_size == 0;
      tr_1_guard_WaitForConfirmation_Emergency_stop_SM = !(Obstacle_M |
          Obstacle_R | Obstacle_L);
      if (tr_1_guard_WaitForConfirmation_Emergency_stop_SM) {
        Emergency_stop_SM_state_act = SSM_st_IDLE_Emergency_stop_SM;
      }
      else if (tr_2_guard_WaitForConfirmation_Emergency_stop_SM) {
        Emergency_stop_SM_state_act = SSM_st_Stop_Emergency_stop_SM;
      }
      else {
        Emergency_stop_SM_state_act = SSM_st_WaitForConfirmation_Emergency_stop_SM;
      }
      outC->init = kcg_false;
      outC->Emergency_stop_SM_reset_act =
        tr_1_guard_WaitForConfirmation_Emergency_stop_SM |
        tr_2_guard_WaitForConfirmation_Emergency_stop_SM;
      break;
    case SSM_st_Stop_Emergency_stop_SM :
      outC->Emergency_stop_SM_reset_act = !(Obstacle_M | Obstacle_R | Obstacle_L);
      if (outC->Emergency_stop_SM_reset_act) {
        Emergency_stop_SM_state_act = SSM_st_IDLE_Emergency_stop_SM;
      }
      else {
        Emergency_stop_SM_state_act = SSM_st_Stop_Emergency_stop_SM;
      }
      break;
    case SSM_st_IDLE_Emergency_stop_SM :
      outC->Emergency_stop_SM_reset_act = Obstacle_M | Obstacle_R | Obstacle_L;
      if (outC->Emergency_stop_SM_reset_act) {
        Emergency_stop_SM_state_act = SSM_st_WaitForConfirmation_Emergency_stop_SM;
      }
      else {
        Emergency_stop_SM_state_act = SSM_st_IDLE_Emergency_stop_SM;
      }
      break;
    default :
      /* this default branch is unreachable */
      break;
  }
  /* Emergency_stop_SM: */
  switch (Emergency_stop_SM_state_act) {
    case SSM_st_WaitForConfirmation_Emergency_stop_SM :
      outC->Emergency_stop = kcg_false;
      outC->Emergency_stop_SM_state_nxt =
        SSM_st_WaitForConfirmation_Emergency_stop_SM;
      break;
    case SSM_st_Stop_Emergency_stop_SM :
      outC->Emergency_stop = kcg_true;
      outC->Emergency_stop_SM_state_nxt = SSM_st_Stop_Emergency_stop_SM;
      break;
    case SSM_st_IDLE_Emergency_stop_SM :
      outC->Emergency_stop = kcg_false;
      outC->Emergency_stop_SM_state_nxt = SSM_st_IDLE_Emergency_stop_SM;
      break;
    default :
      /* this default branch is unreachable */
      break;
  }
}

#ifndef KCG_USER_DEFINED_INIT
void US_handler_init(outC_US_handler *outC)
{
  outC->Emergency_stop_SM_reset_act = kcg_false;
  outC->Emergency_stop = kcg_true;
  outC->init = kcg_true;
  outC->v3_times_3_size = 0;
  outC->Emergency_stop_SM_state_nxt = SSM_st_IDLE_Emergency_stop_SM;
}
#endif /* KCG_USER_DEFINED_INIT */


#ifndef KCG_NO_EXTERN_CALL_TO_RESET
void US_handler_reset(outC_US_handler *outC)
{
  outC->Emergency_stop_SM_reset_act = kcg_false;
  outC->init = kcg_true;
  outC->Emergency_stop_SM_state_nxt = SSM_st_IDLE_Emergency_stop_SM;
}
#endif /* KCG_NO_EXTERN_CALL_TO_RESET */

/*
  Expanded instances for: US_handler/
  @1: (times#3)
*/

/* $********** SCADE Suite KCG 32-bit 6.6 (build i19) ***********
** US_handler.c
** Generation date: 2018-01-18T13:27:06
*************************************************************$ */

