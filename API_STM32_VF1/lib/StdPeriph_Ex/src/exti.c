/**
 * @file    exti.c
 * @author  Curtis Team
 * @brief   Functions to handle external interrupts (EXTI)  
 */

/* Includes ------------------------------------------------------------------*/
#include "exti.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/**
 * @brief     Secified line is not valid (it is not allowed to specify various lines at one time) 
*/ 
#define ERROR_LINE_UNREACHABLE   (uint16_t) -1

/**
 * @brief     Parameter given to compute Channel is invalid
*/ 
#define ERROR_COMPUTING_CHANNEL  (uint8_t) -1

/**
 * @brief     GPIOMode_TypeDef recommended to initialize GPIO for EXTI
*/ 
#define GPIO_MODE_EXTI           GPIO_Mode_IPU

/**
 * @brief     Specified port cannot be found
*/ 
#define ERROR_PORT_SOURCE         (uint8_t) -1

/**
 * @brief     Specified pin cannot be found
*/ 
#define ERROR_PIN_SOURCE             (uint16_t) -1

/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
uint32_t GPIO_Pin_to_EXTI_Line(uint16_t pin);
uint8_t Line_to_IRQn(uint32_t Line);
uint8_t GPIO_TypeDef_to_GPIO_PortSource (GPIO_TypeDef *GPIO);
uint16_t GPIO_Pin_to_GPIO_PinSource (uint16_t GPIO_Pin);


/* Public functions ----------------------------------------------------------*/
/**
 * @brief     Makes the initialization of the given external interrupt (EXTI) with the parameters specified
 * @param     GPIOx Port of the EXTI
 * @param     pin Number of the pin of the EXTI
 * @param     trigger Way to trigg this EXTI
 * @param     priority Priority of the exti to initialize
 * @retval    int (error detected while computing initialization)
 * @return    If everything went right EXTI_NO_ERROR, if not EXTI_ERROR_INVALID_LINE, EXTI_ERROR_INVALID_CHANNEL, EXTI_ERROR_INVALID_PORT_SOURCE or EXTI_ERROR_INVALID_PIN_SOURCE.
 */
int EXTI_QuickInit(GPIO_TypeDef *GPIOx, uint16_t pin, EXTITrigger_TypeDef trigger, uint8_t priority) {

    EXTI_InitTypeDef EXTI_InitStruct;

    uint32_t Line_Number = GPIO_Pin_to_EXTI_Line(pin); 
    uint8_t IRQChannel = Line_to_IRQn(Line_Number);
    uint8_t GPIO_PortSource = GPIO_TypeDef_to_GPIO_PortSource(GPIOx);
    uint16_t GPIO_PinSource = GPIO_Pin_to_GPIO_PinSource(pin);
    
    if (Line_Number == ERROR_LINE_UNREACHABLE) return EXTI_ERROR_INVALID_LINE; else {}
    if (IRQChannel == ERROR_COMPUTING_CHANNEL) return EXTI_ERROR_INVALID_CHANNEL; else {}
    if (GPIO_PortSource == ERROR_PORT_SOURCE) return EXTI_ERROR_INVALID_PORT_SOURCE; else {}    
    if (GPIO_PinSource == ERROR_PIN_SOURCE) return EXTI_ERROR_INVALID_PIN_SOURCE; else {}    
    
    // Enable AFIO clock (required for EXTI)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO , ENABLE);
        
    // Configure GPIO pin as recommended    
    GPIO_QuickInit(GPIOx, pin, GPIO_MODE_EXTI);    
        
    // Associate port to exti
    GPIO_EXTILineConfig(GPIO_PortSource, GPIO_PinSource);
    
    // Configure the particular EXTI 
    EXTI_InitStruct.EXTI_Line = Line_Number;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = trigger;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStruct);

    // Add IRQ Vector to NVIC
    NVIC_QuickInit(IRQChannel, priority);

    return EXTI_NO_ERROR; 
}

__weak void EXTI_Callback(uint32_t EXTI_Line) {}

