#include "adc.h"
#include "lcd.h"
#include "Led.h"
#include "Keypad.h"
#include "Clavier.h"

//float value;
//float valuetmp;

char tmp[20];

enum {LOGO=0, MAIN_SCREEN, OPTION, INFO, URGENCE};
float minAngle = 0.0;
float maxAngle = 180.0;

float currentAngle, currentPourcent;

const int nbreDataWindow= 100;
int dataInteger[nbreDataWindow];
float dataPourcent[nbreDataWindow];
//int x=0;

//Ajout des variables de flag
int interuptFlag = 0, initFlag =1;

unsigned long previousMillis=0;
unsigned int interval=100;

void displayScreen(int disp)
{
  lcdClrScr();
  
  switch(disp)
  {
    case LOGO :
  
    lcdWriteStringAtPosition(0, 0, "********************");
    lcdWriteStringAtPosition(1, 0, "*      POPEYE      *");
    lcdWriteStringAtPosition(2, 0, "*   FCU SOLUTIONS  *");
    lcdWriteStringAtPosition(3, 0, "********************");
    break;
    
    case MAIN_SCREEN:
      lcdWriteStringAtPosition(0, 0, "1- OPTIONS 2-INFO   ");
      //lcdWriteStringAtPosition(1, 0, "LEVIER(%)  = -");
      //lcdWriteStringAtPosition(2, 0, "--------------------");
      lcdWriteStringAtPosition(2, 0, "LEVIER(%)  = -");
      lcdWriteStringAtPosition(3, 0, "ANGLE(DEG) = -");
    break;
    
    case URGENCE :
      lcdWriteStringAtPosition(0, 0, "********************");
      lcdWriteStringAtPosition(1, 0, "*      URGENCE     *");
      lcdWriteStringAtPosition(2, 0, "* (APPUYER SUR OK) *");
      lcdWriteStringAtPosition(3, 0, "********************");
      break;
  }  
  
}

void prepareDisplay(void)
{
  lcdDisplayBaudrate();
  delay(1000);
  
  displayScreen(LOGO);
  delay(1000);
  
  displayScreen(MAIN_SCREEN);
  delay(1000);
}

float getAngle()
{
    float val;
    int valuesum = 0;

    for(int i=0; i<10; ++i)
        valuesum += readLevierInteger();

    valuesum /= 10;

    val = valuesum * (180.0/4089.0);

    return val;
}

int getIntegerFromSlindingWindows(int integer)
{  
  
  int sum=0;
  
  for(int i=0;i<nbreDataWindow-1;i++)
  {
    dataInteger[i]=dataInteger[i+1];
    sum += dataInteger[i];  
  }
    
  dataInteger[nbreDataWindow-1]=integer;
  sum+=dataInteger[nbreDataWindow-1];
  
  return sum/nbreDataWindow;
  
}

float getPourcentFromSlindingWindows(float pourcent)
{  
  
  float sum=0;
  
  for(int i=0;i<nbreDataWindow-1;i++)
  {
    dataPourcent[i]=dataPourcent[i+1];
    sum += dataPourcent[i];  
  }
    
  dataPourcent[nbreDataWindow-1]=pourcent;
  sum+=dataPourcent[nbreDataWindow-1];
  
  return sum/nbreDataWindow;
  
}

void updateData(void)
{
  currentPourcent = getPourcentFromSlindingWindows(readLevierPourcent());
  currentAngle = (currentPourcent/100) * (maxAngle-minAngle)+ minAngle;
}  

void updateMainScreen(void)
{
  //int value = getIntegerFromSlindingWindows(readLevierInteger());
  //float pourcent = getPourcentFromSlindingWindows(readLevierPourcent());
  //float angle = (pourcent/100) * (maxAngle-minAngle)+ minAngle;
  
  //lcdWriteIntegerAtPosition(0,6,x);
  lcdWriteStringAtPosition(2,13,"      ");
  lcdWriteFloatAtPosition(2, 13, currentPourcent);
  //lcdWriteStringAtPosition(2,13,"      ");
  //lcdWriteIntegerAtPosition(2, 13, value);
  lcdWriteStringAtPosition(3,13,"      ");
  lcdWriteFloatAtPosition(3, 13, currentAngle);
}

void setup()
{
    // debug port init
    Serial.begin(9600);

    // adc init
    setupADC(12);
    
    // setup LED
    setupLED();
    
    // lcd init
    lcdInit();
  
    //Bouton d'urgence
    pinMode(53, INPUT);
  
    //Quand on clique sur le bouton, on met le signal à zéro (RISING PEUT ÊTRE CORRECT AUSSI)
    attachInterrupt(53, ISR_Emergency, FALLING); 
   
    prepareDisplay();
}

void loop()
{
    /*char str[10];

    valuetmp = getAngle();

    if(valuetmp != value)
    {
        value = valuetmp;
        Serial.println(value);

        lcdClrScr();
        sprintf(str, "%f", value);
        lcdWriteString(str);
    }

    delay(100);*/
    unsigned long currentMillis = millis();
    char key;
   
    //const char *cckey = &key;
    
    updateData();
    //x++;
    
    if((currentMillis-previousMillis)>interval)
    {
      //Mise à jour du compteur
      previousMillis=currentMillis;
    
      //Quoi mettre à jour
      //Serial.print(value);
      //Serial.print(" ");
      //Serial.println(x); 
      updateMainScreen();
      key = kpGetValue();
      if(key!=NO_KEY)
      {  
        char tmp[5]; 
        sprintf(tmp,"%c",key);
        lcdWriteStringAtPosition(1,0,tmp);
      }    
    }
    
    //Traitement de l'interruption URGENCE
    if(interuptFlag==1)
    {
      //On fait flasher les DEL rapidement
      displayScreen(URGENCE);
      for(int i=0; i<20;i++)
      {
        //setLED(PIN_POWER);
        //setLED(PIN_CONNEXION);
        setLED(PIN_ERROR);
        
        delay(50);
        
        //resetLED(PIN_POWER);
        //resetLED(PIN_CONNEXION);
        resetLED(PIN_ERROR);
        
        delay(50);
      }
      setLED(PIN_ERROR);
      //On peut faire autre choses ici si on veut
      /*Serial.print("Reinitialisation");
      delay(1000);
      Serial.print(".");
      delay(1000);
      Serial.print(".");
      delay(1000);
      Serial.print(".");
      delay(1000);
      Serial.println("DONE!!!");
      delay(1000);*/
    
      //Remise à zéro des valeur
      
      //delay(1000);
      key = NO_KEY;
      while(key!='o')
      {
        key = kpGetValue();
        delay(1);  
      }
      
      displayScreen(MAIN_SCREEN);
      
      resetLED(PIN_ERROR);
      
      delay(100);
      
      previousMillis=currentMillis;
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
