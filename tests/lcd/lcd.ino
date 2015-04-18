#include "lcd.h"

unsigned int x,y;
unsigned long previousMillis=0;
unsigned int interval=1000;

void setup() {
  Serial.begin(9600);
  lcdInit();
  
  lcdDisplayBaudrate();
  delay(3000);
  
  lcdClrScr();
  lcdWriteStringAtPosition(0, 0, "********************");
  lcdWriteStringAtPosition(1, 0, "*      POPEYE      *");
  lcdWriteStringAtPosition(2, 0, "*   FCU SOLUTIONS  *");
  lcdWriteStringAtPosition(3, 0, "********************");
  delay(3000);
  
  lcdClrScr();
  lcdWriteStringAtPosition(0, 0, "Kops = -");
  lcdWriteStringAtPosition(1, 0, "Secondes = -");
  lcdWriteStringAtPosition(2, 0, "--------------------");
  lcdWriteStringAtPosition(3, 0, "Kops/s = -");
  delay(1000);
  
  x=0;
  y=0;
}

void loop() {
  //delay(1);
  char tmp[50];
  unsigned long currentMillis = millis();
  
  //Mise à jour de l'affichage
  if((currentMillis-previousMillis)>interval)
  {
    //Mise à jour du compteur
    previousMillis=currentMillis;
    
    //Quoi mettre à jour
    lcdWriteFloatAtPosition(0, 7, (float)x/1000.);
    lcdWriteIntegerAtPosition(1, 11, y);
    
    if(y>0)
    {
      lcdWriteFloatAtPosition(3, 9, ((float)x/(float)y)/1000.);
    }
    
    Serial.println(y);     
    y++;
  }
  
  x++;
}


