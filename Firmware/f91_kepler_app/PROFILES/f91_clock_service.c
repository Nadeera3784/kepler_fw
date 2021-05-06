/**********************************************************************************************
 * Filename:       f91_clock_service.c
 *
 * Description:    This file contains the implementation of the service.
 *
 * Copyright (c) 2015-2021, Texas Instruments Incorporated
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
#include <ti/display/Display.h>

#include "bcomdef.h"
#include "OSAL.h"
#include "linkdb.h"
#include "att.h"
#include "gatt.h"
#include "gatt_uuid.h"
#include "gattservapp.h"
#include "gapbondmgr.h"
#include "f91_utils.h"

#include "f91_clock_service.h"

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * CONSTANTS
 */

#define SERVAPP_NUM_ATTR_SUPPORTED       13

/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
* GLOBAL VARIABLES
*/

// f91_clock_service Service UUID
CONST uint8_t f91_clock_serviceUUID[ATT_UUID_SIZE] =
{
  F91_BASE_UUID_128(F91_CLOCK_SERVICE_UUID)
};

// Characteristic 1 UUID: 0xB2F1
CONST uint8_t f91_clock_serviceChar1UUID[ATT_UUID_SIZE] =
{
 F91_BASE_UUID_128(F91_CLOCK_SERVICE_CHAR1_UUID)
};

// Characteristic 2 UUID: 0xB2F2
CONST uint8_t f91_clock_serviceChar2UUID[ATT_UUID_SIZE] =
{
 F91_BASE_UUID_128(F91_CLOCK_SERVICE_CHAR2_UUID)
};

// Characteristic 3 UUID: 0xB2F3
CONST uint8_t f91_clock_serviceChar3UUID[ATT_UUID_SIZE] =
{
 F91_BASE_UUID_128(F91_CLOCK_SERVICE_CHAR3_UUID)
};

// Characteristic 4 UUID: 0xB2F4
CONST uint8_t f91_clock_serviceChar4UUID[ATT_UUID_SIZE] =
{
 F91_BASE_UUID_128(F91_CLOCK_SERVICE_CHAR4_UUID)
};
/*********************************************************************
 * LOCAL VARIABLES
 */

static f91_clock_serviceCBs_t *pClocksAppCBs = NULL;

/*********************************************************************
* Profile Attributes - variables
*/

// Service declaration
static CONST gattAttrType_t f91ClockServiceDecl = { ATT_UUID_SIZE, f91_clock_serviceUUID };

// F91 Clock Characteristic 1 Properties
static uint8_t f91ClockServiceChar1Props = GATT_PROP_READ | GATT_PROP_WRITE;

// Characteristic 1 Value
static uint32_t f91ClockServiceChar1 = 0;

// F91 Characteristic 1 User Description
static uint8_t f91ClockServiceUserDesp1[9] = "F91 Time";

// F91 Clock Characteristic 2 Properties
static uint8_t f91ClockServiceChar2Props = GATT_PROP_READ | GATT_PROP_WRITE;

// Characteristic 2 Value
static uint16_t f91ClockServiceChar2 = 0; //TO DO: Change this to be string instead and handle time zone names (PST, CST, MST...)

// F91 Characteristic 2 User Description
static uint8_t f91ClockServiceUserDesp2[14] = "F91 Time Zone";

// F91 Clock Characteristic 3 Properties
static uint8_t f91ClockServiceChar3Props = GATT_PROP_READ | GATT_PROP_WRITE;

// Characteristic 3 Value
static uint8_t f91ClockServiceChar3 = 0;

// F91 Characteristic 3 User Description
static uint8_t f91ClockServiceUserDesp3[14] = "F91 Time Mode";

// F91 Clock Characteristic 4 Properties
static uint8_t f91ClockServiceChar4Props = GATT_PROP_READ | GATT_PROP_WRITE;

// Characteristic 4 Value
static uint8_t f91ClockServiceChar4 = 0;

