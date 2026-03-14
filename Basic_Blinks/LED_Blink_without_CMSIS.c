#include <stdio.h>
#include <stdint.h>

void delay(long t)
{
	while(t--);
}
/*
int main()
{
	unsigned int *RCC_CR =(unsigned int *) 0x40023800;

	unsigned int *RCC_AHB1ENR =(unsigned int *) 0x40023830;

	unsigned int *GPIOA_MODER =(unsigned int *) 0x40020000;

	unsigned int *GPIOA_TYPER =(unsigned int *) 0x40020004;

	unsigned int *GPIOA_SPEEDR =(unsigned int *) 0x40020008;

	unsigned int *GPIOA_ODR =(unsigned int *) 0x40020014;

	*RCC_CR = 0x00000001;

	*RCC_AHB1ENR = 0x00000001;

	*GPIOA_MODER = 0x00000400;

	*GPIOA_TYPER = 0x0000;

	*GPIOA_SPEEDR = 0x00000000;

	while(1)
	{
		*GPIOA_ODR = 0x0020;
		delay(500000);
		*GPIOA_ODR = 0x0000;
		delay(500000);
	}
	return 0;
}
*/

/**
typedef struct
{
	uint32_t MODER;
	uint32_t OTYPER;
	uint32_t OSPEEDER;
	uint32_t PUPDR;
	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSRR;
	uint32_t LCKR;
	uint32_t AFRL;
	uint32_t AFRH;
}GPIO_Def;

typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t PLLCFGR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t AHB1RSTR;
	volatile uint32_t AHB2RSTR;
	volatile uint32_t AHB3RSTR;
	uint32_t RESERVED0;
	volatile uint32_t APB1RSTR;
	volatile uint32_t APB2RSTR;
	uint32_t RESERVED1[2];
	volatile uint32_t AHB1ENR;
	volatile uint32_t AHB2ENR;
	volatile uint32_t AHB3ENR;
	uint32_t RESERVED2;
	volatile uint32_t APB1ENR;
	volatile uint32_t APB2ENR;
	uint32_t RESERVED3[2];
	volatile uint32_t AHB1LPENR;
	volatile uint32_t AHB2LPENR;
	volatile uint32_t AHB3LPENR;
	uint32_t RESERVED4;
	volatile uint32_t APB1LPENR;
	volatile uint32_t APB2LPENR;
	uint32_t RESERVED5[2];
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	uint32_t RESERVED6[2];
	volatile uint32_t SSCGR;
	volatile uint32_t PLLI2SCFGR;
}RCC_Def;


GPIO_Def *GPIOA = (GPIO_Def *)0x40020000;
RCC_Def *RCCA = (RCC_Def *)0x40023800;

**/

#include "STM32F446RE_GPIO"
#include "STM32F446RE_CLOCK"

int main()
{

		RCCA->CR = RCCA->CR | (1<<0);

		RCCA->AHB1ENR = RCCA->AHB1ENR | (1<<0);

		GPIOA->MODER = GPIOA->MODER | (1<<10);

		GPIOA->OTYPER = 0x0000;

		GPIOA->OSPEEDER = 0x00000000;

		while(1)
		{
			GPIOA->ODR = GPIOA->ODR | (1<<5);
			delay(500000);
			GPIOA->ODR = GPIOA->ODR & (~(1<<5));
			delay(500000);
		}
		return 0;
}
