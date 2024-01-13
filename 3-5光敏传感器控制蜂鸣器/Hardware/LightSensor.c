#include "stm32f10x.h"                  // Device header

void LightSensor_Init(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStrecture;
	GPIO_InitStrecture.GPIO_Mode=GPIO_Mode_IPU; //上拉输入模式
	GPIO_InitStrecture.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStrecture.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStrecture);
	
}
uint8_t LightSensor_Get(void)
{	
	
	return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);
	
}