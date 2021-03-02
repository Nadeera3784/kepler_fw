/**********************************************************************************************
 * Filename:       f91_notification_service.c
 *
 * Description:    This file contains the implementation of the service.
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


/*********************************************************************
 * INCLUDES
 */
#include <string.h>

#include "bcomdef.h"
#include "OSAL.h"
#include "linkdb.h"
#include "att.h"
#include "gatt.h"
#include "gatt_uuid.h"
#include "gattservapp.h"
#include "gapbondmgr.h"
#include "f91_utils.h"

#include "f91_notification_service.h"

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * CONSTANTS
 */

#define SERVAPP_NUM_ATTR_SUPPORTED       10

/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
* GLOBAL VARIABLES
*/

// f91_notification_service Service UUID
CONST uint8_t f91_notification_serviceUUID[ATT_UUID_SIZE] =
{
  F91_BASE_UUID_128(F91_NOTIFICATION_SERVICE_UUID)
};

// Characteristic 1 UUID: 0xFFF1
CONST uint8 f91_notification_serviceChar1UUID[ATT_UUID_SIZE] =
{
 F91_BASE_UUID_128(F91_NOTIFICATION_SERVICE_CHAR1_UUID)
};

// Characteristic 2 UUID: 0xFFF2
CONST uint8 f91_notification_serviceChar2UUID[ATT_UUID_SIZE] =
{
 F91_BASE_UUID_128(F91_NOTIFICATION_SERVICE_CHAR2_UUID)
};

// Characteristic 3 UUID: 0xFFF3
CONST uint8 f91_notification_serviceChar3UUID[ATT_UUID_SIZE] =
{
 F91_BASE_UUID_128(F91_NOTIFICATION_SERVICE_CHAR3_UUID)
};



/*********************************************************************
 * LOCAL VARIABLES
 */

static f91_notification_serviceCBs_t *pNotificationsAppCBs = NULL;

/*********************************************************************
* Profile Attributes - variables
*/

// Service declaration
static CONST gattAttrType_t f91NotificationServiceDecl = { ATT_UUID_SIZE, f91_notification_serviceUUID };

// F91 Notification Characteristic 1 Properties
static uint8 f91NotificationServiceChar1Props = GATT_PROP_READ | GATT_PROP_WRITE;

// Characteristic 1 Value
static uint8 f91NotificationServiceChar1 = 0;

// F91 Characteristic 1 User Description
static uint8 f91NotificationServiceUserDesp1[21] = "F91 Notification Bar";

// F91 Notification Characteristic 2 Properties
static uint8 f91NotificationServiceChar2Props = GATT_PROP_READ | GATT_PROP_WRITE;

// Characteristic 2 Value
static uint8 f91NotificationServiceChar2 = 0;

// F91 Characteristic 2 User Description
static uint8 f91NotificationServiceUserDesp2[18] = "F91 Incoming Call";

// F91 Notification Characteristic 3 Properties
static uint8 f91NotificationServiceChar3Props = GATT_PROP_READ | GATT_PROP_WRITE;

// Characteristic 3 Value
static uint8 f91NotificationServiceChar3 = 0;

// F91 Characteristic 3 User Description
static uint8 f91NotificationServiceUserDesp3[18] = "F91 Incoming Text";


/*********************************************************************
* Profile Attributes - Table
*/

