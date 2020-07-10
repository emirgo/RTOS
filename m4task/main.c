#include "stm32f4xx.h"                  // Device header
#include "FreeRTOSConfig.h"             // ARM.FreeRTOS::RTOS:Config

#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core


// Global variables
TaskHandle_t xTaskHandle1 = NULL;
TaskHandle_t xTaskHandle2 = NULL;

// Task function prototypes
void vTask1_handler(void *params);
void vTask2_handler(void *params);

int main(void)
{
	// Create tasks
	// Task 1
	xTaskCreate(vTask1_handler,
							"Task-1",	
							configMINIMAL_STACK_SIZE,
							NULL,
							1, // Lowest priority
							&xTaskHandle1);
	// Task 2
	xTaskCreate(vTask2_handler,
							"Task-2",	
							configMINIMAL_STACK_SIZE,
							NULL,
							1, // Lowest priority
							&xTaskHandle2);
	
	// Start the scheduler (round robin)
	vTaskStartScheduler();
	
	// Won't run unless error in scheduled tasks
	while(1)
	{
	
	}
	
	// Never run
	return 0;
}

void vTask1_handler(void *params)
{
	while(1);
}

void vTask2_handler(void *params)
{
	while(1);
}