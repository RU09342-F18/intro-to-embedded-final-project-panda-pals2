/**
 * @file key.c
 * @author John McAvoy
 * @date 11 Dec 2018
 * @desc provides Key enum typdef
 */

#include "Key.h"

char key2Char(Key k) {
    switch(k) {
        case KEY_0: return '0';
        case KEY_1: return '1';
        case KEY_2: return '2';
        case KEY_3: return '3';
        case KEY_4: return '4';
        case KEY_5: return '5';
        case KEY_6: return '6';
        case KEY_7: return '7';
        case KEY_8: return '8';
        case KEY_9: return '9';
        case KEY_ERR: return '?';
        default: return '!';
    }
}
