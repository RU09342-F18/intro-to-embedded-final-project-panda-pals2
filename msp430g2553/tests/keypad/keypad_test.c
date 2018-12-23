/**
 * @file keypad_test.c
 * @author John McAvoy
 * @date 11 Dec 2018
 * @desc test program for keypad.c
 */

#include <msp430.h>
#include <stdio.h>
#include "../../lib/Key.h"
#include "../../lib/keypad.h"
#include "../../lib/uart.h"

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  setup_uart();
  setup_keypad_pins();

  char start_message[12] = "Keypad Test\n";
  send_bytes(start_message, 12);

  char p1_reg = P1IN;
  while(1){
      __bis_SR_register(GIE);       // enable interrupts
  }

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
    char buffer[3];
    sprintf(buffer, "%02d\n", get_key_pressed());
    send_bytes(buffer, 3);
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
    char buffer[3];
    sprintf(buffer, "%02d\n", get_key_pressed());
    send_bytes(buffer, 3);
    clear_key_interupt_flags();
}
