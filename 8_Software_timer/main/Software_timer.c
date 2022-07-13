/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

TimerHandle_t xTimer;

void vTimerCallback(TimerHandle_t xTimer){
	printf("Timer callback\n");
}

void timer_create()
{
	printf("%d %d %d %d\n", pdFALSE, pdTRUE, pdFAIL, pdPASS);
    xTimer = xTimerCreate("Timer", pdMS_TO_TICKS(1000), pdTRUE, 0, vTimerCallback);
	if (xTimer == NULL)
     {
         printf("Timer create error\n");
		 vTaskDelay(10000 / portTICK_RATE_MS);
     }
    else
    {
		printf("Timer created\n");
		printf("Timer ID: 0\n");
		printf("Timer name: Timer\n");
		printf("Timer Period: 1000ms\n\n");
    }
}

void timer_start()
{
    if ( xTimerStart (xTimer , 0) == pdPASS)
    {
         printf("Timer start\n");
    }else {
		printf("Timer not start\n");
	}
}

void timer_stop(){
	vTaskDelay(5000 / portTICK_RATE_MS);
	printf("Timer stop\n");
	xTimerStop(xTimer , 0);
}

void timer_change(){	
 	vTaskDelay(5000 / portTICK_RATE_MS);
	printf("Timer Change Period to 500ms\n");
	xTimerChangePeriod(xTimer, pdMS_TO_TICKS(500), 0);
}


void app_main()
{
	timer_create();
	timer_start();
	timer_change();
	timer_stop();
    //xTaskCreate(&set_bit, "hello_task", 2048, NULL, 5, NULL);
}
