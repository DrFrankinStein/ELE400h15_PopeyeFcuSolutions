#include <Keypad.h>
#include "clavier.h"

Keypad keypad;

void kpSetup(void){
    const byte ROWS = 4; //four rows
    const byte COLS = 4; //three columns
    char keys[ROWS][COLS] = {
        {'1','2','3','m'},
        {'4','5','6','o'},
        {'7','8','9','s'},
        {'g','0','d','e'}
    };
    byte rowPins[ROWS] = {kpPin1, kpPin2, kpPin3, kpPin4}; //connect to the row pinouts of the keypad
    byte colPins[COLS] = {kpPin5, kpPin6, kpPin7, kpPin8}; //connect to the column pinouts of the keypad

    keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
}

char kpGetValue(void){
    char key = keypad.getKey();

    if (key != NO_KEY)
        return key;
    else
        return -1;
}
