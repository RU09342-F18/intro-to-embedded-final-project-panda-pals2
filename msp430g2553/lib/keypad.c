/**
 * @file keypad.c
 * @author John McAvoy
 * @date 11 Dec 2018
 * @desc provides functions related to reading the keypad inputs
 */

#include <msp430.h>
#include <stdio.h>
#include "keypad.h"
#include "security.h"
#include "uart.h"
#include "Key.h"

/**
 * @func setup_keypad_pins
 * @desc initializes the appropriate I/O pins for reading the keypad
 */
void setup_keypad_pins() {
    // configure pins to I/O mode
    P1SEL &= ~(P1KEYS);
    P1SEL2 &= ~(P1KEYS);
    P1REN &= ~(P1KEYS);

    P2SEL &= ~(P2KEYS);
    P2SEL2 &= ~(P2KEYS);
    P2REN &= ~(P2KEYS);

    // configure pins to inputs
    P1DIR &= ~(P1KEYS);
    P2DIR &= ~(P2KEYS);

    // interrupt on low-to-high
    P1IES &= ~(P1KEYS);
    P2IES &= ~(P2KEYS);

    // enables KF interrupt
    P1IE |= (P1KEYS);
    P2IE |= (P2KEYS);
}

/**
 * @func clear_key_interupt_flags
 * @desc clears keypad port interrupt flags
 */
void clear_key_interupt_flags() {
    P1IFG &= ~(P1KEYS);
    P2IFG &= ~(P2KEYS);
}

/**
 * @func get_key_pressed
 * @desc determines the pressed key based on A3..A0 pins
 * @returns Key enum corresponding to the key pressed
 */
Key get_key_pressed() {

    if(P1IN & A9) return KEY_9;
    if(P2IN & A8) return KEY_8;
    if(P2IN & A7) return KEY_7;
    if(P2IN & A6) return KEY_6;
    if(P2IN & A5) return KEY_5;
    if(P2IN & A4) return KEY_4;
    if(P1IN & A3) return KEY_3;
    if(P1IN & A2) return KEY_2;
    if(P1IN & A1) return KEY_1;
    if(P1IN & A0) return KEY_0;
    return KEY_ERR; // default
}

static Key combination_in[PASSCODE_LENGTH];
static uint8_t in_counter = 0;

void handle_key_press() {
    Key key_in = get_key_pressed();
    if(key_in != KEY_ERR){
        combination_in[in_counter++] = key_in;
        send_combination_in();
        if (in_counter == PASSCODE_LENGTH) {
            handle_combiation(combination_in);
            in_counter = 0;
        }
    }
}

void send_combination_in() {
    const char buffer_size = (in_counter * 2 ); // 1-2-3-4
    char buffer[buffer_size];

    for(uint8_t i = 0; i < in_counter; i++) {
        buffer[i*2] = key2Char(combination_in[i]);
    }
    for(uint8_t i = 0; i < in_counter / 2; i++) {
        buffer[i*2+1] = '-';
    }

    buffer[buffer_size - 1] = '\n';
    send_bytes(buffer, buffer_size);
}
