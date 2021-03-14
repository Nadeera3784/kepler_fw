/******************************************************************************

 @file  f91_clock.c

 @brief This file contains the F91 Kepler Smart Watch clock application.

 Target Device: cc2640r2

 ******************************************************************************

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 ******************************************************************************
 
 
 *****************************************************************************/
#include <string.h>

/* XDC module Headers */
#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Error.h>

#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Event.h>
#include <ti/sysbios/knl/Queue.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/gates/GateMutex.h>
#include <ti/sysbios/BIOS.h>
#include <ti/display/Display.h>
#include <time.h>
#include <ti/sysbios/hal/Seconds.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include <icall.h>
#include "util.h"
#include "att_rsp.h"

/* This Header file contains all BLE API and icall structure definition */
#include "icall_ble_api.h"

#include "devinfoservice.h"
#include "ll_common.h"
#include "board_key.h"

#include "board.h"

#include "ssd1306.h"
#include "f91_utils.h"
#include "f91_clock.h"
#include "f91_clock_service.h"


/*********************************************************************
 * CONSTANTS
 */

// Task configuration
#define F91_CLOCK_TASK_PRIORITY                     1

#ifndef F91_CLOCK_TASK_STACK_SIZE
#define F91_CLOCK_TASK_STACK_SIZE                   644
#endif


// Internal Events for RTOS application
#define F91_ICALL_EVT                         ICALL_MSG_EVENT_ID // Event_Id_31
#define F91_QUEUE_EVT                         UTIL_QUEUE_EVENT_ID // Event_Id_30
#define F91_PERIODIC_EVT                      Event_Id_00

// Bitwise OR of all events to pend on
#define F91_ALL_EVENTS                        (F91_ICALL_EVT        | \
                                               F91_QUEUE_EVT        | \
                                               F91_PERIODIC_EVT)
/*********************************************************************
 * LOCAL VARIABLES
 */

// Entity ID globally used to check for source and/or destination of messages
static ICall_EntityID selfEntity;

static ICall_SyncHandle syncEvent;

// Task configuration
Task_Struct f91ClockTask;
Char f91ClockTaskStack[F91_CLOCK_TASK_STACK_SIZE];

// Event globally used to post local events and pend on system and
// local events.
static ICall_SyncHandle syncEvent;

// Time Zone
static uint16_t TimeZone;

// For clock (24/12hr mode)
static bool TimeMode = true;

// Daylight Saving
static bool Dst = false;

/*********************************************************************
 * LOCAL FUNCTIONS
 */
static void F91Clock_internal_init( void );
static void F91Clock_taskFxn(UArg a0, UArg a1);
static void F91Clock_doTime(void);
static void F91Clock_setTime(uint32_t time);
static void F91Clock_setTimeZone(uint16_t zone);
static void F91Clock_setTimeMode(uint8_t mode);
static void F91Clock_setDst(uint8_t mode);
static uint16_t F91Clock_getTimeZone( void );
static bool F91Clock_getTimeMode( void );
static bool F91Clock_getDst( void );


/*********************************************************************
 * @fn      F91Clock_setTime
 *
 * @brief   Sets time for the clock
 *
 * @param   time - self explanatory.
 *
 */
static void F91Clock_setTime(uint32_t time)
{
    Seconds_set(time);
}

/*********************************************************************
 * @fn      F91Clock_setTimeZone
 *
 * @brief   Sets time zone for the clock
 *
 * @param   timezone - self explanatory.
 *
 */
static void F91Clock_setTimeZone(uint16_t zone)
{
    TimeZone = zone;
    F91_clock_service_SetParameter(F91_CLOCK_SERVICE_CHAR2, sizeof(uint16_t), &TimeZone);
}

/*********************************************************************
 * @fn      F91Clock_setTimeMode
 *
 * @brief   Sets time mode for the clock 
 *
 * @param   mode - (0: 12hr  1: 24hr).
 *
 */
static void F91Clock_setTimeMode(uint8_t mode)
{
    switch ( mode )
    {
        case 0:
            TimeMode = false;
        break;
        case 1:
            TimeMode = true;
        break;
        default:
            mode = 0;
            TimeMode = false;
        break;
    }

    F91_clock_service_SetParameter(F91_CLOCK_SERVICE_CHAR3, 1, &mode);
}

