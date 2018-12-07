#include "timer.h"
#include "led.h"
#include "stm32f4xx.h"   //固件库
/*
通过定时器中断配置，每500ms中断一次，然后中断服务函数中控制LED实现LED1状态取反（闪烁）。
*/
//TIM_Period: 			arr :auto reload  register
//TIM_Prescaler: 		psc: prescaler 
//TIM_CounterMode		计数模式，向上向下中间对齐等
//剩下两个不用：
//TIM_ClockDivision		输入捕获里用，这里不用
//TIM_RepetitionCounter	高级计时器用

//

void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //溢出中断
	{
		LED1 = ~LED1;
	}
	TIM_ClearFlag(TIM3,TIM_IT_Update );

}

void TIM3_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	//1. 使能定时器时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	//2. 初始化定时器，配置ARR，PSC
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;      //随便写一个不用管
	TIM_TimeBaseInitStruct.TIM_CounterMode= TIM_CounterMode_Up; //模式
	TIM_TimeBaseInitStruct.TIM_Period =arr;    //arr自动装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;  //psc预分频系数
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);           //如果找不到定义，在FWLIB下添加一些包
	
	//3.开启定时器中断
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	
	//4.配置NVIC
	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn ;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStruct);
	//5.使能定时器
	TIM_Cmd(TIM3,ENABLE);
}

