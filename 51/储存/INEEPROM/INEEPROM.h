#ifndef __INEEPROM_H
#define __INEEPROM_H

#include <reg52.h>
#include <intrins.h>

#define uchar unsigned char//�궨���޷����ַ���
#define uint unsigned int  //�궨���޷�������
#define NOP()                    _nop_()
#define ADDRESS     0x2000

#include <intrins.h>
#define uchar unsigned char//�궨���޷����ַ���
#define uint unsigned int  //�궨���޷�������
#define NOP()                    _nop_()
#define ADDRESS     0x2000

sfr ISP_DATA  = 0xe2;  //����eeprom�ļĴ���
sfr ISP_ADDRH = 0xe3;
sfr ISP_ADDRL = 0xe4;
sfr ISP_CMD   = 0xe5;
sfr ISP_TRIG  = 0xe6;
sfr ISP_CONTR = 0xe7;
//#define ENABLE_IAP 0X80  //��������ɾ�����������<30MHZѡ�ô��
//#define ENABLE_IAP 0X81  //��������ɾ�����������<24MHZѡ�ô��
//#define ENABLE_IAP 0X82  //��������ɾ�����������<20MHZѡ�ô��
  #define ENABLE_IAP 0X83  //��������ɾ�����������<12MHZѡ�ô��
//#define ENABLE_IAP 0X84  //��������ɾ�����������<6MHZѡ�ô��
//#define ENABLE_IAP 0X85  //��������ɾ�����������<3MHZѡ�ô��
//#define ENABLE_IAP 0X86  //��������ɾ�����������<2MHZѡ�ô��
//#define ENABLE_IAP 0X87  //��������ɾ�����������<1MHZѡ�ô��
uchar EEPROMReadByte(uint addr);
void EEPROMWriteByte(uint addr,uchar byte);
void EEPROMSectorErase(uint addr); 
#endif