/*                                                             *
*                           STM32F103C8T6                      *            
****************************************************************/

#include "includes.h"
//任务句柄
TaskHandle_t LED0Task_Handler; 
TaskHandle_t KEYTask_Handler;
TaskHandle_t CPUask_Handler;
TaskHandle_t OLEDask_Handler;

//任务函数
void led0_task(void *pvParameters);
void KEY_task(void *pvParameters);
void CPU_task(void *pvParameters);
void OLED_task(void *pvParameters);

static void AppTaskCreate (void);
static void AppObjCreate (void);

int main(void)
{	

	__set_PRIMASK(1);  
	
	/* 硬件初始化 */
	bsp_Init();
	
	/* 创建任务 */
	AppTaskCreate();
	
	/* 创建任务通信机制 */
	 AppObjCreate();
	
	 /* 启动调度，开始执行任务 */
   vTaskStartScheduler();
	
/* 
 如果系统正常启动是不会运行到这里的，运行到这里极有可能是用于定时器任务或者空闲任务的
 heap 空间不足造成创建失败，此要加大 FreeRTOSConfig.h 文件中定义的 heap 大小：
 #define configTOTAL_HEAP_SIZE ( ( size_t ) ( 17 * 1024 ) )
*/
   while(1);      
 }

/*
*********************************************************************************************************
*	函 数 名: AppTaskCreate
*	功能说明: 创建应用任务
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void AppTaskCreate (void)
{
 taskENTER_CRITICAL(); //进入临界区
	
	  //创建 LED0 任务
	 xTaskCreate((TaskFunction_t )led0_task, 
                 (const char* )"led0_task", 
                 (uint16_t )128, 
								 (void* )NULL,
								 (UBaseType_t )1,
								 (TaskHandle_t* )&LED0Task_Handler); 
 
     //创建KEY任务
    xTaskCreate((TaskFunction_t )KEY_task,     
                (const char*    )"KEY_task",   
                (uint16_t       )128, 
                (void*          )NULL,
                (UBaseType_t    )5,
                (TaskHandle_t*  )&KEYTask_Handler);   
			
			//创建OLED任务
    xTaskCreate((TaskFunction_t )OLED_task,     
                (const char*    )"OLED_task",   
                (uint16_t       )128, 
                (void*          )NULL,
                (UBaseType_t    )1,
                (TaskHandle_t*  )&OLEDask_Handler);  
								
		//创建CPU任务
    xTaskCreate((TaskFunction_t )CPU_task,     
                (const char*    )"CPU_task",   
                (uint16_t       )256, 
                (void*          )NULL,
                (UBaseType_t    )5,
                (TaskHandle_t*  )&CPUask_Handler); 

   taskEXIT_CRITICAL(); //退出临界区
}


/*
*********************************************************************************************************
*	函 数 名: AppObjCreate
*	功能说明: 创建任务通信机制
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
 void AppObjCreate (void)
 {
	 
 }
 

 /*
*********************************************************************************************************
*	函 数 名: led0_task
*	功能说明: LED灯的任务
*	形    参: 无
*	返 回 值: 无
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
*	函 数 名: KEY_task
*	功能说明: 按键任务
*	形    参: 无
*	返 回 值: 无
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
*	函 数 名: CPU_task
*	功能说明: 任务打印
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void CPU_task(void *pvParameters)
{
	uint8_t CPU_RunInfo[400]; //保存任务运行时间信息
	while(1)
	{
		 memset(CPU_RunInfo,0,400); //信息缓冲区清零
		 vTaskList((char *)&CPU_RunInfo);  //获取任务运行时间信息
    
    printf("---------------------------------------------\r\n");
    printf("任务名                         任务状态           优先级            剩余栈         任务序号\r\n");
    printf("%s", CPU_RunInfo);
    printf("---------------------------------------------\r\n");
    
    memset(CPU_RunInfo,0,400);				//信息缓冲区清零
    
    vTaskGetRunTimeStats((char *)&CPU_RunInfo);
    
    printf("任务名                             运行计数                             使用率\r\n");
    printf("%s", CPU_RunInfo);
    printf("---------------------------------------------\r\n\n");
    vTaskDelay(1000);   /* 延时500个tick */	
}
}
 

/*
*********************************************************************************************************
*	函 数 名: OLED_task
*	功能说明: OLED显示任务
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void OLED_task(void *pvParameters)
{
		while(1)
	{
		  vTaskDelay(500);
	}
}



