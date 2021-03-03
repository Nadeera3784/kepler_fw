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
#include "f91_notification.h"
#include "board.h"
#include "peripheral.h"
#include "util.h"
#include "f91_notification_service.h"
#include "ssd1306.h"

#include <ti/display/Display.h>

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * CONSTANTS  
 */
// Events

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
 * @fn      F91Notificaton_SetNotification
 *
 * @brief   Callback function to be called when notifications are changed.
 *
 * @return  None.
 */
static f91_notification_serviceCBs_t F91Notificaton_StateChangeCB =
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

/*********************************************************************
 * LOCAL FUNCTIONS
 */

/*********************************************************************
 * PROFILE CALLBACKS
 */

/*********************************************************************
 * PUBLIC FUNCTIONS
 */

/*********************************************************************
 * @fn      F91Notificaton_init
 *
 * @brief   Initialization function for the notifications
 *
 * @param   none
 *
 * @return  none
 */
void F91Notificaton_init(Display_Handle logger)
{
  F91_notification_service_AddService(logger);
  F91_notification_service_RegisterAppCBs(&F91Notificaton_StateChangeCB);
  ssd1306_init();
  F91Notificaton_reset();
  F91Notificaton_Update(NOTIFICATION_BAR);
}

/*********************************************************************
 * @fn      F91Notificaton_processCharChangeEvt
 *
 * @brief   F91 notification handling
 *
 * @param   paramID - char identifier
 *
 */
void F91Notificaton_processCharChangeEvt(uint8_t paramID)
{
  static uint8_t received_string[CONTACT_STREAM_LEN] = {0};
  uint8_t incoming_notifications;
  switch (paramID)
  {
    case F91_NOTIFICATION_SERVICE_CHAR1:
      F91_notification_service_GetParameter(F91_NOTIFICATION_SERVICE_CHAR1, &incoming_notifications);
      F91Notificaton_SetNotification(NOTIFICATION_BAR, incoming_notifications);
      F91Notificaton_Update(NOTIFICATION_BAR);
      break;
    case F91_NOTIFICATION_SERVICE_CHAR2:
      F91_notification_service_GetParameter(F91_NOTIFICATION_SERVICE_CHAR2, &received_string);
      F91Notificaton_SetFullNotification(NOTIFICATION_CALL, (char*) received_string);
      F91Notificaton_Update(NOTIFICATION_CALL);
    
      memset(received_string, 0, CONTACT_STREAM_LEN); //reset the string array.
      break;
    case F91_NOTIFICATION_SERVICE_CHAR3:
      F91_notification_service_GetParameter(F91_NOTIFICATION_SERVICE_CHAR3, &received_string);
      F91Notificaton_SetFullNotification(NOTIFICATION_TEXT, (char*) received_string);
      F91Notificaton_Update(NOTIFICATION_TEXT);
      memset(received_string, 0, CONTACT_STREAM_LEN); //reset the string array.
      break;
    default:
      break;
  }
}

/*********************************************************************
 * @fn      F91Notificaton_processEvent
 *
 * @brief   Notification event processor.
 *
 * @param   none
 *
 * @return  none
 */
void F91Notificaton_processEvent(void)
{

}

/*********************************************************************
 * @fn      F91Notificaton_reset
 *
 * @brief   Reset notifications
 *
 * @param   none
 *
 * @return  none
 */
void F91Notificaton_reset(void)
{
  current_notifications.email         = false;
  current_notifications.text          = false;
  current_notifications.voicemail     = false;
  current_notifications.missedcall    = false;
  current_notifications.incoming_call = "";
  current_notifications.incoming_text = "";
}

/*********************************************************************
 * @fn      F91Notificaton_SetNotification
 *
 * @brief   Set a specific notification.
 *
 * @param   notification - the notification to set.
 *
 * @return  None.
 */
void F91Notificaton_SetNotification(uint8_t type, uint8_t notification)
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

void F91Notificaton_SetFullNotification(uint8_t type, char* notification)
{
  if ( type == NOTIFICATION_CALL ) {
    current_notifications.incoming_call = notification;
  } else if ( type == NOTIFICATION_TEXT ) {
    current_notifications.incoming_text = notification;
  }
}

/*********************************************************************
 * @fn      F91Notificaton_Update
 *
 * @brief   Send notification to display.
 *
 * @return  None.
 */
void F91Notificaton_Update(uint8_t type)
{
  if (type == NOTIFICATION_BAR) {
    if (current_notifications.email) {
      ssd1306_display_notification(EMAIL, 0, 0, false);
    } else {
      ssd1306_display_notification(EMAIL, 0, 0, true);
    }
    if (current_notifications.text) {
      ssd1306_display_notification(TEXT, 14, 0, false);
    } else {
      ssd1306_display_notification(TEXT, 14, 0, true);
    }
    if (current_notifications.voicemail) {
      ssd1306_display_notification(VOICEMAIL, 29, 0, false);
    } else {
      ssd1306_display_notification(VOICEMAIL, 29, 0, true);
    }
    if (current_notifications.missedcall) {
      ssd1306_display_notification(MISSEDCALL, 44, 0, false);
    } else {
      ssd1306_display_notification(MISSEDCALL, 44, 0, true);
    }
  } else if (type == NOTIFICATION_CALL) {
    ssd1306_clear_buffer(ssd1306_display_buffer, sizeof(ssd1306_display_buffer));
    ssd1306_display_full_notification(INCOMING_CALL, current_notifications.incoming_call);
  } else if (type == NOTIFICATION_TEXT) {
    ssd1306_clear_buffer(ssd1306_display_buffer, sizeof(ssd1306_display_buffer));
    ssd1306_display_full_notification(INCOMING_TEXT, current_notifications.incoming_text);
  }

  ssd1306_send_buffer(ssd1306_display_buffer, sizeof(ssd1306_display_buffer));
}

/*********************************************************************
*********************************************************************/
