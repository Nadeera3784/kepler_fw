#include "ssd1306.h"
#include "fonts_icons.h"
#include "font_5x7.h"

#include <ti/display/Display.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/I2C.h>

#include <time.h>
#include <ti/sysbios/hal/Seconds.h>

#include <stdint.h>

#include "Board.h"

uint8_t buffer[6];
uint8_t command_buffer[2];
uint8_t txBuffer[1];
uint8_t rxBuffer[2];
uint8_t ssd1306_display_buffer[481];

I2C_Handle              i2c_connection;
I2C_Params              i2c_params;
I2C_Transaction         i2c_transaction;
Display_Handle   ssd_logger;


void ssd1306_init(void) {//Init Sequence
    GPIO_init();
    I2C_init();

    /* Create I2C for usage */
    I2C_Params_init(&i2c_params);
    i2c_params.bitRate = I2C_400kHz;
    i2c_connection = I2C_open(Board_I2C0, &i2c_params);
    if (i2c_connection == NULL) {
        // Display_printf(ssd_logger, 0, 0, "Error Initializing I2C\n");
        while (1);
    }
    else {
        // Display_printf(ssd_logger, 0, 0, "I2C Initialized! \n");
    }

    i2c_transaction.writeBuf   = txBuffer;
    i2c_transaction.writeCount = 1;
    i2c_transaction.readBuf    = rxBuffer;
    i2c_transaction.readCount  = 2;

    /* Try to connect to OLED. */
    // Display_printf(ssd_logger, 0, 0, "Trying to Connect to SSD1306 Display through i2c!\n");
    i2c_transaction.slaveAddress = SSD1306_I2C_ADDR;
    if (!I2C_transfer(i2c_connection, &i2c_transaction)) {
        /* Could not resolve a sensor, error */
        // Display_printf(ssd_logger, 0, 0, "Error. No SSD1306 Display sensor found!, trying again in 5 seconds...");
        // sleep(5);
    } else {
        // Display_printf(ssd_logger, 0, 0, "Starting init sequence for SSD1306.");
        // Display_printf(ssd_logger, 0, 0, "Begin ssd1306 init!");

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

        //Set Display On
        ssd1306_command(SET_DISP_ON);
        // Display_printf(ssd_logger, 0, 0, "Init complete!");

        ssd1306_clear_buffer(ssd1306_display_buffer, sizeof(ssd1306_display_buffer));
        ssd1306_send_buffer(ssd1306_display_buffer, sizeof(ssd1306_display_buffer));
    }

} // end ssd1306_init

void ssd1306_command(uint8_t command) {

    command_buffer[0] = 0x80;
    command_buffer[1] = command;

    ssd1306_send_buffer(command_buffer, sizeof(command_buffer));
} // end ssd1306_command

void ssd1306_send_buffer(uint8_t *buffer, int size) {
        i2c_transaction.writeBuf = buffer;
        i2c_transaction.writeCount = size;
        i2c_transaction.readBuf = NULL;
        i2c_transaction.readCount = 0;
        i2c_transaction.slaveAddress = SSD1306_I2C_ADDR;
        if (!I2C_transfer(i2c_connection, &i2c_transaction)) {
           /* Could not send command to SSD1306, error */
        //    Display_printf(ssd_logger, 0, 0, "Error sending SSD1306 command.\n");
           while(1);
       }
}

void ssd1306_clear_buffer(uint8_t *buffer, int size) {
    ssd1306_set_position(0, 0);
    memset(buffer, 0, size); //Reset buffer

    buffer[0]=0x40;
    ssd1306_set_position(0,0);

    // Display_printf(ssd_logger, 0, 0, "Display Cleared.\n");
}

void ssd1306_draw_pixel(uint8_t x, uint8_t y, bool erase){
    ssd1306_display_buffer[0] = 0x40;

    if(erase){
        ssd1306_display_buffer[1 + x + (y / 8) * 96] &= ~(1 << (y & 7));
    } else {
        ssd1306_display_buffer[1 + x + (y / 8) * 96] |= (1 << (y & 7));
    }
}

void ssd1306_set_position(uint8_t column, uint8_t page) {
    if (column > DISPLAY_WIDTH) {
        column = 0;                                                     // constrain column to upper limit
    }

    if (page > 4) {
        page = 0;                                                       // constrain page to upper limit
    }

    ssd1306_command(SET_COL_ADDR);
    ssd1306_command(column);                                            // Column start address (0 = reset)
    //ssd1306_command(column + 32); //for normal display using 128pixel(0x80) width.
    ssd1306_command(DISPLAY_WIDTH - 1);                                // Column end address (127 = reset)

    ssd1306_command(SET_PAGE_ADDR);
    ssd1306_command(page);                                              // Page start address (0 = reset)
    ssd1306_command(4);                                                 // Page end address
}

void ssd1306_display_text(char *text, uint8_t x, uint8_t y, bool erase) {
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
}

void ssd1306_display_number(uint8_t number, uint8_t x, uint8_t y, bool erase) {
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
}

void ssd1306_display_small_number(uint8_t number, uint8_t x, uint8_t y, bool erase) {
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
}

void ssd1306_display_semicolon(uint8_t x, uint8_t y, bool erase) {
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
}

void ssd1306_display_pm(uint8_t x, uint8_t y, bool erase) {
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
}

void ssd1306_display_notification(uint8_t icon, uint8_t x, uint8_t y, bool erase) {
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
}

void ssd1306_display_full_notification(uint8_t type, char *text) {
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
    ssd1306_display_text(text, space, 21, false);
}

