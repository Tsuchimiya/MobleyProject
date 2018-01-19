/* $********** SCADE Suite KCG 32-bit 6.6 (build i19) ***********
** Command: kcg66.exe -config U:/5A/Prog_synchrone/GeoCar_US/Simulation/config.txt
** Generation date: 2018-01-18T09:58:59
*************************************************************$ */

#include "kcg_consts.h"
#include "kcg_sensors.h"
#include "US_handler.h"

/* US_handler/ */
void US_handler(inC_US_handler *inC, outC_US_handler *outC)
{
  /* Emergency_stop/ */
  kcg_bool Emergency_stop_partial;
  /* Emergency_stop_SM: */
  SSM_ST_Emergency_stop_SM Emergency_stop_SM_state_nxt_partial;
  /* Emergency_stop_SM: */
  kcg_bool Emergency_stop_SM_reset_nxt_partial;
  /* Emergency_stop_SM: */
  SSM_TR_Emergency_stop_SM Emergency_stop_SM_fired_partial;
  /* Emergency_stop/ */
  kcg_bool _1_Emergency_stop_partial;
  /* Emergency_stop_SM: */
  SSM_ST_Emergency_stop_SM _2_Emergency_stop_SM_state_nxt_partial;
  /* Emergency_stop_SM: */
  kcg_bool _3_Emergency_stop_SM_reset_nxt_partial;
  /* Emergency_stop_SM: */
  SSM_TR_Emergency_stop_SM _4_Emergency_stop_SM_fired_partial;
  /* Emergency_stop/ */
  kcg_bool _5_Emergency_stop_partial;
  /* Emergency_stop_SM: */
  SSM_ST_Emergency_stop_SM _6_Emergency_stop_SM_state_nxt_partial;
  /* Emergency_stop_SM: */
  kcg_bool _7_Emergency_stop_SM_reset_nxt_partial;
  /* Emergency_stop_SM: */
  SSM_TR_Emergency_stop_SM _8_Emergency_stop_SM_fired_partial;
  /* Emergency_stop_SM: */
  SSM_ST_Emergency_stop_SM Emergency_stop_SM_state_act_partial;
  /* Emergency_stop_SM: */
  kcg_bool Emergency_stop_SM_reset_act_partial;
  /* Emergency_stop_SM: */
  SSM_TR_Emergency_stop_SM Emergency_stop_SM_fired_strong_partial;
  /* Emergency_stop_SM:IDLE:<1> */
  kcg_bool tr_1_guard_IDLE_Emergency_stop_SM;
  /* Emergency_stop_SM: */
  SSM_ST_Emergency_stop_SM _9_Emergency_stop_SM_state_act_partial;
  /* Emergency_stop_SM: */
  kcg_bool _10_Emergency_stop_SM_reset_act_partial;
  /* Emergency_stop_SM: */
  SSM_TR_Emergency_stop_SM _11_Emergency_stop_SM_fired_strong_partial;
  /* Emergency_stop_SM:Stop:<1> */
  kcg_bool tr_1_guard_Stop_Emergency_stop_SM;
  /* Emergency_stop_SM: */
  SSM_ST_Emergency_stop_SM _12_Emergency_stop_SM_state_act_partial;
  /* Emergency_stop_SM: */
  kcg_bool _13_Emergency_stop_SM_reset_act_partial;
  /* Emergency_stop_SM: */
  SSM_TR_Emergency_stop_SM _14_Emergency_stop_SM_fired_strong_partial;
  /* Emergency_stop_SM:WaitForConfirmation:<2> */
  kcg_bool tr_2_guard_WaitForConfirmation_Emergency_stop_SM;
  /* Emergency_stop_SM:WaitForConfirmation:<1> */
  kcg_bool tr_1_guard_WaitForConfirmation_Emergency_stop_SM;
  /* Emergency_stop_SM: */
  kcg_bool Emergency_stop_SM_reset_sel;
  /* Emergency_stop_SM: */
  kcg_bool Emergency_stop_SM_reset_prv;

  outC->Emergency_stop_SM_state_sel = outC->Emergency_stop_SM_state_nxt;
  switch (outC->Emergency_stop_SM_state_sel) {
    case SSM_st_WaitForConfirmation_Emergency_stop_SM :
      outC->n_times_3_size = 50;
      break;
    default :
      /* this branch is empty */
      break;
  }
  Emergency_stop_SM_reset_prv = outC->Emergency_stop_SM_reset_act;
  switch (outC->Emergency_stop_SM_state_sel) {
    case SSM_st_WaitForConfirmation_Emergency_stop_SM :
      if (Emergency_stop_SM_reset_prv) {
        outC->init = kcg_true;
      }
      /* @1/_/v4= */
      if (outC->init) {
        outC->v4_times_3_size = outC->n_times_3_size;
      }
      else {
        outC->v4_times_3_size = outC->v3_times_3_size;
      }
      outC->c_times_3_size = kcg_true;
      /* @1/_/v3= */
      if (outC->v4_times_3_size < 0) {
        outC->v3_times_3_size = outC->v4_times_3_size;
      }
      else /* @1/_/v3= */
      if (outC->c_times_3_size) {
        outC->v3_times_3_size = outC->v4_times_3_size - 1;
      }
      else {
        outC->v3_times_3_size = outC->v4_times_3_size;
      }
      outC->o_times_3_size = outC->c_times_3_size & (outC->v3_times_3_size == 0);
      break;
    default :
      /* this branch is empty */
      break;
  }
  outC->_L9 = inC->US_FR;
  outC->_L6 = kcg_lit_float64(100.0);
  /* _L3=(checkThreshold#5)/ */
  checkThreshold(outC->_L9, outC->_L6, &outC->Context_checkThreshold_5);
  outC->_L3 = outC->Context_checkThreshold_5.Alarm;
  outC->_L16 = !outC->_L3;
  outC->_L8 = inC->US_FM;
  outC->_L5 = kcg_lit_float64(50.0);
  /* _L2=(checkThreshold#4)/ */
  checkThreshold(outC->_L8, outC->_L5, &outC->Context_checkThreshold_4);
  outC->_L2 = outC->Context_checkThreshold_4.Alarm;
  outC->_L15 = !outC->_L2;
  outC->_L7 = inC->US_FL;
  outC->_L4 = kcg_lit_float64(100.0);
  /* _L1=(checkThreshold#3)/ */
  checkThreshold(outC->_L7, outC->_L4, &outC->Context_checkThreshold_3);
  outC->_L1 = outC->Context_checkThreshold_3.Alarm;
  outC->_L14 = !outC->_L1;
  switch (outC->Emergency_stop_SM_state_sel) {
    case SSM_st_WaitForConfirmation_Emergency_stop_SM :
      tr_2_guard_WaitForConfirmation_Emergency_stop_SM = outC->o_times_3_size;
      break;
    default :
      /* this branch is empty */
      break;
  }
  outC->Obstacle_L = outC->_L14;
  outC->Obstacle_R = outC->_L16;
  outC->Obstacle_M = outC->_L15;
  /* Emergency_stop_SM: */
  switch (outC->Emergency_stop_SM_state_sel) {
    case SSM_st_WaitForConfirmation_Emergency_stop_SM :
      tr_1_guard_WaitForConfirmation_Emergency_stop_SM = !(outC->Obstacle_M |
          outC->Obstacle_R | outC->Obstacle_L);
      if (tr_1_guard_WaitForConfirmation_Emergency_stop_SM) {
        _12_Emergency_stop_SM_state_act_partial = SSM_st_IDLE_Emergency_stop_SM;
      }
      else if (tr_2_guard_WaitForConfirmation_Emergency_stop_SM) {
        _12_Emergency_stop_SM_state_act_partial = SSM_st_Stop_Emergency_stop_SM;
      }
      else {
        _12_Emergency_stop_SM_state_act_partial =
          SSM_st_WaitForConfirmation_Emergency_stop_SM;
      }
      outC->Emergency_stop_SM_state_act = _12_Emergency_stop_SM_state_act_partial;
      if (tr_1_guard_WaitForConfirmation_Emergency_stop_SM) {
        _14_Emergency_stop_SM_fired_strong_partial =
          SSM_TR_WaitForConfirmation_IDLE_1_WaitForConfirmation_Emergency_stop_SM;
      }
      else if (tr_2_guard_WaitForConfirmation_Emergency_stop_SM) {
        _14_Emergency_stop_SM_fired_strong_partial =
          SSM_TR_WaitForConfirmation_Stop_2_WaitForConfirmation_Emergency_stop_SM;
      }
      else {
        _14_Emergency_stop_SM_fired_strong_partial = SSM_TR_no_trans_Emergency_stop_SM;
      }
      outC->Emergency_stop_SM_fired_strong =
        _14_Emergency_stop_SM_fired_strong_partial;
      break;
    case SSM_st_Stop_Emergency_stop_SM :
      tr_1_guard_Stop_Emergency_stop_SM = !(outC->Obstacle_M |
          outC->Obstacle_R | outC->Obstacle_L);
      if (tr_1_guard_Stop_Emergency_stop_SM) {
        _9_Emergency_stop_SM_state_act_partial = SSM_st_IDLE_Emergency_stop_SM;
      }
      else {
        _9_Emergency_stop_SM_state_act_partial = SSM_st_Stop_Emergency_stop_SM;
      }
      outC->Emergency_stop_SM_state_act = _9_Emergency_stop_SM_state_act_partial;
      if (tr_1_guard_Stop_Emergency_stop_SM) {
        _11_Emergency_stop_SM_fired_strong_partial =
          SSM_TR_Stop_IDLE_1_Stop_Emergency_stop_SM;
      }
      else {
        _11_Emergency_stop_SM_fired_strong_partial = SSM_TR_no_trans_Emergency_stop_SM;
      }
      outC->Emergency_stop_SM_fired_strong =
        _11_Emergency_stop_SM_fired_strong_partial;
      break;
    case SSM_st_IDLE_Emergency_stop_SM :
      tr_1_guard_IDLE_Emergency_stop_SM = outC->Obstacle_M | outC->Obstacle_R |
        outC->Obstacle_L;
      if (tr_1_guard_IDLE_Emergency_stop_SM) {
        Emergency_stop_SM_state_act_partial =
          SSM_st_WaitForConfirmation_Emergency_stop_SM;
      }
      else {
        Emergency_stop_SM_state_act_partial = SSM_st_IDLE_Emergency_stop_SM;
      }
      outC->Emergency_stop_SM_state_act = Emergency_stop_SM_state_act_partial;
      if (tr_1_guard_IDLE_Emergency_stop_SM) {
        Emergency_stop_SM_fired_strong_partial =
          SSM_TR_IDLE_WaitForConfirmation_1_IDLE_Emergency_stop_SM;
      }
      else {
        Emergency_stop_SM_fired_strong_partial = SSM_TR_no_trans_Emergency_stop_SM;
      }
      outC->Emergency_stop_SM_fired_strong = Emergency_stop_SM_fired_strong_partial;
      break;
    default :
      /* this default branch is unreachable */
      break;
  }
  /* Emergency_stop_SM: */
  switch (outC->Emergency_stop_SM_state_act) {
    case SSM_st_WaitForConfirmation_Emergency_stop_SM :
      _8_Emergency_stop_SM_fired_partial = outC->Emergency_stop_SM_fired_strong;
      _7_Emergency_stop_SM_reset_nxt_partial = kcg_false;
      _6_Emergency_stop_SM_state_nxt_partial =
        SSM_st_WaitForConfirmation_Emergency_stop_SM;
      outC->_L2_WaitForConfirmation_Emergency_stop_SM = kcg_false;
      _5_Emergency_stop_partial = outC->_L2_WaitForConfirmation_Emergency_stop_SM;
      outC->Emergency_stop = _5_Emergency_stop_partial;
      outC->Emergency_stop_SM_state_nxt = _6_Emergency_stop_SM_state_nxt_partial;
      break;
    case SSM_st_Stop_Emergency_stop_SM :
      _4_Emergency_stop_SM_fired_partial = outC->Emergency_stop_SM_fired_strong;
      _3_Emergency_stop_SM_reset_nxt_partial = kcg_false;
      _2_Emergency_stop_SM_state_nxt_partial = SSM_st_Stop_Emergency_stop_SM;
      outC->_L1_Stop_Emergency_stop_SM = kcg_true;
      _1_Emergency_stop_partial = outC->_L1_Stop_Emergency_stop_SM;
      outC->Emergency_stop = _1_Emergency_stop_partial;
      outC->Emergency_stop_SM_state_nxt = _2_Emergency_stop_SM_state_nxt_partial;
      break;
    case SSM_st_IDLE_Emergency_stop_SM :
      Emergency_stop_SM_fired_partial = outC->Emergency_stop_SM_fired_strong;
      Emergency_stop_SM_reset_nxt_partial = kcg_false;
      Emergency_stop_SM_state_nxt_partial = SSM_st_IDLE_Emergency_stop_SM;
      outC->_L1_IDLE_Emergency_stop_SM = kcg_false;
      Emergency_stop_partial = outC->_L1_IDLE_Emergency_stop_SM;
      outC->Emergency_stop = Emergency_stop_partial;
      outC->Emergency_stop_SM_state_nxt = Emergency_stop_SM_state_nxt_partial;
      break;
    default :
      /* this default branch is unreachable */
      break;
  }
  Emergency_stop_SM_reset_sel = outC->Emergency_stop_SM_reset_nxt;
  /* Emergency_stop_SM: */
  switch (outC->Emergency_stop_SM_state_act) {
    case SSM_st_WaitForConfirmation_Emergency_stop_SM :
      outC->Emergency_stop_SM_reset_nxt = _7_Emergency_stop_SM_reset_nxt_partial;
      outC->Emergency_stop_SM_fired = _8_Emergency_stop_SM_fired_partial;
      break;
    case SSM_st_Stop_Emergency_stop_SM :
      outC->Emergency_stop_SM_reset_nxt = _3_Emergency_stop_SM_reset_nxt_partial;
      outC->Emergency_stop_SM_fired = _4_Emergency_stop_SM_fired_partial;
      break;
    case SSM_st_IDLE_Emergency_stop_SM :
      outC->Emergency_stop_SM_reset_nxt = Emergency_stop_SM_reset_nxt_partial;
      outC->Emergency_stop_SM_fired = Emergency_stop_SM_fired_partial;
      break;
    default :
      /* this default branch is unreachable */
      break;
  }
  /* Emergency_stop_SM: */
  switch (outC->Emergency_stop_SM_state_sel) {
    case SSM_st_WaitForConfirmation_Emergency_stop_SM :
      if (tr_1_guard_WaitForConfirmation_Emergency_stop_SM) {
        _13_Emergency_stop_SM_reset_act_partial = kcg_true;
      }
      else {
        _13_Emergency_stop_SM_reset_act_partial =
          tr_2_guard_WaitForConfirmation_Emergency_stop_SM;
      }
      outC->Emergency_stop_SM_reset_act = _13_Emergency_stop_SM_reset_act_partial;
      outC->init = kcg_false;
      break;
    case SSM_st_Stop_Emergency_stop_SM :
      _10_Emergency_stop_SM_reset_act_partial = tr_1_guard_Stop_Emergency_stop_SM;
      outC->Emergency_stop_SM_reset_act = _10_Emergency_stop_SM_reset_act_partial;
      break;
    case SSM_st_IDLE_Emergency_stop_SM :
      Emergency_stop_SM_reset_act_partial = tr_1_guard_IDLE_Emergency_stop_SM;
      outC->Emergency_stop_SM_reset_act = Emergency_stop_SM_reset_act_partial;
      break;
    default :
      /* this default branch is unreachable */
      break;
  }
}

