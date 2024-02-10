/***************************************************************************//**
  @file     adc_rtos.c
  @brief    ADC RTOS Source File
  @author   Grupo CAN Data Logger
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "board.h"
#include "MK64F12.h"
#include "core_cm4.h"
#include "fsl_debug_console.h"
#include "limits.h"

#include "adc_rtos.h"
#include "logging_rtos.h"
#include "flexcan_rtos.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define ADC16_CHANNEL_GROUP     0U
#define ADC16_DEBUG_PRINT       0U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

static int CalcDigitalValue(float analogValue, float refVoltage, uint8_t bitResolution);
#if ADC16_DEBUG_PRINT
static float CalcAnalogValue(int digitalValue, float refVoltage, uint8_t bitResolution);
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/

static TaskHandle_t* shutdownTaskHandle;
static SemaphoreHandle_t s_ShutdownSemaphore = NULL;
static BaseType_t xHigherPriorityTaskWokenByPost = pdFALSE;
static volatile bool taskRunning = false;

/*******************************************************************************
 * Code
 ******************************************************************************/

void ADC16_IRQ_HANDLER_FUNC(void)
{
    // ADC value is below the threshold
#if ADC16_DEBUG_PRINT
    uint32_t adcValue = ADC16_GetChannelConversionValue(ADC16_BASE, ADC16_CHANNEL_GROUP);
    float analogValue = CalcAnalogValue(adcValue, ADC16_VREF, ADC16_BIT_RESOLUTION);
    PRINTF("ADC value under threshold. Register value = %d, Analog value = %d.%d%dV\r\n", adcValue, (int)(analogValue+0.005f), (int)((analogValue+0.005f) * 10) % 10, (int)((analogValue+0.005f) * 100) % 10);
#endif
    // Wake up the shutdown task
    if (taskRunning)
    {
        taskRunning = false;
        DisableIRQ(ADC16_IRQn);
        ADC16_Deinit(ADC16_BASE);
        xSemaphoreGiveFromISR(s_ShutdownSemaphore, &xHigherPriorityTaskWokenByPost);
        if (xHigherPriorityTaskWokenByPost == pdTRUE)
        {
            portYIELD_FROM_ISR(xHigherPriorityTaskWokenByPost);
        }
    }
}

static void SetIRQPriority(IRQn_Type irq, uint32_t priority)
{
    NVIC_SetPriority(irq, priority);
}

static int CalcDigitalValue(float analogValue, float refVoltage, uint8_t bitResolution)
{
    return (int)(((analogValue / refVoltage) * (1 << bitResolution)) - 1);
}

#if ADC16_DEBUG_PRINT
static float CalcAnalogValue(int digitalValue, float refVoltage, uint8_t bitResolution)
{
    return (float)((((float)digitalValue + 1) / (1 << bitResolution)) * refVoltage);
}
#endif

void ShutdownTask(void *pvParameters)
{
    taskRunning = true;

    while(1)
    {
        if (xSemaphoreTake(s_ShutdownSemaphore, portMAX_DELAY) == pdTRUE)
        {
            // Stop app tasks
            StopLogging();
            StopFlexCAN();
            BOARD_WriteLEDs(true, true, true);

            vTaskSuspend(NULL);
        }
    }
}

void Init_ADC(TaskHandle_t* handle)
{
    adc16_config_t adcConfig;
    adc16_channel_config_t adcChannelConfig;
    adc16_hardware_compare_config_t adcCompareConfig;
    shutdownTaskHandle = handle;
    s_ShutdownSemaphore = xSemaphoreCreateBinary();
    SetIRQPriority(ADC1_IRQn, 4);

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
#if ADC16_BIT_RESOLUTION == 8
    adcConfig.resolution = kADC16_ResolutionSE8Bit; // 8-bit resolution
#elif ADC16_BIT_RESOLUTION == 10
    adcConfig.resolution = kADC16_ResolutionSE10Bit; // 10-bit resolution
#elif ADC16_BIT_RESOLUTION == 12
    adcConfig.resolution = kADC16_ResolutionSE12Bit; // 12-bit resolution
#endif
    ADC16_Init(ADC16_BASE, &adcConfig);
    if (kStatus_Success != ADC16_DoAutoCalibration(ADC16_BASE))
    {
        PRINTF("ADC Auto calibration failed.\r\n");
        BOARD_WriteLEDs(true, false, false);
    }
    ADC16_EnableHardwareTrigger(ADC16_BASE, false); /* Make sure the software trigger is used. */

    // Compare configuration
    adcCompareConfig.hardwareCompareMode = kADC16_HardwareCompareMode0; // Less than threshold
    adcCompareConfig.value1 = CalcDigitalValue(ADC16_LOW_POWER_THRESHOLD, ADC16_VREF, ADC16_BIT_RESOLUTION);
    ADC16_SetHardwareCompareConfig(ADC16_BASE, &adcCompareConfig);

// #if ACTIVE_ADC == CANDLE_ADC
//     ADC16_SetChannelMuxMode(ADC16_BASE, kADC16_ChannelMuxB);
// #endif

    // Only triggers if the comparison condition is met (i.e. low power)
    EnableIRQ(ADC16_IRQn);

    // Channel configuration - Trigger conversions
    adcChannelConfig.channelNumber = ADC16_USER_CHANNEL;
    adcChannelConfig.enableDifferentialConversion = false;
    adcChannelConfig.enableInterruptOnConversionCompleted = true;
    ADC16_SetChannelConfig(ADC16_BASE, ADC16_CHANNEL_GROUP, &adcChannelConfig);
}
