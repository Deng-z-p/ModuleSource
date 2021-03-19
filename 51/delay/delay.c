#include "delay.h"
//60s2
void  Delay_ms_60s2(unsigned int ms)
{
     unsigned int i;
	 do{
	      i = MAIN_Fosc / 14000;
		  while(--i)	;   //14T per loop
     }while(--ms);
}

void Delay1ms()		   //@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
}


//89C52
void  Delay_ms_c52(unsigned int c)   //Îó²î 0us
{
  unsigned char a,b;
	for (; c>0; c--)
	{
		 for (b=199;b>0;b--)
		 {
		  	for(a=1;a>0;a--);
		 }      
	}   	
}

void Delay_us(unsigned int us)   
{
 unsigned int i;
 for(i=0;i<us;i++)
 {
  _nop_();
 }
}


