///////////////////////////////////////////////////////////////////////////////
// Library test list
//
//  # Sending a string
//      * calling send_string will cause all bytes to be sent to tx2buf
//      * for each byte sent, tx full will be checked.
//          * if buffer is full, do nothing
//          * if buffer is not full, send byte to buf
//          * if the buffer is full keep checking to see if it is empty until it is
//      * when sending string, will check if buffer is empty
//          * if it is empty, return
//          * if it is not empty, keep checking until it is.
//
//  # Receiving data
//  ## Receive string
//  * when rxbuf has data, save data to array, when byte is '\0' added to array and return value - done
//  * when rxbuf is empty, keep checking until there is data available - done
//  * When string is not returned within a given time, return false. - done
//  * Same as above, but millis overflows to 0. - done
//  

#include "unity.h"
#include "uart_2_controller.h"
#include "mock_uart_2_driver.h"
#include "mock_timer.h"
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <xc.h>

volatile uint16_t U2STA; 
volatile U2STABITS U2STAbits;

char string[] = "Hello world/n";
uint8_t string_size = 0;
uint16_t timeout_time = 1000;

void setUp(void)
{
    string_size = strlen(string);
    uart_2_controller_set_timeout(timeout_time);
}

void tearDown(void)
{
}

///////////////////////////////////////////////////////////////////////////////
// Transmitting
//

void test_send_string_will_cause_each_byte_to_be_sent_to_tx2buf(void)
{
    uart_2_driver_tx_buff_is_full_IgnoreAndReturn(false);
    uart_2_driver_tx_reg_is_empty_IgnoreAndReturn(true);

    uint8_t i = 0;
    for (i = 0; i < string_size; i++)
    {
        uart_2_driver_put_c_Expect(string[i]);
    }

    uart_2_controller_send_string(string, string_size);       
}

void test_send_string_will_check_if_the_buffer_is_full_before_sending(void)
{
    uart_2_driver_tx_reg_is_empty_IgnoreAndReturn(true);

    uint8_t i = 0;
    for (i = 0; i < string_size; i++)
    {
        uart_2_driver_tx_buff_is_full_ExpectAndReturn(false);
        uart_2_driver_put_c_Expect(string[i]);
    }

    uart_2_controller_send_string(string, string_size);       
}

void test_send_string_if_buffer_is_full_keep_checking_until_it_is_empty(void)
{
    uart_2_driver_tx_reg_is_empty_IgnoreAndReturn(true);
    uint8_t i = 0;
    uint8_t j = 0;

    for (i = 0; i < string_size; i++)
    {
        for (j = 0; j < 5; j++)
        {
            uart_2_driver_tx_buff_is_full_ExpectAndReturn(true);
        }
        uart_2_driver_tx_buff_is_full_ExpectAndReturn(false);
        uart_2_driver_put_c_Expect(string[i]);
    }

    uart_2_controller_send_string(string, string_size);       
}

void test_send_string_will_return_if_tx_reg_is_empty(void)
{
    uart_2_driver_tx_buff_is_full_IgnoreAndReturn(false);
    uart_2_driver_put_c_Ignore();

    uart_2_driver_tx_reg_is_empty_ExpectAndReturn(true);

    U2STAbits.TRMT = 1;
    uart_2_controller_send_string(string, string_size);   
}

void test_send_string_will_keep_checking_for_tx_reg_to_be_empty_before_returning(void)
{
    uart_2_driver_tx_buff_is_full_IgnoreAndReturn(false);
    uart_2_driver_put_c_Ignore();

    uint8_t i = 0;
    for (i = 0; i < 5; i++)
    {
        U2STAbits.TRMT = 0;
        uart_2_driver_tx_reg_is_empty_ExpectAndReturn(false);
    }
    U2STAbits.TRMT = 1;
    uart_2_driver_tx_reg_is_empty_ExpectAndReturn(true);

    uart_2_controller_send_string(string, string_size);   
}

///////////////////////////////////////////////////////////////////////////////
// # Receiving data
//

///////////////////////////////////////////////////////////////////////////////
// ## Receiving string
//

void test_uart_2_driver_receive_string_all_ok(void)
{
    char expected_string[] = "Hello world\0";
    char received_string[16];
    uint8_t i = 0;
    uint32_t fake_time = 0;
    millis_ExpectAndReturn(fake_time++);

    for (i = 0; i < 12; i++)
    {
        uart_2_driver_rx_buff_is_empty_ExpectAndReturn(false);
        millis_ExpectAndReturn(fake_time++);
        uart_2_driver_get_rx_reg_ExpectAndReturn(expected_string[i]);
    }

    bool success = uart_2_controller_receive_string(received_string);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_string, received_string, 12);
    TEST_ASSERT(success);
}

void test_receive_string_will_keep_checking_if_theres_no_data_in_rxbuf(void)
{
    char expected_string[] = "Hello world\0";
    char received_string[16];
    uint8_t i = 0;
    uint8_t j = 0;
    uint32_t fake_time = 0;
    millis_ExpectAndReturn(fake_time++);

    for (i = 0; i < 12; i++)
    {
        for (j = 0; j < 12; j++)
        {
            uart_2_driver_rx_buff_is_empty_ExpectAndReturn(true);
            millis_ExpectAndReturn(fake_time++);
        }
        
        uart_2_driver_rx_buff_is_empty_ExpectAndReturn(false);
        millis_ExpectAndReturn(fake_time++);
        uart_2_driver_get_rx_reg_ExpectAndReturn(expected_string[i]);
    }
    bool success = uart_2_controller_receive_string(received_string);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_string, received_string, 12);
    TEST_ASSERT(success);
}

void test_receive_string_when_no_string_within_timeout_return_false(void)
{   
    uint8_t i = 0; 
    millis_ExpectAndReturn(0);
    
    for (i = 0; i < 10; i++)
    {
        uart_2_driver_rx_buff_is_empty_ExpectAndReturn(true);
        millis_ExpectAndReturn(i);
    }
    uart_2_driver_rx_buff_is_empty_ExpectAndReturn(true);
    millis_ExpectAndReturn(2000);

    char received_string[16];
    bool success = uart_2_controller_receive_string(received_string);
    TEST_ASSERT_FALSE(success);
}

void test_receive_string_when_no_string_within_timeout_with_millis_overflow_return_false(void)
{   
    uint8_t i = 0; 
    uint32_t fake_timer = 1000;
    millis_ExpectAndReturn(fake_timer++);
    
    for (i = 0; i < 10; i++)
    {
        uart_2_driver_rx_buff_is_empty_ExpectAndReturn(true);
        millis_ExpectAndReturn(fake_timer++);
    }
    uart_2_driver_rx_buff_is_empty_ExpectAndReturn(true);
    millis_ExpectAndReturn(0);

    char received_string[16];
    bool success = uart_2_controller_receive_string(received_string);
    TEST_ASSERT_FALSE(success);
}
