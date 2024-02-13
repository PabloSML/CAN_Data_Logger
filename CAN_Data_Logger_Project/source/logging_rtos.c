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
// #include "fsl_rtc.h"
#include "limits.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define DEMO_WRITE_TIMES 10U
#define PRINT_CAN_MSG 0
#define FIRST_MSG_LIGHT 1
#define CREATE_DIR 1

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

static void SDCARD_DetectCallBack(bool isInserted, void *userData);
static status_t DEMO_MakeFileSystem(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/

static bool fileOpen = false;
static bool sdHostInit = false;
static bool sdCardInit = false;
static FIL g_fileObject;  /* File object */
static FATFS g_fileSystem; /* File system object */
/*! @brief SD card detect flag  */
static volatile bool s_cardInserted     = false;
static volatile bool s_cardInsertStatus = false;
/*! @brief Card semaphore  */
static SemaphoreHandle_t s_CardDetectSemaphore = NULL;
static TaskHandle_t* fileAccessTaskHandle;

// Buffer initialization
static char buffer[1024] = {0};
static uint16_t bufferSize;
static uint16_t bufferWriteThreshold;
static size_t bufferIndex = 0;
static UINT bytesWritten   = 0U;

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

static int appendNumber(char* buffer, int bufferIndex, int number, int width, bool isHex) {
    static char digits[] = "0123456789ABCDEF";
    for (int i = width - 1; i >= 0; --i) {
        int digit = number % (isHex ? 16 : 10);
        buffer[bufferIndex + i] = digits[digit];
        number /= (isHex ? 16 : 10);
    }
    return bufferIndex + width;
}

static int writeDateToBuffer(char* buffer, int bufferIndex, rtc_datetime_t* date) {
    bufferIndex = appendNumber(buffer, bufferIndex, date->year, 4, false);
    buffer[bufferIndex++] = ',';
    bufferIndex = appendNumber(buffer, bufferIndex, date->month, 2, false);
    buffer[bufferIndex++] = ',';
    bufferIndex = appendNumber(buffer, bufferIndex, date->day, 2, false);
    buffer[bufferIndex++] = ',';
    bufferIndex = appendNumber(buffer, bufferIndex, date->hour, 2, false);
    buffer[bufferIndex++] = ',';
    bufferIndex = appendNumber(buffer, bufferIndex, date->minute, 2, false);
    buffer[bufferIndex++] = ',';
    bufferIndex = appendNumber(buffer, bufferIndex, date->second, 2, false);
    buffer[bufferIndex++] = ',';
    bufferIndex = appendNumber(buffer, bufferIndex, date->milisecond, 3, false);
    buffer[bufferIndex++] = ',';
    return bufferIndex;
}

static int writeCANMessageToBuffer(char* buffer, int bufferIndex, can_msg_t* canMsg) {
    bufferIndex = appendNumber(buffer, bufferIndex, canMsg->id, 3, true);
    buffer[bufferIndex++] = ',';
    bufferIndex = appendNumber(buffer, bufferIndex, canMsg->length, 1, false);
    buffer[bufferIndex++] = ',';
    for (int i = 0; i < 8; ++i) {
        if (8-i <= canMsg->length)
            bufferIndex = appendNumber(buffer, bufferIndex, canMsg->data[i], 2, true);
        else
            bufferIndex = appendNumber(buffer, bufferIndex, 0, 2, true);
        buffer[bufferIndex++] = ',';
    }
    buffer[bufferIndex++] = '\r';
    buffer[bufferIndex++] = '\n';
    return bufferIndex;
}

static int writeToBuffer(char* buffer, int bufferIndex, can_msg_t* canMsg) {
    bufferIndex = writeDateToBuffer(buffer, bufferIndex, &canMsg->timestamp);
    bufferIndex = writeCANMessageToBuffer(buffer, bufferIndex, canMsg);
    return bufferIndex;
}

static void CloseLoggingFile(void)
{
    if (fileOpen)
    {
        if (bufferIndex > 0)
            f_write(&g_fileObject, buffer, bufferIndex, &bytesWritten);
        f_close(&g_fileObject);
        fileOpen = false;
    }
}

static void ShutdownSDCard(void)
{
    if (sdCardInit)
    {
        SD_SetCardPower(&g_sd, false);
        sdCardInit = false;
    }
    if (sdHostInit)
    {
        SD_HostDeinit(&g_sd);
        sdHostInit = false;
    }
}

void Init_Logging(TaskHandle_t* handle)
{
    fileAccessTaskHandle = handle;
}

void StopLogging(void)
{
    if (fileOpen)
    {
        vTaskSuspend(*fileAccessTaskHandle);
    }
    CloseLoggingFile();
    ShutdownSDCard();
}

void FileAccessTask(void *pvParameters)
{
    rtc_datetime_t date;
    // UINT bytesWritten   = 0U;
    uint32_t writeTimes = 0U;
    FRESULT error;

    xTaskNotifyWait(ULONG_MAX, ULONG_MAX, NULL, portMAX_DELAY);

    // Initialize File
    char fileName[30];
    RTC_GetDatetime(RTC, &date);
    sprintf(fileName, "logs/%02d_%02d_%02d/%02d_%02d_%02d.csv", (date.year)%100, date.month, date.day, date.hour, date.minute, date.second);
    error = f_open(&g_fileObject, _T(fileName), FA_WRITE | FA_OPEN_APPEND);
    if (error)
    {
        if (error == FR_NO_FILE)
        {
            error = f_open(&g_fileObject, _T(fileName), FA_WRITE | FA_CREATE_NEW);
            if (error)
            {
#if BOARD == CANDLE
                BOARD_WriteLEDs(3);
#elif BOARD == FRDM
                BOARD_WriteLEDs(true, false, false);
                PRINTF("Create file failed with error code %d.\r\n", error);
#endif
                return;
            }
        }
        else
        {
#if BOARD == CANDLE
            BOARD_WriteLEDs(4);
#elif BOARD == FRDM
            BOARD_WriteLEDs(true, false, false);
            PRINTF("Open file failed with error code %d.\r\n", error);
#endif
            return;
        }
    }
    fileOpen = true;

    // Write header to the file
    char s_buffer0[] = "Year,Month,Day,Hour,Minute,Second,Milisecond,ID,Data Length,B7,B6,B5,B4,B3,B2,B1,B0\r\n";
    error = f_write(&g_fileObject, s_buffer0, sizeof(s_buffer0) - 1, &bytesWritten);
    if (error || (bytesWritten != sizeof(s_buffer0) - 1))
    {
        // Handle error
#if BOARD == CANDLE
        BOARD_WriteLEDs(4);
#elif BOARD == FRDM
        BOARD_WriteLEDs(true, false, false);
        PRINTF("Write file header failed with error code %d.\r\n", error);
#endif
        CloseLoggingFile();
        return; // Exit the task if header can't be written
    }

#if BOARD == CANDLE
    BOARD_WriteLEDs(5);
#elif BOARD == FRDM
    BOARD_WriteLEDs(true, true, false);
#endif

#if FIRST_MSG_LIGHT
    bool firstTime = true;
#endif
    // CAN message initialization
    QueueHandle_t canMsgQueue = getCanMsgQueue();
    can_msg_t canMsg;
    bufferSize = sizeof(buffer);
    bufferWriteThreshold = bufferSize - 50;

    while (1)
    {
        if (xQueueReceive(canMsgQueue, &canMsg, portMAX_DELAY) == pdTRUE)   // Suspende la tarea hasta que haya un mensaje en la cola
        {
#if FIRST_MSG_LIGHT
            if (firstTime)
            {
#if BOARD == CANDLE
                BOARD_WriteLEDs(6);
#elif BOARD == FRDM
                BOARD_WriteLEDs(false, true, true);
#endif
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

        // if (writeTimes < DEMO_WRITE_TIMES)
        // {
        bufferIndex = writeToBuffer(buffer, bufferIndex, &canMsg);

        if (bufferIndex >= bufferWriteThreshold) // Threshold to write, adjust as needed
        {
            error = f_write(&g_fileObject, buffer, bufferIndex, &bytesWritten);
            if (error || (bytesWritten != bufferIndex))
            {
#if BOARD == CANDLE
                BOARD_WriteLEDs(7);
#elif BOARD == FRDM
                PRINTF("Write file failed with error code %d.\r\n", error);
                BOARD_WriteLEDs(true, false, false);
#endif
                CloseLoggingFile();
                break;
            }
            bufferIndex = 0; // Reset buffer index after writing

            if (++writeTimes == DEMO_WRITE_TIMES)
            {
                // PRINTF("TASK: finished.\r\n");
                CloseLoggingFile();
#if BOARD == CANDLE
                BOARD_WriteLEDs(0);
#elif BOARD == FRDM
                BOARD_WriteLEDs(false, true, false);
#endif
                // xTaskNotifyWait(ULONG_MAX, ULONG_MAX, NULL, portMAX_DELAY);
                break;
            }
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

void CardDetectTask(void *pvParameters)
{
    s_CardDetectSemaphore = xSemaphoreCreateBinary();

    BOARD_SD_Config(&g_sd, SDCARD_DetectCallBack, BOARD_SDMMC_SD_HOST_IRQ_PRIORITY, NULL);

    /* SD host init function */
    if (SD_HostInit(&g_sd) == kStatus_Success)
    {
        sdHostInit = true;
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
                        sdCardInit = true;
                        /* power off card */
                        SD_SetCardPower(&g_sd, false);
                        /* power on the card */
                        SD_SetCardPower(&g_sd, true);
                        /* make file system */
                        if (DEMO_MakeFileSystem() != kStatus_Success)
                        {
                            continue;
                        }
#if BOARD == CANDLE
                        BOARD_WriteLEDs(2);
#elif BOARD == FRDM
                        PRINTF("\r\nFile system ready.\r\n");
                        BOARD_WriteLEDs(false, false, true);
#endif
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
    // PRINTF("\r\nCreate directory......\r\n");
    rtc_datetime_t date;
    RTC_GetDatetime(RTC, &date);
    char folderName[15];
    sprintf(folderName, "/logs/%02d_%02d_%02d", (date.year)%100, date.month, date.day);
    error = f_mkdir(_T(folderName));
    if (error)
    {
        if (error == FR_EXIST)
        {
            // PRINTF("Directory exists.\r\n");
        }
        else
        {
#if BOARD == CANDLE
            BOARD_WriteLEDs(1);
#elif BOARD == FRDM
            PRINTF("Make directory failed.\r\n");
            BOARD_WriteLEDs(true, false, false);
#endif
            return kStatus_Fail;
        }
    }
    else
    {
        // PRINTF("\r\nDirectory created.\r\n");
    }
#endif

    return kStatus_Success;
}
