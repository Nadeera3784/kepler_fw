/**********************************************************************************************
 * Filename:       ssd1306.h
 *
 * Description:    This file contains the ssd1306 driver definitions and
 *                 prototypes.
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


#ifndef _SSD1306_H_
#define _SSD1306_H_

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

/*********************************************************************
 * CONSTANTS
 */

#define INCOMING_CALL       0x01
#define INCOMING_TEXT       0x02
#define EMAIL               0x00
#define TEXT                0x01
#define VOICEMAIL           0x02
#define MISSEDCALL          0x03
#define BLUETOOTH           0x04


// positions for time related stuff.
#define HR_1_POS_X           0
#define HR_2_POS_X           17

#define MIN_1_POS_X          39
#define MIN_2_POS_X          56

#define SEC_1_POS_X          74
#define SEC_2_POS_X          84

#define SEC_POS_Y            25
#define HR_MIN_POS_Y         13

#define PM_POS_X             74
#define PM_POS_Y             13

#define SEM_CLN_POS_X        34
#define SEM_CLN_POS_Y        13

#define DATE_POS_X           59
#define DATE_POS_Y           1

// positions for notification related stuff.
#define EMAIL_POS_X          0
#define TEXT_POS_X           14
#define VOIEMAIL_POS_X       29
#define MISSEDCALL_POS_X     44
#define NOTIFICATIONS_POS_Y  0

/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * Profile Callbacks
 */

/*********************************************************************
 * API FUNCTIONS
 */

extern void ssd1306_init( void );
extern void ssd1306_update( void );
extern void ssd1306_clear( void );
extern void ssd1306_display_text(char *text, uint8_t x, uint8_t y, bool erase);
extern void ssd1306_display_number(uint8_t number, uint8_t x, uint8_t y, bool erase);
extern void ssd1306_display_semicolon( uint8_t x, uint8_t y, bool erase);
extern void ssd1306_display_pm( uint8_t x, uint8_t y, bool erase);
extern void ssd1306_display_small_number(uint8_t number, uint8_t x, uint8_t y, bool erase);
extern void ssd1306_display_notification(uint8_t icon, uint8_t x, uint8_t y, bool erase);
extern void ssd1306_display_full_notification(uint8_t type, char *text);
extern void ssd1306_toggle_display( bool state );
extern bool ssd1306_isReady(void);
extern bool ssd1306_getState(void);

/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* _SSD1306_H_ */
