/**
 * @file msp430g2553_keypad_lock.c
 * @author John McAvoy
 * @date 11 Dec 2018
 * @desc test program for uart.c
 */

#include <msp430.h>
#include <stdio.h>
#include "../../lib/uart.h"

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  setup_uart();

  const char test_message[16] = "UART Testbench";
  send_bytes(test_message, 16);

  __bis_SR_register(GIE);

  while(1) __no_operation();
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCIAB0RX_VECTOR))) USCI0RX_ISR (void)
#else
#error Compiler not supported!
#endif
{
    unsigned char data = UCA0RXBUF;
    unsigned char out_message[15];
    sprintf(out_message, "'%2x' Received\n", data);
    send_bytes(out_message, 15);
}
