#include "lcd_i2c.h"
#include "string.h"
#include "stm32f4xx_hal.h"

static I2C_HandleTypeDef *_lcd_i2c;

static void lcd_send(uint8_t data, uint8_t mode);
static void lcd_write4bits(uint8_t data);
static void lcd_pulse_enable(uint8_t data);
static void lcd_write(uint8_t data);

void lcd_init(I2C_HandleTypeDef *hi2c) {
    _lcd_i2c = hi2c;
    HAL_Delay(50);

    lcd_write4bits(0x30);
    HAL_Delay(5);
    lcd_write4bits(0x30);
    HAL_Delay(1);
    lcd_write4bits(0x30);
    HAL_Delay(10);
    lcd_write4bits(0x20); // 4-bit mode

    lcd_send_cmd(LCD_FUNCTIONSET | LCD_2LINE | LCD_5x8DOTS | LCD_4BITMODE);
    lcd_send_cmd(LCD_DISPLAYCONTROL | LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF);
    lcd_send_cmd(LCD_CLEARDISPLAY);
    HAL_Delay(2);
    lcd_send_cmd(LCD_ENTRYMODESET | LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT);
}

void lcd_send_cmd(uint8_t cmd) {
    lcd_send(cmd, 0);
}

void lcd_send_data(uint8_t data) {
    lcd_send(data, 1);
}

void lcd_send_string(char *str) {
    while (*str) {
        lcd_send_data(*str++);
    }
}

void lcd_clear(void) {
    lcd_send_cmd(LCD_CLEARDISPLAY);
    HAL_Delay(2);
}

void lcd_set_cursor(uint8_t row, uint8_t col) {
    uint8_t addr = (row == 0) ? 0x00 : 0x40;
    lcd_send_cmd(LCD_SETDDRAMADDR | (addr + col));
}

static void lcd_send(uint8_t data, uint8_t mode) {
    uint8_t high = data & 0xF0;
    uint8_t low = (data << 4) & 0xF0;
    lcd_write4bits(high | (mode ? 0x01 : 0x00));
    lcd_write4bits(low | (mode ? 0x01 : 0x00));
}

static void lcd_write4bits(uint8_t data) {
    lcd_write(data | 0x08);  // Backlight ON
    lcd_pulse_enable(data | 0x08);
}

static void lcd_pulse_enable(uint8_t data) {
    lcd_write(data | 0x04);  // En = 1
    HAL_Delay(1);
    lcd_write(data & ~0x04); // En = 0
    HAL_Delay(1);
}

static void lcd_write(uint8_t data) {
    HAL_I2C_Master_Transmit(_lcd_i2c, LCD_I2C_ADDR, &data, 1, 10);
}
