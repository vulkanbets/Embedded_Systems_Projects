#ifndef MYUART_H
#define MYUART_H

//  Register Name   |   Register Function   |   Register Address Offset(Hex)
// ---------------------------------------------------------------------------
//  USART_SR            Status Register                 0000
//  USART_DR            Data Register                   0004
//  USART_BRR           Baud Rate Register              0008
//  USART_CR1           Control Register 1              000C
//  USART_CR2           Control register 2              0010
//  USART_CR3           Control Register 3              0014


void USART2_init(void)
{
    RCC->AHB1ENR |= 1;          /* Enable GPIOA clock */
    
    RCC->APB1ENR |= 0x20000;    /* Enable USART2 clock */

    /* Configure PA2 for USART2_TX */
    GPIOA->AFR[0] &= ~0x0F00;
    GPIOA->AFR[0] |=  0x0700;   /* alt7 for USART2 */
    GPIOA->MODER  &= ~0x0030;
    GPIOA->MODER  |=  0x0020;   /* enable alternate function for PA2 */

    USART2->BRR = 0x0683;       /* 9600 baud @ 16 MHz */
    USART2->CR1 = 0x0008;       /* enable Tx, 8-bit data */
    USART2->CR2 = 0x0000;       /* 1 stop bit */
    USART2->CR3 = 0x0000;       /* no flow control */
    USART2->CR1 |= 0x2000;      /* enable USART2 */
}


/* Write a character to USART2 */
void USART2_write(int ch)
{
    while ( !(USART2->SR & 0x0080) ) {}   // wait until Tx buffer empty
    USART2->DR = (ch & 0xFF);
}


// My own delay function
void my_delay(int n)
{
    int i;
    for (; n > 0; n--)
        for (i = 0; i < 3195; i++) __NOP();
}


#endif // MYUART_H
