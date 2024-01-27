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
#include "clock_config.h"
#include "board.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXAMPLE_CAN            CAN0
#define EXAMPLE_CAN_CLK_SOURCE (kFLEXCAN_ClkSrc1)
// #define EXAMPLE_CAN_CLK_FREQ   CLOCK_GetFreq(kCLOCK_BusClk)
#define EXAMPLE_CAN_CLK_FREQ   60000000   
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
volatile bool txComplete = false;
volatile bool rxComplete = false;
flexcan_handle_t flexcanHandle;
flexcan_mb_transfer_t txXfer, rxXfer;
flexcan_fifo_transfer_t rxFifoXfer;
#if (defined(USE_CANFD) && USE_CANFD)
flexcan_fd_frame_t txFrame, rxFrame;
#else
flexcan_frame_t txFrame, rxFrame;
#endif

static StaticQueue_t s_CanQueue;
static uint8_t s_CanQueueStorage[CAN_QUEUE_LENGTH * CAN_QUEUE_ITEM_SIZE];
static QueueHandle_t s_CanQueueHandle = NULL;

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
    // BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    
    switch (status)
    {
        /* Process FlexCAN Rx event. */
        case kStatus_FLEXCAN_RxFifoIdle:
            // if (RX_MESSAGE_BUFFER_NUM == result)
            // {
            xSemaphoreGiveFromISR(s_FlexCanSemaphore, NULL);
            rxComplete = true;
            // }
            break;

        /* Process FlexCAN Tx event. */
        case kStatus_FLEXCAN_TxIdle:
            if (TX_MESSAGE_BUFFER_NUM == result)
            {
                txComplete = true;
            }
            break;

        default:
            break;
    }
    
    // xSemaphoreGiveFromISR(s_FlexCanSemaphore, &xHigherPriorityTaskWoken);

    // portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

/*!
 * @brief Initialize the FlexCAN
 */