// F91 Characteristic 4 User Description
static uint8_t f91ClockServiceUserDesp4[8] = "F91 DST";

/*********************************************************************
* Profile Attributes - Table
*/

static gattAttribute_t f91_clock_serviceAttrTbl[SERVAPP_NUM_ATTR_SUPPORTED] =
{
  // f91_clock_service Service Declaration
  {
    { ATT_BT_UUID_SIZE, primaryServiceUUID },
    GATT_PERMIT_READ,
    0,
    (uint8_t *)&f91ClockServiceDecl
  },

  // Characteristic 1 Declaration
  {
    { ATT_BT_UUID_SIZE, characterUUID },
    GATT_PERMIT_READ,
    0,
    &f91ClockServiceChar1Props
  },
      // Characteristic Value 1
      {
        { ATT_UUID_SIZE, f91_clock_serviceChar1UUID },
        GATT_PERMIT_AUTHEN_READ | GATT_PERMIT_AUTHEN_WRITE,
        0,
         (uint8_t *)&f91ClockServiceChar1
      },
      // Characteristic 1 User Description
      {
        { ATT_BT_UUID_SIZE, charUserDescUUID },
        GATT_PERMIT_READ,
        0,
        f91ClockServiceUserDesp1
      },
  
  // Characteristic 2 Declaration
  {
    { ATT_BT_UUID_SIZE, characterUUID },
    GATT_PERMIT_READ,
    0,
    &f91ClockServiceChar2Props
  },
      // Characteristic Value 2
      {
        { ATT_UUID_SIZE, f91_clock_serviceChar2UUID },
        GATT_PERMIT_AUTHEN_READ | GATT_PERMIT_AUTHEN_WRITE,
        0,
         (uint8_t *)&f91ClockServiceChar2
      },
      // Characteristic 2 User Description
      {
        { ATT_BT_UUID_SIZE, charUserDescUUID },
        GATT_PERMIT_READ,
        0,
        f91ClockServiceUserDesp2
      },
  
  // Characteristic 3 Declaration
  {
    { ATT_BT_UUID_SIZE, characterUUID },
    GATT_PERMIT_READ,
    0,
    &f91ClockServiceChar3Props
  },
      // Characteristic Value 3
      {
        { ATT_UUID_SIZE, f91_clock_serviceChar3UUID },
        GATT_PERMIT_AUTHEN_READ | GATT_PERMIT_AUTHEN_WRITE,
        0,
        &f91ClockServiceChar3
      },
      // Characteristic 3 User Description
      {
        { ATT_BT_UUID_SIZE, charUserDescUUID },
        GATT_PERMIT_READ,
        0,
        f91ClockServiceUserDesp3
      },

  // Characteristic 4 Declaration
  {
    { ATT_BT_UUID_SIZE, characterUUID },
    GATT_PERMIT_READ,
    0,
    &f91ClockServiceChar4Props
  },
      // Characteristic Value 4
      {
        { ATT_UUID_SIZE, f91_clock_serviceChar4UUID },
        GATT_PERMIT_AUTHEN_READ | GATT_PERMIT_AUTHEN_WRITE,
        0,
        &f91ClockServiceChar4
      },
      // Characteristic 4 User Description
      {
        { ATT_BT_UUID_SIZE, charUserDescUUID },
        GATT_PERMIT_READ,
        0,
        f91ClockServiceUserDesp4
      },
};

/*********************************************************************
 * LOCAL FUNCTIONS
 */
static bStatus_t f91_clock_service_ReadAttrCB( uint16 connHandle, gattAttribute_t *pAttr,
                                           uint8_t *pValue, uint16 *pLen, uint16 offset,
                                           uint16 maxLen, uint8_t method );
static bStatus_t f91_clock_service_WriteAttrCB( uint16 connHandle, gattAttribute_t *pAttr,
                                            uint8_t *pValue, uint16 len, uint16 offset,
                                            uint8_t method );

