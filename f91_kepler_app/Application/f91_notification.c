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
// Events
#define NOTIFICATION_CHANGED_EVT            (1 << 0)

/*********************************************************************
 * TYPEDEFS
 */

static f91_notification_serviceCBs_t *testCB = NULL;
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
void F91Notificaton_init(void)
{
  F91_notification_service_AddService();
  F91_notification_service_RegisterAppCBs(&F91Notificaton_StateChangeCB);
  ssd1306_init();
}

/*********************************************************************
 * @fn      F91Notificaton_processCharChangeEvt
 *
 * @brief   F91 notification event handling
 *
 * @param   event - event identifier
 *
 */
void F91Notificaton_processCharChangeEvt(uint8_t event)
{

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
void F91Notificaton_SetNotification(uint8_t notification)
{

}

/*********************************************************************
 * @fn      F91Notificaton_Update
 *
 * @brief   Send notification to display.
 *
 * @return  None.
 */
void F91Notificaton_Update(void)
{

}

/*********************************************************************
*********************************************************************/
