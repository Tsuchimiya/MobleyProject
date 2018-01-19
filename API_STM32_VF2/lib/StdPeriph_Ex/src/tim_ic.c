/**
 * @file 	tim_ic.c
 * @author  Curtis Team
 * @brief 	Functions to handle timers input capture
*/

/* Includes ------------------------------------------------------------------*/
#include "tim_ic.h"
#include "common_constants.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
/**
 * @brief   Makes the initialization of the TIM_IC with the parameters specified
 * @param   TIMx Timer to use
 * @param   Channelx Channel to use
 * @retval  none
*/
void TIM_IC_QuickInit(TIM_TypeDef *TIMx, uint16_t Channelx, float FrequencyCompareHz) {
    float DureeCompareUsec = US_PER_S/FrequencyCompareHz;
    
    TIM_ICInitTypeDef  TIM_ICInitStructure;

    TIM_QuickInit(TIMx, DureeCompareUsec);

    TIM_ICInitStructure.TIM_Channel = Channelx;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICFilter = 0x0;

    TIM_ICInit(TIMx, &TIM_ICInitStructure);
}

/**
 * @brief   Enables capture on specified timer
 * @param   TIMx Timer to be used  
 * @return  void
*/
void TIM_IC_Start(TIM_TypeDef *TIMx){
   TIM_Start(TIMx); 
}

/**
 * @brief   Enables capture on specified timer
 * @param   TIMx Timer to be used  
 * @return  void
*/
void TIM_IC_Stop(TIM_TypeDef *TIMx){
   TIM_Stop(TIMx); 
}
/* Private functions ---------------------------------------------------------*/
