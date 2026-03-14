#include "stm32f446xx.h"

int main(){

	// First of all I need to handle light-in built LED
	// LED is PA5
	RCC->AHB1ENR |= (1<<0); // Turn on clock for GPIOA
	// 01 => Output mode acc. to datasheet for PA5
	GPIOA->MODER |= (1<<10);
	GPIOA->MODER &= (~(1<<11));

	SysTick->LOAD = 16000000 - 1;// 1second, -1 for starting from 0

	SysTick->VAL  = 0;
	// Now do SYSTICK on :-
	SysTick->CTRL |= (1<<0) | (1<<1) | (1<<2);
	while(1){

	}
	return 0;
}

void SysTick_Handler(void){
	GPIOA->ODR ^= (1<<5); // For blinking
}

