#include "usart.h"

void UsartInit()
{
	SCON=0X50;			//����Ϊ������ʽ1
	TMOD=0X20;			//���ü�����������ʽ2
	PCON=0X80;			//�����ʼӱ�
	TH1=0XF4;				//��������ʼֵ���ã�ע�Ⲩ������4800��
	TL1=0XF4;
	ES=1;						//�򿪽����ж�
	EA=1;						//�����ж�
	TR1=1;					//�򿪼�����
}

void usart() interrupt 4
{
  static unsigned char receivedata;
	receivedata=SBUF;
	RI = 0;           //��������жϱ�־λ
	SBUF=receivedata; //�����յ������ݷ��뵽���ͼĴ���
	while(!TI);			  //�ȴ������������
	TI=0;						  //���������ɱ�־λ
}