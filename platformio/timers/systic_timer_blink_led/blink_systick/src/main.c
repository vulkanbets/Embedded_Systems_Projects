#include "stm32f4xx.h"

int main(void)
{
    // !!!enable GPIOA clock!!!
    // 
    // Bit 0 GPIOAEN: IO port A clock enable
    // This bit is set and cleared by software.
    // 0: IO port A clock disabled
    // 1: IO port A clock enabled
    // 
    RCC->AHB1ENR |=  1;

    // !!!clear pin mode!!!
    // 
    // Set Pin 5 MODER bits "11" and "10" to "1" and "1"
    // (Reset) but leave all other bits untouched
    // PINA5 is the onboard Green LED
    // on the nucleo board
    // 
    GPIOA->MODER &= ~0x00000C00;


    // !!!set pin to output mode!!!
    // 
    // 
    // 
    // 
    GPIOA->MODER |=  0x00000400;    


    /* Configure SysTick */
    SysTick->LOAD = 0xFFFFFF;       /* reload with max value */
    SysTick->CTRL = 5;              /* enable it, no interrupt, use system clock */


    while (1)
    {
        /* take bit 23 of SysTick current value and shift it to bit 5 then write it to PortA */
        GPIOA->ODR = (SysTick->VAL >> (23 - 5)) & 0x00000020;
    }
}
