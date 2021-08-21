/**********************************************************************************************
 * Filename:       f91_buttons.c
 *
 * Description:    This file contains the implementation of SSD1306 OLED Display Driver.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *************************************************************************************************/


/*********************************************************************
 * INCLUDES
 */
#include "ssd1306.h"
#include "util.h"
#include "f91_utils.h"
#include "f91_kepler.h"
#include "f91_buttons.h"
#include "f91_notification.h"

#include <ti/display/Display.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Clock.h>



#include "Board.h"


/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * CONSTANTS
 */
#define DISPLAY_TIMEOUT 5000 //5 seconds

/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
* GLOBAL VARIABLES
*/

/*********************************************************************
 * LOCAL VARIABLES
 */

/* Pin driver handles */
static PIN_Handle buttonPinHandle;
static PIN_State buttonPinState;

/*
 * Application button pin configuration table:
 *   - Buttons interrupts are configured to trigger on falling edge.
 */
#ifdef IS_DEV_BOARD
  #define PIN_PULL_TYPE PIN_PULLUP
  #define PIN_PRESS_IRQ  PIN_IRQ_NEGEDGE
  #define PIN_RELEASE_IRQ PIN_IRQ_POSEDGE
  #define BUTTON_0 Board_BUTTON0
  #define BUTTON_1 Board_BUTTON1
  #define BUTTON_2 Board_BUTTON2
#else //NOT DEV BOARD
  #define PIN_PULL_TYPE PIN_PULLDOWN
  #define PIN_PRESS_IRQ  PIN_IRQ_POSEDGE
  #define PIN_RELEASE_IRQ PIN_IRQ_NEGEDGE
  #define BUTTON_0 0x0000000F // IO Id 15
  #define BUTTON_1 0x00000019 // IO Id 25
  #define BUTTON_2 0x0000001A // IO Id 26
#endif


PIN_Config buttonPinTable[] = {
    BUTTON_0 | PIN_INPUT_EN | PIN_PULL_TYPE | PIN_IRQ_NEGEDGE,
    BUTTON_1 | PIN_INPUT_EN | PIN_PULL_TYPE | PIN_IRQ_NEGEDGE,
    PIN_TERMINATE
};

// Clock objects for debouncing the buttons
static Clock_Struct button0DebounceClock;
static Clock_Struct button1DebounceClock;

// Clock object used to signal display timeout
static Clock_Struct startDispClock;

// State of the buttons
static uint8_t button0State = 0;
static uint8_t button1State = 0;

/*********************************************************************
 * LOCAL FUNCTIONS
 */

static void F91Buttons_buttonCallbackFxn(PIN_Handle handle, PIN_Id pinId);
static void F91Buttons_buttonDebounceSwiFxn(UArg buttonId);
static void F91Buttons_clockChangeDisplayCallbackFxn(UArg state);


/*********************************************************************
 * @fn      F91Buttons_buttonDebounceSwiFxn
 * 
 * @brief  Callback from Clock module on timeout
 *
 *         Determines new state after debouncing
 *
 * @param  buttonId    The pin being debounced
 */
static void F91Buttons_buttonDebounceSwiFxn(UArg buttonId)
{
  // Used to send message to app
  button_state_t buttonMsg = { .pinId = buttonId };
  uint8_t        sendMsg   = FALSE;

  // Get current value of the button pin after the clock timeout
  uint8_t buttonPinVal = PIN_getInputValue(buttonId);

  // Set interrupt direction to opposite of debounced state
  // If button is now released (button is active low, so release is high)
  if (buttonPinVal)
  {
    // Enable negative edge interrupts to wait for press
    PIN_setConfig(buttonPinHandle, PIN_BM_IRQ, buttonId | PIN_PRESS_IRQ);
  }
  else
  {
    // Enable positive edge interrupts to wait for relesae
    PIN_setConfig(buttonPinHandle, PIN_BM_IRQ, buttonId | PIN_RELEASE_IRQ);
  }

  switch(buttonId)
  {
    case BUTTON_0:
      if (buttonPinVal && button0State)
      {
        // Button was released
        buttonMsg.state = button0State = 0;
        sendMsg = TRUE;
      }
      else if (!buttonPinVal && !button0State)
      {
        // Button was pressed
        buttonMsg.state = button0State = 1;
        sendMsg = FALSE;
      }
      break;

    case BUTTON_1:
      if (buttonPinVal && button1State)
      {
        // Button was released
        buttonMsg.state = button1State = 0;
        sendMsg = TRUE;
      }
      else if (!buttonPinVal && !button1State)
      {
        // Button was pressed
        buttonMsg.state = button1State = 1;
        sendMsg = FALSE;
      }
      break;
  }

  //Only send event upon button release.
  if (sendMsg == TRUE)
  {
    button_state_t *pData;
    // Allocate space for the event data.
    if ((pData = ICall_malloc(sizeof(button_state_t))))
    {
      *pData =  buttonMsg;

      // Queue the event.
      F91Kepler_buttonValueChangeCB((uint8_t *) pData);
    }
  }
}