#ifndef KCG_USER_DEFINED_INIT
void US_handler_init(outC_US_handler *outC)
{
  outC->_L16 = kcg_true;
  outC->_L15 = kcg_true;
  outC->_L14 = kcg_true;
  outC->_L9 = kcg_lit_float64(0.0);
  outC->_L8 = kcg_lit_float64(0.0);
  outC->_L7 = kcg_lit_float64(0.0);
  outC->_L6 = kcg_lit_float64(0.0);
  outC->_L5 = kcg_lit_float64(0.0);
  outC->_L4 = kcg_lit_float64(0.0);
  outC->_L3 = kcg_true;
  outC->_L2 = kcg_true;
  outC->_L1 = kcg_true;
  outC->Obstacle_R = kcg_true;
  outC->Obstacle_M = kcg_true;
  outC->Obstacle_L = kcg_true;
  outC->Emergency_stop_SM_fired = SSM_TR_no_trans_Emergency_stop_SM;
  outC->Emergency_stop_SM_fired_strong = SSM_TR_no_trans_Emergency_stop_SM;
  outC->Emergency_stop_SM_state_act = SSM_st_IDLE_Emergency_stop_SM;
  outC->Emergency_stop_SM_state_sel = SSM_st_IDLE_Emergency_stop_SM;
  outC->_L2_WaitForConfirmation_Emergency_stop_SM = kcg_true;
  outC->_L1_Stop_Emergency_stop_SM = kcg_true;
  outC->_L1_IDLE_Emergency_stop_SM = kcg_true;
  outC->v4_times_3_size = 0;
  outC->n_times_3_size = 0;
  outC->c_times_3_size = kcg_true;
  outC->o_times_3_size = kcg_true;
  outC->v3_times_3_size = 0;
  outC->init = kcg_true;
  outC->Emergency_stop = kcg_true;
  /* _L1=(checkThreshold#3)/ */
  checkThreshold_init(&outC->Context_checkThreshold_3);
  /* _L2=(checkThreshold#4)/ */
  checkThreshold_init(&outC->Context_checkThreshold_4);
  /* _L3=(checkThreshold#5)/ */
  checkThreshold_init(&outC->Context_checkThreshold_5);
  outC->Emergency_stop_SM_reset_nxt = kcg_false;
  outC->Emergency_stop_SM_reset_act = kcg_false;
  outC->Emergency_stop_SM_state_nxt = SSM_st_IDLE_Emergency_stop_SM;
}
#endif /* KCG_USER_DEFINED_INIT */


#ifndef KCG_NO_EXTERN_CALL_TO_RESET
void US_handler_reset(outC_US_handler *outC)
{
  outC->init = kcg_true;
  /* _L1=(checkThreshold#3)/ */
  checkThreshold_reset(&outC->Context_checkThreshold_3);
  /* _L2=(checkThreshold#4)/ */
  checkThreshold_reset(&outC->Context_checkThreshold_4);
  /* _L3=(checkThreshold#5)/ */
  checkThreshold_reset(&outC->Context_checkThreshold_5);
  outC->Emergency_stop_SM_reset_nxt = kcg_false;
  outC->Emergency_stop_SM_reset_act = kcg_false;
  outC->Emergency_stop_SM_state_nxt = SSM_st_IDLE_Emergency_stop_SM;
}
#endif /* KCG_NO_EXTERN_CALL_TO_RESET */

/*
  Expanded instances for: US_handler/
  @1: (times#3)
*/

/* $********** SCADE Suite KCG 32-bit 6.6 (build i19) ***********
** US_handler.c
** Generation date: 2018-01-18T09:58:59
*************************************************************$ */

