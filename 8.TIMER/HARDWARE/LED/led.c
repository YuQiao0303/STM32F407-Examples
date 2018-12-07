#include "led.h"
#include "stm32f4xx.h"   //�̼���
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	//1.ʹ��gpio��ʱ��
	//FWLIB , stm32f4xx_rcc.h
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);   //ʱ��ʹ�ܺ���
	//2.GPIO��ʼ��
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;//���������ǿ�ߵ͵�ƽ��
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;//������Ĭ������¸ߵ�ƽ��led������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOF,&GPIO_InitStructure);
	//3.��Ϊ�ߵ�ƽ��Ĭ�ϲ�����
	GPIO_SetBits(GPIOF,GPIO_Pin_9|GPIO_Pin_10);
}
