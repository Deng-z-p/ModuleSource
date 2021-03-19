#ifndef __IIC_1602_H
#define __IIC_1602_H
#include "main.h"

// commands
#define LCD_CLEARDISPLAY   0x01
#define LCD_RETURNHOME     0x02
#define LCD_ENTRYMODESET   0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT    0x10
#define LCD_FUNCTIONSET    0x20
#define LCD_SETCGRAMADDR   0x40
#define LCD_SETDDRAMADDR   0x80

/**
 * @brief flags for display entry mode
 */ 
#define LCD_ENTRYRIGHT          0x00
#define LCD_ENTRYLEFT           0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

/**
 * @brief flags for display on/off control
 */ 
#define LCD_DISPLAYON   0x04
#define LCD_DISPLAYOFF  0x00
#define LCD_CURSORON    0x02
#define LCD_CURSOROFF   0x00
#define LCD_BLINKON     0x01
#define LCD_BLINKOFF    0x00

/**
 * @brief flags for display/cursor shift
 */ 
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE  0x00
#define LCD_MOVERIGHT   0x04
#define LCD_MOVELEFT    0x00


/**
 * @brief LCD_1602 Function set
 * @note Set data interface width and LCD display mode
 */ 
#define LCD_8BITMODE 0x10 
#define LCD_4BITMODE 0x00
#define LCD_2LINE    0x08
#define LCD_1LINE    0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS  0x00

/**
 * @ brief LCD_1602 backlight display control
 */ 
#define LCD_BACKLIGHT   0x08
#define LCD_NOBACKLIGHT 0x00

#define En 0x04  // Enable bit
#define Rw 0x02  // Read/Write bit
#define Rs 0x01  // Register select bit

typedef struct
{
  uint8_t Addr;
  uint8_t displayfunction;
  uint8_t displaycontrol;
  uint8_t displaymode;
  uint8_t numlines;
  uint8_t cols;
  uint8_t rows;
  uint8_t backlightval;
} LiquidCrystal_I2C_Def;


void LCDI2C_init(uint8_t lcd_Addr,uint8_t lcd_rows);
void LCDI2C_clear(void);
void LCDI2C_Show_FloatNum(uint8_t col, uint8_t row,uint8_t len1,uint8_t len2,float num);
void LCDI2C_Show_Num(uint8_t col, uint8_t row,uint8_t len,int num);
void LCDI2C_Show_String(uint8_t col, uint8_t row,char* str);
#endif

