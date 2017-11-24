/**
 * @file    tim.c
 * @author  Curtis Team
 * @brief   Functions to handle Timers  
*/
 
/* Includes ------------------------------------------------------------------*/
#include "tim.h"
#include "common_constants.h"
#include "gpio.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/**
 * @brief     Max Value of Prescaler register in STM32
*/
#define PSC_VALUE_MAX ((uint16_t)UINT16_MAX) // CK_CNT ~ 1.1kHz

/**
 * @brief     Max Value of Autoreload register in STM32
*/
#define ARR_VALUE_MAX ((uint16_t)UINT16_MAX)

/**
 * @brief    Prescaler ceiling limit
*/
#define PSC_CEILING_LIMIT 1.0e-6

/**
 * @brief    Remap set when timer is initialized for the firs time
*/
#define DEFAULT_REMAP DefaultRemap

/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/**
 * @brief    Remap status of the timers
*/
TIM_remap_TypeDef RemapTimersStatus [TIM_MAX_NUMBER];

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void RCC_timer_configuration(TIM_TypeDef *timer);

/* Public functions ----------------------------------------------------------*/
/**
 * @brief     Makes the initialization of the given Timer with the parameter specified
 * @param   TIMx Timer to use
 * @param   PeriodUs Period (in µs) expected for the Timer
*/
void TIM_QuickInit(TIM_TypeDef *TIMx, float PeriodUs) {
   volatile const float fclock = (float)SystemCoreClock;
   const float frequency_ratio = fclock * PeriodUs / US_PER_S;
   float    PSC_val_f, ARR_val_f;
   uint16_t PSC_val  , ARR_val;
   volatile float aux;
   
   TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
   
   // Active la clock
   RCC_timer_configuration(TIMx);

   // PSC conf
   PSC_val_f = frequency_ratio / ((float)ARR_VALUE_MAX + 1.0) - 1.0;
   PSC_val = (uint16_t)PSC_val_f;                                    // floor
   if((PSC_val_f - (float)PSC_val) > PSC_CEILING_LIMIT) PSC_val++;   // ceiling
   if(PSC_val_f > PSC_VALUE_MAX) PSC_val = PSC_VALUE_MAX;            // saturation
  
   // ARR conf
   ARR_val_f = frequency_ratio / ((float)PSC_val + 1.0) - 1.0;
   ARR_val = (uint16_t)ARR_val_f;                           // floor
   if(ARR_val_f > ARR_VALUE_MAX) ARR_val = ARR_VALUE_MAX;   // saturation
   
  // set everything back to default values
  TIM_TimeBaseStructInit (&TIM_TimeBaseStructure);
  // only changes from the defaults are needed
  TIM_TimeBaseStructure.TIM_Period = ARR_val;
  TIM_TimeBaseStructure.TIM_Prescaler = PSC_val;
  TIM_TimeBaseInit (TIMx, &TIM_TimeBaseStructure);
  
  // Set remapping variables
  if (TIMx == TIM1) RemapTimersStatus[0] = DEFAULT_REMAP;
  if (TIMx == TIM2) RemapTimersStatus[1] = DEFAULT_REMAP;
  if (TIMx == TIM3) RemapTimersStatus[2] = DEFAULT_REMAP;
  if (TIMx == TIM4) RemapTimersStatus[3] = DEFAULT_REMAP;
}

/**
 * @brief   Enables specified timer
 * @param   TIMx Timer to be used  
 * @return  void
*/
void TIM_Start(TIM_TypeDef *TIMx){
  TIM_Cmd(TIMx, ENABLE);
}
 
/**
 * @brief   Disables specified timer
 * @param   TIMx Timer to be used  
 * @retval  None
*/
void TIM_Stop(TIM_TypeDef *TIMx){
  TIM_Cmd (TIMx, DISABLE);
}

/**
 * @brief   Remaps given timer according to remap type chosen
 * @param   TIMx Timer to remap 
 * @param   RemapType Type of the remap expected
 * @retval  0 if everything went right, -1 if not (unexpected remap type according to chosen Timer)
*/
int TIM_Remap(TIM_TypeDef *TIMx, TIM_remap_TypeDef RemapType) {
    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);
    RemapTimersStatus[0] = RemapType;
//    if (&TIMx == TIM1) {
//        if (RemapType == DefaultRemap)  
//            GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, DISABLE); 
//        if (RemapType == PartialRemap1) 
//            GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);
//        if (RemapType == PartialRemap2) 
//            return -1;
//        if (RemapType == FullRemap)     
//            GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);
//        
//        RemapTimersStatus[0] = RemapType;
//    }
//    else if (&TIMx == TIM2) {
//        if (RemapType == DefaultRemap)  GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, DISABLE); 
//        if (RemapType == PartialRemap1) GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);
//        if (RemapType == PartialRemap2) GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2, ENABLE);
//        if (RemapType == FullRemap)     GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);
//        
//        RemapTimersStatus[1] = RemapType;
//    }
//    else if (&TIMx == TIM3) {
//        if (RemapType == DefaultRemap)  GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, DISABLE); 
//        if (RemapType == PartialRemap1) GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);
//        if (RemapType == PartialRemap2) return -1;
//        if (RemapType == FullRemap)     GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);
//        
//        RemapTimersStatus[2] = RemapType;
//    }
//    else if (&TIMx == TIM4) {
//        if (RemapType == DefaultRemap)  GPIO_PinRemapConfig(GPIO_Remap_TIM4, DISABLE); 
//        if (RemapType == PartialRemap1) return -1;
//        if (RemapType == PartialRemap2) return -1;
//        if (RemapType == FullRemap)     GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);
//        
//        RemapTimersStatus[3] = RemapType;
//    }
//    else{}
//        
    return 0;
}

/**
 * @brief   Returns the remapping status of the given Timer
 * @param   TIMx Timer to examine 
 * @retval  Remap status of the Timer given as parameter
*/
TIM_remap_TypeDef TIM_RemapStatus(TIM_TypeDef *TIMx) {
            if (TIMx == TIM1) return RemapTimersStatus[0];
    else    if (TIMx == TIM2) return RemapTimersStatus[1];
    else    if (TIMx == TIM3) return RemapTimersStatus[2];
    else    if (TIMx == TIM4) return RemapTimersStatus[3];
    else return ErrorRemap;
}

__weak void TIM_Callback(TIM_TypeDef TIMx) {}

/* Private functions ---------------------------------------------------------*/
/**
 * @brief   Configures the different system clocks.
 * @param   None
 * @retval  None
*/
void RCC_timer_configuration(TIM_TypeDef *TIMx) {
       if (TIMx == TIM1)  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
  else if (TIMx == TIM2)  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  else if (TIMx == TIM3)  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  else if (TIMx == TIM4)  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
}

void TIM_ITHandler(TIM_TypeDef TIMx) {
    TIM_Callback(TIMx);
}
