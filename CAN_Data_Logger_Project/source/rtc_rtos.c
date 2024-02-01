/***************************************************************************//**
  @file     rtc_rtos.c
  @brief    RTC RTOS Source File
  @author   Grupo CAN Data Logger
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "rtc_rtos.h"
#include "MK64F12.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

void Init_RTC(bool configureDateTime)
{
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

    if (configureDateTime)
    {
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
    }
}