/*********************************************************************
 * @fn      F91Clock_setDaylightSavings
 *
 * @brief   Sets daylight savings for the clock 
 *
 * @param   mode - (0: 12hr  1: 24hr).
 *
 */
static void F91Clock_setDst(uint8_t mode)
{
    switch ( mode )
    {
        case 0:
            Dst = false;
        break;
        case 1:
            Dst = true;
        break;
        default:
            mode = 0;
            Dst = false;
        break;
    }

    F91_clock_service_SetParameter(F91_CLOCK_SERVICE_CHAR3, 1, &mode);
}

/*********************************************************************
 * @fn      F91Clock_getTimeZone
 *
 * @brief   Returns time zone
 *
 * @param   none
 *
 */
static uint16_t F91Clock_getTimeZone( void )
{
    return TimeZone;
}

/*********************************************************************
 * @fn      F91Clock_getDst
 *
 * @brief   Returns daylight savings state.
 *
 * @param   none
 *
 */
static bool F91Clock_getDst( void )
{
    return Dst;
}


/*********************************************************************
 * @fn      F91Clock_getTimeMode
 *
 * @brief   Returns the mode to display clock (24 or 12 hr)
 *
 * @param   none
 *
 */
static bool F91Clock_getTimeMode( void )
{
    return TimeMode;
}

 /*********************************************************************
 * @fn      F91Clock_createTask
 *
 * @brief   Task creation function for the F91 Kepler Smart Watch clock application.
 *
 * @param   None.
 *
 * @return  None.
 */
void F91Clock_createTask(void)
{
    Task_Params taskParams;

    // Configure task
    Task_Params_init(&taskParams);
    taskParams.stack = f91ClockTaskStack;
    taskParams.stackSize = F91_CLOCK_TASK_STACK_SIZE;
    taskParams.priority = F91_CLOCK_TASK_PRIORITY;

    Task_construct(&f91ClockTask, F91Clock_taskFxn, &taskParams, NULL);
}

/*********************************************************************
 * @fn      F91Clock_internal_init
 *
 * @brief   Called during initialization and contains application
 *          specific initialization (ie. hardware initialization/setup,
 *          table initialization, power up notification, etc), and
 *          profile initialization/setup.
 *
 * @param   None.
 *
 * @return  None.
 */
static void F91Clock_internal_init(void)
{  
    // Register the current thread as an ICall dispatcher application
    // so that the application can send and receive messages.
    ICall_registerApp(&selfEntity, &syncEvent);

    // initialize the SSD1306 display. 
    ssd1306_init();

    //**************set default time & zone (00:00:00 01/14/1994)(UTC) & PST************
    F91Clock_setTime(DEFAULT_TIME);
    F91Clock_setTimeZone(TZ_PST);
    F91Clock_setTimeMode(0);
    F91Clock_setDst(0);
    //***********************************************************
}

