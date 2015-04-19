#include "Led.h"

//Variable pour le temps (previousMillis pour comparaison et interval= temps en ms pour exécuter une action)
//ATTENTION : delay() est une commande qui ralenti le code, on utilise cette alternative pour être plus rapide.
unsigned long previousMillis=0;
unsigned int interval=1000;

//Ajout des variables de flag
int interuptFlag = 0, initFlag =1;

//Définition des états pour ma machine à état
enum Etat {AUCUNE, VERTE, JAUNE, ROUGE, TOUTES}; //{0,1,2,3,4}
Etat etatCourant = AUCUNE;

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  setupLED();
  
  //Bouton d'urgence
  pinMode(53, INPUT);
  
  //Quand on clique sur le bouton, on met le signal à zéro (RISING PEUT ÊTRE CORRECT AUSSI)
  attachInterrupt(53, ISR_Emergency, FALLING);  
}

void loop() 
{
  // put your main code here, to run repeatedly:
   
  //On regarde le temps du système pour faire comparaison
  unsigned long currentMillis = millis();
  
  //Mise à jour des DEL
  if((currentMillis-previousMillis)>interval)
  {
    //Mise à jour du compteur
    previousMillis=currentMillis;
    
    //Quoi mettre à jour
    
    //Machine à état
    switch(etatCourant)
    {
      case AUCUNE:
        Serial.println("AUCUNE DEL");
        resetLED(DEL_VERTE);
        resetLED(DEL_JAUNE);
        resetLED(DEL_ROUGE);
        etatCourant = VERTE;    
        break;
        
      case VERTE:
        Serial.println("DEL VERTE");
        setLED(DEL_VERTE);
        etatCourant = JAUNE;
        break;
        
      case JAUNE :
        Serial.println("DEL JAUNE");
        resetLED(DEL_VERTE);
        setLED(DEL_JAUNE);
        etatCourant = ROUGE;
        break;
        
      case ROUGE :
        Serial.println("DEL ROUGE");
        resetLED(DEL_JAUNE);
        setLED(DEL_ROUGE);
        etatCourant = TOUTES;
        break;
        
      case TOUTES :
        Serial.println("TOUTES LES DEL");
        setLED(DEL_VERTE);
        setLED(DEL_JAUNE);
        setLED(DEL_ROUGE);
        etatCourant = AUCUNE;    
        break;
    }    
  }
  
  //Traitement de l'interruption URGENCE
  if(interuptFlag==1)
  {
    //On fait flasher les DEL rapidement
    Serial.println("URGENCE");
    for(int i=0; i<20;i++)
    {
      setLED(PIN_POWER);
      setLED(PIN_CONNEXION);
      setLED(PIN_ERROR);
        
      delay(50);
        
      resetLED(PIN_POWER);
      resetLED(PIN_CONNEXION);
      resetLED(PIN_ERROR);
        
      delay(50);
    }
    
    //On peut faire autre choses ici si on veut
    Serial.print("Reinitialisation");
    delay(1000);
    Serial.print(".");
    delay(1000);
    Serial.print(".");
    delay(1000);
    Serial.print(".");
    delay(1000);
    Serial.println("DONE!!!");
    delay(1000);
    
    //Remise à zéro des valeur
    previousMillis=currentMillis;
    etatCourant = AUCUNE;
    interuptFlag = 0; //important de le faire ( et de la faire à la fin du processus)
  }  
}

void ISR_Emergency ()
{
    //Le initFlag est à 1 seulement au début, car l'interrupt se déclanche toujours lorsqu'on active le ISR dans le setup()
    //On le remet à zéro et après le ISR marche comme il le faut.
    if(initFlag)
      initFlag=0;
    else
      interuptFlag = 1;
}
