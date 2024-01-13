#include "stm32f10x.h"                  // Device header

uint16_t AD_Value[4];
void AD_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);//RCC是AHB总线上的设备
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5);
	
	
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_NbrOfChannel = 4;
	ADC_Init(ADC1, &ADC_InitStructure);
	
	
	
	DMA_InitTypeDef DMA_Initstructure;
	DMA_Initstructure.DMA_PeripheralBaseAddr=(uint32_t)&ADC1->DR;
	DMA_Initstructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;
	DMA_Initstructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	DMA_Initstructure.DMA_MemoryBaseAddr=(uint32_t)&AD_Value;
	DMA_Initstructure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;
	DMA_Initstructure.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMA_Initstructure.DMA_BufferSize=4;  //传输次数
	DMA_Initstructure.DMA_DIR=DMA_DIR_PeripheralSRC;
	DMA_Initstructure.DMA_M2M=DMA_M2M_Disable;   //触发源为ADC
	DMA_Initstructure.DMA_Mode=DMA_Mode_Circular;
	DMA_Initstructure.DMA_Priority=DMA_Priority_Medium;
	DMA_Init(DMA1_Channel1,&DMA_Initstructure);
	
	DMA_Cmd(DMA1_Channel1,ENABLE);
	
	ADC_DMACmd(ADC1,ENABLE);    //开启ADC对DMA的触发
	
	
	ADC_Cmd(ADC1, ENABLE);
	
	ADC_ResetCalibration(ADC1);
	while (ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1);
	while (ADC_GetCalibrationStatus(ADC1) == SET);
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);  //ADC的触发
}


//void AD_GetValue(void)
//{
//	DMA_Cmd(DMA1_Channel1,DISABLE);
//	DMA_SetCurrDataCounter(DMA1_Channel1,4);//重新配置计数器的值
//	DMA_Cmd(DMA1_Channel1,ENABLE);
//	
//	
//	
//	while(DMA_GetFlagStatus(DMA1_FLAG_TC1)==RESET);  //转运完成标志位判断
//	DMA_ClearFlag(DMA1_FLAG_TC1);//标志位清除
//}


