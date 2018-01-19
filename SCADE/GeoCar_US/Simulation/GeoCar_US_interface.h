#ifndef GEOCAR_US_INTERFACE_H_
#define GEOCAR_US_INTERFACE_H_

#include "kcg_types.h"
#include "kcg_sensors.h"
#include "SmuProxy.h"
#include "US_handler.h"

#ifdef __cplusplus
extern "C" {
#endif

extern SimSimulator * pSimulator;

/* context */

extern inC_US_handler inputs_ctx;
extern outC_US_handler outputs_ctx;

/* simulation */

#ifdef EXTENDED_SIM
    void BeforeSimInit();
    void AfterSimInit();
    void BeforeSimStep();
    void AfterSimStep();
    void ExtendedSimStop();
    void ExtendedGatherDumpData(char * pData);
    void ExtendedRestoreDumpData(const char * pData);
    int ExtendedGetDumpSize();
    void UpdateValues();
    extern void UpdateSimulatorValues();
    extern int GraphicalInputsConnected;
#endif

/* logging */

#define SIM_INFO    1
#define SIM_WARNING 2
#define SIM_ERROR   3
extern void SsmOutputMessage(int level, const char* str);

#ifdef __cplusplus
} /* "C" */
#endif

#endif /* GEOCAR_US_INTERFACE_H_ */
