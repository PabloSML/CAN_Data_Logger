/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "flexcan_rtos.h"
#include "fsl_flexcan.h"
#include "fsl_debug_console.h"
#include "board_select.h"
#if BOARD == CANDLE
#include "clock_config_candle.h"
#elif BOARD == FRDM
#include "clock_config_frdm.h"
#endif
#include "board.h"
#include "MK64F12.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define CAN_BASE            CAN0
#define CAN_CLK_SOURCE (kFLEXCAN_ClkSrc1)
// #define CAN_CLK_FREQ   CLOCK_GetFreq(kCLOCK_BusClk)
#define CAN_CLK_FREQ   60000000   
/* Set USE_IMPROVED_TIMING_CONFIG macro to use api to calculates the improved CAN / CAN FD timing values. */
#define USE_IMPROVED_TIMING_CONFIG (1U)
#define RX_MESSAGE_BUFFER_NUM      (9)
#define TX_MESSAGE_BUFFER_NUM      (8)
#define DLC                        (8)

#define CAN_QUEUE_LENGTH 10
#define CAN_QUEUE_ITEM_SIZE sizeof(can_msg_t)

/* Fix MISRA_C-2012 Rule 17.7. */
#define LOG_INFO (void)PRINTF
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
static flexcan_handle_t flexcanHandle;
static bool flexcan_init = false;
static flexcan_fifo_transfer_t rxFifoXfer;
#if (defined(USE_CANFD) && USE_CANFD)
static flexcan_fd_frame_t rxFrame;
#else
static flexcan_frame_t rxFrame;
#endif

static StaticQueue_t s_CanQueue;
static uint8_t s_CanQueueStorage[CAN_QUEUE_LENGTH * CAN_QUEUE_ITEM_SIZE];
static QueueHandle_t s_CanQueueHandle = NULL;

static TaskHandle_t* flexCanTaskHandle;
static SemaphoreHandle_t s_FlexCanSemaphore = NULL;
static SemaphoreHandle_t s_CanMsgSemaphore = NULL;

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief FlexCAN Call Back function
 */
static FLEXCAN_CALLBACK(flexcan_callback)
{
    switch (status)
    {
        /* Process FlexCAN Rx event. */
        case kStatus_FLEXCAN_RxFifoIdle:
            xSemaphoreGiveFromISR(s_FlexCanSemaphore, NULL);
            break;
        default:
            break;
    }
}

void StopFlexCAN(void)
{
    if (flexcan_init)
    {
        vTaskSuspend(*flexCanTaskHandle);
        flexcan_init = false;
    }
}

/*!
 * @brief Initialize the FlexCAN
 */
