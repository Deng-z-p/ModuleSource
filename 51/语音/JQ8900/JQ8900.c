#include "jq8900.h"

void Delay1us (unsigned int T )
{
  while(T!=0)
	{
	  _nop_();
		T--;
	}
}

void SendData ( unsigned char addr )
{
    unsigned char i;

    EA = 0;/*����ʱ�ص��жϣ���ֹ�ж�Ӱ��ʱ��  */

    sda = 1;/*��ʼ����  */
    Delay1us ( 1000 );
    sda = 0;/*��ʼ������*/
    Delay1us ( 3000 );/*�˴���ʱ����Ҫ����2ms���˲�����ʱΪ310ms  */

    for ( i = 0; i < 8; i++ ) /*�ܹ�8λ����  */
    {
        sda = 1;
        if ( addr & 0x01 ) /*3:1��ʾ����λ1,ÿ��λ�����������ʾ  */
        {
            Delay1us ( 500 );
            sda = 0;
            Delay1us ( 210 );
        }
        else              /*1��3��ʾ����λ0 ,ÿ��λ�����������ʾ  */
        {
            Delay1us ( 210 );
            sda = 0;
            Delay1us ( 500 );
        }
        addr >>= 1;
    }
    sda = 1;
    EA = 1;
}

void voice_dispose(unsigned char dat1,unsigned char dat2)
{
 SendData(0x0a);//��ʼ
 Delay1us(2000);
 SendData(dat1);
 Delay1us(2000);
 SendData(dat2);
 Delay1us(2000);
 SendData(0x0b);//����
}