#include "60s2ad.h"


/********************* ��һ��ADCת�� *******************/
unsigned int	adc10_start(unsigned char channel)	//channel = 0~7
{
	unsigned int	adc;
	unsigned char	i;

	ADC_RES = 0;   //A/Dת�����register
	ADC_RESL = 0;

	ADC_CONTR = (ADC_CONTR & 0xe0) | ADC_START | channel; //����ADת����ѡ��P1.0��ΪA/D����

	i = 250;
	do{
		if(ADC_CONTR & ADC_FLAG)//���ת����ɺ�
		{
			ADC_CONTR &= ~ADC_FLAG;//�����0��־λ
		//	adc = 0;
		//	adc = (ADC_RES << 8) | ADC_RESL;	//ADRJ_enable()
			adc = (unsigned int)ADC_RES;
			adc = (adc << 2) | (ADC_RESL & 3);//��ȡ���register
			return	adc;
		}
	}while(--i);
	return	1024;
}

 // P1ASF = (1 << ADC_CH7);			//12C5A60AD/S2ϵ��ģ������//(AD)ѡ��
  //ADC_CONTR = ADC_360T | ADC_ON;