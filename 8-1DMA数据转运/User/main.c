#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MyDNA.h"

//const uint8_t aa=0x66;   //const修饰的变量只能读不能写 是存储在Flash里
const uint8_t DataA[]={0x01,0x02,0x03,0x04};
uint8_t DataB[]={0,0,0,0};
int main(void)
{
	OLED_Init();
	MyDMA_Init((uint32_t)DataA,(uint32_t)DataB,4); //stm32里定义的地址是数字偏移所以要转换类型
	OLED_ShowString(1,1,"DataA");
	OLED_ShowString(3,1,"DataB");
	OLED_ShowHexNum(1,8,(uint32_t)DataA,8);
	OLED_ShowHexNum(3,8,(uint32_t)DataB,8);
	
	
	
	
	while(1)
	{
//		DataA[0]++;
//		DataA[1]++;
//		DataA[2]++;
//		DataA[3]++;
		
		OLED_ShowHexNum(2,1,DataA[0],2);
		OLED_ShowHexNum(2,4,DataA[1],2);
		OLED_ShowHexNum(2,7,DataA[2],2);
		OLED_ShowHexNum(2,10,DataA[3],2);
		OLED_ShowHexNum(4,1,DataB[0],2);
		OLED_ShowHexNum(4,4,DataB[1],2);
		OLED_ShowHexNum(4,7,DataB[2],2);
		OLED_ShowHexNum(4,10,DataB[3],2);
		
		Delay_ms(1000);
		
		MyDMA_Transfer();
		
		OLED_ShowHexNum(2,1,DataA[0],2);
		OLED_ShowHexNum(2,4,DataA[1],2);
		OLED_ShowHexNum(2,7,DataA[2],2);
		OLED_ShowHexNum(2,10,DataA[3],2);
		OLED_ShowHexNum(4,1,DataB[0],2);
		OLED_ShowHexNum(4,4,DataB[1],2);
		OLED_ShowHexNum(4,7,DataB[2],2);
		OLED_ShowHexNum(4,10,DataB[3],2);
		Delay_ms(1000);
	}
}