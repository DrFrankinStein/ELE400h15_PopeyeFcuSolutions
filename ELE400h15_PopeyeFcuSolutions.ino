#include "adc.h"
#include "lcd.h"

float value;
float valuetmp;

void setup()
{
    // debug port init
    Serial.begin(9600);
    Serial.println("init");

    // adc init
    setupADC(12);

    // lcd init
    lcdInit();
    lcdWriteString("init");
}

float getAngle()
{
    float val;
    int valuesum = 0;

    for(int i=0; i<1000; ++i)
        valuesum += readLevierInteger();

    valuesum /= 1000;

    val = valuesum * (180.0/4089.0);

    return val;
}

void loop()
{
    char str[10];

    valuetmp = getAngle();

    if(valuetmp != value)
    {
        value = valuetmp;
        Serial.println(value);

        lcdClrScr();
        sprintf(str, "%f", value);
        lcdWriteString(str);
    }

    delay(100);
}
