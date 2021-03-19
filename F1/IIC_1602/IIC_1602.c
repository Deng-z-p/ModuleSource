#include "IIC_1602.h"
#include "i2c.h"

/**
 * *****************************************************
 * @addtogroup LCD_1602 Control operation function
 */ 
void LCDI2C_init(uint8_t lcd_Addr,uint8_t lcd_rows);
void LCDI2C_expanderWrite(uint8_t _data);
void LCDI2C_write4bits(uint8_t value) ;
void LCDI2C_write4bits(uint8_t value);
void LCDI2C_pulseEnable(uint8_t _data);
void LCDI2C_command(uint8_t value);
void LCDI2C_send(uint8_t value, uint8_t mode) ;
void LCDI2C_display(void);
void LCDI2C_home(void);
void LCDI2C_begin( uint8_t lines) ;
void LCDI2C_backlight(void); 
void LCDI2C_clear(void);
void LCDI2C_setCursor(uint8_t col, uint8_t row);
void LCDI2C_Show_String(uint8_t col, uint8_t row,char* str);
void LCDI2C_Show_Char(uint8_t col, uint8_t row,char str);
uint32_t LCDI2C_pow(uint8_t m,uint8_t n);
void LCDI2C_Show_Num(uint8_t col, uint8_t row,uint8_t len,int num);
void LCDI2C_Show_FloatNum(uint8_t col, uint8_t row,uint8_t len1,uint8_t len2,float num);
/******************************************************/

LiquidCrystal_I2C_Def lcdi2c;

/**
 * @brief IIC_LCD1602 initialization
 * @param lcd_Addr LCD1602 slave address,The device 7 bits address value in datasheet must be shifted to the left before calling the interface
 * @param Lcd_rows Number of lines supported by LCD
 */ 
void LCDI2C_init(uint8_t lcd_Addr,uint8_t lcd_rows)
{
  lcdi2c.Addr = lcd_Addr; 
  lcdi2c.rows = lcd_rows;
  lcdi2c.backlightval = LCD_BACKLIGHT;
  lcdi2c.displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
  LCDI2C_begin(lcd_rows);
  LCDI2C_backlight();
  LCDI2C_clear();
}

void LCDI2C_expanderWrite(uint8_t _data)
{
  uint8_t buf=0;
  buf = _data|lcdi2c.backlightval;
  HAL_I2C_Master_Transmit(&hi2c1,lcdi2c.Addr,&buf,1,0xffff);
}

void LCDI2C_write4bits(uint8_t value) 
{
	LCDI2C_expanderWrite(value);
	LCDI2C_pulseEnable(value);
}

void LCDI2C_pulseEnable(uint8_t _data)
{
	LCDI2C_expanderWrite(_data | En);	// En high
	delay_us(1);		/* enable pulse must be >450ns*/
	LCDI2C_expanderWrite(_data & ~En);	// En low
	delay_us(50);		/* commands need > 37us to settle*/
}


void LCDI2C_command(uint8_t value){
	LCDI2C_send(value, 0);
}
void LCDI2C_write(uint8_t value){
	LCDI2C_send(value, Rs);
}


/**
 * @brief write either command or data
 * @param value The value to be written
 * @param mode Write data or command
 */ 
void LCDI2C_send(uint8_t value, uint8_t mode) 
{
	uint8_t highnib=value&0xf0;
	uint8_t lownib=(value<<4)&0xf0;
  LCDI2C_write4bits((highnib)|mode);
	LCDI2C_write4bits((lownib)|mode);
}

/**
 * @brief LCD_1602 Open display
 */ 
void LCDI2C_display(void) 
{
	lcdi2c.displaycontrol |= LCD_DISPLAYON;
	LCDI2C_command(LCD_DISPLAYCONTROL | lcdi2c.displaycontrol);
}

/**
 * @brief Clear display,set cursor position to zero
 */ 
void LCDI2C_clear(void)
{
	LCDI2C_command(LCD_CLEARDISPLAY);
	delay_us(3000);  /* this command takes a long time!*/
}

/**
 * @brief set cursor position to zero
 */ 
void LCDI2C_home(void)
{
	LCDI2C_command(LCD_RETURNHOME);   
	delay_us(3000);  /* this command takes a long time!*/
}

