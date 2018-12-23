/**
 * @file security.h
 * @author John McAvoy
 * @date 11 Dec 2018
 * @desc provides security function logic for keylock
 */

#ifndef SECURITY_H
#define SECURITY_H

#include <msp430.h>
#include <stdint.h>
#include "Key.h"

#define UNLOCKED ( 1 << 3 ) // P2.3
#define TIMEOUT  ( 1 << 4 ) // P2.1
#define LOCKED   ( 1 << 5 ) // P2.5
#define PASSCODE_LENGTH 4

/**
 * @func setup_lock_pins
 * @desc initializes I/O pins for handling the lock/unlock
 */
void setup_lock_pins();

/**
 * @func setup_timeout_timer
 * @desc initializes the 3s timeout timer
 */
void setup_timeout_timer();

/**
 * @func setup_timeout_timer
 * @desc sets the new passcode
 * @param new_passcode - Key array of new passcode sequence
 */
void set_passcode(Key new_passcode[]);

/**
 * @func lock
 * @desc sets the state to locked
 */
void lock();

/**
 * @func lock
 * @desc sets the state to unlocked
 */
void unlock();

/**
 * @func start_timeout_timer
 * @desc starts the timeout timer
 */
void start_timeout_timer();

/**
 * @func stop_timeout_timer
 * @desc stops the timeout timer
 */
void stop_timeout_timer();

/**
 * @func handle_combiation
 * @desc takes in the entered combination and handles appropriate response
 * @param combination - Key array of the entered combination
 */
void handle_combiation(Key combination[]);

#endif // SECURITY_H
