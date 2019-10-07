#include "uart_2_controller.h"

void uart_2_controller_send_string(char * string, uint8_t length)
{
    uint8_t i = 0;
    for (i = 0; i < length; i++)
    {
        do 
        {

        } while (true == uart_2_driver_tx_buff_is_full());
        
        uart_2_driver_put_c(string[i]);
    }

    do
    {

    } while (false == uart_2_driver_tx_reg_is_empty());
}

