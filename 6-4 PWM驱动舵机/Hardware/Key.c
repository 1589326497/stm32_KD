#include "stm32f10x.h"  // Device header
#include "Delay.h"
void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStrecture;
	GPIO_InitStrecture.GPIO_Mode=GPIO_Mode_IPU; //上拉输入模式
	GPIO_InitStrecture.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_10;
	GPIO_InitStrecture.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStrecture);
	
}

uint8_t Key_GetNum(void) //调用这个函数可以得到返回值的键码
{
	uint8_t KeyNum=0;
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0)
	{
		Delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0);//检测松手
		Delay_ms(20);
		KeyNum=1;
	}
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)==0)
	{
		Delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)==0);//检测松手
		Delay_ms(20);
		KeyNum=2;
	}
	
	
	return KeyNum;
}
