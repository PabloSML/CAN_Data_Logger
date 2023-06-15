/***************************************************************************//**
  @file     drive_rtos.h
  @brief    Drive RTOS Header File
  @author   Grupo CAN Data Logger
 ******************************************************************************/

#ifndef _DRIVE_RTOS_H_
#define _DRIVE_RTOS_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "FreeRTOS.h"
// #include "semphr.h"
// #include "task.h"
// #include "queue.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define DRIVE_TASK_STACK_SIZE 512

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/


/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

void Init_Drive(void);

/**
 * @brief Task that handles the drive mode for SD card file access via USB
 */
void DriveTask(void *pvParameters);

/*******************************************************************************
 ******************************************************************************/

// Old .h file, restructure above!!

#if defined(USB_DEVICE_CONFIG_EHCI) && (USB_DEVICE_CONFIG_EHCI > 0)
#define CONTROLLER_ID kUSB_ControllerEhci0
#endif
#if defined(USB_DEVICE_CONFIG_KHCI) && (USB_DEVICE_CONFIG_KHCI > 0)
#define CONTROLLER_ID kUSB_ControllerKhci0
#endif
#if defined(USB_DEVICE_CONFIG_LPCIP3511FS) && (USB_DEVICE_CONFIG_LPCIP3511FS > 0U)
#define CONTROLLER_ID kUSB_ControllerLpcIp3511Fs0
#endif
#if defined(USB_DEVICE_CONFIG_LPCIP3511HS) && (USB_DEVICE_CONFIG_LPCIP3511HS > 0U)
#define CONTROLLER_ID kUSB_ControllerLpcIp3511Hs0
#endif

#if defined(__GIC_PRIO_BITS)
#define USB_DEVICE_INTERRUPT_PRIORITY (25U)
#elif defined(__NVIC_PRIO_BITS) && (__NVIC_PRIO_BITS >= 3)
#define USB_DEVICE_INTERRUPT_PRIORITY (6U)
#else
#define USB_DEVICE_INTERRUPT_PRIORITY (3U)
#endif
/* application define logical unit number, if LOGICAL_UNIT_SUPPORTED > USB_DEVICE_MSC_MAX_LUN, update
 * USB_DEVICE_MSC_MAX_LUN in class driver usb_device_msc.h*/
#define LOGICAL_UNIT_SUPPORTED (1U)

#define USB_DEVICE_MSC_WRITE_BUFF_NUM (3U)
/* USB MSC config*/
/*buffer size for sd card example. the larger the buffer size ,the faster the data transfer speed is ,*/
/*the block size should be multiple of 512, the least value is 512*/

#define USB_DEVICE_MSC_WRITE_BUFF_SIZE (512 * 8U)
#define USB_DEVICE_MSC_READ_BUFF_SIZE  (512 * 8U)


#define USB_DEVICE_SDCARD_BLOCK_SIZE_POWER (9U)
#define USB_DEVICE_MSC_ADMA_TABLE_WORDS    (8U)

#define USB_DEVICE_MSC_USE_WRITE_TASK (0U)
typedef struct _usb_msc_struct
{
    usb_device_handle deviceHandle;
    class_handle_t mscHandle;
    TaskHandle_t device_task_handle;
    TaskHandle_t application_task_handle;
    uint8_t diskLock;
    uint8_t read_write_error;
    uint8_t currentConfiguration;
    uint8_t currentInterfaceAlternateSetting[USB_MSC_INTERFACE_COUNT];
    uint8_t speed;
    uint8_t attach;
} usb_msc_struct_t;

#endif // _DRIVE_RTOS_H_
