#ifndef __STEPPERMOTOR_H
#define __STEPPERMOTOR_H
//#include "reg52.h"
#include "stc12c5a60s2.h"

#define motordata P1   //����������ƽӿڶ���
//���Ϊ8�ģ�A-AB-B-BC-C-CD-D-DA-A....��

void ONEamotorcw(unsigned int n);//��ʱ��ת��,n:ת����Ȧ��
void ONEwmotorcw(unsigned int n);//˳ʱ��ת��,n:ת����Ȧ��
#endif