#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "iwdg.h"


//ALIENTEK ̽����STM32F407������ ʵ��6
//�������Ź�ʵ�� -�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com
//������������ӿƼ����޹�˾   
//���ߣ�����ԭ�� @ALIENTEK


int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	LED_Init();				//��ʼ��LED�˿�
	KEY_Init();		  	//��ʼ������
    delay_ms(100);    //��ʱ100ms 
	
	IWDG_Init(4,500); //Ԥ��Ƶ��Ϊ64,����ֵΪ500,���ʱ��Ϊ1s	/////////////////
	
	LED0=0;					  //�ȵ������
	while(1)
	{
		if(KEY_Scan(0)==WKUP_PRES)//���WK_UP����,��ι��
		{
			
			IWDG_Feed();//ι��//////////////////////////////////
			
		}
		delay_ms(10);
	};

}
