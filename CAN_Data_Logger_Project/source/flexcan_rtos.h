/***************************************************************************//**
  @file     flexcan_rtos.h
  @brief    FlexCan RTOS Header File
  @author   Grupo CAN Data Logger
 ******************************************************************************/

#ifndef _FLEXCAN_RTOS_H_
#define _FLEXCAN_RTOS_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "queue.h"
#include "rtc_rtos.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

// Struct containing the data of a CAN message
/*
  Fields:
    id: CAN message ID
    timestamp: CAN message timestamp
    data: CAN message data
    length: CAN message length
    ack: CAN message ACK
*/
typedef struct {
  rtc_datetime_t timestamp;
  uint32_t id;
  uint8_t length;
  uint8_t data[8];
} can_msg_t;

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/*
* @brief Function that initializes the FlexCAN module
*/
void Init_FlexCAN(TaskHandle_t* handle);

/*
* @brief Function that stops the FlexCAN module
*/
void StopFlexCAN(void);

/*
* @brief Function that returns the queue used to store the CAN messages
*/
QueueHandle_t getCanMsgQueue(void);

/**
 * @brief Task that handles the FlexCan module and transfers data to the SD card task
 */
void FlexCanTask(void *pvParameters);

/*******************************************************************************
 ******************************************************************************/

#endif // _FLEXCAN_RTOS_H_
