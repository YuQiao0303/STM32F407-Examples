#include "stm32f4xx.h"
#include "led.h"
#include "delay.h"
#include "timer.h"
//ͨ����ʱ���ж����ã�ÿ500ms�ж�һ�Σ�Ȼ���жϷ������п���LEDʵ��LED1״̬ȡ������˸����
//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//						500ms = (arr + 1) *(psc + 1 )   /Ft us
//						500ms = (arr + 1) *(psc + 1 )   /84M us
//						500ms = (4999 + 1) *(8399 + 1 )   /84M us
//Ft=��ʱ������Ƶ��,��λ:Mhz
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED_Init();
	delay_init(168); //ʱ��Ϊ168M
	LED0=0;
	LED1=1;
	TIM3_Init(4999,8399);
	while(1){
		
	}
}





