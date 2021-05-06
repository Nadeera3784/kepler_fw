/******************************************************************************

 @file  f91_clock.h

 @brief This file contains the F91 Kepler Smart Watch clock application.

 Target Device: cc2640r2

 ******************************************************************************

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

#ifndef F91CLOCK_H
#define F91CLOCK_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */
#include "board.h"
#include "f91_kepler.h"

/*********************************************************************
*  EXTERNAL VARIABLES
*/

/*********************************************************************
 * CONSTANTS
 */

//Time zones, currently only United States.
#define DEFAULT_TIME    758505600
#define TZ_HST          36000
#define TZ_AKST         32400
#define TZ_PST          28800
#define TZ_MST          25200
#define TZ_CST          21600
#define TZ_EST          18000

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * FUNCTIONS
 */

/*
 * Task creation function for F91 Kepler Smart Watch.
 */
extern void F91Clock_createTask(void);

/*
 * Initialize clock module
 */
extern void F91Clock_init(void);

/*
 * Task Event Processor for characteristic changes
 */
void F91Clock_processCharChangeEvt(uint8_t paramID);

/*
 * Task Event Processor for clock module
 */
extern void F91Clock_processEvent(void);


/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* F91CLOCK_H */
