/* GeoCar_US_mapping.c */

#include "GeoCar_US_type.h"
#include "GeoCar_US_interface.h"
#include "GeoCar_US_mapping.h"

#include "SmuTypes.h"
#include "SmuMapping.h"

#include "kcg_sensors.h"

/* mapping declaration */

#define DECL_ITER(name) extern const MappingIterator iter_##name


#define DECL_SCOPE(name, count) extern const MappingEntry name##_entries[count]; extern const MappingScope name

DECL_SCOPE(scope_10, 1);
DECL_SCOPE(scope_9, 1);
DECL_SCOPE(scope_8, 3);
DECL_SCOPE(scope_7, 1);
DECL_SCOPE(scope_6, 2);
DECL_SCOPE(scope_5, 1);
DECL_SCOPE(scope_4, 2);
DECL_SCOPE(scope_3, 10);
DECL_SCOPE(scope_2, 4);
DECL_SCOPE(scope_1, 23);
DECL_SCOPE(scope_0, 1);

/* clock definition */

static int isActive_SSM_ST_Emergency_stop_SM_SSM_st_IDLE_Emergency_stop_SM(void* pHandle) { return *(SSM_ST_Emergency_stop_SM*)pHandle == SSM_st_IDLE_Emergency_stop_SM; }
static int isActive_SSM_ST_Emergency_stop_SM_SSM_st_Stop_Emergency_stop_SM(void* pHandle) { return *(SSM_ST_Emergency_stop_SM*)pHandle == SSM_st_Stop_Emergency_stop_SM; }
static int isActive_SSM_ST_Emergency_stop_SM_SSM_st_WaitForConfirmation_Emergency_stop_SM(void* pHandle) { return *(SSM_ST_Emergency_stop_SM*)pHandle == SSM_st_WaitForConfirmation_Emergency_stop_SM; }
static int isActive_SSM_TR_Emergency_stop_SM_SSM_TR_IDLE_WaitForConfirmation_1_IDLE_Emergency_stop_SM(void* pHandle) { return *(SSM_TR_Emergency_stop_SM*)pHandle == SSM_TR_IDLE_WaitForConfirmation_1_IDLE_Emergency_stop_SM; }
static int isActive_SSM_TR_Emergency_stop_SM_SSM_TR_Stop_IDLE_1_Stop_Emergency_stop_SM(void* pHandle) { return *(SSM_TR_Emergency_stop_SM*)pHandle == SSM_TR_Stop_IDLE_1_Stop_Emergency_stop_SM; }
static int isActive_SSM_TR_Emergency_stop_SM_SSM_TR_WaitForConfirmation_IDLE_1_WaitForConfirmation_Emergency_stop_SM(void* pHandle) { return *(SSM_TR_Emergency_stop_SM*)pHandle == SSM_TR_WaitForConfirmation_IDLE_1_WaitForConfirmation_Emergency_stop_SM; }
static int isActive_SSM_TR_Emergency_stop_SM_SSM_TR_WaitForConfirmation_Stop_2_WaitForConfirmation_Emergency_stop_SM(void* pHandle) { return *(SSM_TR_Emergency_stop_SM*)pHandle == SSM_TR_WaitForConfirmation_Stop_2_WaitForConfirmation_Emergency_stop_SM; }

/* mapping definition */


const MappingEntry scope_10_entries[1] = {
    /* 0 */ { MAP_STRONG_TRANSITION, ">:", NULL, 0, 0, NULL, &scope_3_entries[5], isActive_SSM_TR_Emergency_stop_SM_SSM_TR_WaitForConfirmation_Stop_2_WaitForConfirmation_Emergency_stop_SM, NULL, 1, 0 }
};
const MappingScope scope_10 = {
    "US_handler/ US_handlerEmergency_stop_SM:WaitForConfirmation:<2",
    scope_10_entries, 1
};

const MappingEntry scope_9_entries[1] = {
    /* 0 */ { MAP_STRONG_TRANSITION, ">:", NULL, 0, 0, NULL, &scope_3_entries[5], isActive_SSM_TR_Emergency_stop_SM_SSM_TR_WaitForConfirmation_IDLE_1_WaitForConfirmation_Emergency_stop_SM, NULL, 1, 0 }
};
const MappingScope scope_9 = {
    "US_handler/ US_handlerEmergency_stop_SM:WaitForConfirmation:<1",
    scope_9_entries, 1
};

