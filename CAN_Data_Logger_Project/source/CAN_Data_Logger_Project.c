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

#include "limits.h"
#include "fsl_sd.h"
#include "ff.h"
#include "diskio.h"
#include "fsl_sd_disk.h"
#include "sdmmc_config.h"
#include "fsl_sysmpu.h"

#include "flexcan_rtos.h"


#define DEMO_TASK_GET_SEM_BLOCK_TICKS 1U
#define DEMO_TASK_ACCESS_SDCARD_TIMES 10U
#define ACCESSFILE_TASK_STACK_SIZE (512U)
#define ACCESSFILE_TASK_PRIORITY (configMAX_PRIORITIES - 2U)
#define CARDDETECT_TASK_STACK_SIZE (512U)
#define CARDDETECT_TASK_PRIORITY (configMAX_PRIORITIES - 1U)
#define FLEXCAN_TASK_PRIORITY (configMAX_PRIORITIES - 2U)

// Variables
static FATFS g_fileSystem; /* File system object */
static FIL g_fileObject1;  /* File object */

// static const uint8_t s_buffer1[] = {'1', '2', '3', ',', '4', '5', '6', ',', '7', '8', '9', '\r', '\n'};

/*! @brief SD card detect flag  */
static volatile bool s_cardInserted     = false;
static volatile bool s_cardInsertStatus = false;
/*! @brief Card semaphore  */
static SemaphoreHandle_t s_CardDetectSemaphore = NULL;

TaskHandle_t test_task_handle;
TaskHandle_t fileAccessTaskHandle;



static void APP_task(void *pvParameters);
static void SDCARD_DetectCallBack(bool isInserted, void *userData);
static void CardDetectTask(void *pvParameters);
static void FileAccessTask(void *pvParameters);
static status_t DEMO_MakeFileSystem(void);


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


    /* Demo blinky blinky lights */
    PRINTF("CAN EXISTS.\n");
    gpio_pin_config_t green_led_config = {
        kGPIO_DigitalOutput,
        0,
    };
    GPIO_PinInit(GPIOE, 26, &green_led_config);
    GPIO_PinWrite(GPIOE, 26, 1);

    ////// Demo Tarjeta SD
    
    SYSMPU_Enable(SYSMPU, false);       //Que hace? No sé



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
    date.year   = 2023U;
    date.month  = 5U;
    date.day    = 4U;
    date.hour   = 0U;
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
    Init_FlexCAN();

    //xTaskCreate(FileAccessTask, (char const *)"FileAccessTask", ACCESSFILE_TASK_STACK_SIZE, NULL, ACCESSFILE_TASK_PRIORITY, &fileAccessTaskHandle);
    //xTaskCreate(CardDetectTask, (char const *)"CardDetectTask", CARDDETECT_TASK_STACK_SIZE, NULL, CARDDETECT_TASK_PRIORITY, NULL);
    xTaskCreate(FlexCanTask,    (char const *)"FlexCanTask",    FLEXCAN_TASK_STACK_SIZE,    NULL, FLEXCAN_TASK_PRIORITY,    NULL);


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



static void APP_task(void *pvParameters)
{
    //xNextWakeTime = xTaskGetTickCount();
    static unsigned long counter = 0;
    rtc_datetime_t date;

    while(true)
    {
        /* Get date time */
        RTC_GetDatetime(RTC, &date);
        printf("Current datetime: %04hd-%02hd-%02hd %02hd:%02hd:%02hd\r\n", date.year, date.month, date.day, date.hour,
                date.minute, date.second);
        
        counter++;
        
        printf("Hola Mundo #%d, milisegundos: %d\n\n", counter, xTaskGetTickCount());
        
        /* Place this task in the blocked state until it is time to run again.
        The block time is specified in ticks, the constant used converts ticks
        to ms.  The task will not consume any CPU time while it is in the
        Blocked state. */
        vTaskDelay( 1000 );
        
    }
}


