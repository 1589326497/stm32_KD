#include "stm32f10x.h"                  // Device header
#include "stdio.h"

uint8_t Serial_RxData;
uint8_t Serial_RxFlag;

void Serial_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);  //USART1是APB2的外设
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	USART_InitTypeDef USAET_InitStructure;
	USAET_InitStructure.USART_BaudRate=9600;
	USAET_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USAET_InitStructure.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;  //同时开启发送和接收
	USAET_InitStructure.USART_Parity=USART_Parity_No;  //无校验
	USAET_InitStructure.USART_StopBits=USART_StopBits_1;   //一位停止位
	USAET_InitStructure.USART_WordLength=USART_WordLength_8b; //8位字长
	USART_Init(USART1,&USAET_InitStructure);
	
	//开启中断的方法
	//RXNE一旦置1就会向NVIC申请中断
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
	
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

uint8_t Serial_GetRxFlag(void)  //转存
{
	if (Serial_RxFlag == 1)
	{
		Serial_RxFlag = 0;
		return 1;
	}
	return 0;
}

uint8_t Serial_GetRxData(void)
{
	return Serial_RxData;
}

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)
	{
		Serial_RxData=USART_ReceiveData(USART1);
		Serial_RxFlag=1;
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
}






