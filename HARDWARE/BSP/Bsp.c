#include "bsp.h" 
#include "includes.h"
void bsp_Init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//����ϵͳ�ж����ȼ����� 4
	delay_init();	    //��ʱ������ʼ��	  
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
  uart_init(115200);     	//��ʼ������
	Timer2_Init(5000-1,7199);
	TIM3_Int_Init(59,59);
	
}

