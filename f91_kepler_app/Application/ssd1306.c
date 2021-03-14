/**********************************************************************************************
 * Filename:       ssd1306.c
 *
 * Description:    This file contains the implementation of SSD1306 OLED Display Driver.
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
#include "ssd1306.h"
#include "fonts_icons.h"
#include "font_5x7.h"
#include "f91_utils.h"

#include <ti/display/Display.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/I2C.h>
#include <ti/sysbios/BIOS.h>

#include "Board.h"


/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * CONSTANTS
 */

// Height and Width
#define DISPLAY_HEIGHT      0x27 //0x27 //39 pixels //0x28 //40 pixels
#define DISPLAY_WIDTH       0x60 //0x60 //96 pixels //0x80 (use for flipped) //128 pixels

// SSD1306 Address
#define SSD1306_I2C_ADDR    0x3c //or 0x3d

// Register Definitions
#define SET_DISP_OFF        0xae
#define SET_DISP_ON         0xaf
#define SET_CONTRAST        0x81
#define SET_ENTIRE_ON       0xa4
#define SET_NORM_INV        0xa6
#define SET_MEM_ADDR        0x20
#define SET_COL_ADDR        0x21
#define SET_PAGE_ADDR       0x22
#define SET_DISP_START_LINE 0x40
// #define SET_SEG_REMAP       0xa1 //For flipped.
#define SET_SEG_REMAP       0xa0
#define SET_MUX_RATIO       0xa8
// #define SET_COM_OUT_DIR     0xc8 //For flipped.
#define SET_COM_OUT_DIR     0xc0
#define SET_DISP_OFFSET     0xd3
#define SET_COM_PIN_CFG     0xda
#define SET_DISP_CLK_DIV    0xd5
#define SET_PRECHARGE       0xd9
#define SET_VCOM_DESEL      0xdb
#define SET_CHARGE_PUMP     0x8d

/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
* GLOBAL VARIABLES
*/

/*********************************************************************
 * LOCAL VARIABLES
 */

uint8_t ssd1306_display_buffer[481];
uint8_t buffer[6];
uint8_t command_buffer[2];
uint8_t txBuffer[1];
uint8_t rxBuffer[2];
bool displayInitialized = false;
uint8_t displayState = 0;

I2C_Handle              i2c_connection;
I2C_Params              i2c_params;
I2C_Transaction         i2c_transaction;

/*********************************************************************
 * LOCAL FUNCTIONS
 */
void ssd1306_command(uint8_t command);
void ssd1306_clear_buffer(uint8_t *buffer, int size);
void ssd1306_send_buffer(uint8_t *buffer, int size);
void ssd1306_draw_pixel(uint8_t x, uint8_t y, bool erase);
void ssd1306_set_position(uint8_t, uint8_t);

/*********************************************************************
 * @fn      ssd1306_command()
 *
 * @brief   Sends internal command to SSD1306 chip
 *
 * @param command the command to send to SSD1306 chip
 *
 * @return  None.
 *
 */
void ssd1306_command(uint8_t command) {
    command_buffer[0] = 0x80;
    command_buffer[1] = command;
    ssd1306_send_buffer(command_buffer, sizeof(command_buffer));
}

/*********************************************************************
 * @fn      ssd1306_clear_buffer()
 *
 * @brief   Clears the display buffer, sets it to all zeros.
 *
 * @param buffer pointer to the buffer to clear.
 * @param size represents the size of the buffer.
 * 
 * @return None.
 *
 */
void ssd1306_clear_buffer(uint8_t *buffer, int size) {
    ssd1306_set_position(0, 0);
    memset(ssd1306_display_buffer, 0, sizeof(ssd1306_display_buffer)); //Reset buffer
    ssd1306_display_buffer[0]=0x40;
    ssd1306_set_position(0,0);
}

/*********************************************************************
 * @fn      ssd1306_send_buffer()
 *
 * @param buffer pointer to the buffer to send.
 * @param size represents the size of the buffer.
 * 
 * @return None.
 *
 */
