#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "led.h"
#include "beep.h"

//ALIENTEK 探索者STM32F407开发板 实验0
//STM32F4工程模板-库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK


void My_USART1_Init(void)
{
	//0. 初始化结构体声明
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//1. 串口和gpio时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	
	//2. gpio复用映射设置
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
	
	//3. GPIO初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;//LED0和LED1对应IO口
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//AF模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
	
	//4. USART初始化
	USART_InitStructure.USART_BaudRate=115200;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART1,&USART_InitStructure); 
		
	//5.串口使能
	USART_Cmd(USART1,ENABLE);
	
	//如果还要用中断
	//6.串口1的接受非空中断使能
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);    //使能   串口1在接收非空时产生的  中断
	//7.中断初始化
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
}

void USART1_IRQHandler(void)    //中断服务函数的名称在启动文件CORE  setup_stm32f40_41xx.s 中定义
{
	u8 res;
	if(USART_GetITStatus(USART1,USART_IT_RXNE)){    //该项目中我们只使能了一个中断：USART_IT_RXNE
		LED0 = 0;             //红灯亮作为指示
		//BEEP = 1;
		res = USART_ReceiveData(USART1);            //其他项目中我们很可能使能了多个不同的中断
		USART_SendData(USART1,res);                 //所以通常要用 USART_GetITStatus(USART1,USART_IT_RXNE)判断一下到底是哪个中断发生了
	
	}
}
int main(void)
{
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	My_USART1_Init();
	BEEP_Init();
	LED_Init();
	LED1 = 0;     //绿灯是指示灯，常量表示程序正在工作
	LED0 = 1;     //红灯默认是灭的
	BEEP = 0;
	
	while(1);
}


