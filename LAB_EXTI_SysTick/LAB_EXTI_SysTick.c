/**
******************************************************************************
* @author	MyeongjunKim
* @Mod		2024-10-11
* @brief	Embedded Controller:  LAB EXTI
*					 - Counting numbers on 7-Segment using EXTI Button
*     	   - Counting numbers on 7-Segment using SysTick
******************************************************************************
*/

#include "ecGPIO2.h"
#include "ecEXTI2.h"
#include "ecSysTick2.h"
#include "ecRCC2.h"

#define BUTTON_PIN PC_13

const PinName_t OUTPUT_PINS[4] = {PA_5,PA_6,PA_7,PA_9};
unsigned int cnt = 0;

// Initialiization 
void setup(void)
{
	RCC_PLL_init();
	SysTick_init();
	GPIO_init(BUTTON_PIN, INPUT);  
	GPIO_pupd(BUTTON_PIN,1);
	
	for(int i=0;i<4;i++){
		GPIO_pupd(OUTPUT_PINS[i],0);
		GPIO_otype(OUTPUT_PINS[i],0);
		GPIO_ospeed(OUTPUT_PINS[i],1);
	}
	
	sevensegment_display_init(OUTPUT_PINS);
	EXTI_init(BUTTON_PIN, FALL, 1);
}
	
int main(void) { 
	setup();

	while(1){
	sevensegment_display(cnt % 10);
	}
}

// EXTI interrupt handler for button press
void EXTI15_10_IRQHandler(void) {
	if(is_pending_EXTI(BUTTON_PIN)) {  // Check if EXTI is pending
		cnt = 0;
		sevensegment_display(cnt);
		clear_pending_EXTI(BUTTON_PIN);  // Clear EXTI pending flag
	}
}