/*********************************************************************
 * PROFILE CALLBACKS
 */
// Simple Profile Service Callbacks
CONST gattServiceCBs_t f91_clock_serviceCBs =
{
  f91_clock_service_ReadAttrCB,  // Read callback function pointer
  f91_clock_service_WriteAttrCB, // Write callback function pointer
  NULL                       // Authorization callback function pointer
};

/*********************************************************************
* PUBLIC FUNCTIONS
*/

/*
 * F91_clock_service_AddService- Initializes the F91_clock_service service by registering
 *          GATT attributes with the GATT server.
 *
 */
bStatus_t F91_clock_service_AddService(void)
{
  uint8_t status;
  // Register GATT attribute list and CBs with GATT Server App
  status = GATTServApp_RegisterService( f91_clock_serviceAttrTbl,
                                        GATT_NUM_ATTRS( f91_clock_serviceAttrTbl ),
                                        GATT_MAX_ENCRYPT_KEY_SIZE,
                                        &f91_clock_serviceCBs );

  return ( status );
}

/*
 * F91_clock_service_RegisterAppCBs - Registers the application callback function.
 *                    Only call this function once.
 *
 *    appCallbacks - pointer to application callbacks.
 */
bStatus_t F91_clock_service_RegisterAppCBs( f91_clock_serviceCBs_t *appCallbacks )
{
  if ( appCallbacks )
  {
    pClocksAppCBs = appCallbacks;

    return ( SUCCESS );
  }
  else
  {
    return ( bleAlreadyInRequestedMode );
  }
}

/*
 * F91_clock_service_SetParameter - Set a F91_clock_service parameter.
 *
 *    param - Profile parameter ID
 *    len - length of data to right
 *    value - pointer to data to write.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16 will be cast to
 *          uint16 pointer).
 */
