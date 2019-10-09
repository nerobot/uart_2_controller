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

void uart_2_controller_receive_string(char* string)
{
    char* tmp_string = string;
    char rec_char = '\0';
    uint8_t i = 0;

    do
    {   
        do 
        {
        } while (false == uart_2_driver_rx_buff_is_empty());

        rec_char = uart_2_driver_get_rx_reg();
        *tmp_string++ = rec_char;
    } while ('\0' != rec_char);
}
