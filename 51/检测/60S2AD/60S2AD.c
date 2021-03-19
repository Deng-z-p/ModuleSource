#include "60s2ad.h"


/********************* 做一次ADC转换 *******************/
unsigned int	adc10_start(unsigned char channel)	//channel = 0~7
{
	unsigned int	adc;
	unsigned char	i;

	ADC_RES = 0;   //A/D转换结果register
	ADC_RESL = 0;

	ADC_CONTR = (ADC_CONTR & 0xe0) | ADC_START | channel; //启动AD转换并选择P1.0作为A/D输入

	i = 250;
	do{
		if(ADC_CONTR & ADC_FLAG)//如果转化完成后
		{
			ADC_CONTR &= ~ADC_FLAG;//软件清0标志位
		//	adc = 0;
		//	adc = (ADC_RES << 8) | ADC_RESL;	//ADRJ_enable()
			adc = (unsigned int)ADC_RES;
			adc = (adc << 2) | (ADC_RESL & 3);//读取结果register
			return	adc;
		}
	}while(--i);
	return	1024;
}

 // P1ASF = (1 << ADC_CH7);			//12C5A60AD/S2系列模拟输入//(AD)选择
  //ADC_CONTR = ADC_360T | ADC_ON;