/******************************************************************************

 @file  f91_utils.h

 @brief Utilities for F91 Kepler services

 Target Device: CC2640

 ******************************************************************************

 Copyright (c) 2012-2018, Texas Instruments Incorporated
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:

 *  Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

 *  Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

 *  Neither the name of Texas Instruments Incorporated nor the names of
    its contributors may be used to endorse or promote products derived
    from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 ******************************************************************************
 Release Name: ble_sdk_2_02_02_25
 Release Date: 2018-04-02 18:03:35
 *****************************************************************************/

#ifndef F91_UTILS_H
#define F91_UTILS_H

#include "gatt.h"
#include <ti/display/Display.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Mailbox.h>

#define IS_DEV_BOARD

/*********************************************************************
 * CONSTANTS
 */
#define NUMMSGS         5


/*********************************************************************
 * TYPEDEFS
 */
/*
 * This type is accessed by the application. When changing the data members of
 * this structure, considerations should be made for padding and data alignment.
 */
typedef struct MsgObj {
   uint8_t    id;
   void       *value;
} MsgObj;

/*
 * Mailbox messages are stored in a queue that requires a header in front of
 * each message. Mailbox_MbxElem is defined such that the header and its size
 * are factored into the total data size requirement for a mailbox instance.
 * Because Mailbox_MbxElem contains Int data types, padding may be added to
 * this struct depending on the data members defined in MsgObj.
 */
typedef struct MailboxMsgObj {
    Mailbox_MbxElem  elem;      /* Mailbox header        */
    MsgObj           obj;       /* Application's mailbox */
} MailboxMsgObj;

/*********************************************************************
 * GLOBALS
 */

extern Display_Handle F91_LOGGER;

extern Mailbox_Struct mbxStruct;
extern Mailbox_Handle mbxHandle;

extern Semaphore_Struct semStruct;
extern Semaphore_Handle semHandle;
/*********************************************************************
 * MACROS
 */

// F91-Kepler Base 128-bit UUID: FA35XXXX-7989-11EB-9439-0242AC130002
#define F91_BASE_UUID_128(uuid) 0x02, 0x00, 0x13, 0xAC, 0x42, 0x02, 0x39, 0x94, \
                0xEB, 0x11, 0x89, 0x79, LO_UINT16(uuid), HI_UINT16(uuid), 0x35, 0xFA


/*-------------------------------------------------------------------
 * FUNCTIONS
 */

#endif /* F91_UTILS_H */
