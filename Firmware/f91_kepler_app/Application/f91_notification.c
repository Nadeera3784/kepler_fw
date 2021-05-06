 /******************************************************************************

 @file  f91_notification.c

 @brief This file contains the notifications application.

 Target Device: cc2640r2

 ******************************************************************************
 *****************************************************************************/


/*********************************************************************
 * INCLUDES
 */
#include "osal_snv.h"
#include "gatt.h"
#include "gattservapp.h"
#include "board.h"
#include "peripheral.h"
#include "util.h"

#include "f91_notification.h"
#include "f91_notification_service.h"
#include "f91_buttons.h"
#include "ssd1306.h"

#include <ti/display/Display.h>
#include <ti/sysbios/knl/Clock.h>

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
 * EXTERNAL VARIABLES
 */

/*********************************************************************
 * EXTERNAL FUNCTIONS
 */
/*********************************************************************
 * @fn      F91Notification_StateChangeCB
 *
 * @brief   Callback function to be called when notifications are changed.
 *
 * @return  None.
 */
static f91_notification_serviceCBs_t F91Notification_StateChangeCB =
{
  F91Kepler_notificationCharValueChangeCB
};
/*********************************************************************
 * LOCAL VARIABLES
 */

static struct {
  bool email;
  bool text;
  bool voicemail;
  bool missedcall;
  char * incoming_call;
  char * incoming_text;
} current_notifications;

// Clock object used to signal display timeout
static Clock_Struct startDispClock;

static bool displayingFullNotification = false;

/*********************************************************************
 * PROFILE CALLBACKS
 */

/*********************************************************************
 * LOCAL FUNCTIONS
 */

/*
 * Reset notification module
 */
static void _F91Notification_reset(void);

/*
 * Set specific notification
 */
static void _F91Notification_setNotification(uint8_t type, uint8_t notification);

/*
 * Set specific notification
 */
static void _F91Notification_setFullNotification(uint8_t type, char* notification);

/*
 * Display a full notifcation
 */
static void _F91Notification_displayFullNotification(uint8_t type);

/*
 * Callback for one-shot clock used for full screen notifications.
 */
static void _F91Notification_oneShotCallback(UArg a1);

/*********************************************************************
 * @fn      _F91Notification_reset
 *
 * @brief   Reset notifications
 *
 * @param   none
 *
 * @return  none
 */
static void _F91Notification_reset(void)
{
  current_notifications.email         = false;
  current_notifications.text          = false;
  current_notifications.voicemail     = false;
  current_notifications.missedcall    = false;
  current_notifications.incoming_call = "";
  current_notifications.incoming_text = "";
}

/*********************************************************************
 * @fn      _F91Notification_setNotification
 *
 * @brief   Set a specific notification.
 *
 * @param   notification - the notification to set.
 *
 * @return  None.
 */
static void _F91Notification_setNotification(uint8_t type, uint8_t notification)
{
    if (notification & (1<<EMAIL)) {
      current_notifications.email = true;
    } else {
      current_notifications.email = false;
    }
    if (notification & (1<<TEXT)) {
      current_notifications.text  = true;
    } else {
      current_notifications.text  = false;
    }
    if (notification & (1<<VOICEMAIL)) {
      current_notifications.voicemail = true;
    } else {
      current_notifications.voicemail = false;
    }
    if (notification & (1<<MISSEDCALL)) {
      current_notifications.missedcall = true;
    } else {
      current_notifications.missedcall = false;
    }
}

/*********************************************************************
 * @fn      _F91Notification_setFullNotification
 *
 * @brief   Updates current notifcations for full screen notifications (call/text).
 *
 * @return  None.
 */
static void _F91Notification_setFullNotification(uint8_t type, char* notification)
{
  if ( type == NOTIFICATION_CALL ) {
    current_notifications.incoming_call = notification;
  } else if ( type == NOTIFICATION_TEXT ) {
    current_notifications.incoming_text = notification;
  }
}

/*********************************************************************
 * @fn      _F91Notification_displayFullNotification
 *
 * @brief   Sets up a one-shot to display a full notification for 5 seconds.
 *
 * @return  None.
 */
static void _F91Notification_displayFullNotification(uint8_t type)
{    
  if ( type == NOTIFICATION_CALL ) {
    displayingFullNotification = true;
    ssd1306_clear();
    ssd1306_display_full_notification(INCOMING_CALL, current_notifications.incoming_call);
  } else if ( type == NOTIFICATION_TEXT ) {
    displayingFullNotification = true;
    ssd1306_clear();
    ssd1306_display_full_notification(INCOMING_TEXT, current_notifications.incoming_text);
  }
  
  // Cancel the one shot clock of the display if it's already going from a button press;
  F91Buttons_resetOneShot();

  ssd1306_update();
  ssd1306_toggle_display(true);
  Util_restartClock(&startDispClock, DISPLAY_TIMEOUT);
}

/*********************************************************************
 * @fn      _F91Notification_oneShotCallback
 *
 * @brief   Sets up a one-shot to display a full notification for 5 seconds.
 *
 * @return  None.
 */
