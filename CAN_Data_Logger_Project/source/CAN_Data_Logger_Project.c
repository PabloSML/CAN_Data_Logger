/*
 * Copyright 2016-2023 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    MK64F12_Project.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */
#include "fsl_gpio.h"

#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

#include "fsl_rtc.h"

// #include "fsl_sd.h"
// #include "ff.h"
// #include "sdmmc_config.h"
#include "fsl_sysmpu.h"

#include "logging_rtos.h"
#include "flexcan_rtos.h"
#include "drive_rtos.h"

#define DEMO_TASK_GET_SEM_BLOCK_TICKS 1U
#define ACCESSFILE_TASK_STACK_SIZE (512U)
#define ACCESSFILE_TASK_PRIORITY (configMAX_PRIORITIES - 2U)
#define CARDDETECT_TASK_STACK_SIZE (512U)
#define CARDDETECT_TASK_PRIORITY (configMAX_PRIORITIES - 1U)
#define FLEXCAN_TASK_STACK_SIZE 512
#define FLEXCAN_TASK_PRIORITY (configMAX_PRIORITIES - 3U)
#define DRIVE_TASK_PRIORITY (configMAX_PRIORITIES - 3U)

// Modes of operation
typedef enum
{
    LOGGER_MODE,
    DRIVE_MODE
} op_mode_t;

// Variables

/* Data structure of msc device, store the information ,such as class handle */
usb_msc_struct_t g_msc;

// static const uint8_t s_buffer1[] = {'1', '2', '3', ',', '4', '5', '6', ',', '7', '8', '9', '\r', '\n'};

// TaskHandle_t test_task_handle;

// static void APP_task(void *pvParameters);

/*
 * @brief   Application entry point.
 */
int main(void) {

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    //BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    op_mode_t op_mode;

    PRINTF("CAN EXISTS.\n");

    if (GPIO_PinRead(BOARD_MODE_GPIO, BOARD_MODE_PIN) == LOGIC_SW_PRESSED)
    {
        op_mode = DRIVE_MODE;
    }
    else                                                                      
    {
        op_mode = LOGGER_MODE;
    }
    
    SYSMPU_Enable(SYSMPU, false);       //Que hace? No sé

    if (op_mode == LOGGER_MODE)
    {
        Init_FlexCAN();

        /* Init RTC */
        /*
        * rtcConfig.wakeupSelect = false;
        * rtcConfig.updateMode = false;
        * rtcConfig.supervisorAccess = false;
        * rtcConfig.compensationInterval = 0;
        * rtcConfig.compensationTime = 0;
        */
        rtc_config_t rtcConfig;
        RTC_GetDefaultConfig(&rtcConfig);
        RTC_Init(RTC, &rtcConfig);
        /* If the oscillator has not been enabled. */
        if (0U == (RTC->CR & RTC_CR_OSCE_MASK))
        {
            /* Select RTC clock source */
            RTC_SetClockSource(RTC);

            /* Wait for OSC clock steady. */
            // Not defined yet
        }
        /* Set a start date time and start RT */
        rtc_datetime_t date;
        date.year   = 2024U;
        date.month  = 02U;
        date.day    = 19U;
        date.hour   = 17U;
        date.minute = 0;
        date.second = 0;

        /* RTC time counter has to be stopped before setting the date & time in the TSR register */
        RTC_StopTimer(RTC);
        /* Set RTC time to default */
        RTC_SetDatetime(RTC, &date);
        /* Enable RTC alarm interrupt */
        //RTC_EnableInterrupts(RTC, kRTC_AlarmInterruptEnable);
        /* Enable at the NVIC */
        //EnableIRQ(RTC_IRQn);

        /* Start the RTC time counter */
        RTC_StartTimer(RTC);

        // /* Demo de RTOS */
        // xTaskCreate(APP_task,                       /* pointer to the task */
        //             (char const *)"app task",       /* task name for kernel awareness debugging */
        //             512L / sizeof(portSTACK_TYPE), /* task stack size */
        //             NULL,                           /* optional task startup argument */
        //             3,                              /* initial priority */
        //             &test_task_handle               /* optional task handle to create */
        //             );
        TaskHandle_t fileAccessTaskHandle;
        xTaskCreate(FileAccessTask, (char const *)"FileAccessTask", ACCESSFILE_TASK_STACK_SIZE, NULL, ACCESSFILE_TASK_PRIORITY, &fileAccessTaskHandle);
        xTaskCreate(CardDetectTask, (char const *)"CardDetectTask", CARDDETECT_TASK_STACK_SIZE, NULL, CARDDETECT_TASK_PRIORITY, NULL);
        xTaskCreate(FlexCanTask,    (char const *)"FlexCanTask",    FLEXCAN_TASK_STACK_SIZE,    NULL, FLEXCAN_TASK_PRIORITY,    NULL);
    }
    else if (op_mode == DRIVE_MODE)
    {
        Init_Drive();

        xTaskCreate(DriveTask, (char const *)"DriveTask", DRIVE_TASK_STACK_SIZE, &g_msc, DRIVE_TASK_PRIORITY, &g_msc.application_task_handle);
    }

    vTaskStartScheduler();

    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
        i++ ;
        /* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */
        __asm volatile ("nop");
    }
    return 0 ;
}

// static void APP_task(void *pvParameters)
// {
//     //xNextWakeTime = xTaskGetTickCount();
//     static unsigned long counter = 0;
//     rtc_datetime_t date;

//     while(true)
//     {
//         /* Get date time */
//         RTC_GetDatetime(RTC, &date);
//         PRINTF("Current datetime: %04hd-%02hd-%02hd %02hd:%02hd:%02hd\r\n", date.year, date.month, date.day, date.hour,
//                 date.minute, date.second);
        
//         counter++;
        
//         PRINTF("Hola Mundo #%d, milisegundos: %d\n\n", counter, xTaskGetTickCount());
        
//         /* Place this task in the blocked state until it is time to run again.
//         The block time is specified in ticks, the constant used converts ticks
//         to ms.  The task will not consume any CPU time while it is in the
//         Blocked state. */
//         vTaskDelay( 1000 );
        
//     }
// }
