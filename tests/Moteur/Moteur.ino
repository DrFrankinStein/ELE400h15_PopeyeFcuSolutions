//#include "Moteur.h"

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(7, OUTPUT);
}

void loop() 
{
  // put your main code here, to run repeatedly:
   unsigned long time = micros();
   for(long i=0; i<1000000; i++)
   {
      digitalWrite(7,HIGH);
      digitalWrite(7,LOW); 
   }
   unsigned long afterTime = micros();
   Serial.println(afterTime-time);  
  
}
