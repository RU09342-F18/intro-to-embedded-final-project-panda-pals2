/**
 * @file timer_test.c
 * @author John McAvoy
 * @date 11 Dec 2018
 * @desc test program for timeout_timer
 */

#include <msp430.h>
#include <stdio.h>
#include "../../lib/security.h"
#include "../../lib/uart.h"

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  setup_uart();
  setup_lock_pins();
  setup_timeout_timer();

  char start_message[12] = "Timer Test\n";
  send_bytes(start_message, 12);

  start_timeout_timer();

  //__no_operation();
  while(1){
      __bis_SR_register(GIE);       // enable interrupts
  }

}

// Timer A0 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) Timer_A (void)
#else
#error Compiler not supported!
#endif
{
    char message[13] = "Timer Reached";
    send_bytes(message, 13);
}
