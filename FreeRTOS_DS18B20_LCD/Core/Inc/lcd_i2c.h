#ifndef __LCD_I2C_H__
#define __LCD_I2C_H__

#include "stm32f4xx_hal.h"

// LCD boyutu (örneğin 16x2 için)
#define LCD_COLS 16
#define LCD_ROWS 2

// LCD komutları
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_FUNCTIONSET 0x20
#define LCD_SETDDRAMADDR 0x80

// LCD mod
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTDECREMENT 0x00
#define LCD_DISPLAYON 0x04
#define LCD_CURSOROFF 0x00
#define LCD_BLINKOFF 0x00
#define LCD_2LINE 0x08
#define LCD_5x8DOTS 0x00
#define LCD_4BITMODE 0x00

#define LCD_I2C_ADDR (0x27 << 1)

void lcd_init(I2C_HandleTypeDef *hi2c);
void lcd_send_string(char *str);
void lcd_send_cmd(uint8_t cmd);
void lcd_send_data(uint8_t data);
void lcd_clear(void);
void lcd_set_cursor(uint8_t row, uint8_t col);

#endif
