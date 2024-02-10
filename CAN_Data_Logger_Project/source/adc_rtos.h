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
#include "FreeRTOS.h"
#include "task.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define CANDLE_ADC  0
#define FRDM_ADC    1
#define ACTIVE_ADC  FRDM_ADC

#if ACTIVE_ADC == CANDLE_ADC
#define ADC16_BASE              ADC1
#define ADC16_USER_CHANNEL      14U /* ADC1_SE14 */
#define ADC16_IRQn              ADC1_IRQn
#define ADC16_IRQ_HANDLER_FUNC  ADC1_IRQHandler
#define ADC16_VREF              3
#define ADC16_LOW_POWER_THRESHOLD 2
#elif ACTIVE_ADC == FRDM_ADC
#define ADC16_BASE              ADC1
#define ADC16_USER_CHANNEL      0U /* ADC1_DP0 */
#define ADC16_IRQn              ADC1_IRQn
#define ADC16_IRQ_HANDLER_FUNC  ADC1_IRQHandler
#define ADC16_VREF              3.3
#define ADC16_LOW_POWER_THRESHOLD 2
#endif

#define ADC16_BIT_RESOLUTION    8U

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

void Init_ADC(TaskHandle_t* handle);
void ShutdownTask(void *pvParameters);

/*******************************************************************************
 ******************************************************************************/

#endif // _ADC_RTOS_H_