void ssd1306_send_buffer(uint8_t *buffer, int size) {
    i2c_transaction.writeBuf = buffer;
    i2c_transaction.writeCount = size;
    i2c_transaction.readBuf = NULL;
    i2c_transaction.readCount = 0;
    i2c_transaction.slaveAddress = SSD1306_I2C_ADDR;
    if (!I2C_transfer(i2c_connection, &i2c_transaction)) {
        /* Could not send command to SSD1306, error */
        Display_print0(F91_LOGGER, 9, 0, "ERROR OCCURED");
        while(1);
    }
}

/*********************************************************************
 * @fn      ssd1306_draw_pixel()
 *
 * @brief   Adds a single pixel to the buffer.
 *
 * @param x represents x-coordinate.
 * @param y represents y-coordinate.
 * @param erase represents wether to erase a pixel (true) or draw one (false)
 * 
 * @return None.
 *
 */
void ssd1306_draw_pixel(uint8_t x, uint8_t y, bool erase){
    ssd1306_display_buffer[0] = 0x40; //Command byte.

    if(erase){
        ssd1306_display_buffer[1 + x + (y / 8) * 96] &= ~(1 << (y & 7));
    } else {
        ssd1306_display_buffer[1 + x + (y / 8) * 96] |= (1 << (y & 7));
    }
}

/*********************************************************************
 * @fn      ssd1306_set_position()
 *
 * @brief   Sets position of the cursor.
 *
 * @param column represents the column to go to.
 * @param page represents the row. SSD1306 handles rows in bytes.
 *
 * @return None.
 *
 */
void ssd1306_set_position(uint8_t column, uint8_t page) {
    if (column > DISPLAY_WIDTH) {
        column = 0;                     // constrain column to upper limit
    }

    if (page > 4) {
        page = 0;                       // constrain page to upper limit
    }

    ssd1306_command(SET_COL_ADDR);
    ssd1306_command(column);            // Column start address (0 = reset) //flipped
    // ssd1306_command(column + 32);    // Use for flipped.
    ssd1306_command(DISPLAY_WIDTH - 1); // Column end address (96 = reset)

    ssd1306_command(SET_PAGE_ADDR);
    ssd1306_command(page);              // Page start address (0 = reset)
    ssd1306_command(4);                 // Page end address
}

/*********************************************************************
 * PROFILE CALLBACKS
 */

/*********************************************************************
* PUBLIC FUNCTIONS
*/

/*********************************************************************
 * @fn      ssd1306_init()
 *
 * @brief   Initializes the SSD1306 oled display.
 *
 * @param None.
 *
 * @return None.
 *
 */
void ssd1306_init(void) {//Init Sequence
    /* Create I2C for usage */
    I2C_Params_init(&i2c_params);
    i2c_params.bitRate = I2C_400kHz;
    i2c_connection = I2C_open(Board_I2C0, &i2c_params);
    if (i2c_connection == NULL) {
        while (1);
    }

    i2c_transaction.writeBuf   = txBuffer;
    i2c_transaction.writeCount = 1;
    i2c_transaction.readBuf    = rxBuffer;
    i2c_transaction.readCount  = 2;

    /* Try to connect to OLED. */
    i2c_transaction.slaveAddress = SSD1306_I2C_ADDR;
    if (!I2C_transfer(i2c_connection, &i2c_transaction)) {
        /* Could not resolve a sensor, error */
        while(1){}
    } else {

        //Set Display to OFF.
        ssd1306_command(SET_DISP_OFF);

        //Set Display clock divide ratio/oscillator frequency
        ssd1306_command(SET_DISP_CLK_DIV);
        ssd1306_command(0X80);

        //Set multiplex ratio.
        ssd1306_command(SET_MUX_RATIO);
        ssd1306_command(DISPLAY_HEIGHT - 1);

        //Set Display offset
        ssd1306_command(SET_DISP_OFFSET);
        ssd1306_command(0x00);

        //Set Display Start Line
        ssd1306_command(SET_DISP_START_LINE);

        //Set Charge Pump (0x10 External, 0x14 Internal DC)
        ssd1306_command(SET_CHARGE_PUMP);
        ssd1306_command(0x14);

        //Resolution and layout
        ssd1306_command(SET_SEG_REMAP);

        //Set Com output scan direction
        ssd1306_command(SET_COM_OUT_DIR);

        //Set Com hardware configuration
        ssd1306_command(SET_COM_PIN_CFG);
        ssd1306_command(0x12);

        //Set Contrast
        ssd1306_command(SET_CONTRAST);
        ssd1306_command(0xff);

        //Set Pre-charge period (0x22 external, 0xF1 internal)
        ssd1306_command(SET_PRECHARGE);
        ssd1306_command(0x25);

        //Set VCOMH deselect level
        ssd1306_command(SET_VCOM_DESEL);
        ssd1306_command(0x20);

        //Set all pixels (output follows RAM contents)
        ssd1306_command(SET_ENTIRE_ON);

        //Set Display not inverted
        ssd1306_command(SET_NORM_INV);

        //Set Memory Address.
        ssd1306_command(SET_MEM_ADDR);
        ssd1306_command(0x10);

        //Set Display Off (default)
        ssd1306_command(SET_DISP_OFF);
        // //Display_print0(F91_LOGGER, 0, 0, "Init complete!");

        ssd1306_clear();
        ssd1306_update();
        displayInitialized = true;
    }
}

