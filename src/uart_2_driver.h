/**
 * @file        uart_2_driver.h
 * @author      Steven Daglish
 * @brief       Contains the interface for uart2 for PIC24FJ64GA204 
 * @version     0.1
 * @date        23 July 2019
 *
 * @copyright Copyright (c) 2019
 *
 * \remove      Split tx_reg address saving into seperate function.
 * \todo        Add a function to change the baud_rate.
 * \todo        Add functions to enable and disable RX and TX
 * \done        Add function to read data from RXREG
 * \done        Add function to check if RXREG has data or is empty
 * \remove      Add function to provide address of RXREG
 */

#ifndef _UART_2_DRIVER_H
#define _UART_2_DRIVER_H

// #include <xc.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief   Creates and initialises the uart module with a fixed BR
 *
 */
void uart_2_driver_init();

/**
 * Adds char to TXREG
 * @param c Char to be sent
 * @warning No checks made to see if there is space in the TX buffer or not!
 */
void uart_2_driver_put_c(uint8_t c);

bool uart_2_driver_tx_buff_is_full(void);

/**
 * Returns the value of rxreg
 * @return  [description]
 *
 * Will return 0x00 if the rx buffer is empty
 */
uint8_t uart_2_driver_get_rx_reg(void);

/**
 * Returns if the RX buffer is empty, or if there is data to be read.
 * @return  True = RX buffer is empty
 */
bool uart_2_driver_rx_buff_is_empty(void);

bool uart_2_driver_tx_reg_is_empty(void);

#endif // _UART_2_DRIVER_H