static gattAttribute_t f91_notification_serviceAttrTbl[SERVAPP_NUM_ATTR_SUPPORTED] =
{
  // f91_notification_service Service Declaration
  {
    { ATT_BT_UUID_SIZE, primaryServiceUUID },
    GATT_PERMIT_READ,
    0,
    (uint8_t *)&f91NotificationServiceDecl
  },
  // Characteristic 1 Declaration
  {
    { ATT_BT_UUID_SIZE, characterUUID },
    GATT_PERMIT_READ,
    0,
    &f91NotificationServiceChar1Props
  },
      // Characteristic Value 1
      {
        { ATT_UUID_SIZE, f91_notification_serviceChar1UUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        &f91NotificationServiceChar1
      },
      // Characteristic 1 User Description
      {
        { ATT_BT_UUID_SIZE, charUserDescUUID },
        GATT_PERMIT_READ,
        0,
        f91NotificationServiceUserDesp1
      },
    // Characteristic 2 Declaration
  {
    { ATT_BT_UUID_SIZE, characterUUID },
    GATT_PERMIT_READ,
    0,
    &f91NotificationServiceChar2Props
  },
      // Characteristic Value 2
      {
        { ATT_UUID_SIZE, f91_notification_serviceChar2UUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        &f91NotificationServiceChar2
      },
      // Characteristic 2 User Description
      {
        { ATT_BT_UUID_SIZE, charUserDescUUID },
        GATT_PERMIT_READ,
        0,
        f91NotificationServiceUserDesp2
      },
    // Characteristic 3 Declaration
  {
    { ATT_BT_UUID_SIZE, characterUUID },
    GATT_PERMIT_READ,
    0,
    &f91NotificationServiceChar3Props
  },
      // Characteristic Value 3
      {
        { ATT_UUID_SIZE, f91_notification_serviceChar3UUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        &f91NotificationServiceChar3
      },
      // Characteristic 3 User Description
      {
        { ATT_BT_UUID_SIZE, charUserDescUUID },
        GATT_PERMIT_READ,
        0,
        f91NotificationServiceUserDesp3
      },
};

/*********************************************************************
 * LOCAL FUNCTIONS
 */
static bStatus_t f91_notification_service_ReadAttrCB( uint16 connHandle, gattAttribute_t *pAttr,
                                           uint8 *pValue, uint16 *pLen, uint16 offset,
                                           uint16 maxLen, uint8 method );
static bStatus_t f91_notification_service_WriteAttrCB( uint16 connHandle, gattAttribute_t *pAttr,
                                            uint8 *pValue, uint16 len, uint16 offset,
                                            uint8 method );

/*********************************************************************
 * PROFILE CALLBACKS
 */
// Simple Profile Service Callbacks
CONST gattServiceCBs_t f91_notification_serviceCBs =
{
  f91_notification_service_ReadAttrCB,  // Read callback function pointer
  f91_notification_service_WriteAttrCB, // Write callback function pointer
  NULL                       // Authorization callback function pointer
};

/*********************************************************************
* PUBLIC FUNCTIONS
*/

/*
 * F91_notification_service_AddService- Initializes the F91_notification_service service by registering
 *          GATT attributes with the GATT server.
 *
 */
bStatus_t F91_notification_service_AddService( void )
{
  uint8_t status;

  // Register GATT attribute list and CBs with GATT Server App
  status = GATTServApp_RegisterService( f91_notification_serviceAttrTbl,
                                        GATT_NUM_ATTRS( f91_notification_serviceAttrTbl ),
                                        GATT_MAX_ENCRYPT_KEY_SIZE,
                                        &f91_notification_serviceCBs );

  return ( status );
}

/*
 * F91_notification_service_RegisterAppCBs - Registers the application callback function.
 *                    Only call this function once.
 *
 *    appCallbacks - pointer to application callbacks.
 */
bStatus_t F91_notification_service_RegisterAppCBs( f91_notification_serviceCBs_t *appCallbacks )
{
  if ( appCallbacks )
  {
    pNotificationsAppCBs = appCallbacks;

    return ( SUCCESS );
  }
  else
  {
    return ( bleAlreadyInRequestedMode );
  }
}

/*
 * F91_notification_service_SetParameter - Set a F91_notification_service parameter.
 *
 *    param - Profile parameter ID
 *    len - length of data to right
 *    value - pointer to data to write.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16 will be cast to
 *          uint16 pointer).
 */
bStatus_t F91_notification_service_SetParameter( uint8 param, uint8 len, void *value )
{
  bStatus_t ret = SUCCESS;
  switch ( param )
  {
    case F91_NOTIFICATION_SERVICE_CHAR1:
      if ( len == sizeof ( uint8 ) )
      {
        f91NotificationServiceChar1 = *((uint8*)value);
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;
    case F91_NOTIFICATION_SERVICE_CHAR2:
      if ( len == sizeof ( uint8 ) )
      {
        f91NotificationServiceChar2 = *((uint8*)value);
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;
    case F91_NOTIFICATION_SERVICE_CHAR3:
      if ( len == sizeof ( uint8 ) )
      {
        f91NotificationServiceChar3 = *((uint8*)value);
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;
    default:
      ret = INVALIDPARAMETER;
      break;
  }
  return ret;
}


/*
 * F91_notification_service_GetParameter - Get a F91_notification_service parameter.
 *
 *    param - Profile parameter ID
 *    value - pointer to data to write.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16 will be cast to
 *          uint16 pointer).
 */
bStatus_t F91_notification_service_GetParameter( uint8 param, void *value )
{
  bStatus_t ret = SUCCESS;
  switch ( param )
  {
    case F91_NOTIFICATION_SERVICE_CHAR1:
          *((uint8*)value) = f91NotificationServiceChar1;
      break;
    case F91_NOTIFICATION_SERVICE_CHAR2:
          *((uint8*)value) = f91NotificationServiceChar2;
      break;
    case F91_NOTIFICATION_SERVICE_CHAR3:
          *((uint8*)value) = f91NotificationServiceChar3;
      break;
    default:
      ret = INVALIDPARAMETER;
      break;
  }
  return ret;
}


/*********************************************************************
 * @fn          f91_notification_service_ReadAttrCB
 *
 * @brief       Read an attribute.
 *
 * @param       connHandle - connection message was received on
 * @param       pAttr - pointer to attribute
 * @param       pValue - pointer to data to be read
 * @param       pLen - length of data to be read
 * @param       offset - offset of the first octet to be read
 * @param       maxLen - maximum length of data to be read
 * @param       method - type of read message
 *
 * @return      SUCCESS, blePending or Failure
 */
static bStatus_t f91_notification_service_ReadAttrCB( uint16 connHandle, gattAttribute_t *pAttr,
                                       uint8 *pValue, uint16 *pLen, uint16 offset,
                                       uint16 maxLen, uint8 method )
{
  bStatus_t status = SUCCESS;

  // Make sure it's not a blob operation (no attributes in the profile are long)
  if ( offset > 0 )
  {
    return ( ATT_ERR_ATTR_NOT_LONG );
  }

  if ( pAttr->type.len == ATT_UUID_SIZE ) {
        // 128-bit UUID
    if (!memcmp(pAttr->type.uuid, f91_notification_serviceChar1UUID, ATT_UUID_SIZE)) {
      *pLen = 1;
      pValue[0] = *pAttr->pValue;
    } else if (!memcmp(pAttr->type.uuid, f91_notification_serviceChar2UUID, ATT_UUID_SIZE)) {
      *pLen = 1;
      pValue[0] = *pAttr->pValue;
    } else if (!memcmp(pAttr->type.uuid, f91_notification_serviceChar3UUID, ATT_UUID_SIZE)) {
      *pLen = 1;
      pValue[0] = *pAttr->pValue;
    }
  }


  return status;
}


/*********************************************************************
 * @fn      f91_notification_service_WriteAttrCB
 *
 * @brief   Validate attribute data prior to a write operation
 *
 * @param   connHandle - connection message was received on
 * @param   pAttr - pointer to attribute
 * @param   pValue - pointer to data to be written
 * @param   len - length of data
 * @param   offset - offset of the first octet to be written
 * @param   method - type of write message
 *
 * @return  SUCCESS, blePending or Failure
 */
static bStatus_t f91_notification_service_WriteAttrCB( uint16 connHandle, gattAttribute_t *pAttr,
                                        uint8 *pValue, uint16 len, uint16 offset,
                                        uint8 method )
{
  bStatus_t status = SUCCESS;
  uint8 notifyApp = 0xFF;

  if ( pAttr->type.len == ATT_UUID_SIZE ) {
      // 128-bit UUID
      if (!memcmp(pAttr->type.uuid, f91_notification_serviceChar1UUID, ATT_UUID_SIZE)) {
          uint8 *pCurValue = (uint8 *)pAttr->pValue;
          *pCurValue = pValue[0];
          if( pAttr->pValue == &f91NotificationServiceChar1 ) {
            notifyApp = F91_NOTIFICATION_SERVICE_CHAR1;
          }
      } else if(!memcmp(pAttr->type.uuid, f91_notification_serviceChar2UUID, ATT_UUID_SIZE)) {
          uint8 *pCurValue = (uint8 *)pAttr->pValue;
          *pCurValue = pValue[0];
          if( pAttr->pValue == &f91NotificationServiceChar2 ) {
            notifyApp = F91_NOTIFICATION_SERVICE_CHAR2;
          }
      } else if(!memcmp(pAttr->type.uuid, f91_notification_serviceChar3UUID, ATT_UUID_SIZE)) {
          uint8 *pCurValue = (uint8 *)pAttr->pValue;
          *pCurValue = pValue[0];
          if( pAttr->pValue == &f91NotificationServiceChar3 ) {
            notifyApp = F91_NOTIFICATION_SERVICE_CHAR3;
          }
      } else {
          status = ATT_ERR_INVALID_HANDLE;
      }

  } else {
    // 128-bit UUID
    status = ATT_ERR_INVALID_HANDLE;
  }


  // If a characteristic value changed then callback function to notify application of change
  if ( (notifyApp != 0xFF ) && pNotificationsAppCBs && pNotificationsAppCBs->pfnNotificationChangeCb ) {
    pNotificationsAppCBs->pfnNotificationChangeCb( notifyApp );
  }

  return status;
}
