/***************************************************************************//**
  @file     logging_rtos.h
  @brief    Logging RTOS Header File
  @author   Grupo CAN Data Logger
 ******************************************************************************/

#ifndef _LOGGING_RTOS_H_
#define _LOGGING_RTOS_H_

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

#define CREATE_DIR 0

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/


/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

void Init_CardDetect(TaskHandle_t* handle);
/*
* @brief complete documentation for this function :)
*/
void CardDetectTask(void *pvParameters);
void FileAccessTask(void *pvParameters);
void CloseLoggingFile(void);


/*******************************************************************************
 ******************************************************************************/

#endif // _LOGGING_RTOS_H_