static void _F91Notification_oneShotCallback(UArg a1)
{  
  displayingFullNotification = false;
  F91Kepler_displayStateChangeCB();
}

/*********************************************************************
 * PUBLIC FUNCTIONS
 */

/*********************************************************************
 * @fn      F91Notification_init
 *
 * @brief   Initialization function for the notifications
 *
 * @param   none
 *
 * @return  none
 */
void F91Notification_init(void)
{
  F91_notification_service_AddService();
  F91_notification_service_RegisterAppCBs(&F91Notification_StateChangeCB);
  _F91Notification_reset();

  //Setup one-shot clock to turn off display after set time.
  Util_constructClock(&startDispClock, _F91Notification_oneShotCallback,
                  0, 0, false, NULL);
}

/*********************************************************************
 * @fn      F91Notification_processCharChangeEvt
 *
 * @brief   F91 notification handling
 *
 * @param   paramID - char identifier
 *
 */
void F91Notification_processCharChangeEvt(uint8_t paramID)
{
  static uint8_t received_string[CONTACT_STREAM_LEN] = {0};
  uint8_t incoming_notifications;
  switch (paramID)
  {
    case F91_NOTIFICATION_SERVICE_CHAR1:
      F91_notification_service_GetParameter(F91_NOTIFICATION_SERVICE_CHAR1, &incoming_notifications);
      _F91Notification_setNotification(NOTIFICATION_BAR, incoming_notifications);
      F91Notification_update(NOTIFICATION_BAR);
      break;
    case F91_NOTIFICATION_SERVICE_CHAR2:
      F91_notification_service_GetParameter(F91_NOTIFICATION_SERVICE_CHAR2, &received_string);
      _F91Notification_setFullNotification(NOTIFICATION_CALL, (char*) received_string);
      F91Notification_update(NOTIFICATION_CALL);
    
      memset(received_string, 0, CONTACT_STREAM_LEN); //reset the string array.
      break;
    case F91_NOTIFICATION_SERVICE_CHAR3:
      F91_notification_service_GetParameter(F91_NOTIFICATION_SERVICE_CHAR3, &received_string);
      _F91Notification_setFullNotification(NOTIFICATION_TEXT, (char*) received_string);
      F91Notification_update(NOTIFICATION_TEXT);

      memset(received_string, 0, CONTACT_STREAM_LEN); //reset the string array.
      break;
    default:
      break;
  }
}

/*********************************************************************
 * @fn      F91Notification_update
 *
 * @brief   Send notification to display.
 *
 * @return  None.
 */
void F91Notification_update(uint8_t type)
{
  if (type == NOTIFICATION_BAR) {
    if (current_notifications.email) {
      ssd1306_display_notification(EMAIL, EMAIL_POS_X, NOTIFICATIONS_POS_Y, false);
    } else {
      ssd1306_display_notification(EMAIL, EMAIL_POS_X, NOTIFICATIONS_POS_Y, true);
    }
    if (current_notifications.text) {
      ssd1306_display_notification(TEXT, TEXT_POS_X, NOTIFICATIONS_POS_Y, false);
    } else {
      ssd1306_display_notification(TEXT, TEXT_POS_X, NOTIFICATIONS_POS_Y, true);
    }
    if (current_notifications.voicemail) {
      ssd1306_display_notification(VOICEMAIL, VOIEMAIL_POS_X, NOTIFICATIONS_POS_Y, false);
    } else {
      ssd1306_display_notification(VOICEMAIL, VOIEMAIL_POS_X, NOTIFICATIONS_POS_Y, true);
    }
    if (current_notifications.missedcall) {
      ssd1306_display_notification(MISSEDCALL, MISSEDCALL_POS_X, NOTIFICATIONS_POS_Y, false);
    } else {
      ssd1306_display_notification(MISSEDCALL, MISSEDCALL_POS_X, NOTIFICATIONS_POS_Y, true);
    }
  } 
  else if ((type == NOTIFICATION_CALL) || (type == NOTIFICATION_TEXT)) {
    _F91Notification_displayFullNotification(type);
  }
}

/*********************************************************************
 * @fn      F91Notification_processEvent
 *
 * @brief   Notification event processor.
 *
 * @param   none
 *
 * @return  none
 */
void F91Notification_processEvent(void)
{

}

/*********************************************************************
 * @fn      F91Notification_getNotificationState
 *
 * @brief   Notification state to stop the clock from overwriting the buffer during full screen notifications.
 *
 * @param   none
 *
 * @return  returns true if there is a full screen notification being displayed, false otherwise.
 */
bool F91Notification_getNotificationState(void)
{
  return displayingFullNotification;
}

/*********************************************************************
 * @fn      F91Notification_resetNotificationState
 *
 * @brief   Reset the full screen notifcation and one-shot, used mainly if button is pressed while displaying
 *          a full screen notification.
 *
 * @param   none
 *
 * @return  none
 */
void F91Notification_resetNotificationState(void)
{
  Util_stopClock(&startDispClock);
  ssd1306_toggle_display(false);
  ssd1306_clear();
  ssd1306_update();
  displayingFullNotification = false;
}

/*********************************************************************
*********************************************************************/
