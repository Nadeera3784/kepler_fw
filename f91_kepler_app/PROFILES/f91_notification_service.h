/**********************************************************************************************
 * Filename:       f91_notification_service.h
 *
 * Description:    This file contains the f91_notification_service service definitions and
 *                 prototypes.
 *
 * Copyright (c) 2015-2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
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


#ifndef _F91_NOTIFICATION_SERVICE_H_
#define _F91_NOTIFICATION_SERVICE_H_

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */

/*********************************************************************
 * CONSTANTS
 */

/*********************************************************************
* CONSTANTS
*/

// Profile Parameters
#define F91_NOTIFICATION_SERVICE_CHAR1                 0  // RW uint8 - Profile Characteristic 1 value (Notification Bar)
#define F91_NOTIFICATION_SERVICE_CHAR2                 1  // RW uint8 - Profile Characteristic 2 value (Incoming Call)
#define F91_NOTIFICATION_SERVICE_CHAR3                 2  // RW uint8 - Profile Characteristic 3 value (Incoming Text)

// Service UUID
#define F91_NOTIFICATION_SERVICE_UUID                  0xFFF0

// Characteristic UUID
#define F91_NOTIFICATION_SERVICE_CHAR1_UUID            0xFFF1
#define F91_NOTIFICATION_SERVICE_CHAR2_UUID            0xFFF2
#define F91_NOTIFICATION_SERVICE_CHAR3_UUID            0xFFF3


#define NINEONENOTIFICATION_SERVICE                    0x00000010

#define CONTACT_STREAM_LEN                             11
#define CONTACT_STREAM_LEN_MIN                         0


/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * Profile Callbacks
 */

// Callback when a characteristic value has changed
typedef void (*f91_notification_serviceChange_t)( uint8 paramID );

typedef struct
{
  f91_notification_serviceChange_t        pfnNotificationChangeCb;  // Called when characteristic value changes
} f91_notification_serviceCBs_t;



/*********************************************************************
 * API FUNCTIONS
 */


/*
 * F91_notification_service_AddService- Initializes the F91_notification_service service by registering
 *          GATT attributes with the GATT server.
 *
 */
extern bStatus_t F91_notification_service_AddService( Display_Handle logger );

/*
 * F91_notification_service_RegisterAppCBs - Registers the application callback function.
 *                    Only call this function once.
 *
 *    appCallbacks - pointer to application callbacks.
 */
extern bStatus_t F91_notification_service_RegisterAppCBs( f91_notification_serviceCBs_t *appCallbacks );

/*
 * F91_notification_service_SetParameter - Set a F91_notification_service parameter.
 *
 *    param - Profile parameter ID
 *    len - length of data to write
 *    value - pointer to data to write.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16 will be cast to
 *          uint16 pointer).
 */
extern bStatus_t F91_notification_service_SetParameter( uint8_t param, uint16_t len, void *value );

/*
 * F91_notification_service_GetParameter - Get a F91_notification_service parameter.
 *
 *    param - Profile parameter ID
 *    value - pointer to data to write.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16 will be cast to
 *          uint16 pointer).
 */
extern bStatus_t F91_notification_service_GetParameter( uint8_t param, void *value );
/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* _F91_NOTIFICATION_SERVICE_H_ */
