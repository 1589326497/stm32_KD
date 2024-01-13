#include "stm32f10x.h"                  // Device header


void Encoder_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStrecture;
	GPIO_InitStrecture.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStrecture.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStrecture.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStrecture);
	
	//TIM_InternalClockConfig(TIM3); 编码器接口会托管时钟，所以内部时钟没有用了
	
	TIM_TimeBaseInitTypeDef TIM_TimBaseInitStructure;
	TIM_TimeBaseStructInit(&TIM_TimBaseInitStructure);
	TIM_TimBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimBaseInitStructure.TIM_Period=65536-1;
	TIM_TimBaseInitStructure.TIM_Prescaler=1-1;
	TIM_TimBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM3,&TIM_TimBaseInitStructure);
	
	TIM_ICInitTypeDef TIM_ICInitStrecture;
	TIM_ICStructInit(&TIM_ICInitStrecture);  //结构体初始化
	TIM_ICInitStrecture.TIM_Channel=TIM_Channel_1;  
	TIM_ICInitStrecture.TIM_ICFilter=0xF;
	//这里的上升沿代表高低电平不反转 给上升沿不反向，给下降沿反向
	TIM_ICInit(TIM3,&TIM_ICInitStrecture);
	
	TIM_ICInitStrecture.TIM_Channel=TIM_Channel_2;  
	TIM_ICInitStrecture.TIM_ICFilter=0xF;
	
	TIM_ICInit(TIM3,&TIM_ICInitStrecture);
	
	TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);//配置接口
	
	TIM_Cmd(TIM3,ENABLE);
}
int16_t Encoder_Get(void)
{
	int16_t Temp;
	Temp=TIM_GetCounter(TIM3);
	TIM_SetCounter(TIM3,0);
	return Temp;
}






