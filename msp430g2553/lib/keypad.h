/**
 * @file keypad.h
 * @author John McAvoy
 * @date 11 Dec 2018
 * @desc provides functions related to reading the keypad inputs
 */

#ifndef KEYPAD_H
#define KEYPAD_H

#include <msp430.h>
#include "Key.h"

#define A0 ( 1 << 0 ) // P1.0
#define A1 ( 1 << 3 ) // P1.3
#define A2 ( 1 << 4 ) // P1.4
#define A3 ( 1 << 5 ) // P1.5
#define A9 ( 1 << 7 ) // P1.7

#define A4 ( 1 << 0 ) // P2.0
#define A5 ( 1 << 2 ) // P2.1
#define A6 ( 1 << 1 ) // P2.2
#define A7 ( 1 << 6 ) // P2.6
#define A8 ( 1 << 7 ) // P2.7

#define P1KEYS ( A0 | A1 | A2 | A3 | A9 )
#define P2KEYS ( A4 | A5 | A6 | A7 | A8 )
/**
 * @func setup_keypad_pins
 * @desc initializes the appropriate I/O pins for reading the keypad
 */
void setup_keypad_pins();

/**
 * @func clear_key_interupt_flags
 * @desc clears keypad port interrupt flags
 */
void clear_key_interupt_flags();


/**
 * @func get_key_pressed
 * @desc determines the pressed key based on A3..A0 pins
 * @returns Key enum corresponding to the key pressed
 */
Key get_key_pressed();

/**
 * @func handle_key_press
 * @desc handles reading the combination endetered
 */
void handle_key_press();

/**
 * @func send_combination_in
 * @desc sends current combination enter via uart
 */
void send_combination_in();
#endif // KEYPAD_H
