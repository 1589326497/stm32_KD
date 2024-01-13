#include "stm32f10x.h"                  // Device header
#include "stdio.h"

void Serial_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);  //USART1是APB2的外设
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	USART_InitTypeDef USAET_InitStructure;
	USAET_InitStructure.USART_BaudRate=9600;
	USAET_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USAET_InitStructure.USART_Mode=USART_Mode_Tx;
	USAET_InitStructure.USART_Parity=USART_Parity_No;  //无校验
	USAET_InitStructure.USART_StopBits=USART_StopBits_1;   //一位停止位
	USAET_InitStructure.USART_WordLength=USART_WordLength_8b; //8位字长
	USART_Init(USART1,&USAET_InitStructure);
	
	USART_Cmd(USART1,ENABLE);
	
}

void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART1,Byte);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);  //标志位置1的时候会自动清零
	
	
	
}

void Serial_SendArray(uint8_t *Array,uint16_t Length)
{
	uint16_t i;
	for(i=1;i<=Length;i++)
	{
		Serial_SendByte(Array[i]);
	}
}

void Serial_SendString(char *String)
{
	uint8_t i;
	for(i=0;String[i]!='\0';i++)
	{
		Serial_SendByte(String[i]);
	}
}

uint32_t Serial_Pow(uint32_t x,uint32_t Y)
{
	uint32_t Result=1;
	while(Y--)
	{
		Result*=x;     //Result累乘Y次X就是X的Y次方
	}
	return Result;
}

void Serial_SendNumber(uint32_t Number,uint8_t Length)
{
	uint8_t i;
	for (i=0;i<Length;i++)
	{
		
		Serial_SendByte(Number/Serial_Pow(10,Length-i-1)%10+'0'); //最后要加上ASC码表的偏移
		
	}
}
 
/*
	printf默认的输出端口在屏幕，但单片机没有屏幕
	所以我们通过改变fputc的重映射到串口
*/
int fputc(int ch,FILE *f)   //fputc是printf的底层 
{
	Serial_SendByte(ch);    //将fputc重映射到串口
	return ch;
}