/**
 * @brief Start to configure the LCD
 * @param lines The number of lines to be displayed on the LCD
 */ 
void LCDI2C_begin( uint8_t lines) 
{
	if (lines > 1) 
	{
		lcdi2c.displayfunction |= LCD_2LINE;
	}
	lcdi2c.numlines = lines;
	LCDI2C_expanderWrite(lcdi2c.backlightval);	/*reset expanderand turn backlight off (Bit 8 =1)*/
	delay_us(1000);

  /* ***************************************************
	 * put the LCD into 4 bit mode
	 * this is according to the hitachi HD44780 datasheet
	 * figure 24, pg 46
	 * we start in 8bit mode, try to set 4 bit mode¡¢
	 * ***************************************************
	 */
	LCDI2C_write4bits(0x03 << 4);
	delay_us(4500); // wait min 4.1ms

  // second try
  LCDI2C_write4bits(0x03 << 4);
  delay_us(4500); // wait min 4.1ms

  // third go!
  LCDI2C_write4bits(0x03 << 4);
  delay_us(150);

  // finally, set to 4-bit interface
  LCDI2C_write4bits(0x02 << 4);

	// set # lines, font size, etc.
	LCDI2C_command(LCD_FUNCTIONSET | lcdi2c.displayfunction);

	// turn the display on with no cursor or blinking default
	lcdi2c.displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
	LCDI2C_display();

	// clear it off
	LCDI2C_clear();

	// Initialize to default text direction (for roman languages)
	lcdi2c.displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;

	// set the entry mode
	LCDI2C_command(LCD_ENTRYMODESET | lcdi2c.displaymode);

	LCDI2C_home();
}

/**
 * @brief LCD_1602 Open BACKLIGHT
 */ 
void LCDI2C_backlight(void) 
{
	lcdi2c.backlightval=LCD_BACKLIGHT;
	LCDI2C_expanderWrite(0);
}

/**
 * @brief Set location information
 * @param col Horizontal axis
 * @param row Vertical axis
 */ 
void LCDI2C_setCursor(uint8_t col, uint8_t row)
{
	int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
	if ( row > lcdi2c.numlines ) {
		row = lcdi2c.numlines-1;    /* we count rows starting w/0*/
	}
	LCDI2C_command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

/**
 * @brief Display the character at the specified position
 * @param col Horizontal axis
 * @param row Vertical axis
 * @param str Character to write
 */ 
void LCDI2C_Show_Char(uint8_t col, uint8_t row,char str)
{
	LCDI2C_setCursor(col,row);
	LCDI2C_write(str);
}

/**
 * @brief Display the string at the specified position
 * @param col Horizontal axis
 * @param row Vertical axis
 * @param str String to write
 */ 
void LCDI2C_Show_String(uint8_t col, uint8_t row,char* str)
{
	uint8_t i=0;
	LCDI2C_setCursor(col,row);
	while(str[i])
  {
    LCDI2C_write(str[i]);
    i++;
  }
}

/**
 * @brief  Implement m^n function
 */ 
uint32_t LCDI2C_pow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)result*=m;    
	return result;
}	

/**
 * @brief Display number function
 * @param col Horizontal axis
 * @param row Vertical axis
 * @param len Displayed number length
 * @param num Displayed number
 */ 
void LCDI2C_Show_Num(uint8_t col, uint8_t row,uint8_t len,int num)
{
	uint8_t t,temp;
	uint8_t enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCDI2C_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCDI2C_Show_Char(col+t,row,' ');
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCDI2C_Show_Char(col+t,row,temp+'0'); 
	}
}

/**
 * @brief Display decimal function
 * @param col: Horizontal axis
 * @param row: Vertical axis
 * @param len1: Integer length  
 * @param len2: Decimal length
 * @param num: number to display
 */ 
void LCDI2C_Show_FloatNum(uint8_t col, uint8_t row,uint8_t len1,uint8_t len2,float num)
{
	int i;
	LCDI2C_Show_Num(col,row,len1,num);
	num=num-(int)num;
	LCDI2C_Show_Char(col+len1,row,'.');
	for (i=0;i<len2;i++) num=num*10;
	LCDI2C_Show_Num(col+len1+1,row,len2,num);
}

