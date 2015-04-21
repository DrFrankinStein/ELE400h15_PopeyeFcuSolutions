#include "Moteur.h"

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  moteurSetup();
}

void loop() 
{
  // put your main code here, to run repeatedly:
   /*unsigned long time = micros()-micros();
   
   digitalWrite(6,LOW);
   for(long i=0; i<51200; i++)
   {
      digitalWrite(7,HIGH);
      delayMicroseconds(10);
      digitalWrite(7,LOW);
     
     //SET(PORTC, 23);
     //CLR(PORTC, 23) ; 
   }
   
   //digitalWrite(6,HIGH);
   delay(2000);
   for(long i=0; i<51200; i++)
   {
      digitalWrite(7,HIGH);
      delayMicroseconds(10);
      digitalWrite(7,LOW);
     
     //SET(PORTC, 23);
     //CLR(PORTC, 23) ; 
   }
   //tourneMoteur(0, 0); 
   delay(2000);
   Serial.println(time);  */
   
   //moteurTourne(360, CW);
   moteurGoToAngle(0);
   delay(1000);
   moteurGoToAngle(60);
   delay(1000);
   moteurGoToAngle(120);
   delay(1000);
   moteurGoToAngle(180);
   delay(1000); 
}
