#include "stm32f10x.h"                  // Device header

void AD_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6); //ADC的时钟预分频配置 
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;//模拟输入模式 
	/*
	模拟输入模式下GPIO口是断开的，这时是ADC的专用模式
	*/
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5); //通道0放在1的位置
	
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;        //独立模式
	ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;       //外部触发转换选择
	ADC_InitStructure.ADC_ContinuousConvMode=DISABLE;
	ADC_InitStructure.ADC_ScanConvMode=DISABLE;
	ADC_InitStructure.ADC_NbrOfChannel=1;
	ADC_Init(ADC1,&ADC_InitStructure);
	
	ADC_Cmd(ADC1,ENABLE);
	
	//配置好ADC之后还需要对ADC进行校准
	
	ADC_ResetCalibration(ADC1);//复位校准 把标注为置1
	while(ADC_GetResetCalibrationStatus(ADC1)==SET); //校准完成吧标志位自动清除 所以要放在循环里
	ADC_StartCalibration(ADC1);//开始校准
	while(ADC_GetCalibrationStatus(ADC1)==SET);    //校准标志位是否=SET
}

uint16_t AD_GetValue(void)
{
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);
	return ADC_GetConversionValue(ADC1);
}
