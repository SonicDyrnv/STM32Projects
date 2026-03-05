#include "stm32f446xx.h"

volatile int flag=0;

void delay(long l)
{
	while(l--);
}
void blinkLED()
{
	GPIOA->ODR |= (1<<5);
	delay(500000);
	GPIOA->ODR &= (~(1<<5));
	delay(500000);
}

void EXTI15_10_IRQHandler()
{
	delay(5000); // Debounce delay
	if(EXTI->PR & 1<<13)
	{
		EXTI->PR = (1<<13); // Clearing
		if(!flag){flag = 1;}
		else if(flag){flag = 0;}
		delay(5);
	}

}

int main()
{
	// Turns on clock
	RCC->CR = RCC->CR | (1<<0);
	// Turns on clock for GPIOA, Enable clock for GPIOC
	RCC->AHB1ENR = RCC->AHB1ENR | (1<<0) | (1<<2);
	// Sets The pin connected to inbuilt LED to output mode
	GPIOA->MODER |= (1<<10);
	GPIOA->MODER &= ~(1<<11);
	// Its software based output writing.
	GPIOA->OTYPER = 0x0000;
	// Decides speed, since we are blinking LED low is also good.
	GPIOA->OSPEEDR = 0x00000000;
	// Enable the mask bit
	EXTI->IMR |= (1<<13);
	// Trigger config
	EXTI->RTSR |= (1<<13);
	EXTI->FTSR |= (1<<13);
	// Enable clock for sysconfig controller
	RCC->APB2ENR |= (1<<14);
	// Select the source of i/p for RXTI
	SYSCFG->EXTICR[3] |= (2<<4);
	// Enable interrupt
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	// Set the priority of interrupt
	NVIC_SetPriority(EXTI15_10_IRQn,15);

	while(1)
	{
		if(flag)
		{
			blinkLED(); // Blink LED
		}else{
			GPIOA->ODR &= (~(1<<5));   // LED OFF
		}
	}
	return 0;
}
