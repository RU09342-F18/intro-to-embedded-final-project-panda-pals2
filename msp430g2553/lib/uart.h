// uart.h

#ifndef UART_H
#define UART_H

#include <msp430.h>
#include <stdint.h>

void setup_uart();

void send_bytes(char *bytes, uint8_t length);

#endif // UART_H
