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

TaskHandle_t xTask1 = NULL, xTask2 = NULL;

void task_1(void *pvParameter)
{
  	while(1) {
  		ulTaskNotifyTake( pdTRUE, portMAX_DELAY );
	  	vTaskDelay(100 / portTICK_RATE_MS);
		printf("Task1: Hello world\n");
  	}
}

void task_2(void *xtask)
{
  	while(1) {
	  	vTaskDelay(3000 / portTICK_RATE_MS);
		xTaskNotifyGive( xTask1 );
		printf("Task2: Give\n");
  	}
}


void app_main()
{
    xTaskCreate(&task_1, "hello_task", 2048, NULL, 5, &xTask1);
    xTaskCreate(&task_2, "hello_task", 2048, NULL, 5, &xTask2);
}
