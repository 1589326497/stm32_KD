#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	
//	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);  //开启映射复用OC2通道映射在PA15引脚上
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//关闭JTDI的复用 把PA15变成普通引脚
	
	//开启GPIO A0 oc1通道使用的这个引脚
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	TIM_InternalClockConfig(TIM2); //选择时钟 TIM2
	
	TIM_TimeBaseInitTypeDef TIM_TimBaseStructure;
	TIM_TimBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;  //防止抖动
	TIM_TimBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimBaseStructure.TIM_Period=100-1;      //ARR
	TIM_TimBaseStructure.TIM_Prescaler=720-1;    //PSC
	TIM_TimBaseStructure.TIM_RepetitionCounter=0; //这里重复计数器是高级定时器的功能这里我们是基础定时器所以给0
	TIM_TimeBaseInit(TIM2,&TIM_TimBaseStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCNPolarity_High;  //有效电平为高电平
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse=0;  //设置CCR寄存器的值
	
	TIM_OC1Init(TIM2,&TIM_OCInitStructure); ///初始化OC1通道
	
	
	TIM_Cmd(TIM2,ENABLE);      //启动定时器
	
	
	
}
void PWM_SetCompare1(uint16_t Compare)  //配置CCR 改变占空比
{
	TIM_SetCompare1(TIM2,Compare);
}
void PWM_SetPrescaler(uint16_t Prescaler)   //配置PSC 改变频率
{
	TIM_PrescalerConfig(TIM2,Prescaler,TIM_PSCReloadMode_Immediate);
}

