#include "Led.h"

int value = 0;
int interuptFlag = 0;

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  setupLED();
  
  resetLED(PIN_POWER);
  resetLED(PIN_CONNEXION);
  resetLED(PIN_ERROR);
  
  //Bouton d'urgence
  pinMode(53, INPUT);
  attachInterrupt(53, ISR_Emergency, RISING);  
}

void loop() 
{
  // put your main code here, to run repeatedly:
     
    /*Serial.println(value);
        
    setLEDState(DEL_VERTE,(bool)(value>>2 & 1));
    setLEDState(DEL_JAUNE,(bool)(value>>1 & 1));
    setLEDState(DEL_ROUGE,(bool)(value>>0 & 1));
    
    value++;   */
    
    resetLED(DEL_VERTE);
    resetLED(DEL_JAUNE);
    resetLED(DEL_ROUGE);
    //delay(1000);
    
    Serial.println("LED VERTE");
    setLED(DEL_VERTE);
    delay(1000);
    
    Serial.println("LED JAUNE");
    resetLED(DEL_VERTE);
    setLED(DEL_JAUNE);
    delay(1000);
    
    Serial.println("LED ROUGE");
    resetLED(DEL_JAUNE);
    setLED(DEL_ROUGE);
    delay(1000);
    
    /*Serial.println("AUCUNE LED");
    resetLED(DEL_VERTE);
    resetLED(DEL_JAUNE);
    resetLED(DEL_ROUGE);
    delay(1000);*/
    
    Serial.println("TOUTE LED");
    setLED(DEL_VERTE);
    setLED(DEL_JAUNE);
    setLED(DEL_ROUGE);
    delay(1000);
       
    // Traitement de l'interruption URGENCE
    /*if(interuptFlag==1)
    {
      unsigned char lu=0;
      Serial.println("URGENCE");
      for(int i=0; i<5;i++)
      {
        setLED(PIN_POWER);
        setLED(PIN_CONNEXION);
        setLED(PIN_ERROR);
        
        delay(100);
        
        resetLED(PIN_POWER);
        resetLED(PIN_CONNEXION);
        resetLED(PIN_ERROR);
        
        delay(100);
      }
      
        value =0;
      
     // if (Serial.available() > 0) 
     // {
        interuptFlag = 0;
     // }
    }
    
    delay(1000);*/
      
}

void ISR_Emergency (){
    //interuptFlag = 1;
}
