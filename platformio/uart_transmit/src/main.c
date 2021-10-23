#include "stm32f4xx.h"
#include "myuart.h"


int main(void)
{
    USART2_init();          /* initialize USART2 */

    while(1)                /* Loop forever */
    {
        USART2_write('Y');
        USART2_write('e');
        USART2_write('s');
        my_delay(628);
    }
}
