#include "stm32f4xx.h"
#include "led.h"
#include "delay.h"
#include "timer.h"
//通过定时器中断配置，每500ms中断一次，然后中断服务函数中控制LED实现LED1状态取反（闪烁）。
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//						500ms = (arr + 1) *(psc + 1 )   /Ft us
//						500ms = (arr + 1) *(psc + 1 )   /84M us
//						500ms = (4999 + 1) *(8399 + 1 )   /84M us
//Ft=定时器工作频率,单位:Mhz
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED_Init();
	delay_init(168); //时钟为168M
	LED0=0;
	LED1=1;
	TIM3_Init(4999,8399);
	while(1){
		
	}
}





