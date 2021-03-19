#include "capture.h"

unsigned int  CCAP0_tmp,CCAP1_tmp;
float time;

bit		B_Cap0,B_Cap1;


void cature_init()
{
 	CCAPM0 = 0x21;	//CCAP0�½��ز�׽�������ж�		�½��ز�׽: 0x11,  �����ز�׽: 0x21, �����½��ز�׽: 0x31
	CCAPM1 = 0x11;	//CCAP1�½��ز�׽�������ж�		�½��ز�׽: 0x11,  �����ز�׽: 0x21, �����½��ز�׽: 0x31
	CMOD = (PCA_IDLE_DISABLE << 7) | (PCA_SOURCE_SELECT << 1) | PCA_ECF;	//��ʼ��PCAģʽ�Ĵ�����
	CL = 0;					//���PCA������������
	CH = 0;
	CR = 1;					//Start CR
	EA = 1;
}

void PCA_interrupt (void) interrupt 7
{
 static unsigned char i=0,frequency=0;
	if(CCF0 == 1)		 //PCAģ��0�ж�
	{
	  i++;
		CCF0 = 0;		   //��PCAģ��0�жϱ�־
		if(i==1)
		{
	    CCAP0H=0;
			CCAP0L=0;
			frequency=0;
			CCAPM0=0x11; //�½��ز���
		}
	  else if(i>=2)
		{
		 i=0;
	   time =  CCAP0H;	                 //��CCAP0H
		 time =  (CCAP0_tmp << 8) + CCAP0L;//��CCAPOL
		 time =  CCAP0_tmp+frequency*65535;//�õ���ʱ��
		 time =  time/1000;
		 CCAPM0 = 0x21;                    //�����ز���
		 frequency=0;    
		 B_Cap0=1;
		}
	}
	
	if(CF == 1)	         //PCA����ж�
	{
		CF = 0;			       //��PCA����жϱ�־
		frequency++;
		if(frequency>=200) 		 frequency=0;
	}
}