/*********************************************************************
 * @fn      ssd1306_update()
 *
 * @brief   Sends the display buffer to update the display.
 *
 * @param None.
 *
 * @return  None.
 *
 */
void ssd1306_update( void ) {
    Semaphore_pend(semHandle, BIOS_WAIT_FOREVER);
    ssd1306_send_buffer(ssd1306_display_buffer, sizeof(ssd1306_display_buffer));
    Semaphore_post(semHandle);
}

/*********************************************************************
 * @fn      ssd1306_clear()
 *
 * @brief   Clears the display buffer.
 *
 * @param None.
 * @return None.
 *
 */
void ssd1306_clear( void ) {
    Semaphore_pend(semHandle, BIOS_WAIT_FOREVER);
    ssd1306_clear_buffer(ssd1306_display_buffer, sizeof(ssd1306_display_buffer));;
    Semaphore_post(semHandle);
}

/*********************************************************************
 * @fn      ssd1306_display_text()
 *
 * @brief   Adds plain text to the buffer to be displayed.
 *
 * @param text pointer to the string to be displayed.
 * @param x position in the x-plane to display the text.
 * @param y poisition in the y-plane to display the text.
 * @param erase represents wether to erase (true) or write (false) the text.
 *
 * @return None.
 *
 */
void ssd1306_display_text(char *text, uint8_t x, uint8_t y, bool erase) {
    Semaphore_pend(semHandle, BIOS_WAIT_FOREVER);

    ssd1306_set_position(0, 0);
    while (*text != '\0') {
        uint8_t b_x, b_y, dataByte;
        for(b_x = 0; b_x<=4; b_x++) {
            dataByte = font_5x7[*text - ' '][b_x];
            for(b_y=0; b_y<=8; b_y++){
                if(((dataByte & 0x01) == 0x01) && !erase) {
                    ssd1306_draw_pixel(x + b_x, y + (b_y), false);
                } else {
                    ssd1306_draw_pixel(x + b_x, y + (b_y), true);
                }
                dataByte>>=1; // Shift.
            }
        }
        text++;
        x+=6;
    }

    Semaphore_post(semHandle);
}

/*********************************************************************
 * @fn      ssd1306_display_number()
 *
 * @brief   Adds large seven-segment style number to buffer to be displayed. (hour & minutes style)
 *
 * @param number number to be displayed.
 * @param x position in the x-plane to display the number.
 * @param y poisition in the y-plane to display the number.
 * @param erase represents wether to erase (true) or write (false) the number.
 *
 * @return None.
 *
 */
