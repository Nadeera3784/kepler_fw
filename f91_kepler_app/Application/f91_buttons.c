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
#include "f91_utils.h"
#include "f91_kepler.h"
#include "f91_buttons.h"

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
PIN_Config buttonPinTable[] = {
    Board_BUTTON0 | PIN_INPUT_EN | PIN_PULLUP | PIN_IRQ_NEGEDGE,
    Board_BUTTON1 | PIN_INPUT_EN | PIN_PULLUP | PIN_IRQ_NEGEDGE,
    PIN_TERMINATE
};

// Clock objects for debouncing the buttons
static Clock_Struct button0DebounceClock;
static Clock_Struct button1DebounceClock;

// State of the buttons
static uint8_t button0State = 0;
static uint8_t button1State = 0;

/*********************************************************************
 * LOCAL FUNCTIONS
 */

static void F91Buttons_buttonCallbackFxn(PIN_Handle handle, PIN_Id pinId);
static void F91Buttons_buttonDebounceSwiFxn(UArg buttonId);


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
    PIN_setConfig(buttonPinHandle, PIN_BM_IRQ, buttonId | PIN_IRQ_NEGEDGE);
  }
  else
  {
    // Enable positive edge interrupts to wait for relesae
    PIN_setConfig(buttonPinHandle, PIN_BM_IRQ, buttonId | PIN_IRQ_POSEDGE);
  }

  switch(buttonId)
  {
    case Board_BUTTON0:
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

    case Board_BUTTON1:
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
    case Board_BUTTON0:
      Clock_start(Clock_handle(&button0DebounceClock));
      break;
    case Board_BUTTON1:
      Clock_start(Clock_handle(&button1DebounceClock));
      break;
  }
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
    clockParams.arg = Board_BUTTON0;

    // Initialize to 50 ms timeout when Clock_start is called.
    // Timeout argument is in ticks, so convert from ms to ticks via tickPeriod.
    Clock_construct(&button0DebounceClock, F91Buttons_buttonDebounceSwiFxn,
                    50 * (1000/Clock_tickPeriod),
                    &clockParams);

    // Second button
    clockParams.arg = Board_BUTTON1;
    Clock_construct(&button1DebounceClock, F91Buttons_buttonDebounceSwiFxn,
                    50 * (1000/Clock_tickPeriod),
                    &clockParams);
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
  
  //TO-DO: HANDLE BUTTON PRESS LOGIC HERE
}

/*********************************************************************
*********************************************************************/



