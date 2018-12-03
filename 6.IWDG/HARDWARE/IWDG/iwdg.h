#ifndef __IWDG_H
#define __IWDG_H
#include "sys.h"



//LED端口定义
#define LED0 PFout(9)	// DS0
#define LED1 PFout(10)	// DS1	 

void LED_Init(void);//初始化		 				    
#endif
