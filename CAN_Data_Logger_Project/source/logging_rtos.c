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

#define DEMO_WRITE_TIMES 254U

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

/*******************************************************************************
 * Code
 ******************************************************************************/

void FileAccessTask(void *pvParameters)
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

        if (++writeTimes > DEMO_WRITE_TIMES)
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

void CardDetectTask(void *pvParameters)
{
    s_CardDetectSemaphore = xSemaphoreCreateBinary();
    TaskHandle_t fileAccessTaskHandle;

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
