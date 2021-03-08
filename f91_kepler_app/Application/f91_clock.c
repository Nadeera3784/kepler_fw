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

/*********************************************************************
 * LOCAL FUNCTIONS
 */
static void F91Clock_init( void );
static void F91Clock_taskFxn(UArg a0, UArg a1);
static void F91Clock_doTime(void);



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
 * @fn      F91Clock_init
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
static void F91Clock_init(void)
{  
    // Register the current thread as an ICall dispatcher application
    // so that the application can send and receive messages.
    ICall_registerApp(&selfEntity, &syncEvent);

    // initialize the SSD1306 display. 
    ssd1306_init();

    //**************set default time (01/14/1994) (UTC)************
    Seconds_set(758505600);
    //***********************************************************
}

static void F91Clock_doTime(void) {
    time_t t1;
    struct tm *ltm;
    char *dateString;
    char hour[2];
    char minute[2];
    char second[2];
    char month[2];
    char day[2];
    bool eraseFirstDigit;
    bool militaryTime = false;
    int timezone = 28800;
    int lastWrittenHr=999; //Default value, something it can't be.
    int lastWrittenMin=999;
    int lastWrittenSec=999;

    t1 = time(NULL);
    t1 = t1 - timezone;
    ltm = localtime(&t1);
    eraseFirstDigit = false;

    if((!militaryTime) && (ltm->tm_hour>=13)){
        ltm->tm_hour = ltm->tm_hour - 12;
        ssd1306_display_pm(74, 13, false);
    } else if((!militaryTime) && (ltm->tm_hour == 0)){
        ltm->tm_hour = 12;
        ssd1306_display_pm(74, 13, true);
    } else if((!militaryTime) && (ltm->tm_hour == 12)){
        ssd1306_display_pm(74, 13, false);
    } else {
        ssd1306_display_pm(74, 13, true);
    }

    ltoa(ltm->tm_hour, hour);
    ltoa(ltm->tm_min, minute);
    ltoa(ltm->tm_sec, second);
    ltoa(ltm->tm_mon+1, month);
    ltoa(ltm->tm_mday, day);


    dateString = strcat(strcat(month,"/"),day);
    ssd1306_display_semicolon(34, 13, false);
    ssd1306_display_text("00000", 64, 1, true); // erase all date field first
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

    if(lastWrittenHr != ltm->tm_hour) {
        ssd1306_display_number(hour[0]-'0', 0, 13, eraseFirstDigit);
        ssd1306_display_number(hour[1]-'0', 17, 13, false);
        lastWrittenHr = ltm->tm_hour;
    }

    if(lastWrittenMin != ltm->tm_min) {
        ssd1306_display_number(minute[0]-'0', 39, 13, false);
        ssd1306_display_number(minute[1]-'0', 56, 13, false);
        lastWrittenMin = ltm->tm_min;
    }

    if(lastWrittenSec != ltm->tm_sec){
        ssd1306_display_small_number(second[0]-'0', 74, 25, false);
        ssd1306_display_small_number(second[1]-'0', 84, 25, false);
        lastWrittenSec = ltm->tm_sec;
        ssd1306_send_buffer(ssd1306_display_buffer, sizeof(ssd1306_display_buffer));
    }
}

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
    F91Clock_init();
    // Application main loop
    for (;;)
    {   
        F91Clock_doTime();
        Task_sleep(1000 * (1000 / Clock_tickPeriod));
    }
}
