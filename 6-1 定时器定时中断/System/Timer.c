#include "stm32f10x.h"                  // Device header

extern uint16_t Num;               //声明变量

void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_InternalClockConfig(TIM2); //选择时钟 TIM2
	
	TIM_TimeBaseInitTypeDef TIM_TimBaseStructure;
	TIM_TimBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;  //防止抖动
	TIM_TimBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimBaseStructure.TIM_Period=10000-1;
	TIM_TimBaseStructure.TIM_Prescaler=7200-1;    //1M=1乘10的六次方
	TIM_TimBaseStructure.TIM_RepetitionCounter=0; //这里重复计数器是高级定时器的功能这里我们是基础定时器所以给0
	TIM_TimeBaseInit(TIM2,&TIM_TimBaseStructure);
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_Initstructure;
	NVIC_Initstructure.NVIC_IRQChannel=TIM2_IRQn;  //定时器在NVIC的通道
	NVIC_Initstructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_Initstructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_Initstructure);
	
	TIM_Cmd(TIM2,ENABLE);      //启动定时器
	
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
	{
		Num++;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}
