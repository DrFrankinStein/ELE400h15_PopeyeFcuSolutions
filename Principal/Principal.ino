#include "adc.h"
#include "Led.h"

float value;

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  setupADC(12);
  setupLED();
  resetLED(PIN_POWER);
  resetLED(PIN_CONNEXION);
  resetLED(PIN_ERROR);
  delay(1000);
  setLED(PIN_POWER);
  delay(1000);
  setLED(PIN_CONNEXION);
  delay(1000);
  setLED(PIN_ERROR);
  delay(1000);
  resetLED(PIN_POWER);
  resetLED(PIN_CONNEXION);
  resetLED(PIN_ERROR);
  value=0;
  
}

void loop() 
{
  // put your main code here, to run repeatedly:
  value = readLevierInteger();
  /*resetLED(PIN_POWER);
  resetLED(PIN_CONNEXION);
  resetLED(PIN_ERROR);
  if(value>30)
    setLED(PIN_POWER);
  if(value>60)
    setLED(PIN_CONNEXION);
  if(value>90)
    setLED(PIN_ERROR);*/
    
    Serial.println(value);
    delay(100);
}
