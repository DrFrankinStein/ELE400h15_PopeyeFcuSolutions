#include "adc.h"
#include "Led.h"

float value;
int interuptFlag = 0;

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  setupADC(12);
  /*setupLED();
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
  resetLED(PIN_ERROR);*/
  value=0;
  
  //Bouton d'urgence
 /* pinMode(53, INPUT);
  attachInterrupt(53, ISR_Emergency, RISING);*/
  
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
    
    // Traitement de l'interruption URGENCE
    /*if(interuptFlag==1)
    {
      unsigned char lu=0;
      Serial.print("URGENCE");
      if (Serial.available() > 0) {
        interuptFlag = 0;
      }
    }*/
      
}

void ISR_Emergency (){
    interuptFlag = 1;
}
