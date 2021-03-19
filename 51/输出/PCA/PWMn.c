#include	"PWMn.h"
//========================================================================
// �ļ�: PWMn.c
// ����: ʹ��STC�ڴ���PCA��9~16λ��PWM����PWMn.h��ѡ����STC12C5201ADϵ�л���STC12C5A60S2ϵ�С�
// �汾: VER1.0
// ����: 2009-12-30
// ��ע: 
//========================================================================

/*
                 ԭ��˵����
��ʾ�����������һЩӦ��������Ҫ�ĸ���8λ�ֱ��ʵ�9~16λPWM����8λ��PWM����ֱ��ʹ��STC��Ӳ��PWM����ο��йصĵ�(Datasheet)��
��Ӧ������Ҫ��Դ��PCA�ɱ�̼��������У�����Ĵ�����ƥ���ж�������
�����õ�����16λ����:
PWM_high  ����PWM����ߵ�ƽ��PCAʱ������
PWM_low   ����PWM����͵�ƽ��PCAʱ������
PWM������ = PWM_HIGH + PWM_LOW��
PCAʱ��Դ��8��ѡ��
PCAģ�鱻����Ϊ16λ���������ʽ����PCA����ֵ�벶��Ĵ�����ֵƥ��ʱ����CCP0���ȡ����ͬʱ�����Ƚ�ƥ���жϡ�
�Ƚ�ƥ���ж����жϸ�������ĵ�ƽ������Ǹߵ�ƽ�����򲶻�Ĵ���װ��ߵ�ƽ��PCAʱ����������ǵ͵�ƽ����װ��͵�ƽ��PCAʱ������
�����жϴ�����Ҫһ��ʱ�䣬���������ռ�ձȲ��ܵ�0%��100%�����Զ�PWM_high����С�����ֵ���жϴ������ʱ���ԼΪ100��SYSCLK��

��ʾ������Ĳ����ǻ������¼��裺
PCAʱ���ź�Ϊϵͳʱ��Fosc��PCA�ж����ȼ�Ϊ��ߡ�
��ʾ�������жϷ������ܳ�ʱ��ʱ���п��ܻ�Ӱ�챾������������С�

��ʾ�������û�������"�û����ú�"��ѡ�����²�����
PCA_IDLE_DISABLE	��IDLEģʽ�Ƿ��ֹPCA������ѡ��1: MCU��IDLEģʽʱ��ֹPCA������	ѡ��0:  MCU��IDLEģʽʱ����PCA������
PCA_SOURCE_SELECT	ѡ��PCA�Ļ�׼ʱ��Դ����ʾ��ʹ��ϵͳʱ��Fosc��PCAʱ��Դ��
PWM_DUTY			����PWM�����ڣ���ֵΪPCA��ѡ���ʱ������������û�ֻ��Ҫװ��PWM_high��PWM_low�Ǹ���������ڼ�������ġ�
PWM_HIGH_MAX		����PWM��������ռ�ձȣ�ԭ����ǰ���������װ��PWM_high���ڴ���ֵ�������ش���
PWM_HIGH_MIN		����PWM�������Сռ�ձȣ�ԭ����ǰ���������װ��PWM_highС�ڴ���ֵ�������ش���
*/
//========================================================================
// ����: void PWMn_SetHighReg(unsigned int high)
// ����: д��ռ�ձ����ݡ�
// ����: high: 	ռ�ձ����ݣ���PWM����ߵ�ƽ��PCAʱ�����������
// ����: ��
// �汾: VER1.0
// ����: 2009-12-30
// ��ע: 
//========================================================================

 PWM_Parameter PWM_Para;//���ر�������

/*��ʼ��PWM���� */
void PWM_Parameter_init(PWM_Parameter*p)
{
	p->PWM_high=0;
	p->PWM_low=0;
	p->CCAP0_tmp=0;
	p->PWM_DUTY=MAIN_Fosc/1000;
	p->PWM_HIGH_MAX=(p->PWM_DUTY)-32;
	p->PWM_HIGH_MIN=32;
}


void PWMn_SetHighReg(PWM_Parameter*SetHigh,unsigned int high)
{
	if(high > (SetHigh->PWM_HIGH_MAX))	high = SetHigh->PWM_HIGH_MAX;	//���д��������ռ�ձ����ݣ�ǿ��Ϊ���ռ�ձȡ�
	if(high < (SetHigh->PWM_HIGH_MIN))	high = SetHigh->PWM_HIGH_MIN;	//���д��С����Сռ�ձ����ݣ��򷵻ش������2��
	CR = 0;						//ֹͣPCA��
	SetHigh->PWM_high = high;						//��������ȷ��Χ����װ��ռ�ձȼĴ�����
	SetHigh->PWM_low = SetHigh->PWM_DUTY - high;	//���㲢����PWM����͵�ƽ��PCAʱ�����������
	CR = 1;						//����PCA��
}

// ����: ��ʼ������
// ����: high: 	��ʼ��ռ�ձ����ݣ���PWM����ߵ�ƽ��PCAʱ�����������
void PWMn_init()
{
	#ifdef	STC12C5201AD
		P3M1 &= ~0x80,	P3M0 |=  0x80;		//CCAP0ʹ��PUSH-PULL���ģʽ��STC12C5201ADϵ��, P3.7��
	#else
		P1M1 &= ~0x08,	P1M0 |=  0x08;		//CCAP0ʹ��PUSH-PULL���ģʽ��STC12C5A60S2ϵ��, P1.3��
	#endif
	CCON = 0;					//���CF��CR��CCF0��CCF1
	IPH |= 0x80;				//PCA�ж�ʹ��������ȼ�
	PPCA = 1;

	CMOD = (PCA_IDLE_DISABLE << 7) | (PCA_SOURCE_SELECT << 1);	//��ʼ��PCAģʽ�Ĵ�������������PWMn.h��ѡ��
	CCAPM0 = CAP_16_HO+1;		//16λ�������ģʽ������Ƚ�ƥ���ж�(ECCF0=1)��
	CL = 0;						//���PCA������������
	CH = 0;
	CR = 1;						//����PCA��
	EA = 1;						//�������ж�
}

// ����: PCA�жϷ������
void PCA_interrupt () interrupt 7
{
	if(CCF0 == 1)		//PCAģ��0�ж�
	{
		CCF0 = 0;		//��PCAģ��0�жϱ�־

		if(CCP0 == 1)	PWM_Para.CCAP0_tmp+=PWM_Para.PWM_high;	//���Ϊ�ߵ�ƽ�����Ӱ��Ĵ���װ�ظߵ�ƽʱ�䳤��
		else            PWM_Para.CCAP0_tmp+=PWM_Para.PWM_low;	//���Ϊ�ߵ�ƽ�����Ӱ��Ĵ���װ�ظߵ�ƽʱ�䳤��
				
		CCAP0L = (unsigned char)PWM_Para.CCAP0_tmp;			//��Ӱ��Ĵ���д�벶��Ĵ�������дCCAP0L
		CCAP0H = (unsigned char)((PWM_Para.CCAP0_tmp) >> 8);	//��дCCAP0H
	
	}
}
