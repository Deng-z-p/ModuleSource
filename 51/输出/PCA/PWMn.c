#include	"PWMn.h"
//========================================================================
// 文件: PWMn.c
// 功能: 使用STC内带的PCA做9~16位的PWM。在PWMn.h中选择是STC12C5201AD系列还是STC12C5A60S2系列。
// 版本: VER1.0
// 日期: 2009-12-30
// 备注: 
//========================================================================

/*
                 原理说明：
本示例程序介绍在一些应用中所需要的高于8位分辨率的9~16位PWM，而8位的PWM可以直接使用STC的硬件PWM，请参考有关的的(Datasheet)。
本应用所需要资源：PCA可编程计数器阵列，捕获寄存器，匹配中断向量。
程序用到两个16位变量:
PWM_high  保存PWM输出高电平的PCA时钟数。
PWM_low   保存PWM输出低电平的PCA时钟数。
PWM的周期 = PWM_HIGH + PWM_LOW。
PCA时钟源有8种选择。
PCA模块被配置为16位高速输出方式，当PCA计数值与捕获寄存器数值匹配时，将CCP0输出取反，同时发生比较匹配中断。
比较匹配中断里判断高速输出的电平，如果是高电平，则向捕获寄存器装入高电平的PCA时钟数。如果是低电平，则装入低电平的PCA时钟数。
由于中断处理需要一点时间，所以输出的占空比不能到0%或100%，所以对PWM_high有最小和最大值，中断处理绝对时间大约为100个SYSCLK。

本示例程序的测试是基于如下假设：
PCA时基信号为系统时钟Fosc，PCA中断优先级为最高。
提示：其它中断服务开销很长时间时，有可能会影响本程序的正常运行。

本示例程序用户可以在"用户配置宏"中选择以下参数：
PCA_IDLE_DISABLE	在IDLE模式是否禁止PCA工作，选择1: MCU在IDLE模式时禁止PCA工作，	选择0:  MCU在IDLE模式时允许PCA工作。
PCA_SOURCE_SELECT	选择PCA的基准时钟源，本示例使用系统时钟Fosc做PCA时钟源。
PWM_DUTY			定义PWM的周期，数值为PCA所选择的时钟脉冲个数，用户只需要装载PWM_high，PWM_low是根据这个周期计算出来的。
PWM_HIGH_MAX		限制PWM输出的最大占空比，原因如前所述。如果装载PWM_high大于此数值，将返回错误。
PWM_HIGH_MIN		限制PWM输出的最小占空比，原因如前所述。如果装载PWM_high小于此数值，将返回错误。
*/
//========================================================================
// 函数: void PWMn_SetHighReg(unsigned int high)
// 描述: 写入占空比数据。
// 参数: high: 	占空比数据，即PWM输出高电平的PCA时钟脉冲个数。
// 返回: 无
// 版本: VER1.0
// 日期: 2009-12-30
// 备注: 
//========================================================================

 PWM_Parameter PWM_Para;//本地变量声明

/*初始化PWM参数 */
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
	if(high > (SetHigh->PWM_HIGH_MAX))	high = SetHigh->PWM_HIGH_MAX;	//如果写入大于最大占空比数据，强制为最大占空比。
	if(high < (SetHigh->PWM_HIGH_MIN))	high = SetHigh->PWM_HIGH_MIN;	//如果写入小于最小占空比数据，则返回错误代码2。
	CR = 0;						//停止PCA。
	SetHigh->PWM_high = high;						//数据在正确范围，则装入占空比寄存器。
	SetHigh->PWM_low = SetHigh->PWM_DUTY - high;	//计算并保存PWM输出低电平的PCA时钟脉冲个数。
	CR = 1;						//启动PCA。
}

// 描述: 初始化程序。
// 参数: high: 	初始化占空比数据，即PWM输出高电平的PCA时钟脉冲个数。
void PWMn_init()
{
	#ifdef	STC12C5201AD
		P3M1 &= ~0x80,	P3M0 |=  0x80;		//CCAP0使用PUSH-PULL输出模式，STC12C5201AD系列, P3.7。
	#else
		P1M1 &= ~0x08,	P1M0 |=  0x08;		//CCAP0使用PUSH-PULL输出模式，STC12C5A60S2系列, P1.3。
	#endif
	CCON = 0;					//清除CF、CR、CCF0、CCF1
	IPH |= 0x80;				//PCA中断使用最高优先级
	PPCA = 1;

	CMOD = (PCA_IDLE_DISABLE << 7) | (PCA_SOURCE_SELECT << 1);	//初始化PCA模式寄存器，这两项在PWMn.h中选择。
	CCAPM0 = CAP_16_HO+1;		//16位高速输出模式，允许比较匹配中断(ECCF0=1)。
	CL = 0;						//清空PCA基本计数器。
	CH = 0;
	CR = 1;						//启动PCA。
	EA = 1;						//允许总中断
}

// 描述: PCA中断服务程序。
void PCA_interrupt () interrupt 7
{
	if(CCF0 == 1)		//PCA模块0中断
	{
		CCF0 = 0;		//清PCA模块0中断标志

		if(CCP0 == 1)	PWM_Para.CCAP0_tmp+=PWM_Para.PWM_high;	//输出为高电平，则给影射寄存器装载高电平时间长度
		else            PWM_Para.CCAP0_tmp+=PWM_Para.PWM_low;	//输出为高电平，则给影射寄存器装载高电平时间长度
				
		CCAP0L = (unsigned char)PWM_Para.CCAP0_tmp;			//将影射寄存器写入捕获寄存器，先写CCAP0L
		CCAP0H = (unsigned char)((PWM_Para.CCAP0_tmp) >> 8);	//后写CCAP0H
	
	}
}