/*********************************************************************
 * @fn      F91Buttons_buttonCallbackFxn
 * 
 * @brief  Callback from PIN driver on interrupt
 *
 *         Sets in motion the debouncing.
 *
 * @param  handle    The PIN_Handle instance this is about
 * @param  pinId     The pin that generated the interrupt
 */
static void F91Buttons_buttonCallbackFxn(PIN_Handle handle, PIN_Id pinId)
{
  // Disable interrupt on that pin for now. Re-enabled after debounce.
  PIN_setConfig(handle, PIN_BM_IRQ, pinId | PIN_IRQ_DIS);

  // Start debounce timer
  switch (pinId)
  {
    case BUTTON_0:
      Clock_start(Clock_handle(&button0DebounceClock));
      break;
    case BUTTON_1:
      Clock_start(Clock_handle(&button1DebounceClock));
      break;
  }
}

/*********************************************************************
 * @fn      F91Buttons_clockChangeDisplayCallbackFxn
 * 
 * @brief  Callback from clock to change display state
 *
 *         Sets in motion the debouncing.
 *
 * @param  handle    The PIN_Handle instance this is about
 * @param  pinId     The pin that generated the interrupt
 */
static void F91Buttons_clockChangeDisplayCallbackFxn(UArg state)
{   
    //As Clock functions execute in either a Swi or Hwi context, they are not permitted to call blocking APIs!!!
    // I2C call is blocking unless we use a callback transferMode, which I DO NOT want to...
    // So trigger an event and let the F91_Kepler task handle turning the display back off.
    F91Kepler_displayStateChangeCB();
}

/*********************************************************************
 *  EXTERN FUNCTIONS
 */

void F91Buttons_init( void ) {
    // Init buttons.
    buttonPinHandle = PIN_open(&buttonPinState, buttonPinTable);
    if(!buttonPinHandle) {
        Display_print0(F91_LOGGER, 0, 0, "Error occured opening button pin!");
        return;
    }

    if (PIN_registerIntCb(buttonPinHandle, &F91Buttons_buttonCallbackFxn) != 0) {
        Display_print0(F91_LOGGER, 0, 0, "Error occured registering button callback!");
        return;
    }

    // Create the debounce clock objects for Button 0 and Button 1
    Clock_Params clockParams;
    Clock_Params_init(&clockParams);

    // Both clock objects use the same callback, so differentiate on argument
    // given to the callback in Swi context
    clockParams.arg = BUTTON_0;

    // Initialize to 50 ms timeout when Clock_start is called.
    // Timeout argument is in ticks, so convert from ms to ticks via tickPeriod.
    Clock_construct(&button0DebounceClock, F91Buttons_buttonDebounceSwiFxn,
                    50 * (1000/Clock_tickPeriod),
                    &clockParams);

    // Second button
    clockParams.arg = BUTTON_1;
    Clock_construct(&button1DebounceClock, F91Buttons_buttonDebounceSwiFxn,
                    50 * (1000/Clock_tickPeriod),
                    &clockParams);

    //Setup one-shot clock to turn off display after set time upon button press.
    Util_constructClock(&startDispClock, F91Buttons_clockChangeDisplayCallbackFxn,
                    0, 0, false, NULL);
}

/*********************************************************************
 * @fn      F91Buttons_processButtonPress
 *
 * @brief   Process button press event.
 *
 * @param buttonInfo pointer to info on what button was pressed and state
 */
void F91Buttons_processButtonPress(button_state_t *buttonInfo)
{
    Display_print1(F91_LOGGER, 7, 0, "BUTTON: %d", buttonInfo->pinId);
    Display_print1(F91_LOGGER, 8, 0, "STATE: %d", buttonInfo->state);

    //If button_0 is pressed, toggle display ON and start the one-shot clock for 5 seconds.
    // Unless there is a full screen display. In that case just turn the display off as to clear the notification.
    // This one shot clock then triggers an event to turn display off.
    if (buttonInfo->pinId == BUTTON_0) {
      if (F91Notification_getNotificationState()) {
        F91Notification_resetNotificationState();
      } else {
        F91Notification_update(NOTIFICATION_BAR); //Add notifications if any.
        ssd1306_toggle_display(true);
        Util_restartClock(&startDispClock, DISPLAY_TIMEOUT);
      }
    }
}

/*********************************************************************
 * @fn      F91Buttons_resetOneShot
 *
 * @brief   Reset the one shot clock that was displaying the time (This is to override the clock with full screen notifcations).
 *
 * @param none
 */
void F91Buttons_resetOneShot(void)
{
  Util_stopClock(&startDispClock);
}


/*********************************************************************
*********************************************************************/



