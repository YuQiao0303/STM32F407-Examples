#include "led.h"
#include "stm32f4xx.h"   //固件库
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	//1.使能gpio的时钟
	//FWLIB , stm32f4xx_rcc.h
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);   //时钟使能函数
	//2.GPIO初始化
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;//推挽输出（强高低电平）
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;//上拉（默认情况下高电平，led不亮）
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOF,&GPIO_InitStructure);
	//3.置为高电平（默认不亮）
	GPIO_SetBits(GPIOF,GPIO_Pin_9|GPIO_Pin_10);
}
