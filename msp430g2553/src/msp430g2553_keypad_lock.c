/**
 * @file msp430g2553_keypad_lock.c
 * @author John McAvoy
 * @date 11 Dec 2018
 * @desc main program that uses MSP430 as keypad combinational lock
 */

#include <msp430.h>
#include <stdio.h>
#include "../lib/keypad.h" // setup_keypad_pins, handle_keypress
#include "../lib/security.h" // setup_lock_pins, setup_timeout_timer, lock
#include "../lib/uart.h" // setup_uart

int main(void)
{

  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer

  setup_lock_pins();
  setup_keypad_pins();
  setup_timeout_timer();
  setup_uart();

  char welcome_message[27] = "Keypad Lock - John McAvoy\n\n";
  send_bytes(welcome_message, 27);

  __bis_SR_register(GIE);       // enable interrupts
}

// Timer A0 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer0_A1 (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_A1_VECTOR))) Timer0_A1 (void)
#else
#error Compiler not supported!
#endif
{
    stop_timeout_timer();
    lock(); // lock
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
}

// Port 1 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(PORT1_VECTOR))) Port_1 (void)
#else
#error Compiler not supported!
#endif
{
    handle_key_press();
    clear_key_interupt_flags();
}

// Port 2 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(PORT2_VECTOR))) Port_2 (void)
#else
#error Compiler not supported!
#endif
{
    handle_key_press();
    clear_key_interupt_flags();
}
