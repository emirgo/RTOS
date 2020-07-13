#include <stdio.h>
#include "stm32f10x.h"                  // Device header
#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core

TaskHandle_t myTask1Handle = NULL;

void myTask1(void *p)
{
	TickType_t myLastUnblock = xTaskGetTickCount();
	int count = (int*) p;
	
	while(1)
	{
		count++;
		// 1 sec delay
		vTaskDelayUntil(&myLastUnblock, 1000 * configTICK_RATE_HZ / 1000);
		
		// If goes beyond 30 delete the task
		if (count > 30)
		{
			vTaskDelete(myTask1Handle);
		}
	}
}

int main(void)
{
	int count = 0;
	// Pass count
	xTaskCreate(myTask1, "Task-1", 200, (void*) count, tskIDLE_PRIORITY, &myTask1Handle);
	// Schedule tasks
	vTaskStartScheduler();
	
	while(1)
	{
		
	}
	
	return 0;
}