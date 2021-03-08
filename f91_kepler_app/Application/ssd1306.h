#ifndef SSD1306_H_
#define SSD1306_H_

#include <stdint.h>
#include <string.h>
#include <ti/drivers/I2C.h>
#include <ti/display/Display.h>

extern uint8_t ssd1306_display_buffer[481];
extern bool displayInitialized;
/* ====================================================================
 * Horizontal Centering Number Array
 * ==================================================================== */
#define HCENTERUL_OFF   0
#define HCENTERUL_ON    1

/* ====================================================================
 * SSD1306 OLED Settings and Command Definitions
 * ==================================================================== */

// Height and Width

#define DISPLAY_HEIGHT      0x27 //0x27 //39 pixels //0x28 //40 pixels
#define DISPLAY_WIDTH       0x60 //0x60 //96 pixels //0x80 //128 pixels

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
#define SET_SEG_REMAP       0xa0
#define SET_MUX_RATIO       0xa8
#define SET_COM_OUT_DIR     0xc0
#define SET_DISP_OFFSET     0xd3
#define SET_COM_PIN_CFG     0xda
#define SET_DISP_CLK_DIV    0xd5
#define SET_PRECHARGE       0xd9
#define SET_VCOM_DESEL      0xdb
#define SET_CHARGE_PUMP     0x8d

// currently no scroll functionality, left for possible future use
#define SSD1306_ACTIVATE_SCROLL                         0x2F
#define SSD1306_DEACTIVATE_SCROLL                       0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA                0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL                 0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL                  0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL    0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL     0x2A

/* ====================================================================
 * DEFINITIONS
 * ==================================================================== */
#define INCOMING_CALL        0x01
#define INCOMING_TEXT        0x02

#define EMAIL       0x00
#define TEXT        0x01
#define VOICEMAIL   0x02
#define MISSEDCALL  0x03
#define BLUETOOTH   0x04

/* ====================================================================
 * SSD1306 OLED Prototype Definitions
 * ==================================================================== */
void ssd1306_init(void);
void ssd1306_command(uint8_t);
void ssd1306_send_buffer(uint8_t *buffer, int size);
void ssd1306_clear_buffer(uint8_t *buffer, int size);
void ssd1306_draw_pixel(uint8_t x, uint8_t y, bool erase);
void ssd1306_set_position(uint8_t, uint8_t);
void ssd1306_display_text(char *text, uint8_t x, uint8_t y, bool erase);
void ssd1306_display_number(uint8_t number, uint8_t x, uint8_t y, bool erase);
void ssd1306_display_semicolon( uint8_t x, uint8_t y, bool erase);
void ssd1306_display_pm( uint8_t x, uint8_t y, bool erase);
void ssd1306_display_small_number(uint8_t number, uint8_t x, uint8_t y, bool erase);
void ssd1306_display_notification(uint8_t icon, uint8_t x, uint8_t y, bool erase);
void ssd1306_display_full_notification(uint8_t type, char *text);
bool ssd1306_isReady(void);

#endif /* SSD1306_H_ */
