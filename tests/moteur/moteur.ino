#include <Moteur.h>

void setup()
{
  setupMoteur();
}

void loop() 
{
  while(true)
    tourneMoteur(143, CCW);
}