/* Private functions ---------------------------------------------------------*/
/**
 * @brief       Returns EXTI_Line associated to Pin number passed in argument
 * @param       pin uint16_t (Pin number with numerotation given by GPIO_Pin_X)
 * @return      uint32_t (EXTI_Line corresponding to Pin passed as argument)
 * @retval      EXTI_Line0 to EXTI_Line15 if Pin is valid, ERROR_LINE_UNREACHABLE if not
*/
uint32_t GPIO_Pin_to_EXTI_Line(uint16_t pin) {
    switch (pin) {
        case GPIO_Pin_0 : return EXTI_Line0;  break;
        case GPIO_Pin_1 : return EXTI_Line1;  break;
        case GPIO_Pin_2 : return EXTI_Line2;  break;
        case GPIO_Pin_3 : return EXTI_Line3;  break;
        case GPIO_Pin_4 : return EXTI_Line4;  break;
        case GPIO_Pin_5 : return EXTI_Line5;  break;
        case GPIO_Pin_6 : return EXTI_Line6;  break;
        case GPIO_Pin_7 : return EXTI_Line7;  break;
        case GPIO_Pin_8 : return EXTI_Line8;  break;
        case GPIO_Pin_9 : return EXTI_Line9;  break;
        case GPIO_Pin_10: return EXTI_Line10; break;
        case GPIO_Pin_11: return EXTI_Line11; break;
        case GPIO_Pin_12: return EXTI_Line12; break;
        case GPIO_Pin_13: return EXTI_Line13; break;
        case GPIO_Pin_14: return EXTI_Line14; break;    
        case GPIO_Pin_15: return EXTI_Line15; break;
        default: return ERROR_LINE_UNREACHABLE; break;
    }
}



/**
 * @brief     Return IRQn associated to Line number passed in argument
 * @param     Line uint32_t (Line number with numerotation from EXTI_Line_0 to EXTI_Line_15)
 * @return     uint8_t (IRQn corresponding to Line passed as argument)
 * @retval     EXTI0_IRQn to EXTI15_10_IRQn if Line is valid, ERROR_COMPUTING_CHANNEL if not
*/
uint8_t Line_to_IRQn(uint32_t Line) {
    uint8_t IRQn = ERROR_COMPUTING_CHANNEL;
    if (Line == EXTI_Line0) {
        IRQn = EXTI0_IRQn;
    }
    else if (Line == EXTI_Line1) {
        IRQn = EXTI1_IRQn;
    }
    else if (Line == EXTI_Line2) { 
        IRQn = EXTI2_IRQn;
    }
    else if (Line == EXTI_Line3) { 
        IRQn = EXTI3_IRQn;
    }
    else if (Line == EXTI_Line4) {
        IRQn = EXTI4_IRQn;
    }    
    else if (Line == EXTI_Line5) {
        IRQn = EXTI9_5_IRQn;
    }
    else if (Line == EXTI_Line6) {
        IRQn = EXTI9_5_IRQn;
    }
    else if (Line == EXTI_Line7) {
        IRQn = EXTI9_5_IRQn;
    }
    else if (Line == EXTI_Line8) {
        IRQn = EXTI9_5_IRQn;
    }
    else if (Line == EXTI_Line9) {
        IRQn = EXTI9_5_IRQn;
    }
    else if (Line == EXTI_Line10) {
        IRQn = EXTI15_10_IRQn;
    }
    else if (Line == EXTI_Line11) {
        IRQn = EXTI15_10_IRQn;
    }    
    else if (Line == EXTI_Line12) {
        IRQn = EXTI15_10_IRQn;
    }    
    else if (Line == EXTI_Line13) {
        IRQn = EXTI15_10_IRQn;
    }
    else if (Line == EXTI_Line14) {
        IRQn = EXTI15_10_IRQn;
    }
    else if (Line == EXTI_Line15) {
        IRQn = EXTI15_10_IRQn;
    }
    else {
        IRQn = ERROR_COMPUTING_CHANNEL;
    }
        
    return IRQn;
}

