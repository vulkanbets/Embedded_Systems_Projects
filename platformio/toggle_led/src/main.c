#include "stm32f4xx.h"

void mydelay(int n)
{
    for (; n > 0; n--)
    {
        __ASM volatile("NOP");
    }
}

int main(void)
{
    RCC->AHB1ENR |=  1;             /* enable GPIOA clock */
    
    GPIOA->MODER &= ~0x00000C00;    /* clear pin mode */
    GPIOA->MODER |=  0x00000400;    /* set pin to output mode */

    while(1)
    {
        GPIOA->ODR |=  0x00000020;  /* turn on LED */
        mydelay(100000);
        GPIOA->ODR &= ~0x00000020;  /* turn off LED */
        mydelay(100000);
    }
}

