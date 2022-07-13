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
#include "freertos/semphr.h"
struct Message{								/* QUEUE - Message */
	char MesID;
	int Num;
}xMessage;
SemaphoreHandle_t xSemaphore;						/* A QUEUE */
int sum = 0;
void hello_task(void *pvParameter)
{
  	while(1) {
  	printf("\nTask 1: %d",sum);
	  	for(int i = 0; i < 10000; i++){
	  		if(xSemaphoreTake( xSemaphore, ( TickType_t ) 10 ) == pdTRUE){
	  			sum++;
	  			xSemaphoreGive( xSemaphore );
	  		}
	  	}
	  	vTaskDelay(1000 / portTICK_RATE_MS);
		printf("\nTask 1: %d",sum);
		printf("\nTask 1: %d",sum);
		vTaskDelay(100000 / portTICK_RATE_MS);
  	}
	
}

void hello_task_2(void *pvParameter)
{

  	while(1) {
	  	for(int i = 0; i < 10000; i++){
	  		if(xSemaphoreTake( xSemaphore, ( TickType_t ) 10 ) == pdTRUE){
	  			sum++;
	  			xSemaphoreGive( xSemaphore );
	  		}
	  	}
	  	vTaskDelay(100000 / portTICK_RATE_MS);
  	}
}

void hello_task_3(void *pvParameter)
{

  	while(1) {
	  	for(int i = 0; i < 10000; i++){
	  		if(xSemaphoreTake( xSemaphore, ( TickType_t ) 10 ) == pdTRUE){
	  			sum++;
	  			xSemaphoreGive( xSemaphore );
	  		}
	  	}
	  	vTaskDelay(100000 / portTICK_RATE_MS);
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
	xSemaphore = xSemaphoreCreateMutex();
	while(xSemaphore == NULL);
    xTaskCreate(&hello_task, "hello_task", 2048, NULL, 5, &task1);
    xTaskCreate(&hello_task_2, "hello_task", 2048, task1, 5, NULL);
    xTaskCreate(&hello_task_3, "hello_task", 2048, task1, 5, NULL);
}
