#include "stm32f10x.h"                  // Device header

uint16_t CountSensor_Count;

void CountSensor_Init(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//GPIOB是APB2的外设
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitTypeDef GPIO_Strecture;
	GPIO_Strecture.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Strecture.GPIO_Pin=GPIO_Pin_14;
	GPIO_Strecture.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Strecture);
	//配置AFIO
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);
	//配置EXTI
	EXTI_InitTypeDef EXTI_Strecture;
	EXTI_Strecture.EXTI_Line=EXTI_Line14;
	EXTI_Strecture.EXTI_LineCmd=ENABLE;
	EXTI_Strecture.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_Strecture.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_Strecture);
	//配置NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
	
}

uint16_t CountSensor_Get(void)
{
	return CountSensor_Count;
}

void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line14)==SET)
	{
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0)
		{
			CountSensor_Count ++;
		}
		EXTI_ClearITPendingBit(EXTI_Line14);//将中断标志位清除要不然会一直进入中断函数
	}
}
