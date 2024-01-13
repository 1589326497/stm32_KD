#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

uint8_t RxData;

int main(void)
{
	OLED_Init();
	OLER_ShowString(1,1,"RxData");
	Serial_Init();
	

	
	printf("你好，世界");          //最常见的方法
	
	while(1)
	{
		if(Serial_GetRxFlag()==1)  //查询 在主函数里不断的判断RXNE标志位
		{
			RxData=Serial_GetRxData();
			Serial_SendByte(RxData);
			OLED_ShowHexNum(1,8,RxData,2);
		}
	}
}