/*----------------------------------------------------------------------------
 * Name:    ADC.c
 * Purpose: low level ADC functions
 * Note(s): possible defines select the used ADC interface:
 *            __ADC_IRQ   - ADC works in Interrupt mode
 *                        - ADC works in DMA mode (default)
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2009-2013 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include "STM32F10x.h"
#include "ADC.h"

uint16_t AD_last;                         /* Last converted value             */
uint8_t  AD_done = 0;                     /* AD conversion done flag          */

/*----------------------------------------------------------------------------
  Function that initializes ADC
    5 MHz operation, 20µs startup time, 600ns track and hold time
 *----------------------------------------------------------------------------*/
void ADC_Init (void) {

  RCC->APB2ENR |= ( 1UL <<  2);           /* enable periperal clock for GPIOA */
  GPIOA->CRL &= ~0x000000F0;              /* set PIN1 as analog input         */

#ifndef __ADC_IRQ
  /* DMA1 Channel1 configuration ---------------------------------------------*/
  RCC->AHBENR |= ( 1UL <<  0);            /* enable periperal clock for DMA   */

  DMA1_Channel1->CMAR  = (uint32_t)&AD_last;    /* set chn1 memory address    */
  DMA1_Channel1->CPAR  = (uint32_t)&(ADC1->DR); /* set chn1 peripheral address*/
  DMA1_Channel1->CNDTR = 1;               /* transmit 1 word                  */
  DMA1_Channel1->CCR   = 0x00002522;      /* configure DMA channel            */
  NVIC_EnableIRQ(DMA1_Channel1_IRQn);     /* enable DMA1 Channel1 Interrupt   */
  DMA1_Channel1->CCR  |= (1 << 0);        /* DMA Channel 1 enable             */
#endif

  /* Setup and initialize ADC converter                                       */
  RCC->CFGR    |= ( 3UL << 14);           /* ADC clk = PCLK2 / 8              */

  RCC->APB2ENR |= ( 1UL <<  9);           /* enable periperal clock for ADC1  */

  ADC1->SQR1    =  0;                     /* Regular chn. Sequence length = 1 */
  ADC1->SQR2    =  0;                     /* Clear register                   */
  ADC1->SQR3    = ( 1UL <<  0);           /* 1. conversion = channel 1        */
  ADC1->SMPR2   = ( 5UL <<  3);           /* sample time channel 1  55,5 cyc. */
  ADC1->CR1     = ( 1UL <<  8);           /* Scan mode on                     */
  ADC1->CR2     = ( 7UL << 17)|           /* select SWSTART                   */
                  ( 1UL << 20) ;          /* enable external Trigger          */

#ifndef __ADC_IRQ
  ADC1->CR2    |= ( 1UL <<  8);           /* DMA mode enable                  */
#else
  ADC1->CR1    |= ( 1UL <<  5);           /* enable for EOC Interrupt         */
  NVIC_EnableIRQ(ADC1_2_IRQn);            /* enable ADC Interrupt             */
#endif

  ADC1->CR2    |= ( 1UL <<  0);           /* ADC enable                       */

  ADC1->CR2    |=  1 <<  3;               /* Initialize calibration registers */
  while (ADC1->CR2 & (1 << 3));           /* Wait for init to finish          */
  ADC1->CR2    |=  1 <<  2;               /* Start calibration                */
  while (ADC1->CR2 & (1 << 2));           /* Wait for calibration to finish   */
}


/*----------------------------------------------------------------------------
  start AD Conversion
 *----------------------------------------------------------------------------*/
void ADC_StartCnv (void) {

  ADC1->CR2    |=  (1UL << 22);           /* Start A/D conversion             */ 
}


/*----------------------------------------------------------------------------
  stop AD Conversion
 *----------------------------------------------------------------------------*/
void ADC_StopCnv (void) {

  ADC1->CR2    &= ~(1UL << 22);           /* Stop  A/D conversion             */ 
}


/*----------------------------------------------------------------------------
  get converted AD value
 *----------------------------------------------------------------------------*/
uint16_t ADC_GetCnv (void) {

  while (!(AD_done));                     /* Wait for Conversion end          */
  AD_done = 0;

  return(AD_last);
}


#ifndef __ADC_IRQ
/*----------------------------------------------------------------------------
  DMA IRQ: Executed when a transfer is completet
 *----------------------------------------------------------------------------*/
void DMA1_Channel1_IRQHandler(void) {

  if (DMA1->ISR & (1 << 1)) {            /* TCIF interrupt?                   */
    AD_done = 1;

    DMA1->IFCR  = (1 << 1);              /* clear TCIF interrupt              */
  }
}
#endif


#ifdef __ADC_IRQ
/*----------------------------------------------------------------------------
  A/D IRQ: Executed when A/D Conversion is done
 *----------------------------------------------------------------------------*/
void ADC1_2_IRQHandler(void) {

  if (ADC1->SR & (1 << 1)) {            /* ADC1 EOC interrupt?                */
    AD_last = ADC1->DR;
    AD_done = 1;

    ADC1->SR &= ~(1 << 1);              /* clear EOC interrupt                */
  }

}
#endif
