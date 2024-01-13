#include "stm32f10x.h"                  // Device header
#include "Delay.h"
int main(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);   //RCC里面的APB2外设时钟控制函数
	GPIO_InitTypeDef GPIO_InitStructure; //定义一个结构体类型
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP; //工作模式为推挽输出
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;  //位置为0号引脚
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;  //配置速度为50HZ
	GPIO_Init(GPIOB,&GPIO_InitStructure);  //GPIO的初始化
	//内部的主要执行逻辑读取结构体的参数，执行判断和运算，写到GPIO配置寄存器
	//推挽输出高低电平都有驱动能力，开漏输出高电平相当于高阻态，没有驱动能力，低电平有驱动能力
	while(1)
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		Delay_ms(100);
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
		Delay_ms(100);
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		Delay_ms(100);
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
		Delay_ms(500);
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		Delay_ms(100);
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
		Delay_ms(500);
		
	}
}