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
  while(1) {																																																				
  	vTaskDelay(1000 / portTICK_RATE_MS);
    struct Message Mesreciver; 
    xQueueReceive( Queue,&(Mesreciver),( TickType_t ) 10 );
    int num = Mesreciver.Num;
    printf("\n%d",num);
    fflush(stdout);
  }
}

void hello_task_2(void *pvParameter)
{
  while(1) {
  	vTaskDelay(1000 / portTICK_RATE_MS);
  	static int i = 0;
  	i++;
  	xMessage.MesID = 1;
  	xMessage.Num = i;
    xQueueSend(Queue, (void *) &xMessage,( TickType_t ) 0);	/* QUEUE - Send */
  }
}

void Wait(void *pvParameter)
{
  while(1) {
    vTaskDelay(300 / portTICK_RATE_MS);
  	printf("\b\\");
  	fflush(stdout);
  	vTaskDelay(200 / portTICK_RATE_MS);
  	printf("\b|");
  	fflush(stdout);
  	vTaskDelay(200 / portTICK_RATE_MS);
  	printf("\b/");
  	fflush(stdout);
  	vTaskDelay(300 / portTICK_RATE_MS);
  	printf("\b-");
  	fflush(stdout);
  }
}

void app_main()
{
	TaskHandle_t task1 = NULL;
	Queue = xQueueCreate( 10, sizeof(xMessage));	/* QUEUE - Create */
    xTaskCreate(&hello_task, "hello_task", 2048, NULL, 5, &task1);
    xTaskCreate(&hello_task_2, "hello_task", 2048, task1, 5, NULL);
}