static void FileAccessTask(void *pvParameters)
{
    rtc_datetime_t date;
    UINT bytesWritten   = 0U;
    uint32_t writeTimes = 1U;
    FRESULT error;

    xTaskNotifyWait(ULONG_MAX, ULONG_MAX, NULL, portMAX_DELAY);

    while (1)
    {

        if (xSemaphoreTake(s_CanMsgSemaphore, portMAX_DELAY) == pdTRUE){

            PRINTF("Hola, recibí un mensaje de CAN!\r\n");
        }

        error = f_open(&g_fileObject1, _T("/dir_1/magic.csv"), FA_WRITE);
        if (error)
        {
            if (error == FR_EXIST)
            {
                PRINTF("File exists.\r\n");
            }
            /* if file not exist, creat a new file */
            else if (error == FR_NO_FILE)
            {
                if (f_open(&g_fileObject1, _T("/dir_1/magic.csv"), (FA_WRITE | FA_CREATE_NEW)) != FR_OK)
                {
                    PRINTF("Create file failed.\r\n");
                    break;
                }
            }
            else
            {
                PRINTF("Open file failed.\r\n");
                break;
            }
        }
        /* write append */
        if (f_lseek(&g_fileObject1, g_fileObject1.obj.objsize) != FR_OK)
        {
            PRINTF("lseek file failed.\r\n");
            break;
        }
        
        char s_buffer0[] = "Year,Month,Day,Hour,Minute,Second\r\n";
        if(writeTimes == 1)
        {
            error = f_write(&g_fileObject1, s_buffer0, sizeof(s_buffer0), &bytesWritten);
            if ((error) || (bytesWritten != sizeof(s_buffer0)))
            {
                PRINTF("Write file failed.\r\n");
                break;
            }
        }

        /* Get date time */
        RTC_GetDatetime(RTC, &date);
        char s_buffer1[100];
        sprintf(s_buffer1, "%04hd,%02hd,%02hd,%02hd,%02hd,%02hd\r\n", date.year, date.month, date.day, date.hour, date.minute, date.second);
        int len = strlen(s_buffer1);
        int size = sizeof(char)*len;

        error = f_write(&g_fileObject1, s_buffer1, size, &bytesWritten);
        if ((error) || (bytesWritten != size))
        {
            PRINTF("Write file failed.\r\n");
            break;
        }
        f_close(&g_fileObject1);

        if (++writeTimes > DEMO_TASK_ACCESS_SDCARD_TIMES)
        {
            PRINTF("TASK: finished.\r\n");
            writeTimes = 1U;
            xTaskNotifyWait(ULONG_MAX, ULONG_MAX, NULL, portMAX_DELAY);
            continue;
        }
        {
            PRINTF("TASK: write file succeded.\r\n");
        }

        //vTaskDelay(1000);
    }

    vTaskSuspend(NULL);
}




static void SDCARD_DetectCallBack(bool isInserted, void *userData)
{
    s_cardInsertStatus = isInserted;
    xSemaphoreGiveFromISR(s_CardDetectSemaphore, NULL);
}

static void CardDetectTask(void *pvParameters)
{
    s_CardDetectSemaphore = xSemaphoreCreateBinary();

    BOARD_SD_Config(&g_sd, SDCARD_DetectCallBack, BOARD_SDMMC_SD_HOST_IRQ_PRIORITY, NULL);

    /* SD host init function */
    if (SD_HostInit(&g_sd) == kStatus_Success)
    {
        while (true)
        {
            /* take card detect semaphore */
            if (xSemaphoreTake(s_CardDetectSemaphore, portMAX_DELAY) == pdTRUE)
            {
                if (s_cardInserted != s_cardInsertStatus)
                {
                    s_cardInserted = s_cardInsertStatus;

                    if (s_cardInserted)
                    {
                        PRINTF("\r\nCard inserted.\r\n");
                        /* power off card */
                        SD_SetCardPower(&g_sd, false);
                        /* power on the card */
                        SD_SetCardPower(&g_sd, true);
                        /* make file system */
                        if (DEMO_MakeFileSystem() != kStatus_Success)
                        {
                            continue;
                        }
                        xTaskNotifyGive(fileAccessTaskHandle);
                    }
                }

                if (!s_cardInserted)
                {
                    PRINTF("\r\nPlease insert a card into board.\r\n");
                }
            }
        }
    }
    else
    {
        PRINTF("\r\nSD host init fail\r\n");
    }

    vTaskSuspend(NULL);
}

static status_t DEMO_MakeFileSystem(void)
{
    FRESULT error;
    const TCHAR driverNumberBuffer[3U] = {SDDISK + '0', ':', '/'};
    BYTE work[FF_MAX_SS];

    if (f_mount(&g_fileSystem, driverNumberBuffer, 0U))
    {
        PRINTF("Mount volume failed.\r\n");
        return kStatus_Fail;
    }

#if (FF_FS_RPATH >= 2U)
    error = f_chdrive((char const *)&driverNumberBuffer[0U]);
    if (error)
    {
        PRINTF("Change drive failed.\r\n");
        return kStatus_Fail;
    }
#endif

#if FF_USE_MKFS
    PRINTF("\r\nMake file system......The time may be long if the card capacity is big.\r\n");
    if (f_mkfs(driverNumberBuffer, 0, work, sizeof work))
    {
        PRINTF("Make file system failed.\r\n");
        return kStatus_Fail;
    }
#endif /* FF_USE_MKFS */

    PRINTF("\r\nCreate directory......\r\n");
    error = f_mkdir(_T("/dir_1"));
    if (error)
    {
        if (error == FR_EXIST)
        {
            PRINTF("Directory exists.\r\n");
        }
        else
        {
            PRINTF("Make directory failed.\r\n");
            return kStatus_Fail;
        }
    }
    else
    {
        PRINTF("\r\nDirectory created.\r\n");
    }

    return kStatus_Success;
}