#ifndef _1602_H
#define _1602_H
#include "reg52.h"
#include "intrins.h"

sbit SCL = P3^7;
sbit SDA = P3^6;

void delay_nus(unsigned int n); //N us延时函数
void delay_nms(unsigned int n); //N ms延时函数
void display_string(unsigned char x,unsigned char y,unsigned char *s);//显示数据
void LCD_write_command(unsigned char command);//写命令
void LCD_write_data(unsigned char value) ;    //写数据
void LCD_init(void) ;//lcd初始化

#endif