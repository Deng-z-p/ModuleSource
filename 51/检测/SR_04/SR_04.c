#include "sr_04.h"

unsigned int Distance; //����

void T0_init()
{
  TMOD=0x01;	 //��T0Ϊ��ʽ1��GATE=1��
	TH0=0;
	TL0=0;          
	ET0=1;       //����T0�ж�
	EA=1;			   //�������ж�	
}

void  StartModule() 		//����ģ��
{
	unsigned char i;
	Trig=1;			          //����һ��ģ��>10us
	for(i=10;i>0;i--)
	_nop_(); 
	Trig=0;
}

void Conut(void)
{
   static unsigned int time;
	 time=TH0*256+TL0;
	 TH0=0;
	 TL0=0;
	
	 Distance=(time*1.7)/100;     //�������CM
}

void start_count()
{
	 StartModule();   //����ģ��
	 while(!Echo);		//��ECHOΪ��ʱ�ȴ�
	 TR0=1;			      //��������
	 while(Echo);			//��ECH0Ϊ�߼������ȴ�
	 TR0=0;				    //�رռ���
	 Conut();			    //����
}