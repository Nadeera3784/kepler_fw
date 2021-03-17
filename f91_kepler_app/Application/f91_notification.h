 /******************************************************************************

 @file  f91_notification.h

 @brief This file contains the notifications definitions
    and prototypes.

 Target Device: cc2640r2

 ******************************************************************************
 *****************************************************************************/


#ifndef F91NOTIFICATION_H
#define F91NOTIFICATION_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */
#include "board.h"
#include "f91_kepler.h"
#include <ti/display/Display.h>

/*********************************************************************
 * CONSTANTS
 */

#define NOTIFICATION_BAR   0x01
#define NOTIFICATION_CALL  0x02
#define NOTIFICATION_TEXT  0x04


/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * FUNCTIONS
 */

/*
 * Initialize notifications module
 */
extern void F91Notification_init(void);

/*
 * Task Event Processor for characteristic changes
 */
extern void F91Notification_processCharChangeEvt(uint8_t paramID);

/*
 * Task Event Processor for notifications module
 */
extern void F91Notification_processEvent(void);

/*
 * Update notifications
 */
extern void F91Notification_update(uint8_t type);

/*
 * Returns wether a full screen notification is being shown.
 */
extern bool F91Notification_getNotificationState( void );

/*
 * Reset full screen notifcation and one shot clock.
 */
extern void F91Notification_resetNotificationState( void );

/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* F91NOTIFICATION_H */
