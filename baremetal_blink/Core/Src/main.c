#include "stm32f4xx.h"


void delayMs(int n);

int main(void)
{
	RCC->AHB1ENR |= 1;						// Enable GPIOA clock

	GPIOA->MODER &= ~0x00000C00;			// clear pin mode
	GPIOA->MODER |= 0x00000400;				// set pin to output mode

	while(1)
	{
		;
	}

}

