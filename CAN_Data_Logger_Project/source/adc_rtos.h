/***************************************************************************//**
  @file     adc_rtos.h
  @brief    ADC RTOS Header File
  @author   Grupo CAN Data Logger
 ******************************************************************************/

#ifndef _ADC_RTOS_H_
#define _ADC_RTOS_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "fsl_adc16.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define CANDLE_ADC  0
#define FRDM_ADC    1
#define ACTIVE_ADC  FRDM_ADC

#if ACTIVE_ADC == CANDLE_ADC
#define ADC16_BASE              ADC0
#define ADC16_USER_CHANNEL      12U /* ADC0_SE12 */
#define ADC16_IRQn              ADC0_IRQn
#define ADC16_IRQ_HANDLER_FUNC  ADC0_IRQHandler
#elif ACTIVE_ADC == FRDM_ADC
#define ADC16_BASE              ADC1
#define ADC16_USER_CHANNEL      18U /* ADC1_SE18 */
#define ADC16_IRQn              ADC1_IRQn
#define ADC16_IRQ_HANDLER_FUNC  ADC1_IRQHandler
#endif

#define LOW_POWER_THRESHOLD     2

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

void Init_ADC(void);

/*******************************************************************************
 ******************************************************************************/

#endif // _ADC_RTOS_H_
