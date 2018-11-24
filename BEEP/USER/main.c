#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"

//ALIENTEK ̽����STM32F407������ ʵ��2
//������ʵ��-�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com
//������������ӿƼ����޹�˾    
//���ߣ�����ԭ�� @ALIENTEK

int main(void)
{ 
 
	delay_init(168);		   //��ʼ����ʱ����
	LED_Init();				    //��ʼ��LED�˿�
	BEEP_Init();         	//��ʼ���������˿�
	
	while(1)
	{ 
		GPIO_ResetBits(GPIOF,GPIO_Pin_9); // DS0���ͣ���   ��ͬLED0=0;
		GPIO_ResetBits(GPIOF,GPIO_Pin_8); //BEEP�������ͣ� ��ͬBEEP=0;
		delay_ms(300);                    //��ʱ300ms
		GPIO_SetBits(GPIOF,GPIO_Pin_9);   // DS0���ߣ���   ��ͬLED0=1;
		GPIO_SetBits(GPIOF,GPIO_Pin_8);   //BEEP�������ߣ� ��ͬBEEP=1;
		delay_ms(300); 										//��ʱ300ms
	}
}
