#include "stm32f10x.h"                  // Device header
#include "Delay.h"
int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);//开启时钟
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//引脚工作模式
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;//选择引脚
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//选择输出速度   
	GPIO_Init(GPIOB,&GPIO_InitStructure);//初始化
	//GPIO_ResetBits(GPIOA,GPIO_Pin_0); //推挽输出低电平
	//GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
	while(1)
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		Delay_ms(500);
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
		Delay_ms(500);
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		Delay_ms(500);
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
		Delay_ms(2000);
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
		
	}
	
}