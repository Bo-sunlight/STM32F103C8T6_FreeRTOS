#include "bsp.h" 
#include "includes.h"
void bsp_Init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组 4
	delay_init();	    //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
  uart_init(115200);     	//初始化串口
	Timer2_Init(5000-1,7199);
	TIM3_Int_Init(59,59);
	
}

