#include "uart_2_controller.h"

volatile static uint32_t timeout_period = 0;

void uart_2_controller_set_timeout(uint32_t timeout)
{
    timeout_period = timeout;   
}

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

bool uart_2_controller_receive_string(char* string)
{
    char* tmp_string = string;
    char rec_char = '\0';
    uint8_t i = 0;
    uint32_t start_time = millis();
    uint32_t now_time = 0;
    bool is_empty = false;

    do
    {   
        do 
        {
            is_empty = uart_2_driver_rx_buff_is_empty();
            now_time = millis();
            if ((true == is_empty) && (timeout_period < (now_time - start_time)))
            {
                return false;
            }
        } while (true == is_empty);
        
        rec_char = uart_2_driver_get_rx_reg();
        *tmp_string++ = rec_char;
    } while ('\0' != rec_char);

    return true;
}