const MappingEntry scope_8_entries[3] = {
    /* 0 */ { MAP_FORK, "<1", NULL, 0, 0, NULL, &scope_3_entries[5], isActive_SSM_TR_Emergency_stop_SM_SSM_TR_WaitForConfirmation_IDLE_1_WaitForConfirmation_Emergency_stop_SM, &scope_9, 1, 0 },
    /* 1 */ { MAP_FORK, "<2", NULL, 0, 0, NULL, &scope_3_entries[5], isActive_SSM_TR_Emergency_stop_SM_SSM_TR_WaitForConfirmation_Stop_2_WaitForConfirmation_Emergency_stop_SM, &scope_10, 1, 1 },
    /* 2 */ { MAP_LOCAL, "_L2", NULL, sizeof(kcg_bool), (size_t)&outputs_ctx._L2_WaitForConfirmation_Emergency_stop_SM, &_Type_kcg_bool_Utils, &scope_3_entries[0], isActive_SSM_ST_Emergency_stop_SM_SSM_st_WaitForConfirmation_Emergency_stop_SM, NULL, 1, 2 }
};
const MappingScope scope_8 = {
    "US_handler/ US_handlerEmergency_stop_SM:WaitForConfirmation:",
    scope_8_entries, 3
};

const MappingEntry scope_7_entries[1] = {
    /* 0 */ { MAP_STRONG_TRANSITION, ">:", NULL, 0, 0, NULL, &scope_3_entries[5], isActive_SSM_TR_Emergency_stop_SM_SSM_TR_Stop_IDLE_1_Stop_Emergency_stop_SM, NULL, 1, 0 }
};
const MappingScope scope_7 = {
    "US_handler/ US_handlerEmergency_stop_SM:Stop:<1",
    scope_7_entries, 1
};

const MappingEntry scope_6_entries[2] = {
    /* 0 */ { MAP_FORK, "<1", NULL, 0, 0, NULL, &scope_3_entries[5], isActive_SSM_TR_Emergency_stop_SM_SSM_TR_Stop_IDLE_1_Stop_Emergency_stop_SM, &scope_7, 1, 0 },
    /* 1 */ { MAP_LOCAL, "_L1", NULL, sizeof(kcg_bool), (size_t)&outputs_ctx._L1_Stop_Emergency_stop_SM, &_Type_kcg_bool_Utils, &scope_3_entries[0], isActive_SSM_ST_Emergency_stop_SM_SSM_st_Stop_Emergency_stop_SM, NULL, 1, 1 }
};
const MappingScope scope_6 = {
    "US_handler/ US_handlerEmergency_stop_SM:Stop:",
    scope_6_entries, 2
};

const MappingEntry scope_5_entries[1] = {
    /* 0 */ { MAP_STRONG_TRANSITION, ">:", NULL, 0, 0, NULL, &scope_3_entries[5], isActive_SSM_TR_Emergency_stop_SM_SSM_TR_IDLE_WaitForConfirmation_1_IDLE_Emergency_stop_SM, NULL, 1, 0 }
};
const MappingScope scope_5 = {
    "US_handler/ US_handlerEmergency_stop_SM:IDLE:<1",
    scope_5_entries, 1
};

const MappingEntry scope_4_entries[2] = {
    /* 0 */ { MAP_FORK, "<1", NULL, 0, 0, NULL, &scope_3_entries[5], isActive_SSM_TR_Emergency_stop_SM_SSM_TR_IDLE_WaitForConfirmation_1_IDLE_Emergency_stop_SM, &scope_5, 1, 0 },
    /* 1 */ { MAP_LOCAL, "_L1", NULL, sizeof(kcg_bool), (size_t)&outputs_ctx._L1_IDLE_Emergency_stop_SM, &_Type_kcg_bool_Utils, &scope_3_entries[0], isActive_SSM_ST_Emergency_stop_SM_SSM_st_IDLE_Emergency_stop_SM, NULL, 1, 1 }
};
const MappingScope scope_4 = {
    "US_handler/ US_handlerEmergency_stop_SM:IDLE:",
    scope_4_entries, 2
};

