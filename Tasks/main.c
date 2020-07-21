#include <stdio.h>
#include "stm32f10x.h"                  // Device header
#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core

TaskHandle_t myTask1Handle = NULL;
TaskHandle_t myTask2Handle = NULL;

void myTask1(void *p)
{
	TickType_t myLastUnblock;
	int count = (int*) p;
	
	while(1)
	{
		
		// 1 sec delay
		// vTaskDelay is not as precise as vTaskDelayUntil
		// I prefer vTaskDelay for my audio projects to give the 
		// analogue feel.
		// vTaskDelay(pdMS_TO_TICKS(1000));
		myLastUnblock = xTaskGetTickCount();
		vTaskDelayUntil(&myLastUnblock, pdMS_TO_TICKS(1000));
		
		count++;
		// If goes beyond 30 delete the task
		if (count > 30)
		{
			vTaskDelete(myTask1Handle);
		}
	}
}

void myTask2(void *p)
{
	while(1)
	{
		vTaskDelay(pdMS_TO_TICKS(5000));
		vTaskSuspend(myTask1Handle);
		vTaskDelay(pdMS_TO_TICKS(5000));
		vTaskResume(myTask1Handle);
	}
}

int main(void)
{
	int count = 0;
	// Pass count
	xTaskCreate(myTask1, "Task-1", 200, (void*) count, tskIDLE_PRIORITY, &myTask1Handle);
	
	xTaskCreate(myTask2, "Task-2", 200, (void*) count, tskIDLE_PRIORITY, &myTask2Handle);
	// Schedule tasks
	vTaskStartScheduler();
	
	while(1)
	{
		
	}
	
	return 0;
}