void ssd1306_display_number(uint8_t number, uint8_t x, uint8_t y, bool erase) {
    Semaphore_pend(semHandle, BIOS_WAIT_FOREVER);

    ssd1306_set_position(0, 0);
    uint8_t page, b_x, b_y, dataByte;
    for (page = 0; page<4; page++) {
        for(b_x = 0; b_x<=14; b_x++) {
            dataByte = numbers_15x25[number][b_x + (15*page)];
            for(b_y=0; b_y<=8; b_y++){
                if(((dataByte & 0x80) == 0x80) && !erase) {
                    ssd1306_draw_pixel(x + b_x, y + (b_y+(8*page)), false);
                } else {
                    ssd1306_draw_pixel(x + b_x, y + (b_y+(8*page)), true);
                }
                dataByte<<=1; // Shift.
            }
        }
    }
    Semaphore_post(semHandle);
}

/*********************************************************************
 * @fn      ssd1306_display_small_number()
 *
 * @brief   Adds small seven-segment style number to buffer to be displayed. (Seconds style)
 *
 * @param number number to be displayed.
 * @param x position in the x-plane to display the number.
 * @param y poisition in the y-plane to display the number.
 * @param erase represents wether to erase (true) or write (false) the number.
 *
 * @return None.
 *
 */
void ssd1306_display_small_number(uint8_t number, uint8_t x, uint8_t y, bool erase) {
    Semaphore_pend(semHandle, BIOS_WAIT_FOREVER);

    ssd1306_set_position(0, 0);
    uint8_t page, b_x, b_y, dataByte;
    for (page = 0; page<2; page++) {
        for(b_x = 0; b_x<=8; b_x++) {
            dataByte = numbers_9x13[number][b_x + (9*page)];
            for(b_y=0; b_y<=8; b_y++){
                if(((dataByte & 0x80) == 0x80) && !erase) {
                    ssd1306_draw_pixel(x + b_x, y + (b_y+(8*page)), false);
                } else {
                    ssd1306_draw_pixel(x + b_x, y + (b_y+(8*page)), true);
                }
                dataByte<<=1; // Shift.
            }
        }
    }
    Semaphore_post(semHandle);
}

/*********************************************************************
 * @fn      ssd1306_display_semicolon()
 *
 * @brief   Adds semicolon to buffer to be displayed.
 *
 * @param x position in the x-plane to display the semicolon.
 * @param y poisition in the y-plane to display the semicolon.
 * @param erase represents wether to erase (true) or write (false) the semicolon.
 *
 * @return None.
 *
 */
void ssd1306_display_semicolon(uint8_t x, uint8_t y, bool erase) {
    Semaphore_pend(semHandle, BIOS_WAIT_FOREVER);

    ssd1306_set_position(0, 0);
    uint8_t page, b_x, b_y, dataByte;
    for (page = 0; page<4; page++) {
        for(b_x = 0; b_x<=2; b_x++) {
            dataByte = semicolon_3x27[b_x + (3*page)];
            for(b_y=0; b_y<=8; b_y++){
                if(((dataByte & 0x80) == 0x80) && !erase) {
                    ssd1306_draw_pixel(x + b_x, y + (b_y+(8*page)), false);
                } else {
                    ssd1306_draw_pixel(x + b_x, y + (b_y+(8*page)), true);
                }
                dataByte<<=1; // Shift.
            }
        }
    }
    Semaphore_post(semHandle);
}

/*********************************************************************
 * @fn      ssd1306_display_pm()
 *
 * @brief   Adds "PM" to buffer to be displayed.
 *
 * @param x position in the x-plane to display the symbol.
 * @param y poisition in the y-plane to display the symbol.
 * @param erase represents wether to erase (true) or write (false) the symbol.
 *
 * @return None.
 *
 */
void ssd1306_display_pm(uint8_t x, uint8_t y, bool erase) {
    Semaphore_pend(semHandle, BIOS_WAIT_FOREVER);

    ssd1306_set_position(0, 0);
    uint8_t b_x, b_y, dataByte;
    for(b_x = 0; b_x<=11; b_x++) {
        dataByte = pm_12x7[b_x];
        for(b_y=0; b_y<=8; b_y++){
            if(((dataByte & 0x80) == 0x80) && !erase) {
                ssd1306_draw_pixel(x + b_x, y + (b_y), false);
            } else {
                ssd1306_draw_pixel(x + b_x, y + (b_y), true);
            }
            dataByte<<=1; // Shift.
        }
    }
    Semaphore_post(semHandle);
}