const MappingEntry scope_3_entries[10] = {
    /* 0 */ { MAP_LOCAL, "@active_state", NULL, sizeof(SSM_ST_Emergency_stop_SM), (size_t)&outputs_ctx.Emergency_stop_SM_state_act, &_Type_SSM_ST_Emergency_stop_SM_Utils, NULL, NULL, NULL, 0, 0 },
    /* 1 */ { MAP_LOCAL, "@reset_active_state", NULL, sizeof(kcg_bool), (size_t)&outputs_ctx.Emergency_stop_SM_reset_act, &_Type_kcg_bool_Utils, NULL, NULL, NULL, 0, 1 },
    /* 2 */ { MAP_LOCAL, "@next_state", NULL, sizeof(SSM_ST_Emergency_stop_SM), (size_t)&outputs_ctx.Emergency_stop_SM_state_nxt, &_Type_SSM_ST_Emergency_stop_SM_Utils, NULL, NULL, NULL, 0, 2 },
    /* 3 */ { MAP_LOCAL, "@reset_next_state", NULL, sizeof(kcg_bool), (size_t)&outputs_ctx.Emergency_stop_SM_reset_nxt, &_Type_kcg_bool_Utils, NULL, NULL, NULL, 0, 3 },
    /* 4 */ { MAP_LOCAL, "@selected_state", NULL, sizeof(SSM_ST_Emergency_stop_SM), (size_t)&outputs_ctx.Emergency_stop_SM_state_sel, &_Type_SSM_ST_Emergency_stop_SM_Utils, NULL, NULL, NULL, 0, 4 },
    /* 5 */ { MAP_LOCAL, "@active_strong_transition", NULL, sizeof(SSM_TR_Emergency_stop_SM), (size_t)&outputs_ctx.Emergency_stop_SM_fired_strong, &_Type_SSM_TR_Emergency_stop_SM_Utils, NULL, NULL, NULL, 0, 5 },
    /* 6 */ { MAP_LOCAL, "@active_weak_transition", NULL, sizeof(SSM_TR_Emergency_stop_SM), (size_t)&outputs_ctx.Emergency_stop_SM_fired, &_Type_SSM_TR_Emergency_stop_SM_Utils, NULL, NULL, NULL, 0, 6 },
    /* 7 */ { MAP_STATE, "IDLE:", NULL, 0, 0, NULL, &scope_3_entries[0], isActive_SSM_ST_Emergency_stop_SM_SSM_st_IDLE_Emergency_stop_SM, &scope_4, 1, 7 },
    /* 8 */ { MAP_STATE, "Stop:", NULL, 0, 0, NULL, &scope_3_entries[0], isActive_SSM_ST_Emergency_stop_SM_SSM_st_Stop_Emergency_stop_SM, &scope_6, 1, 8 },
    /* 9 */ { MAP_STATE, "WaitForConfirmation:", NULL, 0, 0, NULL, &scope_3_entries[0], isActive_SSM_ST_Emergency_stop_SM_SSM_st_WaitForConfirmation_Emergency_stop_SM, &scope_8, 1, 9 }
};
const MappingScope scope_3 = {
    "US_handler/ US_handlerEmergency_stop_SM:",
    scope_3_entries, 10
};

const MappingEntry scope_2_entries[4] = {
    /* 0 */ { MAP_OUTPUT, "Alarm", NULL, sizeof(kcg_bool), offsetof(outC_checkThreshold, Alarm), &_Type_kcg_bool_Utils, NULL, NULL, NULL, 1, 0 },
    /* 1 */ { MAP_LOCAL, "_L1", NULL, sizeof(kcg_bool), offsetof(outC_checkThreshold, _L1), &_Type_kcg_bool_Utils, NULL, NULL, NULL, 1, 1 },
    /* 2 */ { MAP_LOCAL, "_L2", NULL, sizeof(kcg_float64), offsetof(outC_checkThreshold, _L2), &_Type_kcg_float64_Utils, NULL, NULL, NULL, 1, 2 },
    /* 3 */ { MAP_LOCAL, "_L3", NULL, sizeof(kcg_float64), offsetof(outC_checkThreshold, _L3), &_Type_kcg_float64_Utils, NULL, NULL, NULL, 1, 3 }
};
const MappingScope scope_2 = {
    "checkThreshold/ checkThreshold",
    scope_2_entries, 4
};

