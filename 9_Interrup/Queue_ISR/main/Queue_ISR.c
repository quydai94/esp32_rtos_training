/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_system.h"

TaskHandle_t xTask1 = NULL, xTask2 = NULL;
QueueHandle_t xQueue;

void vOutputCharacter(int num){
	printf("Task2: %d\n",num);   
}

void task_1(void *pvParameter)
{
	int cValueToPost;
	const TickType_t xTicksToWait = ( TickType_t )0xff;
	
  	while(1) {
  		cValueToPost = 99;
	  	vTaskDelay(3000 / portTICK_RATE_MS);
	  	xQueueSend( xQueue, ( void * ) &cValueToPost, xTicksToWait );
		printf("Task1: Data send\n");     
  	}
}

void task_2(void *xtask)
{
	BaseType_t xTaskWokenByReceive = pdFALSE;
	int cRxedChar;
  	while( 1)
    {
    	if(xQueueReceiveFromISR( xQueue, (void*) &cRxedChar, &xTaskWokenByReceive) == pdTRUE){
        	vOutputCharacter( cRxedChar );
        }
        vTaskDelay(100 / portTICK_RATE_MS);
    }

    /*if( xTaskWokenByReceive != pdFALSE )
    {
        taskYIELD ();
    }*/
}


void app_main()
{
	xQueue = xQueueCreate( 10, sizeof( char ) );
    xTaskCreate(&task_1, "hello_task", 2048, NULL, 5, &xTask1);
    xTaskCreate(&task_2, "hello_task", 2048, NULL, 5, &xTask2);
}
