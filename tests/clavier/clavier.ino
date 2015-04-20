#include "Keypad.h"
#include "Clavier.h"
#include "lcd.h"

void setup()
{
    Serial.begin(9600);
    lcdInit();
}

void loop()
{
    char key = kpGetValue();
    const char *cckey = &key;

    if (key != NO_KEY){
        Serial.println(key);
        lcdClrScr();
        lcdWriteStringAtPosition(0, 0, cckey);
    }

    delay(100);
}
