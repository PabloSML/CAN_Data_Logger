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
#include "board_select.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#if BOARD == CANDLE
#define ADC16_BASE              ADC1
#define ADC16_USER_CHANNEL      6U /* ADC1_SE6b */
#define ADC16_IRQn              ADC1_IRQn
#define ADC16_IRQ_HANDLER_FUNC  ADC1_IRQHandler
#define ADC16_VREF              3.0
#define ADC16_LOW_POWER_THRESHOLD 8.0   /* Considering the resistor divider of 220 and 10k */
#elif BOARD == FRDM
#define ADC16_BASE              ADC1
#define ADC16_USER_CHANNEL      0U /* ADC1_DP0 */
#define ADC16_IRQn              ADC1_IRQn
#define ADC16_IRQ_HANDLER_FUNC  ADC1_IRQHandler
#define ADC16_VREF              3.3
#define ADC16_LOW_POWER_THRESHOLD 2.0
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
