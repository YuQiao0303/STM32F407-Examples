#include "wwdg.h"
#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//���Ź� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/6/12
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved				
//********************************************************************************
//V1.1 20140504
//�����˴��ڿ��Ź���غ�����
////////////////////////////////////////////////////////////////////////////////// 

//����WWDG������������ֵ,Ĭ��Ϊ���. ��������ֻ����λ6��0��
u8 WWDG_CNT=0X7F;

//��ʼ�����ڿ��Ź� 	
//tr   :T[6:0],������ֵ 
//wr   :W[6:0],����ֵ 
//fprer:��Ƶϵ����WDGTB��,�����2λ��Ч 
//Fwwdg=PCLK1/(4096*2^fprer). һ��PCLK1=42Mhz
void WWDG_Init(u8 tr,u8 wr,u32 fprer)
{
 
	NVIC_InitTypeDef NVIC_InitStructure;
 
	//1.ʹ�ܴ��ڿ��Ź�ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE); //ʹ�ܴ��ڿ��Ź�ʱ��
	
	//�����������ֵ��ȷ�����������ֵ��������ֻ����λ��
	WWDG_CNT=tr&WWDG_CNT;   //��ʼ��WWDG_CNT. 
	
	//2.���÷�Ƶֵ
	WWDG_SetPrescaler(fprer); 
	
	//4.�����ϴ���ֵ
	WWDG_SetWindowValue(wr);
//	WWDG_SetCounter(WWDG_CNT);//���ü���ֵ
	
	//5.�������Ź�
	WWDG_Enable(WWDG_CNT);  //�������Ź�
	
	//6.���� ��ǰ�����жϵ����ȼ���ʹ��
	NVIC_InitStructure.NVIC_IRQChannel=WWDG_IRQn;  //���ڿ��Ź��ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02;  //��ռ���ȼ�Ϊ2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03;					//�����ȼ�Ϊ3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;  //ʹ�ܴ��ڿ��Ź�
	NVIC_Init(&NVIC_InitStructure);
	
	
	WWDG_ClearFlag();//�����ǰ�����жϱ�־λ
    WWDG_EnableIT();//������ǰ�����ж�
}



//���ڿ��Ź��жϷ������ 
void WWDG_IRQHandler(void)
{
	WWDG_SetCounter(WWDG_CNT); //���贰�ڿ��Ź�ֵ ��ι����
	WWDG_ClearFlag();//�����ǰ�����жϱ�־λ
	LED1=!LED1;
}
