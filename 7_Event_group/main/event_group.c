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
#include "freertos/queue.h"
#include "freertos/event_groups.h"
#define BIT_0	( 1 << 0 )
#define BIT_1	( 1 << 1 )

EventGroupHandle_t xEventGroup;

void event_create()
{
  	xEventGroup = xEventGroupCreate();
  	printf("Event Group Create\n");
}

void set_bit(void *pvParameter)
{
	EventBits_t uxBits;
	while(1) {
	
		vTaskDelay(3000 / portTICK_RATE_MS);
		printf("Event Group set bit to 1\n");
		uxBits = xEventGroupSetBits( xEventGroup,BIT_0 | BIT_1);
		
		vTaskDelay(3000 / portTICK_RATE_MS);
		printf("Event Group clear bit to 0\n");
        xEventGroupClearBits (xEventGroup, BIT_0 | BIT_1);
	}
}

void wait_bit(void *pvParameter)
{
	EventBits_t uxBits;
  	while(1) {
    
	const TickType_t xTicksToWait = 1000 / portTICK_PERIOD_MS;
	printf("Wait bit\n");
  	uxBits = xEventGroupWaitBits (xEventGroup, BIT_0 | BIT_1, pdFALSE, pdFALSE, xTicksToWait); 
  	if((uxBits & BIT_0) != 0){
  		printf("Wait bit OK\n");
  		//vTaskDelay(10000 / portTICK_RATE_MS);
  	}else{
  		printf("Wait bit not OK\n");

  	}
  }
}

void get_bit(void *pvParameter)
{
	EventBits_t uxBits;
	vTaskDelay(10 / portTICK_RATE_MS);
    while(1) {
    	vTaskDelay(1000 / portTICK_RATE_MS);
        uxBits = xEventGroupGetBits(xEventGroup);
        printf("Get bit: %d",uxBits & BIT_0);
        printf(" %d\n",uxBits & BIT_1);
    }
}

void clear_bit(void *pvParameter)
{
    while(1) {
    	vTaskDelay(7000 / portTICK_RATE_MS);
    	printf("Event Group clear bit 0 and 1 to 0\n");
        xEventGroupClearBits (xEventGroup, BIT_0 | BIT_1); 
    }
}

void app_main()
{
	event_create();
    	xTaskCreate(&set_bit, "hello_task", 2048, NULL, 5, NULL);
	xTaskCreate(&wait_bit, "hello_task", 2048, NULL, 5, NULL);
	xTaskCreate(&get_bit, "hello_task", 2048, NULL, 5, NULL);
	//xTaskCreate(&clear_bit, "hello_task", 2048, NULL, 5, NULL);
}
