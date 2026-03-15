#include "stm32f446xx.h"

#define baudrate 9600

int main(){

	// I can see PA2 & PA3(On nucleo board otherwise chip supports
	// other pins also) supporting USART2
	RCC->CR |= (1<<0);
	RCC->AHB1ENR |= (1<<0);

	// Pin PA2
	GPIOA->MODER |= (1<<5);
	GPIOA->MODER &= (~(1<<4));
	GPIOA->AFR[0] |= (1<<10) | (1<<9) | (1<<8);
	GPIOA->AFR[0] &= (~(1<<11));

	// Pin PA3
	GPIOA->MODER |= (1<<7);
	GPIOA->MODER &= (~(1<<6));
	GPIOA->AFR[0] &= (~(1<<15));
	GPIOA->AFR[0] |= (1<<14) | (1<<13) | (1<<12);

	RCC->APB1ENR |= (1<<17);

	USART2->BRR = (16000000/baudrate); // 16MHz internal oscillator

	USART2->CR1 |= (1<<3);
	USART2->CR1 |= (1<<13);

	while(1){
		while(!(USART2->SR & (1<<7))){		}; // Wait till buffer register gets empty
		USART2->DR = '0';
	}

	return 0;
}
