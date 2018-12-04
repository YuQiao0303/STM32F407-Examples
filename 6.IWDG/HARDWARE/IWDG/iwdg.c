#include "iwdg.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//�������Ź� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/6/12
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

//��ʼ���������Ź�
//prer:��Ƶ��:0~7(ֻ�е�3λ��Ч!)
//rlr:�Զ���װ��ֵ,0~0XFFF.
//��Ƶ����=4*2^prer.�����ֵֻ����256!
//rlr:��װ�ؼĴ���ֵ:��11λ��Ч.
//ʱ�����(���):Tout=((4*2^prer)*rlr)/32 (ms).
void IWDG_Init(u8 prer,u16 rlr)
{
	//1.ȡ���Ĵ���д������0x5555ʹ��
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); //ʹ�ܶ�IWDG->PR IWDG->RLR��д
	
	//2. ����IWDG��Ƶϵ����дPR
	IWDG_SetPrescaler(prer); 
	
	//3. ����IWDGװ��ֵ
	IWDG_SetReload(rlr);   

	//4. ι����д0xAAAA��KR������ֵ
	IWDG_ReloadCounter(); //reload
	
	//5. ʹ�ܿ��Ź���д0xCCCC��KR
	IWDG_Enable();       
}

//ι�������Ź�
void IWDG_Feed(void)
{
	IWDG_ReloadCounter();//ι����д0xAAAA��KR
}
