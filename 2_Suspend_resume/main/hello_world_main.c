/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "freertos/queue.h"
struct Message{										/* QUEUE - Message */
	char MesID;
	int Num;
}xMessage;
QueueHandle_t Queue = NULL;								/* A QUEUE */
void hello_task(void *pvParameter)
{
	int i = 0;
  while(1) {
	i++;
  	vTaskDelay(1000 / portTICK_RATE_MS);
    printf("Task1: %d\n",i); 
  }
}

void hello_task_2(void *xtask)
{
  while(1) {
  	vTaskDelay(5000 / portTICK_RATE_MS);
  	printf("Task2: Task1 suspend\n");
	vTaskSuspend( xtask );
	
  	
	//fflush(stdout);
	vTaskDelay(5000 / portTICK_RATE_MS);
	printf("Task2: Task1 resume\n");
	vTaskResume( xtask );
  	
  }
}


void app_main()
{
	TaskHandle_t task1 = NULL;
	//xTaskCreate(&Clean_buf, "Clean_buf", 2048, NULL, 5, &task1);
    xTaskCreate(&hello_task, "hello_task", 2048, NULL, 5, &task1);
    xTaskCreate(&hello_task_2, "hello_task", 2048, task1, 5, NULL);
}
