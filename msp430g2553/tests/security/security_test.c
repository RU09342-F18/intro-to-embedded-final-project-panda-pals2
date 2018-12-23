/**
 * @file security_test.c
 * @author John McAvoy
 * @date 11 Dec 2018
 * @desc test program for security_test.c
 */

#include <msp430.h>
#include <stdio.h>
#include "../../lib/Key.h"
#include "../../lib/security.h"
#include "../../lib/uart.h"

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  setup_uart();
  setup_lock_pins();

  char start_message[25] = "Start of Security Test\n";
  send_bytes(start_message, 20);

  char locking_message[13] = "Locking Test\n";
  send_bytes(locking_message, 13);

  // locking test
  char unlock_message[7] = "Unlock\n";
  send_bytes(unlock_message, 7);
  unlock();
  __delay_cycles(1000000);
  char lock_message[5] = "Lock\n";
  send_bytes(lock_message, 5);
  lock();

  __delay_cycles(1000000);

  char cc_message[20] = "Correct Combination\n";
  send_bytes(cc_message, 20);
  // correct key combination test
  Key correctCombination[4] = {KEY_0, KEY_1, KEY_3, KEY_4};
  handle_combiation(correctCombination);
  __delay_cycles(1000000);
  send_bytes(lock_message, 5);
  lock();

  __delay_cycles(1000000);

  char bc_message[17] = "Bad Combination\n";
  send_bytes(bc_message, 17);
  // bad key combination test
  Key badCombination[17] = {KEY_5, KEY_3, KEY_2, KEY_0};
  handle_combiation(badCombination);

  __delay_cycles(10000000);
  send_bytes(lock_message, 5);
  lock();

  char nc_message[17] = "New Combination\n";
  send_bytes(nc_message, 17);
  // passcode set test
  Key newCombination[4] = {KEY_7, KEY_8, KEY_9, KEY_1};
  set_passcode(newCombination);
  correctCombination[0] = KEY_7;
  correctCombination[1] = KEY_8;
  correctCombination[2] = KEY_9;
  correctCombination[3] = KEY_1;
  send_bytes(cc_message, 20);
  handle_combiation(correctCombination);
  send_bytes(cc_message, 20);
  __delay_cycles(10000000);
  lock();

  uint8_t end_message[21] = "End of Security Test\n";
  send_bytes(end_message, 21);

}
