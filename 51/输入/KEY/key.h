#ifndef __KEY_H
#define __KEY_H
#include<reg52.h>

#define GPIO_KEY P1               //�������

void KeyDown(void);
void key_keydata_dispose();
void Delay1ms(unsigned int c);   //��� 0us

//������ֵ������

extern unsigned char value,key_temp,select,key_clean;
#endif