#ifndef _UART_2_CONTROLLER_H
#define _UART_2_CONTROLLER_H

#include <stdint.h>
#include "uart_2_driver.h"
#include "timer.h"

/**
 * Sets the timeout period for expecting a string to occur
 */
void uart_2_controller_set_timeout(uint32_t timeout);

void uart_2_controller_send_string(char * string, uint8_t length);

bool uart_2_controller_receive_string(char* string);

#endif // _UART_2_CONTROLLER_H