const MappingEntry scope_1_entries[23] = {
    /* 0 */ { MAP_OUTPUT, "Emergency_stop", NULL, sizeof(kcg_bool), (size_t)&outputs_ctx.Emergency_stop, &_Type_kcg_bool_Utils, NULL, NULL, NULL, 1, 0 },
    /* 1 */ { MAP_INPUT, "US_FL", NULL, sizeof(kcg_float64), (size_t)&inputs_ctx.US_FL, &_Type_kcg_float64_Utils, NULL, NULL, NULL, 1, 1 },
    /* 2 */ { MAP_INPUT, "US_FM", NULL, sizeof(kcg_float64), (size_t)&inputs_ctx.US_FM, &_Type_kcg_float64_Utils, NULL, NULL, NULL, 1, 2 },
    /* 3 */ { MAP_INPUT, "US_FR", NULL, sizeof(kcg_float64), (size_t)&inputs_ctx.US_FR, &_Type_kcg_float64_Utils, NULL, NULL, NULL, 1, 3 },
    /* 4 */ { MAP_LOCAL, "Obstacle_L", NULL, sizeof(kcg_bool), (size_t)&outputs_ctx.Obstacle_L, &_Type_kcg_bool_Utils, NULL, NULL, NULL, 1, 4 },
    /* 5 */ { MAP_LOCAL, "Obstacle_M", NULL, sizeof(kcg_bool), (size_t)&outputs_ctx.Obstacle_M, &_Type_kcg_bool_Utils, NULL, NULL, NULL, 1, 5 },
    /* 6 */ { MAP_LOCAL, "Obstacle_R", NULL, sizeof(kcg_bool), (size_t)&outputs_ctx.Obstacle_R, &_Type_kcg_bool_Utils, NULL, NULL, NULL, 1, 6 },
    /* 7 */ { MAP_LOCAL, "_L1", NULL, sizeof(kcg_bool), (size_t)&outputs_ctx._L1, &_Type_kcg_bool_Utils, NULL, NULL, NULL, 1, 7 },
    /* 8 */ { MAP_LOCAL, "_L2", NULL, sizeof(kcg_bool), (size_t)&outputs_ctx._L2, &_Type_kcg_bool_Utils, NULL, NULL, NULL, 1, 8 },
    /* 9 */ { MAP_LOCAL, "_L3", NULL, sizeof(kcg_bool), (size_t)&outputs_ctx._L3, &_Type_kcg_bool_Utils, NULL, NULL, NULL, 1, 9 },
    /* 10 */ { MAP_LOCAL, "_L4", NULL, sizeof(kcg_float64), (size_t)&outputs_ctx._L4, &_Type_kcg_float64_Utils, NULL, NULL, NULL, 1, 10 },
    /* 11 */ { MAP_LOCAL, "_L5", NULL, sizeof(kcg_float64), (size_t)&outputs_ctx._L5, &_Type_kcg_float64_Utils, NULL, NULL, NULL, 1, 11 },
    /* 12 */ { MAP_LOCAL, "_L6", NULL, sizeof(kcg_float64), (size_t)&outputs_ctx._L6, &_Type_kcg_float64_Utils, NULL, NULL, NULL, 1, 12 },
    /* 13 */ { MAP_LOCAL, "_L7", NULL, sizeof(kcg_float64), (size_t)&outputs_ctx._L7, &_Type_kcg_float64_Utils, NULL, NULL, NULL, 1, 13 },
    /* 14 */ { MAP_LOCAL, "_L8", NULL, sizeof(kcg_float64), (size_t)&outputs_ctx._L8, &_Type_kcg_float64_Utils, NULL, NULL, NULL, 1, 14 },
    /* 15 */ { MAP_LOCAL, "_L9", NULL, sizeof(kcg_float64), (size_t)&outputs_ctx._L9, &_Type_kcg_float64_Utils, NULL, NULL, NULL, 1, 15 },
    /* 16 */ { MAP_LOCAL, "_L14", NULL, sizeof(kcg_bool), (size_t)&outputs_ctx._L14, &_Type_kcg_bool_Utils, NULL, NULL, NULL, 1, 16 },
    /* 17 */ { MAP_LOCAL, "_L15", NULL, sizeof(kcg_bool), (size_t)&outputs_ctx._L15, &_Type_kcg_bool_Utils, NULL, NULL, NULL, 1, 17 },
    /* 18 */ { MAP_LOCAL, "_L16", NULL, sizeof(kcg_bool), (size_t)&outputs_ctx._L16, &_Type_kcg_bool_Utils, NULL, NULL, NULL, 1, 18 },
    /* 19 */ { MAP_INSTANCE, "checkThreshold 3", NULL, sizeof(outC_checkThreshold), (size_t)&outputs_ctx.Context_checkThreshold_3, NULL, NULL, NULL, &scope_2, 1, 19 },
    /* 20 */ { MAP_INSTANCE, "checkThreshold 4", NULL, sizeof(outC_checkThreshold), (size_t)&outputs_ctx.Context_checkThreshold_4, NULL, NULL, NULL, &scope_2, 1, 20 },
    /* 21 */ { MAP_INSTANCE, "checkThreshold 5", NULL, sizeof(outC_checkThreshold), (size_t)&outputs_ctx.Context_checkThreshold_5, NULL, NULL, NULL, &scope_2, 1, 21 },
    /* 22 */ { MAP_AUTOMATON, "Emergency_stop_SM:", NULL, 0, 0, NULL, NULL, NULL, &scope_3, 1, 22 }
};
const MappingScope scope_1 = {
    "US_handler/ US_handler",
    scope_1_entries, 23
};

const MappingEntry scope_0_entries[1] = {
    /* 0 */ { MAP_ROOT, "US_handler", NULL, 0, 0, NULL, NULL, NULL, &scope_1, 1, 0 }
};
const MappingScope scope_0 = {
    "",
    scope_0_entries, 1
};

/* entry point */
const MappingScope* pTop = &scope_0;
