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

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * FUNCTIONS
 */

/*
 * Initialize notifications module
 */
extern void F91Notificaton_init(void);

/*
 * Task Event Processor for characteristic changes
 */
void F91Notificaton_processCharChangeEvt(uint8_t paramID);

/*
 * Task Event Processor for notifications module
 */
extern void F91Notificaton_processEvent(void);

/*
 * Reset notification module
 */
extern void F91Notificaton_reset(void);

/*
 * Set specific notification
 */
extern void F91Notificaton_SetNotification(uint8_t notification);

/*
 * Update notifications
 */
extern void F91Notificaton_Update(void);


/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* F91NOTIFICATION_H */