/*********************************************************************
 * @fn      ssd1306_display_notification()
 *
 * @brief   Adds notification symbol to buffer to be displayed.
 *
 * @param icon the notification symbol to be displayed.
 * @param x position in the x-plane to display the symbol.
 * @param y poisition in the y-plane to display the symbol.
 * @param erase represents wether to erase (true) or write (false) the symbol.
 *
 * @return None.
 *
 */
void ssd1306_display_notification(uint8_t icon, uint8_t x, uint8_t y, bool erase) {
    Semaphore_pend(semHandle, BIOS_WAIT_FOREVER);

    ssd1306_set_position(0, 0);
    uint8_t page, b_x, b_y, dataByte;
    for (page = 0; page<2; page++) {
        for(b_x = 0; b_x<=11; b_x++) {
            dataByte = icons_12x9[icon][b_x + (12*page)];
            for(b_y=0; b_y<=8; b_y++){
                if(((dataByte & 0x80) == 0x80) && !erase) {
                    ssd1306_draw_pixel(x + b_x, y + (b_y+(8*page)), false);
                } else {
                    ssd1306_draw_pixel(x + b_x, y + (b_y+(8*page)), true);
                }
                dataByte<<=1; // Shift.
            }
        }
    }
    Semaphore_post(semHandle);
}

/*********************************************************************
 * @fn      ssd1306_display_full_notification()
 *
 * @brief   Fills entire buffer with a full screen notification. Used for Texts & Calls.
 *
 * @param type represents the type of full screen notification to display.
 * @param text pointer to text string to add to the notification. ie. contact name.
 *
 * @return None.
 *
 */
void ssd1306_display_full_notification(uint8_t type, char *text) {
    Semaphore_pend(semHandle, BIOS_WAIT_FOREVER);

    ssd1306_set_position(0, 0);
    uint8_t page, b_x, b_y, dataByte;
    for (page = 0; page<5; page++) {
        for(b_x = 0; b_x<=95; b_x++) {
            if(type == INCOMING_CALL){
                dataByte = call_from_96x39[b_x + (96*page)];
            } else if (type == INCOMING_TEXT) {
                dataByte = text_from_96x39[b_x + (96*page)];
            } else {
                return;
            }
            for(b_y=0; b_y<=8; b_y++){
                if((dataByte & 0x80) == 0x80) {
                    ssd1306_draw_pixel(b_x, b_y+(8*page), false);
                }
                dataByte<<=1; // Shift.
            }
        }
    }

    // center the string and add to buffer
    // center within the available 69 pixels.  :|
    // each character is 6 pixels (+1 for whitespace after character)
    double centerPadding = 12 - strlen(text);
    centerPadding = ((centerPadding/2)*6)+25;
    int space = (int)centerPadding;
    Semaphore_post(semHandle);

    ssd1306_display_text(text, space, 21, false);
}

/*********************************************************************
 * @fn      ssd1306_toggle_display()
 *
 * @brief   Toggles the display to ON or OFF.
 *
 * @param state bool that indicates wether to turn ON or OFF the display.
 *
 * @return None.
 *
 */
void ssd1306_toggle_display ( bool state ) {
    Semaphore_pend(semHandle, BIOS_WAIT_FOREVER);
    if (state) {
        ssd1306_command(SET_DISP_ON);
        displayState = 1;
    } else {
        ssd1306_command(SET_DISP_OFF);
        displayState = 0;
    }
    Semaphore_post(semHandle);
}

/*********************************************************************
 * @fn      ssd1306_isReady()
 *
 * @brief   Used to check if the SSD1306 finished initialization.
 *
 * @param None.
 *
 * @return true if initialized, false otherwise.
 *
 */
bool ssd1306_isReady() {
    return displayInitialized;
}

/*********************************************************************
*********************************************************************/
