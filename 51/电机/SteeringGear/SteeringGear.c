#include "SteeringGear.h"

unsigned char count; //0.5ms������ʶ
unsigned char Angle; //�Ƕȱ�ʶ

void Time0_Init()    //��ʱ����ʼ��
{
    AUXR&=0x7f;      //12��Ƶ
    TMOD = 0x01;     //��ʱ��0�����ڷ�ʽ1,16λ��ʱ/������ 
    IE   = 0x82;     //�൱�ڴ�EA��ET0
    TH0  = 0xfe;
    TL0  = 0x33;     //11.0592MZ����0.5ms
    TR0  =1;         //��ʱ����ʼ
}

void Time0_Int() interrupt 1 //�жϳ���
{
    TH0 = 0xfe;             //���¸�ֵ
	  TL0 = 0x33;
    if(count< Angle)        //�ж�0.5ms�����Ƿ�С�ڽǶȱ�ʶ
      pwm=1;                //ȷʵС�ڣ�PWM����ߵ�ƽ
    else
      pwm=0;                //����������͵�ƽ
    count++;                //0.5ms������1
    count=count%40;         //����ʼ�ձ���Ϊ40 ����������Ϊ20ms
}
