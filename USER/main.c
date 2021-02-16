/*                                                             *
*                           STM32F103C8T6                      *            
****************************************************************/

#include "includes.h"
//������
TaskHandle_t LED0Task_Handler; 
TaskHandle_t KEYTask_Handler;
TaskHandle_t CPUask_Handler;
TaskHandle_t OLEDask_Handler;

//������
void led0_task(void *pvParameters);
void KEY_task(void *pvParameters);
void CPU_task(void *pvParameters);
void OLED_task(void *pvParameters);

static void AppTaskCreate (void);
static void AppObjCreate (void);

int main(void)
{	

	__set_PRIMASK(1);  
	
	/* Ӳ����ʼ�� */
	bsp_Init();
	
	/* �������� */
	AppTaskCreate();
	
	/* ��������ͨ�Ż��� */
	 AppObjCreate();
	
	 /* �������ȣ���ʼִ������ */
   vTaskStartScheduler();
	
/* 
 ���ϵͳ���������ǲ������е�����ģ����е����Ｋ�п��������ڶ�ʱ��������߿��������
 heap �ռ䲻����ɴ���ʧ�ܣ���Ҫ�Ӵ� FreeRTOSConfig.h �ļ��ж���� heap ��С��
 #define configTOTAL_HEAP_SIZE ( ( size_t ) ( 17 * 1024 ) )
*/
   while(1);      
 }

/*
*********************************************************************************************************
*	�� �� ��: AppTaskCreate
*	����˵��: ����Ӧ������
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void AppTaskCreate (void)
{
 taskENTER_CRITICAL(); //�����ٽ���
	
	  //���� LED0 ����
	 xTaskCreate((TaskFunction_t )led0_task, 
                 (const char* )"led0_task", 
                 (uint16_t )128, 
								 (void* )NULL,
								 (UBaseType_t )1,
								 (TaskHandle_t* )&LED0Task_Handler); 
 
     //����KEY����
    xTaskCreate((TaskFunction_t )KEY_task,     
                (const char*    )"KEY_task",   
                (uint16_t       )128, 
                (void*          )NULL,
                (UBaseType_t    )5,
                (TaskHandle_t*  )&KEYTask_Handler);   
			
			//����OLED����
    xTaskCreate((TaskFunction_t )OLED_task,     
                (const char*    )"OLED_task",   
                (uint16_t       )128, 
                (void*          )NULL,
                (UBaseType_t    )1,
                (TaskHandle_t*  )&OLEDask_Handler);  
								
		//����CPU����
    xTaskCreate((TaskFunction_t )CPU_task,     
                (const char*    )"CPU_task",   
                (uint16_t       )256, 
                (void*          )NULL,
                (UBaseType_t    )5,
                (TaskHandle_t*  )&CPUask_Handler); 

   taskEXIT_CRITICAL(); //�˳��ٽ���
}


/*
*********************************************************************************************************
*	�� �� ��: AppObjCreate
*	����˵��: ��������ͨ�Ż���
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
 void AppObjCreate (void)
 {
	 
 }
 

 /*
*********************************************************************************************************
*	�� �� ��: led0_task
*	����˵��: LED�Ƶ�����
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void led0_task(void *pvParameters)
{
 while(1)
 {
	 LED0 = !LED0;
   vTaskDelay(500);
 }
}


 /*
*********************************************************************************************************
*	�� �� ��: KEY_task
*	����˵��: ��������
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void KEY_task(void *pvParameters)
{
	while(1)
	{
		  vTaskDelay(500);
	}
}

/*
*********************************************************************************************************
*	�� �� ��: CPU_task
*	����˵��: �����ӡ
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void CPU_task(void *pvParameters)
{
	uint8_t CPU_RunInfo[400]; //������������ʱ����Ϣ
	while(1)
	{
		 memset(CPU_RunInfo,0,400); //��Ϣ����������
		 vTaskList((char *)&CPU_RunInfo);  //��ȡ��������ʱ����Ϣ
    
    printf("---------------------------------------------\r\n");
    printf("������                         ����״̬           ���ȼ�            ʣ��ջ         �������\r\n");
    printf("%s", CPU_RunInfo);
    printf("---------------------------------------------\r\n");
    
    memset(CPU_RunInfo,0,400);				//��Ϣ����������
    
    vTaskGetRunTimeStats((char *)&CPU_RunInfo);
    
    printf("������                             ���м���                             ʹ����\r\n");
    printf("%s", CPU_RunInfo);
    printf("---------------------------------------------\r\n\n");
    vTaskDelay(1000);   /* ��ʱ500��tick */	
}
}
 

/*
*********************************************************************************************************
*	�� �� ��: OLED_task
*	����˵��: OLED��ʾ����
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void OLED_task(void *pvParameters)
{
		while(1)
	{
		  vTaskDelay(500);
	}
}