void Init_FlexCAN(TaskHandle_t* handle)
{
    flexCanTaskHandle = handle;
    flexcan_config_t flexcanConfig;
    flexcan_rx_fifo_config_t rxFifoConfig;

    /* Init FlexCAN module. */
    /*
     * flexcanConfig.clkSrc                 = kFLEXCAN_ClkSrc0;
     * flexcanConfig.baudRate               = 1000000U;
     * flexcanConfig.baudRateFD             = 2000000U;
     * flexcanConfig.maxMbNum               = 16;
     * flexcanConfig.enableLoopBack         = false;
     * flexcanConfig.enableSelfWakeup       = false;
     * flexcanConfig.enableIndividMask      = false;
     * flexcanConfig.disableSelfReception   = false;
     * flexcanConfig.enableListenOnlyMode   = false;
     * flexcanConfig.enableDoze             = false;
     */
    FLEXCAN_GetDefaultConfig(&flexcanConfig);

#if defined(CAN_CLK_SOURCE)
    flexcanConfig.clkSrc = CAN_CLK_SOURCE;
#endif

    flexcanConfig.enableLoopBack = false;
    // flexcanConfig.enableListenOnlyMode = true;   // NO FUNCIONA (se puede arreglar quizas)
    // flexcanConfig.baudRate = 125000U;
    flexcanConfig.bitRate = 125000U;

#if (defined(USE_IMPROVED_TIMING_CONFIG) && USE_IMPROVED_TIMING_CONFIG)
    flexcan_timing_config_t timing_config;
    memset(&timing_config, 0, sizeof(flexcan_timing_config_t));
#if (defined(USE_CANFD) && USE_CANFD)
    if (FLEXCAN_FDCalculateImprovedTimingValues(CAN_BASE, flexcanConfig.baudRate, flexcanConfig.baudRateFD,
                                                CAN_CLK_FREQ, &timing_config))
    {
        /* Update the improved timing configuration*/
        memcpy(&(flexcanConfig.timingConfig), &timing_config, sizeof(flexcan_timing_config_t));
    }
    else
    {
        LOG_INFO("No found Improved Timing Configuration. Just used default configuration\r\n\r\n");
    }
#else
    if (FLEXCAN_CalculateImprovedTimingValues(CAN_BASE, flexcanConfig.baudRate, CAN_CLK_FREQ,
                                              &timing_config))
    {
        /* Update the improved timing configuration*/
        memcpy(&(flexcanConfig.timingConfig), &timing_config, sizeof(flexcan_timing_config_t));
    }
    else
    {
        LOG_INFO("No found Improved Timing Configuration. Just used default configuration\r\n\r\n");
    }
#endif
#endif

#if (defined(USE_CANFD) && USE_CANFD)
    FLEXCAN_FDInit(CAN_BASE, &flexcanConfig, CAN_CLK_FREQ, BYTES_IN_MB, true);
#else
    FLEXCAN_Init(CAN_BASE, &flexcanConfig, CAN_CLK_FREQ);
#endif

    /* Setup Rx FIFO */
    FLEXCAN_SetRxFifoGlobalMask(CAN_BASE, 0);    /* Set Rx FIFO global mask to receive all frames. */
    rxFifoConfig.idFilterTable = (uint32_t*)(CAN0_BASE + 0xE0u);
    rxFifoConfig.idFilterNum  = 0;
    rxFifoConfig.idFilterType = kFLEXCAN_RxFifoFilterTypeA;
    rxFifoConfig.priority     = kFLEXCAN_RxFifoPrioHigh;
    FLEXCAN_SetRxFifoConfig(CAN_BASE, &rxFifoConfig, true);

    /* set IRQ priority */
    NVIC_SetPriority(CAN0_ORed_Message_buffer_IRQn, 5);
    NVIC_SetPriority(CAN0_Bus_Off_IRQn, 5);
    NVIC_SetPriority(CAN0_Error_IRQn, 5);
    NVIC_SetPriority(CAN0_Tx_Warning_IRQn, 5);
    NVIC_SetPriority(CAN0_Rx_Warning_IRQn, 5);
    NVIC_SetPriority(CAN0_Wake_Up_IRQn, 5);

    /* Create FlexCAN handle structure and set call back function. */
    FLEXCAN_TransferCreateHandle(CAN_BASE, &flexcanHandle, flexcan_callback, NULL);
    
    s_FlexCanSemaphore = xSemaphoreCreateBinary();
    s_CanMsgSemaphore = xSemaphoreCreateBinary();

    s_CanQueueHandle = xQueueCreateStatic(CAN_QUEUE_LENGTH, CAN_QUEUE_ITEM_SIZE, s_CanQueueStorage, &s_CanQueue);
    flexcan_init = true;
}

QueueHandle_t getCanMsgQueue(void){
    return s_CanQueueHandle;
}

void FlexCanTask(void *pvParameters)
{
    can_msg_t can_msg;
#if BOARD == FRDM
    uint16_t msg_count = 0;
    vTaskDelay(5000);

    while (1)
    {
        vTaskDelay(5);
        RTC_GetDatetime(RTC, &can_msg.timestamp);
        can_msg.id = 0x223;
        can_msg.length = 8;
        can_msg.data[0] = 0x01;
        can_msg.data[1] = 0x23;
        can_msg.data[2] = 0x45;
        can_msg.data[3] = 0x67;
        can_msg.data[4] = 0x89;
        can_msg.data[5] = 0xAB;
        can_msg.data[6] = 0xCD;
        can_msg.data[7] = 0xEF;

        xQueueSend(s_CanQueueHandle, &can_msg, portMAX_DELAY);
    }
#elif BOARD == CANDLE
    while (1)
    {
        /* Start receive data through Rx Fifo */
        rxFifoXfer.frame = &rxFrame;
        (void)FLEXCAN_TransferReceiveFifoNonBlocking(CAN_BASE, &flexcanHandle, &rxFifoXfer);

        /* Waiting for Rx Message finish. */
        if  (xSemaphoreTake(s_FlexCanSemaphore, portMAX_DELAY) == pdTRUE)
        {
            // BOARD_WriteLED(BOARD_LED_1_PIN, LOGIC_LED_ON);
            // Create a CAN message struct with the received data
            RTC_GetDatetime(RTC, &can_msg.timestamp);
            can_msg.id = FLEXCAN_ID_INVERSE(rxFrame.id);
            can_msg.length = rxFrame.length;
            can_msg.data[0] = rxFrame.dataByte7;
            can_msg.data[1] = rxFrame.dataByte6;
            can_msg.data[2] = rxFrame.dataByte5;
            can_msg.data[3] = rxFrame.dataByte4;
            can_msg.data[4] = rxFrame.dataByte3;
            can_msg.data[5] = rxFrame.dataByte2;
            can_msg.data[6] = rxFrame.dataByte1;
            can_msg.data[7] = rxFrame.dataByte0;

            // Send the CAN message struct to the CAN message queue
            xQueueSend(s_CanQueueHandle, &can_msg, portMAX_DELAY);
            // BOARD_WriteLED(BOARD_LED_1_PIN, LOGIC_LED_OFF);
        }
    }
#endif
    vTaskSuspend(NULL);
}
