#ifndef		PWMn_H
#define		PWMn_H

#include	"STC12C5A60S2.h"

//#define		STC12C5201AD					//���ע������PCA���Ĭ��ʹ��STC12C5A60S2ϵ��

#define		MAIN_Fosc	11059200L	//����ʱ��
                                            //IDLE����ģʽ
#define		PCA_IDLE_DISABLE	0			//1: MCU��IDLEģʽʱ��ֹPCA������	0:  MCU��IDLEģʽʱ����PCA������
#define		PCA_SOURCE_SELECT	4			//ѡ��PCA�Ļ�׼ʱ��Դ��
											//0��ϵͳʱ��Fosc/12��
											//1��ϵͳʱ��Fosc/2��
											//2����ʱ��0�������
											//3��ECI/P3.4�ŵ��ⲿʱ�����루���=Fosc/2����
											//4��ϵͳʱ��Fosc��
											//5��ϵͳʱ��Fosc/4��
											//6��ϵͳʱ��Fosc/6��
											//7��ϵͳʱ��Fosc/8��

//SYSclk/PWM_DUTY=frequency;

typedef struct{
	unsigned int PWM_high;	//����PWMռ�ձȼĴ�������PWM����ߵ�ƽ��PCAʱ�����������ռ�ձ�д���������
    unsigned int PWM_low;	//����PWM����͵�ƽ��PCAʱ�����������
    unsigned int CCAP0_tmp;	//����CCAP0��װ��Ӱ��Ĵ�����
	unsigned int PWM_DUTY;	//����PWM�����ڣ���ֵΪPCA��ѡ���ʱ�����������
	unsigned int PWM_HIGH_MAX;//����PWM��������ռ�ձȡ�
	unsigned int PWM_HIGH_MIN;//����PWM�������Сռ�ձȡ�
}PWM_Parameter;


/*PCAģ�鹤��ģʽ�趨 */
#define PWM_8_NOI 0x42//8λPWM�����ж�
#define PWM_8_HIR 0x63//8λPWM���ɵͱ�߿ɲ����ж�
#define PWM_8_HIF 0x53//8λPWM���ɸ߱�Ϳɲ����ж�
#define PWM_8_HIE 0x73//8λPWM, ���ش���
#define CAP_16_RI 0x60//16λ����ģʽ����CCPN/PCAN�������ش�����ECOMn=1;ECCFn=0;
#define CAP_16_FI 0x50//16λ����ģʽ����CCPN/PCAN�������ش���  ECOMn=1;ECCFn=0;
#define CAP_16_EI 0x70//16λ����ģʽ�����ش���  ECOMn=1;ECCFn=0;
#define CAP_16_TI 0x48//16λ�����ʱ����ECCFn=0;
#define CAP_16_HO 0x4c//16λ���������ECCFn=0;

/**********************************************************************************************************/

#ifdef	STC12C5201AD
	sbit  CCP0  = P3^7;	//STC12C5201AD/PWM
	sbit  CCP1  = P3^5;	//STC12C5201AD/PWM

#else
	sbit  CCP0  = P1^3;	//STC12C5A60S2
	sbit  CCP1  = P1^4;	//STC12C5A60S2
#endif

void PWM_Parameter_init(PWM_Parameter*p);
void PWMn_init();
void PWMn_SetHighReg(PWM_Parameter*SetHigh,unsigned int high);

#endif
