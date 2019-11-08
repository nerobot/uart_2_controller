#ifndef _UART_2_CONTROLLER_H
#define _UART_2_CONTROLLER_H

#include <stdint.h>
#include "uart_2_driver.h"
#include "timer.h"
#include "circular_buf.h"

void uart_2_controller_init(void);

/**
 * Sets the timeout period for expecting a string to occur
 */
void uart_2_controller_set_timeout(uint32_t timeout);

void uart_2_controller_send_string(char * string, uint8_t length);

bool uart_2_controller_receive_string(char* string);

bool uart_2_controller_add_char_to_cir_buf(char sting);

bool uart_2_controller_update_tx(void);

bool uart_2_controller_update_rx(void);

uint8_t uart_2_controller_read_cir_buf_char(void);

uint8_t uart_2_controller_rx_buf_size(void);

uint8_t uart_2_controller_tx_buf_size(void);

#endif // _UART_2_CONTROLLER_H
