/**
******************************************************************************
* @author	KIM MYEONGJUN
* @Mod		2024-09-20
* @brief	Embedded Controller:  LAB Digital In/Out
*					 - Toggle LED LD1,2,3,4 by Button B1 pressing
* 
******************************************************************************
*/

#include <stdio.h>
#include "stm32f4xx.h"
#include "ecRCC2_.h"
#include "ecGPIO2.h"

PinName_t LED_pins[] = {PA_5, PA_6, PA_7, PB_6}; 
PinName_t button_pin = PC_13;
int currentLED = 0;

void setup(void) {
	RCC_HSI_init();	
	GPIO_init(button_pin, INPUT);  
	GPIO_pupd(button_pin, 1);
	

	for (int i = 0; i < 4; i++) {
		GPIO_init(LED_pins[i], OUTPUT);
		GPIO_otype(LED_pins[i], 0);  
	}
}


int main(void) { 
	setup();
	int buttonState = 0;
	int currentLED = 0;
	int allLEDoff = 1;

	for (int i = 0; i < 4; i++) {
		GPIO_write(LED_pins[i], LOW);
	}

	while(1) {
		buttonState = GPIO_read(button_pin); 

		if (buttonState == LOW && allLEDoff == 1) {
			allLEDoff = 0;
			currentLED = 0;
			GPIO_write(LED_pins[currentLED], HIGH);  
			while(GPIO_read(button_pin) == LOW);  
		}

		else if(buttonState == LOW && allLEDoff == 0) {
			GPIO_write(LED_pins[currentLED], LOW);  
			currentLED = (currentLED + 1) % 4; 

			if (currentLED == 0) {
				allLEDoff = 1;  
			}else{		
			GPIO_write(LED_pins[currentLED], HIGH);
			}
		
			while(GPIO_read(button_pin) == LOW); 
		}
	}
}