#include "stm32f4xx.h"
#include "led.h"
#include "delay.h"


int main(void)
{
	LED_Init();
	delay_init(168); //Ê±ÖÓÎª168M
	while(1){
		GPIO_ResetBits(GPIOF,GPIO_Pin_9|GPIO_Pin_10);
		delay_ms(500);
		GPIO_SetBits(GPIOF,GPIO_Pin_9|GPIO_Pin_10);
		delay_ms(500);
	}
}





