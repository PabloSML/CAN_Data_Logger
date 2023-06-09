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

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define FLEXCAN_TASK_STACK_SIZE 512

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
  uint32_t timestamp;
  uint32_t id;
  uint8_t length;
  uint8_t data[8];
//  bool ack;
} can_msg_t;

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

void Init_FlexCAN(void);

/*
* @brief Function that returns the queue used to store the CAN messages
*/
QueueHandle_t getCanMsgQueue(void);

/**
 * @brief Task that handles the FlexCan module and transfers data to the SD card task
 */
void FlexCanTask(void *pvParameters);

SemaphoreHandle_t getCanMsgSemaphore(void);
/*******************************************************************************
 ******************************************************************************/

#endif // _FLEXCAN_RTOS_H_
