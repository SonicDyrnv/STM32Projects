/* This code recieves one ASCII character through USART
 * and returns next ASCII Character, its circular in nature
 * and if ASCII values goes out of the value then code returns
 * 0 through tx of USART, basically this code can be used for
 * easy-low level encoding.
 */

#include "stm32f446xx.h"

#define baudrate 9600
char d;

void USART2write(char c){
	while(!(USART2->SR & (1<<7))){		};
	USART2->DR = c;
}

char USART2read(void){
	return USART2->DR;
}

int main(){

	// I can see PA2 & PA3(On nucleo board otherwise chip supports
	// other pins also) supporting USART2
	// I can easily get USART2, other USART will require some
	// bridge to get output according to datasheet

	// clock startings
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

	// Giving clock to peripherals specifically USART2
	RCC->APB1ENR |= (1<<17);

	// Baudrate setting
	USART2->BRR = (16000000/baudrate); // 16MHz internal oscillator

	// Controll registers
	USART2->CR1 |= (1<<3) | (1<<2);
	USART2->CR1 |= (1<<13);

	while(1){
		while(!(USART2->SR & (1<<5))){ };
		d = USART2read();
		if(d=='Z'){
			USART2write('A');
		}else if(d>'Z'){
			USART2write('0');
		}else if(d<'A'){
			USART2write('0');
		}else{
			USART2write(d+1);
		}
	}

	return 0;
}
