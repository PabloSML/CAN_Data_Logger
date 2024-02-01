#include "logging_rtos.h"
#include "flexcan_rtos.h"

#include <stdio.h>
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "MK64F12.h"
#include "board.h"
#include "ff.h"
#include "fsl_sd.h"
#include "fsl_sd_disk.h"
#include "sdmmc_config.h"
#include "diskio.h"
#include "fsl_rtc.h"
#include "limits.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define DEMO_WRITE_TIMES 10U
#define PRINT_CAN_MSG 0
#define FIRST_MSG_LIGHT 0

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void SDCARD_DetectCallBack(bool isInserted, void *userData);
static status_t DEMO_MakeFileSystem(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/

static FIL g_fileObject1;  /* File object */
static FATFS g_fileSystem; /* File system object */
/*! @brief SD card detect flag  */
static volatile bool s_cardInserted     = false;
static volatile bool s_cardInsertStatus = false;
/*! @brief Card semaphore  */
static SemaphoreHandle_t s_CardDetectSemaphore = NULL;
static TaskHandle_t* fileAccessTaskHandle;

/*******************************************************************************
 * Code
 ******************************************************************************/

#if PRINT_CAN_MSG
static void PrintCanMsg(can_msg_t* canMsg)
{
    PRINTF("\r\nHola, recibí un mensaje de CAN!\r\n");
    PRINTF("Timestamp = %d\r\n", canMsg->timestamp);
    PRINTF("ID = 0x%x\r\n", canMsg->id);
    PRINTF("Length = %d\r\n", canMsg->length);
    PRINTF("Data = ");
    for (uint8_t i = 0; i < canMsg->length; i++)
    {
        PRINTF("0x%x ", canMsg->data[i]);
    }
    PRINTF("\r\n");
}
#endif

void FileAccessTask(void *pvParameters)
{
    rtc_datetime_t date;
    UINT bytesWritten   = 0U;
    uint32_t writeTimes = 0U;
    FRESULT error;

    xTaskNotifyWait(ULONG_MAX, ULONG_MAX, NULL, portMAX_DELAY);

    // Initialize File
    error = f_open(&g_fileObject1, _T("/dir_1/magic.csv"), FA_WRITE | FA_OPEN_APPEND);
    if (error)
    {
        if (error == FR_NO_FILE)
        {
            error = f_open(&g_fileObject1, _T("/dir_1/magic.csv"), FA_WRITE | FA_CREATE_NEW);
            if (error)
            {
                BOARD_WriteLEDs(true, false, false);
                PRINTF("Create file failed with error code %d.\r\n", error);
                return;
            }
        }
        else
        {
            BOARD_WriteLEDs(true, false, false);
            PRINTF("Open file failed with error code %d.\r\n", error);
            return;
        }
    }

    // Write header to the file
    char s_buffer0[] = "Year,Month,Day,Hour,Minute,Second,CAN Timestamp,ID,Data Length,B0,B1,B2,B3,B4,B5,B6,B7\r\n";
    error = f_write(&g_fileObject1, s_buffer0, sizeof(s_buffer0) - 1, &bytesWritten);
    if (error || (bytesWritten != sizeof(s_buffer0) - 1))
    {
        // Handle error
        BOARD_WriteLEDs(true, false, false);
        PRINTF("Write file header failed with error code %d.\r\n", error);
        CloseLoggingFile();
        return; // Exit the task if header can't be written
    }
    BOARD_WriteLEDs(true, true, false);

#if FIRST_MSG_LIGHT
    bool firstTime = true;
#endif
    // CAN message initialization
    QueueHandle_t canMsgQueue = getCanMsgQueue();
    can_msg_t canMsg;
    // Buffer initialization
    char buffer[1024] = {0};
    uint16_t bufferSize = sizeof(buffer);
    uint16_t bufferWriteThreshold = bufferSize - 50;
    size_t bufferIndex = 0;

    while (1)
    {
        if (xQueueReceive(canMsgQueue, &canMsg, portMAX_DELAY) == pdTRUE)   // Suspende la tarea hasta que haya un mensaje en la cola
        {
            /* Get date time */
            RTC_GetDatetime(RTC, &date);
#if FIRST_MSG_LIGHT
            if (firstTime)
            {
                BOARD_WriteLEDs(false, true, true);
                firstTime = false;
            }
#endif
#if PRINT_CAN_MSG
            PrintCanMsg(&canMsg);
#endif
        }
        else
        {
            PRINTF("No pude encontrar los datos en la queue :(\r\n");
        }

        // Process the message...
        int len = snprintf(buffer + bufferIndex, sizeof(buffer) - bufferIndex, 
            "%04hd,%02hd,%02hd,%02hd,%02hd,%02hd,%d,%08x,%d,%02x,%02x,%02x,%02x,%02x,%02x,%02x,%02x\r\n",
            date.year, date.month, date.day, date.hour, date.minute, date.second, canMsg.timestamp, canMsg.id, canMsg.length,
            canMsg.data[0], canMsg.data[1], canMsg.data[2], canMsg.data[3], canMsg.data[4], canMsg.data[5], canMsg.data[6], canMsg.data[7]
        );

        if (len > 0)
        {
            bufferIndex += len;
        }

        if (bufferIndex >= bufferWriteThreshold) // Threshold to write, adjust as needed
        {
            // CHECK IF NECESSARY
            // /* write append */
            // if (f_lseek(&g_fileObject1, g_fileObject1.obj.objsize) != FR_OK)
            // {
            //     PRINTF("lseek file failed.\r\n");
            //     break;
            // }
            error = f_write(&g_fileObject1, buffer, bufferIndex, &bytesWritten);
            if (error || (bytesWritten != bufferIndex))
            {
                PRINTF("Write file failed with error code %d.\r\n", error);
                BOARD_WriteLEDs(true, false, false);
                CloseLoggingFile();
                break;
            }
            // f_sync(&g_fileObject1);
            bufferIndex = 0; // Reset buffer index after writing

            if (++writeTimes >= DEMO_WRITE_TIMES)
            {
                PRINTF("TASK: finished.\r\n");
                BOARD_WriteLEDs(false, true, false);
                CloseLoggingFile();
                xTaskNotifyWait(ULONG_MAX, ULONG_MAX, NULL, portMAX_DELAY);
                break;
            }
        }
    }

    vTaskSuspend(NULL);
}

void CloseLoggingFile(void)
{
    f_close(&g_fileObject1);
}

static void SDCARD_DetectCallBack(bool isInserted, void *userData)
{
    s_cardInsertStatus = isInserted;
    xSemaphoreGiveFromISR(s_CardDetectSemaphore, NULL);
}

void Init_CardDetect(TaskHandle_t* handle)
{
    fileAccessTaskHandle = handle;
}

void CardDetectTask(void *pvParameters)
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
                        BOARD_WriteLEDs(false, false, true);
                        xTaskNotifyGive(*fileAccessTaskHandle);
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
#if FF_USE_MKFS
    BYTE work[FF_MAX_SS];
#endif

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

#if CREATE_DIR
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
            GPIO_PinWrite(BOARD_LED_RED_GPIO, BOARD_LED_RED_PIN, LOGIC_LED_ON);
            return kStatus_Fail;
        }
    }
    else
    {
        PRINTF("\r\nDirectory created.\r\n");
    }
#endif

    return kStatus_Success;
}
