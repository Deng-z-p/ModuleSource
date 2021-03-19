#ifndef __INEEPROM_H
#define __INEEPROM_H

#include <reg52.h>
#include <intrins.h>

#define uchar unsigned char//宏定义无符号字符型
#define uint unsigned int  //宏定义无符号整型
#define NOP()                    _nop_()
#define ADDRESS     0x2000

#include <intrins.h>
#define uchar unsigned char//宏定义无符号字符型
#define uint unsigned int  //宏定义无符号整型
#define NOP()                    _nop_()
#define ADDRESS     0x2000

sfr ISP_DATA  = 0xe2;  //定义eeprom的寄存器
sfr ISP_ADDRH = 0xe3;
sfr ISP_ADDRL = 0xe4;
sfr ISP_CMD   = 0xe5;
sfr ISP_TRIG  = 0xe6;
sfr ISP_CONTR = 0xe7;
//#define ENABLE_IAP 0X80  //编程周期由晶振决定（如果<30MHZ选用此项）
//#define ENABLE_IAP 0X81  //编程周期由晶振决定（如果<24MHZ选用此项）
//#define ENABLE_IAP 0X82  //编程周期由晶振决定（如果<20MHZ选用此项）
  #define ENABLE_IAP 0X83  //编程周期由晶振决定（如果<12MHZ选用此项）
//#define ENABLE_IAP 0X84  //编程周期由晶振决定（如果<6MHZ选用此项）
//#define ENABLE_IAP 0X85  //编程周期由晶振决定（如果<3MHZ选用此项）
//#define ENABLE_IAP 0X86  //编程周期由晶振决定（如果<2MHZ选用此项）
//#define ENABLE_IAP 0X87  //编程周期由晶振决定（如果<1MHZ选用此项）
uchar EEPROMReadByte(uint addr);
void EEPROMWriteByte(uint addr,uchar byte);
void EEPROMSectorErase(uint addr); 
#endif