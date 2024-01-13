#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

int main(void)
{
	OLED_Init();
	
	Serial_Init();
	
//	Serial_SendArray()
	
//	uint8_t MyArray[]={0x42,0x43,0x44,0x45};
//	Serial_SendArray(MyArray,4);
	
//	Serial_SendString("HelloWorld!\r\n");  // \r\n用于换行
	
//	Serial_SendNumber(12345,5);
	
	/*
	char String[100];                  //创建一个字符串
	sprintf(String,"Num=%d\r\n",666);  //sprintf可以进行重定向
	Serial_SendString(String);         //将参数放到端口
	*/
	
	printf("你好，世界");          //最常见的方法
	
	while(1)
	{
		
	}
}