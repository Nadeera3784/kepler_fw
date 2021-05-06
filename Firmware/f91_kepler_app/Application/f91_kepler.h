/******************************************************************************

 @file  f91_kepler.h

 @brief This file contains the F91 Kepler Smart Watch application
        definitions and prototypes.

 Target Device: cc2640r2

 ******************************************************************************
 
 Copyright (c) 2013-2021, Texas Instruments Incorporated
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
 
 
 *****************************************************************************/

#ifndef F91KEPLER_H
#define F91KEPLER_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */

/*********************************************************************
*  EXTERNAL VARIABLES
*/

/*********************************************************************
 * CONSTANTS
 */

#define GAP_DEVICE_NAME_LEN_KEPLER        14

// Service ID's for internal application use
#define SERVICE_ID_NOTIFICATION      1
#define SERVICE_ID_CLOCK             2



/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * FUNCTIONS
 */

/*
 * Task creation function for F91 Kepler Smart Watch.
 */
extern void F91Kepler_createTask(void);

/*
 * Function to call when a characteristic value has changed
 */
extern void F91Kepler_notificationCharValueChangeCB(uint8_t paramID);

/*
 * Function to call when a characteristic value has changed
 */
extern void F91Kepler_clockCharValueChangeCB(uint8_t paramID);

/*
 * Function to call when a button value has changed
 */
extern void F91Kepler_buttonValueChangeCB(uint8_t *pData);

/*
 * Function to call when a display state change has been requested.
 */
extern void F91Kepler_displayStateChangeCB( void );
/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* F91KEPLER_H */
