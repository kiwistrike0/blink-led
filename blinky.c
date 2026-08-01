#include <stdio.h>
#include "driver/gpio.h"			//connecting GPIO w/ led_strip
#include "led_strip.h"				//To connect to led_strip instead of gpio, since my ESP32-S3 needs help w/ GPIO pins rn
#include "freertos/FreeRTOS.h"		//Real-Time OS's use tools with strict fixed-time deadlines
#include "freertos/task.h"			//for vTaskDelay() 
#include "esp_err.h"				//for error check function 

#define LED_PIN 38
#define TRUE 1

static led_strip_handle_t led_strip;
const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;		//converts milliseconds to ticks (1000 ms to 1000 ticks) (for led off)
const TickType_t yDelay = 500 / portTICK_PERIOD_MS;			//for the led on

void blink_led(void);
void configs4led(void);

void app_main(void){
		
		configs4led();		//the ESP32-S3 is only running based off the code it sees in app_main()
							//if the code for the GPIO connection is missing, then the code cannot 
							//directly connect to the MCU
		
		while(TRUE){		//infinite superloop				
			blink_led();	
		}	
}

void blink_led(void){
		led_strip_set_pixel(led_strip, 0, 83, 0, 0);	//Sets the color. The # refers to brightness of each color from 0-255
		led_strip_refresh(led_strip);					//the command that emits the led visually
		vTaskDelay(xDelay);								//delay for X amount of seconds
		
		//turn led off
		led_strip_clear(led_strip);		
		vTaskDelay(yDelay);								//delay for X amonut of seconds
		
		led_strip_set_pixel(led_strip, 0, 0, 83, 0);	
		led_strip_refresh(led_strip);					//emits green
		vTaskDelay(xDelay);
		
		//turn led off
		led_strip_clear(led_strip);		
		vTaskDelay(yDelay);								//delay for X amonut of seconds
		
		led_strip_set_pixel(led_strip, 0, 0, 0, 83);	
		led_strip_refresh(led_strip);					//emits blue
		vTaskDelay(xDelay);
		
		led_strip_clear(led_strip);
		vTaskDelay(yDelay);								//turns off before repeating loop so that it doesn't 
														//go from blue to red without a break
	}
	
void configs4led(void){
		led_strip_config_t config_led = { .strip_gpio_num = LED_PIN, .max_leds = 1 };		//configuring led to match GPIO pin 38
		led_strip_rmt_config_t rmt_config = { .resolution_hz = 10 * 1000 * 1000 };			//necessary for led to display colors at 
																							//needed pace (sends light pulses)
		ESP_ERROR_CHECK(led_strip_new_rmt_device(&config_led, &rmt_config, &led_strip));	//fully connects code/led_strip to GPIO
																							//38 and returns important error message
																							//if failure (success or failure)
}