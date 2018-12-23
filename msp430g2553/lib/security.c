/**
 * @file security.c
 * @author John McAvoy
 * @date 11 Dec 2018
 * @desc provides security function logic for keylock
 */

#define DEBUG 1
#ifdef DEBUG
#include    <stdio.h>
#include    "uart.h"
#endif

#include "security.h"
#include "Key.h"


Key passcode[PASSCODE_LENGTH] = { KEY_1, KEY_2, KEY_3, KEY_4 }; // initial passcode: 1-2-3-4
Key input_buffer[PASSCODE_LENGTH] = { KEY_ERR, KEY_ERR, KEY_ERR, KEY_ERR }; // holds input keys

uint8_t input_counter = 0; // tracks input count

/**
 * @func setup_lock_pins
 * @desc initializes I/O pins for handling the lock/unlock
 */
void setup_lock_pins() {

    // configure pins to I/O mode
    P2SEL &= ~(LOCKED + UNLOCKED);
    P2SEL2 &= ~(LOCKED + UNLOCKED);

    // configure pins to outputs
    P2DIR |= LOCKED + UNLOCKED;

    lock();
}

/**
 * @func setup_timeout_timer
 * @desc initializes the timeout timer
 */
void setup_timeout_timer() {
    CCTL0 = CCIE;
    TACTL = TASSEL_2 + MC_1 + TACLR;    //ACLK, up mode, clear
    CCR0 = 3200;
}

/**
 * @func setup_timeout_timer
 * @desc sets the new passcod* @param new_passcode - Key array of new passcode sequence
 */
void set_passcode(Key new_passcode[]) {
    for(uint8_t i = 0 ; i < PASSCODE_LENGTH; i++) {
        passcode[i] = new_passcode[i];
    }
}

/**
 * @func lock
 * @desc sets the state to locked
 */
void lock() {
    P2OUT &= ~UNLOCKED;
    P2OUT |= LOCKED;
}

/**
 * @func lock
 * @desc sets the state to unlocked
 */
void unlock() {
    P2OUT &= ~LOCKED;
    P2OUT |= UNLOCKED;
}

/**
 * @func start_timeout_timer
 * @desc starts the timeout timer
 */
void start_timeout_timer() {
    TA0CTL = MC_2; // continuous mode
    P2OUT |= TIMEOUT; // turn on timeout LED
}

/**
 * @func stop_timeout_timer
 * @desc stops the timeout timer
 */
void stop_timeout_timer() {
    TA0CTL = MC_0; // halt
    TAR = 0; // clear timer
}

/**
 * @func handle_combiation
 * @desc takes in the entered combination and handles appropriate response
 * @param combination - Key array of the entered combination
 */
void handle_combiation(Key combination[]) {
    uint8_t passcode_entered = 1; // true
    for(uint8_t i = 0; i < PASSCODE_LENGTH; i++) {
        if(combination[i] != passcode[i])
            passcode_entered = 0; // false
    }

    if(passcode_entered)
        unlock();
    else
        lock();

    start_timeout_timer();
}