bStatus_t F91_clock_service_SetParameter( uint8_t param, uint16_t len, void *value )
{
  bStatus_t ret = SUCCESS;

  switch ( param )
  {
    case F91_CLOCK_SERVICE_CHAR1:
      if ( len == sizeof ( uint32_t ) )
      {
        f91ClockServiceChar1 = *((uint32_t*)value);
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;
    case F91_CLOCK_SERVICE_CHAR2:
      if ( len == sizeof ( uint16_t ) )
      {
        f91ClockServiceChar2 = *((uint16_t*)value);
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;
    case F91_CLOCK_SERVICE_CHAR3:
      if ( len == sizeof ( uint8_t ) )
      {
        f91ClockServiceChar3 = *((uint8_t*)value);
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;
    case F91_CLOCK_SERVICE_CHAR4:
      if ( len == sizeof ( uint8_t ) )
      {
        f91ClockServiceChar4 = *((uint8_t*)value);
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
 * F91_clock_service_GetParameter - Get a F91_clock_service parameter.
 *
 *    param - Profile parameter ID
 *    value - pointer to data to write.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16 will be cast to
 *          uint16 pointer).
 */
bStatus_t F91_clock_service_GetParameter( uint8_t param, void *value )
{
  bStatus_t ret = SUCCESS;
  switch ( param )
  {
    case F91_CLOCK_SERVICE_CHAR1:
        *((uint32_t*)value) = f91ClockServiceChar1;
      break;
    case F91_CLOCK_SERVICE_CHAR2:
        *((uint16_t*)value) = f91ClockServiceChar2;
      break;
    case F91_CLOCK_SERVICE_CHAR3:
        *((uint8_t*)value) = f91ClockServiceChar3;
      break;
    case F91_CLOCK_SERVICE_CHAR4:
        *((uint8_t*)value) = f91ClockServiceChar4;
      break;
    default:
      ret = INVALIDPARAMETER;
      break;
  }
  return ret;
}

/*********************************************************************
 * @fn          f91_clock_service_ReadAttrCB
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
static bStatus_t f91_clock_service_ReadAttrCB( uint16_t connHandle, gattAttribute_t *pAttr,
                                       uint8_t *pValue, uint16_t *pLen, uint16_t offset,
                                       uint16_t maxLen, uint8_t method )
{
  bStatus_t status = SUCCESS;

  // Make sure it's not a blob operation (no attributes in the profile are long)
  if ( offset > 0 )
  {
    return ( ATT_ERR_ATTR_NOT_LONG );
  }

  if ( pAttr->type.len == ATT_UUID_SIZE ) {
        // 128-bit UUID
    if (!memcmp(pAttr->type.uuid, f91_clock_serviceChar1UUID, ATT_UUID_SIZE)) {
      *pLen = sizeof(uint32_t);
      memcpy(pValue, pAttr->pValue + offset, *pLen);
      
    } else if (!memcmp(pAttr->type.uuid, f91_clock_serviceChar2UUID, ATT_UUID_SIZE)) {
      *pLen = sizeof(uint16_t);
      memcpy(pValue, pAttr->pValue + offset, *pLen);
    } else if (!memcmp(pAttr->type.uuid, f91_clock_serviceChar3UUID, ATT_UUID_SIZE)) {
      *pLen = 1;
      pValue[0] = *pAttr->pValue;
    } else if (!memcmp(pAttr->type.uuid, f91_clock_serviceChar4UUID, ATT_UUID_SIZE)) {
      *pLen = 1;
      pValue[0] = *pAttr->pValue;
    } 
  }


  return status;
}


/*********************************************************************
 * @fn      f91_clock_service_WriteAttrCB
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
static bStatus_t f91_clock_service_WriteAttrCB( uint16_t connHandle, gattAttribute_t *pAttr,
                                        uint8_t *pValue, uint16_t len, uint16_t offset,
                                        uint8_t method )
{
  bStatus_t status = SUCCESS;
  uint8_t notifyApp = 0xFF;
  if ( pAttr->type.len == ATT_UUID_SIZE ) {
      // 128-bit UUID
      if (!memcmp(pAttr->type.uuid, f91_clock_serviceChar1UUID, ATT_UUID_SIZE)) {
          memcpy(pAttr->pValue + offset, pValue, len);
          notifyApp = F91_CLOCK_SERVICE_CHAR1;
      } else if(!memcmp(pAttr->type.uuid, f91_clock_serviceChar2UUID, ATT_UUID_SIZE)) {
          memcpy(pAttr->pValue + offset, pValue, len);
          notifyApp = F91_CLOCK_SERVICE_CHAR2;
      } else if(!memcmp(pAttr->type.uuid, f91_clock_serviceChar3UUID, ATT_UUID_SIZE)) {
          uint8_t *pCurValue = (uint8_t *)pAttr->pValue;
          *pCurValue = pValue[0];
          if( pAttr->pValue == &f91ClockServiceChar3 ) {
            notifyApp = F91_CLOCK_SERVICE_CHAR3;
          }
      } else if(!memcmp(pAttr->type.uuid, f91_clock_serviceChar4UUID, ATT_UUID_SIZE)) {
          uint8_t *pCurValue = (uint8_t *)pAttr->pValue;
          *pCurValue = pValue[0];
          if( pAttr->pValue == &f91ClockServiceChar4 ) {
            notifyApp = F91_CLOCK_SERVICE_CHAR4;
          }
      } else {
          status = ATT_ERR_INVALID_HANDLE;
      }
  } else {
    // 128-bit UUID
    status = ATT_ERR_INVALID_HANDLE;
  }


  // If a characteristic value changed then callback function to notify application of change
  if ( (notifyApp != 0xFF ) && pClocksAppCBs && pClocksAppCBs->pfnClockChangeCb ) {
    pClocksAppCBs->pfnClockChangeCb( notifyApp );
  }

  return status;
}
