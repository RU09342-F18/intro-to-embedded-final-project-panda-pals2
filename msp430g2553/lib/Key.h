/**
 * @file key.h
 * @author John McAvoy
 * @date 11 Dec 2018
 * @desc provides Key enum typdef
 */
#ifndef KEY_H
#define KEY_H

typedef enum Key {
    KEY_0,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_ERR
} Key;

char key2Char(Key k);

#endif // KEY_H
