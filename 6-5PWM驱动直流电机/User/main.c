#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "Motor.h"
#include "Key.h"

uint8_t KeyNum;
int8_t Speed;
int8_t NumSpeed=25;
int main(void)
{
	OLED_Init();
	Motor_Init();
	Key_Init();
	Motor_SetSpeed(50);
	OLED_ShowString(1,1,"Speed:");
	
	while(1)
	{
		KeyNum=Key_GetNum();
		if(KeyNum==1)
		{
			Speed+=NumSpeed;
			if(Speed>=100)
			{
				NumSpeed=-NumSpeed;
			}
			if(Speed<=0)
			{
				NumSpeed=-NumSpeed;
			}
		}
		Motor_SetSpeed(Speed);
		OLED_ShowSignedNum(1,7,Speed,3);
	}
}