/**
 * @brief     Returns GPIO_PortSource associated to GPIO_TypeDef number passed in argument
 * @param     GPIO GPIO_TypeDef (Port number with numerotation given by GPIOx)
 * @return     uint8_t (GPIO_PortSource corresponding to GPIO passed as argument)
 * @retval     GPIO_PortSourceGPIOA to GPIO_PortSourceGPIOG if Pin is valid, ERROR_PORT_SOURCE if not
*/
uint8_t GPIO_TypeDef_to_GPIO_PortSource(GPIO_TypeDef *GPIO) {
    uint8_t PortSource = ERROR_PORT_SOURCE;
    if (GPIO == GPIOA) {
        PortSource = GPIO_PortSourceGPIOA;
    }
    else if (GPIO == GPIOB) {
        PortSource = GPIO_PortSourceGPIOB;
    }
    else if (GPIO == GPIOC) {
        PortSource = GPIO_PortSourceGPIOC;
    }
    else if (GPIO == GPIOD) {
        PortSource = GPIO_PortSourceGPIOD;
    }
    else if (GPIO == GPIOE) {
        PortSource = GPIO_PortSourceGPIOE;
    }
    else if (GPIO == GPIOF) {
        PortSource = GPIO_PortSourceGPIOF;
    }
    else if (GPIO == GPIOG) {
        PortSource = GPIO_PortSourceGPIOG;
    }    
    else {
        PortSource = ERROR_PORT_SOURCE;
    }
    return PortSource;
}

/**
 * @brief     Returns GPIO_Pin associated to GPIO_PinSource number passed in argument
 * @param     GPIO_Pin uint16_t (Pin number with numerotation given by GPIO_Pin_x)
 * @return     uint16_t (GPIO_PinSourcex corresponding to GPIO_Pin_x passed as argument)
 * @retval     GPIO_Pin_0 to GPIO_Pin_15 if GPIO_Pin is valid, ERROR_PIN_SOURCE if not
*/
uint16_t GPIO_Pin_to_GPIO_PinSource (uint16_t GPIO_Pin) {
    uint16_t GPIO_PinSource = ERROR_PIN_SOURCE;
    
    if (GPIO_Pin == GPIO_Pin_0) {
        GPIO_PinSource = GPIO_PinSource0;
    }
    else if (GPIO_Pin == GPIO_Pin_1) {
        GPIO_PinSource = GPIO_PinSource1;
    }
    else if (GPIO_Pin == GPIO_Pin_2) {
        GPIO_PinSource = GPIO_PinSource2;
    }
    else if (GPIO_Pin == GPIO_Pin_3) {
        GPIO_PinSource = GPIO_PinSource3;
    }
    else if (GPIO_Pin == GPIO_Pin_4) {
        GPIO_PinSource = GPIO_PinSource4;
    }
    else if (GPIO_Pin == GPIO_Pin_5) {
        GPIO_PinSource = GPIO_PinSource5;
    }
    else if (GPIO_Pin == GPIO_Pin_6) {
        GPIO_PinSource = GPIO_PinSource6;
    }
    else if (GPIO_Pin == GPIO_Pin_7) {
        GPIO_PinSource = GPIO_PinSource7;
    }
    else if (GPIO_Pin == GPIO_Pin_8) {
        GPIO_PinSource = GPIO_PinSource8;
    }
    else if (GPIO_Pin == GPIO_Pin_9) {
        GPIO_PinSource = GPIO_PinSource9;
    }
    else if (GPIO_Pin == GPIO_Pin_10) {
        GPIO_PinSource = GPIO_PinSource10;
    }
    else if (GPIO_Pin == GPIO_Pin_11) {
        GPIO_PinSource = GPIO_PinSource11;
    }
    else if (GPIO_Pin == GPIO_Pin_12) {
        GPIO_PinSource = GPIO_PinSource12;
    }
    else if (GPIO_Pin == GPIO_Pin_13) {
        GPIO_PinSource = GPIO_PinSource13;
    }
    else if (GPIO_Pin == GPIO_Pin_14) {
        GPIO_PinSource = GPIO_PinSource14;
    }
    else if (GPIO_Pin == GPIO_Pin_15) {
        GPIO_PinSource = GPIO_PinSource15;
    }
    else {
        GPIO_PinSource = ERROR_PIN_SOURCE;
    }
    
    return GPIO_PinSource;
}

/**
 * @brief   Handler associated to external interrupts 
*/
void EXTI_ITHandler(uint32_t EXTI_Line) {
    EXTI_Callback(EXTI_Line);
}
