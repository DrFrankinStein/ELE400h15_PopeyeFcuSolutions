#include "adc.h"

float value;
float valuetmp;

void setup()
{
    Serial.begin(9600);
    Serial.println("init");
    setupADC(12);
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
    valuetmp = getAngle();

    if(valuetmp != value)
    {
        value = valuetmp;
        Serial.println(value);
    }

    delay(100);
}
