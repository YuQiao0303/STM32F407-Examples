#include "timer.h"
#include "led.h"
#include "stm32f4xx.h"   //�̼���
/*
ͨ����ʱ���ж����ã�ÿ500ms�ж�һ�Σ�Ȼ���жϷ������п���LEDʵ��LED1״̬ȡ������˸����
*/
//TIM_Period: 			arr :auto reload  register
//TIM_Prescaler: 		psc: prescaler 
//TIM_CounterMode		����ģʽ�����������м�����
//ʣ���������ã�
//TIM_ClockDivision		���벶�����ã����ﲻ��
//TIM_RepetitionCounter	�߼���ʱ����

//

void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //����ж�
	{
		LED1 = ~LED1;
	}
	TIM_ClearFlag(TIM3,TIM_IT_Update );

}

void TIM3_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	//1. ʹ�ܶ�ʱ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	//2. ��ʼ����ʱ��������ARR��PSC
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;      //���дһ�����ù�
	TIM_TimeBaseInitStruct.TIM_CounterMode= TIM_CounterMode_Up; //ģʽ
	TIM_TimeBaseInitStruct.TIM_Period =arr;    //arr�Զ�װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;  //pscԤ��Ƶϵ��
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);           //����Ҳ������壬��FWLIB�����һЩ��
	
	//3.������ʱ���ж�
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	
	//4.����NVIC
	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn ;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStruct);
	//5.ʹ�ܶ�ʱ��
	TIM_Cmd(TIM3,ENABLE);
}

