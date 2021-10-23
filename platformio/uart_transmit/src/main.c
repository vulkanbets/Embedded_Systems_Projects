#include "stm32f4xx.h"
#include "myuart.h"


int main(void)
{
    USART2_init(); /* initialize USART2 */

    // Super loop
    while(1)
    {
        USART2_write('H');
        USART2_write('e');
        USART2_write('l');
        USART2_write('l');
        USART2_write('o');
        USART2_write(' ');
        USART2_write('F');
        USART2_write('r');
        USART2_write('o');
        USART2_write('m');
        USART2_write(' ');
        USART2_write('S');
        USART2_write('T');
        USART2_write('M');
        USART2_write('3');
        USART2_write('2');
        USART2_write('!');
        USART2_write('\n');
        my_delay(700);
    }
}
