#include "stm32f4xx.h"
#include "ecGPIO2.h"
#include "ecRCC2.h"

#define BUTTON_PIN PC_13

const PinName_t OUTPUT_PINS[4] = {PA_7, PB_6, PC_7, PA_9};

void setup(void);

	
int main(void) { 
	// Initialiization --------------------------------------------------------
	setup();
	unsigned int cnt = 0;
	
	// Inifinite Loop ----------------------------------------------------------
	while(1){
		if(GPIO_read(BUTTON_PIN) == 0) {	
			if (cnt > 9) cnt = 0;
			
			sevensegment_display(cnt % 10);
			cnt++; 

			for (int i = 0; i < 50000; i++) {}  

			while(GPIO_read(BUTTON_PIN) == 0);
		}
	}
}
// Initialiization 
void setup(void)
{
	RCC_HSI_init();	
	GPIO_init(BUTTON_PIN, INPUT);  // calls RCC_GPIOC_enable()
	GPIO_pupd(BUTTON_PIN, 1);
	sevensegment_display_init(OUTPUT_PINS);// Decoder input A,B,C,D

}