void Init_FlexCAN(void)
{
    flexcan_config_t flexcanConfig;
    flexcan_rx_mb_config_t mbConfig;
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

#if defined(EXAMPLE_CAN_CLK_SOURCE)
    flexcanConfig.clkSrc = EXAMPLE_CAN_CLK_SOURCE;
#endif

    flexcanConfig.enableLoopBack = false;
    // flexcanConfig.enableListenOnlyMode = true;   // NO FUNCIONA (se puede arreglar quizas)
    // flexcanConfig.baudRate = 125000U;
    flexcanConfig.bitRate = 1000000U;
    // flexcanConfig.enableIndividMask = true;

#if (defined(USE_IMPROVED_TIMING_CONFIG) && USE_IMPROVED_TIMING_CONFIG)
    flexcan_timing_config_t timing_config;
    memset(&timing_config, 0, sizeof(flexcan_timing_config_t));
#if (defined(USE_CANFD) && USE_CANFD)
    if (FLEXCAN_FDCalculateImprovedTimingValues(EXAMPLE_CAN, flexcanConfig.baudRate, flexcanConfig.baudRateFD,
                                                EXAMPLE_CAN_CLK_FREQ, &timing_config))
    {
        /* Update the improved timing configuration*/
        memcpy(&(flexcanConfig.timingConfig), &timing_config, sizeof(flexcan_timing_config_t));
    }
    else
    {
        LOG_INFO("No found Improved Timing Configuration. Just used default configuration\r\n\r\n");
    }
#else
    if (FLEXCAN_CalculateImprovedTimingValues(EXAMPLE_CAN, flexcanConfig.baudRate, EXAMPLE_CAN_CLK_FREQ,
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
    FLEXCAN_FDInit(EXAMPLE_CAN, &flexcanConfig, EXAMPLE_CAN_CLK_FREQ, BYTES_IN_MB, true);
#else
    FLEXCAN_Init(EXAMPLE_CAN, &flexcanConfig, EXAMPLE_CAN_CLK_FREQ);
#endif

//     /* Setup Rx Message Buffer. */
//     mbConfig.format = kFLEXCAN_FrameFormatStandard;
//     mbConfig.type   = kFLEXCAN_FrameTypeData;
//     mbConfig.id     = FLEXCAN_ID_STD(0x223);
// #if (defined(USE_CANFD) && USE_CANFD)
//     FLEXCAN_SetFDRxMbConfig(EXAMPLE_CAN, RX_MESSAGE_BUFFER_NUM, &mbConfig, true);
// #else
//     FLEXCAN_SetRxMbConfig(EXAMPLE_CAN, RX_MESSAGE_BUFFER_NUM, &mbConfig, true);
// #endif

    /* Setup Rx FIFO */
    FLEXCAN_SetRxFifoGlobalMask(EXAMPLE_CAN, 0);    /* Set Rx FIFO global mask to receive all frames. */
    rxFifoConfig.idFilterTable = CAN0_BASE + 0xE0u;
    rxFifoConfig.idFilterNum  = 0;
    rxFifoConfig.idFilterType = kFLEXCAN_RxFifoFilterTypeA;
    rxFifoConfig.priority     = kFLEXCAN_RxFifoPrioHigh;
    FLEXCAN_SetRxFifoConfig(EXAMPLE_CAN, &rxFifoConfig, true);

// /* Setup Tx Message Buffer. */
// #if (defined(USE_CANFD) && USE_CANFD)
//     FLEXCAN_SetFDTxMbConfig(EXAMPLE_CAN, TX_MESSAGE_BUFFER_NUM, true);
// #else
//     FLEXCAN_SetTxMbConfig(EXAMPLE_CAN, TX_MESSAGE_BUFFER_NUM, true);
// #endif

    /* set IRQ priority */
    NVIC_SetPriority(CAN0_ORed_Message_buffer_IRQn, 5);
    NVIC_SetPriority(CAN0_Bus_Off_IRQn, 5);
    NVIC_SetPriority(CAN0_Error_IRQn, 5);
    NVIC_SetPriority(CAN0_Tx_Warning_IRQn, 5);
    NVIC_SetPriority(CAN0_Rx_Warning_IRQn, 5);
    NVIC_SetPriority(CAN0_Wake_Up_IRQn, 5);

    /* Create FlexCAN handle structure and set call back function. */
    FLEXCAN_TransferCreateHandle(EXAMPLE_CAN, &flexcanHandle, flexcan_callback, NULL);
    
    s_FlexCanSemaphore = xSemaphoreCreateBinary();
    s_CanMsgSemaphore = xSemaphoreCreateBinary();

    s_CanQueueHandle = xQueueCreateStatic(CAN_QUEUE_LENGTH, CAN_QUEUE_ITEM_SIZE, s_CanQueueStorage, &s_CanQueue);
}

QueueHandle_t getCanMsgQueue(void){
    return s_CanQueueHandle;
}

void FlexCanTask(void *pvParameters)
{
    can_msg_t can_msg;

    while (1)
    {
        // vTaskDelay(100);   // Delete this delay to test faster CAN transfers.
    //     /* Start receive data through Rx Message Buffer. */
    //     rxXfer.mbIdx = (uint8_t)RX_MESSAGE_BUFFER_NUM;
    // #if (defined(USE_CANFD) && USE_CANFD)
    //     rxXfer.framefd = &rxFrame;
    //     (void)FLEXCAN_TransferFDReceiveNonBlocking(EXAMPLE_CAN, &flexcanHandle, &rxXfer);
    // #else
    //     rxXfer.frame = &rxFrame;
    //     (void)FLEXCAN_TransferReceiveNonBlocking(EXAMPLE_CAN, &flexcanHandle, &rxXfer);
    // #endif

        /* Start receive data through Rx Fifo */
        rxFifoXfer.frame = &rxFrame;
        (void)FLEXCAN_TransferReceiveFifoNonBlocking(EXAMPLE_CAN, &flexcanHandle, &rxFifoXfer);

    //     /* Prepare Tx Frame for sending. */
    //     txFrame.format = (uint8_t)kFLEXCAN_FrameFormatStandard;
    //     txFrame.type   = (uint8_t)kFLEXCAN_FrameTypeData;
    //     txFrame.id     = FLEXCAN_ID_STD(0x123);
    //     txFrame.length = (uint8_t)DLC;
    // #if (defined(USE_CANFD) && USE_CANFD)
    //     txFrame.brs = 1U;
    // #endif
    // #if (defined(USE_CANFD) && USE_CANFD)
    //     uint8_t i = 0;
    //     for (i = 0; i < DWORD_IN_MB; i++)
    //     {
    //         txFrame.dataWord[i] = i;
    //     }
    // #else
    //     txFrame.dataWord0 = CAN_WORD0_DATA_BYTE_0(0x11) | CAN_WORD0_DATA_BYTE_1(0x22) | CAN_WORD0_DATA_BYTE_2(0x33) |
    //                         CAN_WORD0_DATA_BYTE_3(0x44);
    //     txFrame.dataWord1 = CAN_WORD1_DATA_BYTE_4(0x55) | CAN_WORD1_DATA_BYTE_5(0x66) | CAN_WORD1_DATA_BYTE_6(0x77) |
    //                         CAN_WORD1_DATA_BYTE_7(0x88);
    // #endif

    //     // LOG_INFO("Send message from MB%d to MB%d\r\n", TX_MESSAGE_BUFFER_NUM, RX_MESSAGE_BUFFER_NUM);
    // #if (defined(USE_CANFD) && USE_CANFD)
    //     for (i = 0; i < DWORD_IN_MB; i++)
    //     {
    //         LOG_INFO("tx word%d = 0x%x\r\n", i, txFrame.dataWord[i]);
    //     }
    // #else
    //     LOG_INFO("CAN ID: 0x%x\r\n", txFrame.id);
    //     LOG_INFO("tx word0 = 0x%x\r\n", txFrame.dataWord0);
    //     LOG_INFO("tx word1 = 0x%x\r\n", txFrame.dataWord1);
    // #endif

    //     /* Send data through Tx Message Buffer. */
    //     txXfer.mbIdx = (uint8_t)TX_MESSAGE_BUFFER_NUM;
    // #if (defined(USE_CANFD) && USE_CANFD)
    //     txXfer.framefd = &txFrame;
    //     (void)FLEXCAN_TransferFDSendNonBlocking(EXAMPLE_CAN, &flexcanHandle, &txXfer);
    // #else
    //     txXfer.frame = &txFrame;
    //     (void)FLEXCAN_TransferSendNonBlocking(EXAMPLE_CAN, &flexcanHandle, &txXfer);
    // #endif

        /* Waiting for Rx Message finish. */
        if  (false || (xSemaphoreTake(s_FlexCanSemaphore, portMAX_DELAY) == pdTRUE)){


            // while(!txComplete){}
            // LOG_INFO("Good news, tx complete\r\n");
            
            // /* Waiting for Rx Message finish. */
            // while (!rxComplete){}

            // Create a CAN message struct with the received data
            can_msg.timestamp = rxFrame.timestamp;
            can_msg.id = FLEXCAN_ID_INVERSE(rxFrame.id);
            can_msg.length = rxFrame.length;
            can_msg.data[0] = rxFrame.dataByte0;
            can_msg.data[1] = rxFrame.dataByte1;
            can_msg.data[2] = rxFrame.dataByte2;
            can_msg.data[3] = rxFrame.dataByte3;
            can_msg.data[4] = rxFrame.dataByte4;
            can_msg.data[5] = rxFrame.dataByte5;
            can_msg.data[6] = rxFrame.dataByte6;
            can_msg.data[7] = rxFrame.dataByte7;

            // Send the CAN message struct to the CAN message queue
            xQueueSend(s_CanQueueHandle, &can_msg, portMAX_DELAY);

            // xSemaphoreGive(s_CanMsgSemaphore);

            // LOG_INFO("\r\nReceived message from MB%d\r\n", RX_MESSAGE_BUFFER_NUM);
        // #if (defined(USE_CANFD) && USE_CANFD)
        //     for (i = 0; i < DWORD_IN_MB; i++)
        //     {
        //         LOG_INFO("rx word%d = 0x%x\r\n", i, rxFrame.dataWord[i]);
        //     }
        // #else
        //     LOG_INFO("CAN ID: 0x%x\r\n", FLEXCAN_ID_INVERSE(rxFrame.id));
        //     LOG_INFO("Timestamp = %d\r\n", rxFrame.timestamp);
        //     LOG_INFO("rx word0 = 0x%x\r\n", rxFrame.dataWord0);
        //     LOG_INFO("rx word1 = 0x%x\r\n", rxFrame.dataWord1);
        // #endif
            rxComplete = false;
            //LOG_INFO("\r\n==FlexCAN loopback example -- Finish.==\r\n");
        }
    }

    vTaskSuspend(NULL);
}


SemaphoreHandle_t getCanMsgSemaphore(void){
    return s_CanMsgSemaphore;
}