#include "simulationusart.h"


/********************** ģ�⴮����غ���************************/

void	BitTime(void)	                              //λʱ�亯��
{
	unsigned int i;
	i = ((MAIN_Fosc / 100) * 104) / 140000L - 1;		//������ʱ��������λʱ��
	while(--i);
}

//ģ�⴮�ڷ���
void	Tx1Send(unsigned char dat)		              //9600��N��8��1		����һ���ֽ�
{
	unsigned char	i;
	P_TXD1 = 0;
	BitTime();
  for(i=0; i<8; i++)
	{
		if(dat & 1)		P_TXD1 = 1;                                                                
		else			P_TXD1 = 0;
		dat >>= 1;
		BitTime();
	}
	P_TXD1 = 1;
	BitTime();
	BitTime();
}

void PrintString(unsigned char code *puts)		    //����һ���ַ���
{
    for (; *puts != 0;	puts++)  Tx1Send(*puts); 	//����ֹͣ��0����
}
