//#include <clavier.h>
#include <Keypad.h>
//#include "lcd.h"

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','m'},
  {'4','5','6','o'},
  {'7','8','9','s'},
  {'g','0','d','e'}
};
byte rowPins[ROWS] = {26, 27, 28, 29}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {30, 31, 32, 33};  //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
  //kpSetup();
}

void loop(){
  char key = keypad.getKey();
   //char key = kpGetValue();
   
  delay(100);
  Serial.println(key);
 // Serial.print("TEST");
  
  if (key != NO_KEY){
    Serial.println(key);
  }
}


