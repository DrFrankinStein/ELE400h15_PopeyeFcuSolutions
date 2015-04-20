#include "Keypad.h"
#include "Clavier.h"
#include "lcd.h"

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    char key = kpGetValue();

    if (key != NO_KEY){
        Serial.println(key);
    }

    delay(100);
}