static void F91Clock_doTime(void) {
    time_t t1;
    struct tm *ltm;
    bool eraseFirstDigit;
    char *dateString;
    char hour[2];
    char minute[2];
    char second[2];
    char month[2];
    char day[2];
    uint32_t timeInSeconds = 0;
    
    t1 = time(NULL);
    t1 = t1 - F91Clock_getTimeZone();

    //Handle daylight savings
    if(F91Clock_getDst()){
        t1 += 3600;
    }

    ltm = localtime(&t1);
    timeInSeconds = Seconds_get();
    eraseFirstDigit = false;

    //Handle 24hr or 12 hr time.
    if((!F91Clock_getTimeMode()) && (ltm->tm_hour>=13)){
        ltm->tm_hour = ltm->tm_hour - 12;
        ssd1306_display_pm(PM_POS_X, PM_POS_Y, false);
    } else if((!F91Clock_getTimeMode()) && (ltm->tm_hour == 0)){
        ltm->tm_hour = 12;
        ssd1306_display_pm(PM_POS_X, PM_POS_Y, true);
    } else if((!F91Clock_getTimeMode()) && (ltm->tm_hour == 12)){
        ssd1306_display_pm(PM_POS_X, PM_POS_Y, false);
    } else {
        ssd1306_display_pm(PM_POS_X, PM_POS_Y, true);
    }

    ltoa(ltm->tm_hour, hour);
    ltoa(ltm->tm_min, minute);
    ltoa(ltm->tm_sec, second);
    ltoa(ltm->tm_mon + 1, month);
    ltoa(ltm->tm_mday, day);

    dateString = strcat(strcat(month,"/"),day);
    ssd1306_display_semicolon(SEM_CLN_POS_X, SEM_CLN_POS_Y, false);
    ssd1306_display_text("000000", DATE_POS_X, DATE_POS_Y, true); // erase all date field first
    ssd1306_display_text(dateString, 95 - (strlen(dateString)*6), 1, false); // display date, right aligned

    if(ltm->tm_hour<10){
        hour[1]=hour[0];
        hour[0]='0';
        // Don't display the first hour digit.
        eraseFirstDigit = true;
    }

    if(ltm->tm_min<10){
        minute[1]=minute[0];
        minute[0]='0';
    }

    if(ltm->tm_sec<10){
        second[1]=second[0];
        second[0]='0';
    }
    //Hour
    ssd1306_display_number(hour[0]-'0', HR_1_POS_X, HR_MIN_POS_Y, eraseFirstDigit);
    ssd1306_display_number(hour[1]-'0', HR_2_POS_X, HR_MIN_POS_Y, false);
    //Minutes
    ssd1306_display_number(minute[0]-'0', MIN_1_POS_X, HR_MIN_POS_Y, false);
    ssd1306_display_number(minute[1]-'0', MIN_2_POS_X, HR_MIN_POS_Y, false);
    //Seconds
    ssd1306_display_small_number(second[0]-'0', SEC_1_POS_X, SEC_POS_Y, false);
    ssd1306_display_small_number(second[1]-'0', SEC_2_POS_X, SEC_POS_Y, false);

    //Update Display
    ssd1306_update();

    //Update service
    F91_clock_service_SetParameter(F91_CLOCK_SERVICE_CHAR1, sizeof(uint32_t), &timeInSeconds);
}

/*********************************************************************
 * EXTERNAL FUNCTIONS
 */

/*********************************************************************
 * @fn      F91Clock_StateChangeCB
 *
 * @brief   Callback function to be called when clock is changed.
 *
 * @return  None.
 */
static f91_clock_serviceCBs_t F91Clock_StateChangeCB =
{
  F91Kepler_clockCharValueChangeCB
};


/*********************************************************************
 * PUBLIC FUNCTIONS
 */


/*********************************************************************
 * @fn      F91Clock_taskFxn
 *
 * @brief   Application task entry point for the F91 Clock.
 *
 * @param   a0, a1 - not used.
 *
 * @return  None.
 */
static void F91Clock_taskFxn(UArg a0, UArg a1)
{
    // Initialize application
    F91Clock_internal_init();
    // Application main loop
    for (;;)
    {   
        F91Clock_doTime();
        Task_sleep(1000 * (1000 / Clock_tickPeriod));
    }
}


/*********************************************************************
 * @fn      F91Clock_init
 *
 * @brief   Initialization function for the clock
 *
 * @param   none
 *
 * @return  none
 */
void F91Clock_init(void)
{
  F91_clock_service_AddService();
  F91_clock_service_RegisterAppCBs(&F91Clock_StateChangeCB);
}


/*********************************************************************
 * @fn      F91Clock_processCharChangeEvt
 *
 * @brief   F91 clock change handling
 *
 * @param   paramID - char identifier
 *
 */
void F91Clock_processCharChangeEvt(uint8_t paramID)
{
  uint32_t time;
  uint16_t zone;
  uint8_t  mode;
  switch (paramID)
  {
    case F91_CLOCK_SERVICE_CHAR1:
      F91_clock_service_GetParameter(F91_CLOCK_SERVICE_CHAR1, &time);
      F91Clock_setTime(time);
      break;
    case F91_CLOCK_SERVICE_CHAR2:
      F91_clock_service_GetParameter(F91_CLOCK_SERVICE_CHAR2, &zone);
      F91Clock_setTimeZone(zone);
      break;
    case F91_CLOCK_SERVICE_CHAR3:
      F91_clock_service_GetParameter(F91_CLOCK_SERVICE_CHAR3, &mode);
      F91Clock_setTimeMode(mode);
    case F91_CLOCK_SERVICE_CHAR4:
      F91_clock_service_GetParameter(F91_CLOCK_SERVICE_CHAR4, &mode);
      F91Clock_setDst(mode);
      break;
    default:
      break;
  }
}
