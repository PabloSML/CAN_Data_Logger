/***************************************************************************//**
  @file     adc_rtos.c
  @brief    ADC RTOS Source File
  @author   Grupo CAN Data Logger
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "adc_rtos.h"
#include "board.h"
#include "MK64F12.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define ADC16_CHANNEL_GROUP     0U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

void ADC16_IRQ_HANDLER_FUNC(void)
{
    // ADC value is below the threshold
    PRINTF("ADC value under threshold. Shutting Down...\r\n");
    // Perform necessary actions
}

static int CalcDigitalValue(float analogValue, float refVoltage, uint8_t bitResolution)
{
    return (int)(((analogValue / refVoltage) * (1 << bitResolution)) - 1);
}

static float CalcAnalogValue(int digitalValue, float refVoltage, uint8_t bitResolution)
{
    return (((float)digitalValue + 1) / (1 << bitResolution)) * refVoltage;
}

void Init_ADC(void)
{
    adc16_config_t adcConfig;
    adc16_channel_config_t adcChannelConfig;
    adc16_hardware_compare_config_t adcCompareConfig;

    // Main configuration
    /*
    *   config->referenceVoltageSource     = kADC16_ReferenceVoltageSourceVref;
    *   config->clockSource                = kADC16_ClockSourceAsynchronousClock;
    *   config->enableAsynchronousClock    = true;
    *   config->clockDivider               = kADC16_ClockDivider8;
    *   config->resolution                 = kADC16_ResolutionSE12Bit;
    *   config->longSampleMode             = kADC16_LongSampleDisabled;
    *   config->enableHighSpeed            = false;
    *   config->enableLowPower             = false;
    *   config->enableContinuousConversion = false;
    */
    ADC16_GetDefaultConfig(&adcConfig);
    adcConfig.enableContinuousConversion = true;    // Continuous mode
    adcConfig.resolution = kADC16_ResolutionSE8Bit; // 8-bit resolution
    ADC16_Init(ADC16_BASE, &adcConfig);
    if (kStatus_Success != ADC16_DoAutoCalibration(ADC16_BASE))
    {
        PRINTF("ADC Auto calibration failed.\r\n");
        BOARD_WriteLEDs(true, false, false);
    }
    ADC16_EnableHardwareTrigger(ADC16_BASE, false); /* Make sure the software trigger is used. */

    // Compare configuration
    adcCompareConfig.hardwareCompareMode = kADC16_HardwareCompareMode0; // Less than threshold
    adcCompareConfig.value1 = CalcDigitalValue(LOW_POWER_THRESHOLD, 3.3, 8);
    ADC16_SetHardwareCompareConfig(ADC16_BASE, &adcCompareConfig);

    // Only triggers if the comparison condition is met (i.e. low power)
    EnableIRQ(ADC16_IRQn);

    // Channel configuration - Trigger conversions
    adcChannelConfig.channelNumber = ADC16_USER_CHANNEL;
    ADC16_SetChannelConfig(ADC16_BASE, ADC16_CHANNEL_GROUP, &adcChannelConfig);
}
