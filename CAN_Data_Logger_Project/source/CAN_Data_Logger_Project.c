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
#include "fsl_gpio.h"

#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

#include "fsl_sysmpu.h"

#include "rtc_rtos.h"
#include "flexcan_rtos.h"
#include "logging_rtos.h"
#include "drive_rtos.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define DEMO_TASK_GET_SEM_BLOCK_TICKS 1U
#define ACCESSFILE_TASK_STACK_SIZE (512U)
#define ACCESSFILE_TASK_PRIORITY (configMAX_PRIORITIES - 2U)
#define CARDDETECT_TASK_STACK_SIZE (512U)
#define CARDDETECT_TASK_PRIORITY (configMAX_PRIORITIES - 1U)
#define FLEXCAN_TASK_STACK_SIZE 512
#define FLEXCAN_TASK_PRIORITY (configMAX_PRIORITIES - 3U)
#define DRIVE_TASK_PRIORITY (configMAX_PRIORITIES - 3U)

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

// Modes of operation
typedef enum
{
    LOGGER_MODE,
    DRIVE_MODE
} op_mode_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Data structure of msc device, store the information ,such as class handle */
usb_msc_struct_t g_msc;
static TaskHandle_t fileAccessTaskHandle;

/*******************************************************************************
 * Code
 ******************************************************************************/

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
        Init_RTC(true);
        Init_FlexCAN();
        Init_CardDetect(&fileAccessTaskHandle);

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
