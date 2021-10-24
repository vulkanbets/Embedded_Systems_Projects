#include "stm32f4xx.h"

// Program to toggle Green LED at
// an interval of 1Hz. Uses SysTick
// timer to issue interrupts and toggle
// Internal clock runs at 16_MHz by defualt

int main(void)
{
    // Global Disable IRQs
    __disable_irq();

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
    // Set Pin 5 MODER bits "11" and "10" to "0" and "1"
    // (General Purpose Output Mode) but leave all
    // other bits untouched PIN_A5 is the onboard Green
    // LED on the nucleo board
    // 
    GPIOA->MODER |=  0x00000400;


    /* !!!Configure SysTick!!! */
    // reload with number of clocks per second
    // Set SysTick Reload Value Rgister
    SysTick->LOAD = (16000000 - 1);

    // Set initial value of the SysTick countdown register
    SysTick->VAL = 0;

    // enable SysTick interrupt, use system clock
    SysTick->CTRL = 7;

    // Global Enable IRQs
    __enable_irq();

    while(1)
        { ; }
}

void SysTick_Handler(void)
{
    // Toggle LED
    GPIOA->ODR ^= 0x00000020;
}
