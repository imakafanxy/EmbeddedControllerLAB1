/**
******************************************************************************
* @author	KIM MYEONGJUN
* @Mod		2024-09-10
* @brief	Embedded Controller:  LAB Digital In/Out
*					 - Toggle LED LD2 by Button B1 pressing
* 
******************************************************************************
*/
#include "stdio.h"
#include "stm32f4xx.h"
#include "ecRCC2_.h"
#include "ecGPIO2.h"

PinName_t LED_pin = PA_5;
PinName_t button_pin = PC_13;

void setup(void) {
	RCC_HSI_init();	
	GPIO_init(button_pin, INPUT);  
	//GPIO_pupd(button_pin, 1);     
	GPIO_init(LED_pin, OUTPUT);    
	//GPIO_otype(LED_pin, 0);        
}

int main(void) { 
	setup();
	int buttonState = 0;
	int ledState = LOW;        

	GPIO_write(LED_pin, ledState);

	while(1) {
		buttonState = GPIO_read(button_pin); 

		if (buttonState == LOW) {
			ledState = !ledState;  
			GPIO_write(LED_pin, ledState);  


			while(GPIO_read(button_pin) == LOW);
		}
	}
}