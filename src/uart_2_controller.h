#ifndef _UART_2_CONTROLLER_H
#define _UART_2_CONTROLLER_H

#include <stdint.h>
#include "uart_2_driver.h"

void uart_2_controller_send_string(char * string, uint8_t length);

#endif // _UART_2_CONTROLLER_H
