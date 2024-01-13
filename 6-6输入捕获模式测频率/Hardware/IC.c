#include "stm32f10x.h"                  // Device header

void IC_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	
	GPIO_InitTypeDef GPIO_InitStrecture;
	GPIO_InitStrecture.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStrecture.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStrecture.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStrecture);
	
	TIM_InternalClockConfig(TIM3);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrecyure;
	TIM_TimeBaseInitStrecyure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStrecyure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStrecyure.TIM_Period=65536-1;   //ARR
	TIM_TimeBaseInitStrecyure.TIM_Prescaler=72-1;       //PSC    72/PSC就是计数器自增频率
	TIM_TimeBaseInitStrecyure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStrecyure);
	
	TIM_ICInitTypeDef TIM_ICInitStrecture;
	TIM_ICInitStrecture.TIM_Channel=TIM_Channel_1; //通道
	TIM_ICInitStrecture.TIM_ICFilter=0xF;             //滤波器
	TIM_ICInitStrecture.TIM_ICPolarity=TIM_ICPolarity_Rising;
	TIM_ICInitStrecture.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	TIM_ICInitStrecture.TIM_ICSelection=TIM_ICSelection_DirectTI;  //直连通道
	
	TIM_ICInit(TIM3,&TIM_ICInitStrecture);
	
	
	TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);  //设置触发源
	TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);  //配置从模式 清零
	
	TIM_Cmd(TIM3,ENABLE);
}

uint32_t IC_GetFreq(void)
{
	return 1000000/(TIM_GetCapture1(TIM3)+1);  //捕获CCR的值
}
	


