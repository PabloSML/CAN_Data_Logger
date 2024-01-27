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
#include "drive_rtos.h"

#define DEMO_TASK_GET_SEM_BLOCK_TICKS 1U
#define DEMO_TASK_ACCESS_SDCARD_TIMES 254U
#define ACCESSFILE_TASK_STACK_SIZE (512U)
#define ACCESSFILE_TASK_PRIORITY (configMAX_PRIORITIES - 2U)
#define CARDDETECT_TASK_STACK_SIZE (512U)
#define CARDDETECT_TASK_PRIORITY (configMAX_PRIORITIES - 1U)
#define FLEXCAN_TASK_PRIORITY (configMAX_PRIORITIES - 3U)
#define DRIVE_TASK_PRIORITY (configMAX_PRIORITIES - 3U)

// Modes of operation
typedef enum
{
    LOGGER_MODE,
    DRIVE_MODE
} op_mode_t;

// Variables
static FATFS g_fileSystem; /* File system object */
static FIL g_fileObject1;  /* File object */

/* Data structure of msc device, store the information ,such as class handle */
usb_msc_struct_t g_msc;

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

static void APP_task(void *pvParameters)
{
    //xNextWakeTime = xTaskGetTickCount();
    static unsigned long counter = 0;
    rtc_datetime_t date;

    while(true)
    {
        /* Get date time */
        RTC_GetDatetime(RTC, &date);
        PRINTF("Current datetime: %04hd-%02hd-%02hd %02hd:%02hd:%02hd\r\n", date.year, date.month, date.day, date.hour,
                date.minute, date.second);
        
        counter++;
        
        PRINTF("Hola Mundo #%d, milisegundos: %d\n\n", counter, xTaskGetTickCount());
        
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

    // SemaphoreHandle_t s_CanMsgSemaphore = getCanMsgSemaphore();
    QueueHandle_t canMsgQueue = getCanMsgQueue();
    can_msg_t canMsg;

    while (1)
    {

        // vTaskDelay(1000);
        // if (xSemaphoreTake(s_CanMsgSemaphore, portMAX_DELAY) == pdTRUE){

        if (xQueueReceive(canMsgQueue, &canMsg, portMAX_DELAY) == pdTRUE)   // Suspende la tarea hasta que haya un mensaje en la cola
        {
            GPIO_PinWrite(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_PIN, LOGIC_LED_ON);
            // PRINTF("\r\nHola, recibí un mensaje de CAN!\r\n");
            // PRINTF("Timestamp = %d\r\n", canMsg.timestamp);
            // PRINTF("ID = 0x%x\r\n", canMsg.id);
            // PRINTF("Length = %d\r\n", canMsg.length);
            // PRINTF("Data = ");
            // for (uint8_t i = 0; i < canMsg.length; i++)
            // {
            //     PRINTF("0x%x ", canMsg.data[i]);
            // }
            // PRINTF("\r\n");
        }
        else
        {
            PRINTF("No pude encontrar los datos en la queue :(\r\n");
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
                    GPIO_PinWrite(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_PIN, LOGIC_LED_OFF);
                    GPIO_PinWrite(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_PIN, LOGIC_LED_OFF);
                    GPIO_PinWrite(BOARD_LED_RED_GPIO, BOARD_LED_RED_PIN, LOGIC_LED_ON);
                    PRINTF("Create file failed.\r\n");
                    break;
                }
            }
            else
            {
                GPIO_PinWrite(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_PIN, LOGIC_LED_OFF);
                GPIO_PinWrite(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_PIN, LOGIC_LED_OFF);
                GPIO_PinWrite(BOARD_LED_RED_GPIO, BOARD_LED_RED_PIN, LOGIC_LED_ON);
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
        
        char s_buffer0[] = "Year,Month,Day,Hour,Minute,Second,CAN Timestamp,ID,Data Lenght,B0,B1,B2,B3,B4,B5,B6,B7\r\n";
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
        sprintf(s_buffer1, "%04hd,%02hd,%02hd,%02hd,%02hd,%02hd,%d,%08x,%d,%02x,%02x,%02x,%02x,%02x,%02x,%02x,%02x\r\n", 
        date.year, date.month, date.day, date.hour, date.minute, date.second, canMsg.timestamp, canMsg.id, canMsg.length, canMsg.data[0], canMsg.data[1], canMsg.data[2], canMsg.data[3], canMsg.data[4], canMsg.data[5], canMsg.data[6], canMsg.data[7]);
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
            GPIO_PinWrite(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_PIN, LOGIC_LED_OFF);
            writeTimes = 1U;
            xTaskNotifyWait(ULONG_MAX, ULONG_MAX, NULL, portMAX_DELAY);
            continue;
        }
        {
            // PRINTF("TASK: write file succeded.\r\n");
        }

        // }
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
        PRINTF("\r\nPlease insert a card into board.\r\n");
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
                        PRINTF("\r\nFile system ready.\r\n");
                        GPIO_PinWrite(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_PIN, LOGIC_LED_ON);
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

    // PRINTF("\r\nCreate directory......\r\n");
    // error = f_mkdir(_T("/dir_1"));
    // if (error)
    // {
    //     if (error == FR_EXIST)
    //     {
    //         PRINTF("Directory exists.\r\n");
    //     }
    //     else
    //     {
    //         PRINTF("Make directory failed.\r\n");
    //         GPIO_PinWrite(BOARD_LED_RED_GPIO, BOARD_LED_RED_PIN, LOGIC_LED_ON);
    //         return kStatus_Fail;
    //     }
    // }
    // else
    // {
    //     PRINTF("\r\nDirectory created.\r\n");
    // }

    return kStatus_Success;
}
