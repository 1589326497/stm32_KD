#include "stm32f10x.h"                  // Device header
uint16_t MyDMA_Size;
void MyDMA_Init(uint32_t AddrA,uint32_t AddrB,uint16_t Size)
{
	MyDMA_Size=Size;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);//RCC是AHB总线上的设备
	
	DMA_InitTypeDef DMA_Initstructure;
	DMA_Initstructure.DMA_PeripheralBaseAddr=AddrA;
	DMA_Initstructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
	DMA_Initstructure.DMA_PeripheralInc=DMA_PeripheralInc_Enable;
	DMA_Initstructure.DMA_MemoryBaseAddr=AddrB;
	DMA_Initstructure.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
	DMA_Initstructure.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMA_Initstructure.DMA_BufferSize=Size;  //传输次数
	DMA_Initstructure.DMA_DIR=DMA_DIR_PeripheralSRC;
	DMA_Initstructure.DMA_M2M=DMA_M2M_Enable;
	DMA_Initstructure.DMA_Mode=DMA_Mode_Normal;
	DMA_Initstructure.DMA_Priority=DMA_Priority_Medium;
	DMA_Init(DMA1_Channel1,&DMA_Initstructure);
	
	DMA_Cmd(DMA1_Channel1,DISABLE);
}
void MyDMA_Transfer(void)
{
	DMA_Cmd(DMA1_Channel1,DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel1,MyDMA_Size);//重新配置计数器的值
	DMA_Cmd(DMA1_Channel1,ENABLE);
	
	while(DMA_GetFlagStatus(DMA1_FLAG_TC1)==RESET);  //转运完成标志位判断
	DMA_ClearFlag(DMA1_FLAG_TC1);//标志位清除
}


