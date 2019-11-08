#include "uart_2_controller.h"

#define TX_BUF_SIZE     32
#define RX_BUF_SIZE     32

volatile static uint32_t timeout_period = 0;
static circular_buf_t tx_cir_buf;
static uint8_t tx_buf_array[TX_BUF_SIZE];
static circular_buf_t* p_tx_cir_buf = &tx_cir_buf;

static circular_buf_t rx_cir_buf;
static uint8_t rx_buf_array[RX_BUF_SIZE];
static circular_buf_t* p_rx_cir_buf = &rx_cir_buf;


static bool millis_overrun(uint32_t old_time, uint32_t new_time)
{
    if (new_time < old_time)
    {
        return true;
    }
    return false;
}

void uart_2_controller_init(void)
{
    p_tx_cir_buf = circular_buf_create(TX_BUF_SIZE, tx_buf_array, p_tx_cir_buf);
    p_rx_cir_buf = circular_buf_create(RX_BUF_SIZE, rx_buf_array, p_rx_cir_buf);
}

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
    uint32_t time_diff = 0;

    do
    {   
        do 
        {
            is_empty = uart_2_driver_rx_buff_is_empty();
            now_time = millis();
            if (true == millis_overrun(start_time, now_time))
            {
                time_diff = (0xffffffff - start_time) + now_time;
            }
            else
            {
                time_diff = now_time - start_time;
            }

            if ((true == is_empty) && (timeout_period < time_diff))
            {
                return false;
            }
        } while (true == is_empty);
        
        rec_char = uart_2_driver_get_rx_reg();
        *tmp_string++ = rec_char;
    } while ('\0' != rec_char);

    return true;
}

bool uart_2_controller_add_char_to_cir_buf(char c)
{
    bool buf_full = circular_buf_is_full(&tx_cir_buf);
    if (true == buf_full)
    {
        return false;
    }
    bool success = circular_buf_add(&tx_cir_buf, c); 
    return success;
}

bool uart_2_controller_update_tx(void)
{
    if (true == circular_buf_is_empty(&tx_cir_buf))
    {
        return false;
    }
    if (true == uart_2_driver_tx_buff_is_full())
    {
        return false;
    }
    uint8_t c = circular_buf_get(&tx_cir_buf);
    uart_2_driver_put_c(c);

    return true;
}

bool uart_2_controller_update_rx(void)
{
    if (true == uart_2_driver_rx_buff_is_empty())
    {
        return false;
    }
    if (true == circular_buf_is_full(p_rx_cir_buf))
    {
        return false;
    }
    uint8_t c = uart_2_driver_get_rx_reg();
    circular_buf_add(p_rx_cir_buf, c);
    return true;
}

uint8_t uart_2_controller_read_cir_buf_char(void)
{
    if (true == circular_buf_is_empty(p_rx_cir_buf))
    {
        return 0;
    }
    uint8_t c = circular_buf_get(p_rx_cir_buf);
    return c;
}


uint8_t uart_2_controller_rx_buf_size(void)
{
    return circular_buf_size(p_rx_cir_buf);
}

uint8_t uart_2_controller_tx_buf_size(void)
{
    return circular_buf_size(p_tx_cir_buf);
}


