/**
 * @file    spi.c
 * @author  Curtis Team
 * @brief   Functions to handle SPI  
 */
 
/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
#include "spi.h"


/**
 * @brief   SPI1 GPIO associated to the SPI used.
 */
#define SPI1_GPIO       GPIOA

/**
 * @brief   SPI1 Pin where the clock is received
 */
#define SPI1_PIN_SCK    GPIO_Pin_5

/**
 * @brief   SPI1 Pin MISO (Master Input, Slave Output)
 */
#define SPI1_PIN_MISO   GPIO_Pin_6

/**
 * @brief   SPI1 Pin MISO (Master Output, Slave Input)
 */
#define SPI1_PIN_MOSI   GPIO_Pin_7


/**
 * @brief   SPI2 GPIO associated to the SPI used.
 */
#define SPI2_GPIO       GPIOB

/**
 * @brief   SPI2 Pin where the clock is received
 */
#define SPI2_PIN_SCK    GPIO_Pin_13

/**
 * @brief   SPI2 Pin MISO (Master Input, Slave Output)
 */
#define SPI2_PIN_MISO   GPIO_Pin_14

/**
 * @brief   SPI2 Pin MISO (Master Output, Slave Input)
 */
#define SPI2_PIN_MOSI   GPIO_Pin_15

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void SPI_ClockEnable(SPI_TypeDef* SPIx);

/* Public functions ----------------------------------------------------------*/
/**
 * @brief Makes the initialization of the SPI with the parameters specified
 * @param SPI_Mode uint16_t Mode (master or slave) chosen for STM32 (usage : SPI_Mode_Master or SPI_Mode_Slave)
*/
void SPI_QuickInit(SPI_TypeDef* SPIx, uint16_t SPI_Mode) {
    SPI_InitTypeDef SPI_InitStructure;
    
    // GPIO configuration
    if (SPIx == SPI1) {
        GPIO_QuickInit(SPI1_GPIO, SPI1_PIN_SCK,  GPIO_Mode_IN_FLOATING);
        GPIO_QuickInit(SPI1_GPIO, SPI1_PIN_MOSI, GPIO_Mode_IN_FLOATING);
        GPIO_QuickInit(SPI1_GPIO, SPI1_PIN_MISO, GPIO_Mode_AF_PP);
    } else if (SPIx == SPI2) {
        GPIO_QuickInit(SPI2_GPIO, SPI2_PIN_SCK,  GPIO_Mode_IN_FLOATING);
        GPIO_QuickInit(SPI2_GPIO, SPI2_PIN_MOSI, GPIO_Mode_IN_FLOATING);
        GPIO_QuickInit(SPI2_GPIO, SPI2_PIN_MISO, GPIO_Mode_AF_PP);
    }
    
    SPI_ClockEnable(SPIx);
    
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 0; // no CRC
    SPI_Init(SPIx, &SPI_InitStructure);
}

/**
 * @brief Starts the SPI.
 * @return None
 */
void SPI_Start(SPI_TypeDef* SPIx) {
    SPI_Cmd(SPIx, ENABLE);
}

/**
 * @brief Stops the SPI.
 * @return None
 */
void SPI_Stop(SPI_TypeDef* SPIx) {
   // Make sure tranfer is complete:
   //    - avoid data corruption
   while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) != SET);
   //    - avoid unreliable BUSY flag
   while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_BSY) != RESET);
   // Disable SPIx
   SPI_Cmd(SPIx, DISABLE);
}

__weak void SPI_Callback(SPI_TypeDef* SPIx) {}

/* Private functions ---------------------------------------------------------*/
/**
 * @brief     Enables clock on the adequate GPIO
 * @param     SPIx SPI_TypeDef (SPI to switch on the clock)
 * @retval     None
*/
void SPI_ClockEnable(SPI_TypeDef* SPIx) {
            if (SPIx == SPI1) RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
    else    if (SPIx == SPI2) RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
    else{}
}

/**
 * @brief   Handler associated to SPI
*/
void SPI_ITHandler(SPI_TypeDef* SPIx) {
    SPI_Callback(SPIx);
}
