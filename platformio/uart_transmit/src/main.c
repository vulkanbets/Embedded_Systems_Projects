#include "stm32f4xx.h"
#include "myuart.h"


int main(void)
{
    USART2_init(); /* initialize USART2 */

    // Super loop
    while(1)
    {
        USART2_write('Y');
        USART2_write('e');
        USART2_write('s');
        USART2_write('\n');
        my_delay(700);
    }
}
