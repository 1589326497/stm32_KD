#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"

uint16_t Num,Minute,Hour,Day;
int main(void)
{
	OLED_Init();
	Timer_Init();
	OLED_ShowString(1,1,"Day:");
	OLED_ShowString(3,1,"ARR:");
	OLED_ShowChar(2,3,':');
	OLED_ShowChar(2,6,':');
	
	while(1)
	{
		if(Num==60)
		{
			Minute++;
			Num=0;
			if(Minute==60)
			{
				Hour++;
				Minute=0;
				if(Hour==24)
				{
					Day++;
					Hour=0;
				}
			}
		}
		
		
		OLED_ShowNum(1,6,Day,3);
		OLED_ShowNum(2,1,Hour,2);
		OLED_ShowNum(2,4,Minute,2);
		OLED_ShowNum(2,7,Num,2);
		OLED_ShowNum(3,6,TIM_GetCounter(TIM2),5);
	}
}

