/* ================ ELE400h15_PopeyeFcuSolutions.ino =================================================
** ELE-400 MÉTHODOLOGIE DE DESIGN EN GÉNIE ÉLECTRIQUE
** HIVER 2015
** Ecole de Technologie Supérieure
** ========================================================================

			TEAM:	PopeyeFcuSolutions	
				
** ========================================================================
** RÉALISATION: Controleur de FCU	
** ========================================================================
** Written by: Julien LEMAY
** ========================================================================
** Description: Programme principal du contrôleur de FCU
** ======================================================================== */ 



/* ========================================================================
** Include files 
** ======================================================================== */

#include "adc.h"
#include "lcd.h"
#include "Led.h"
#include "Keypad.h"
#include "Clavier.h"
#include "Moteur.h"



/* ========================================================================
** Global variables
** ======================================================================== */

//Énumération des différences écrans possibles
enum menu_t {LOGO=0, PRINCIPAL, OPTION, MAX_ANGLE_EDIT, MIN_ANGLE_EDIT, IDLE_ANGLE_EDIT, DEBUG, MENU_DEBUG, INFO, TEST_MOTEUR, AJUSTE_MOTEUR, URGENCE, INVALIDE, VALIDE}; 
enum moteur_t {INACTIF, IDLE_M, ACTIF};

//Variable limites des angles 
float minAngle = 0.0;
float maxAngle = 180.0;
float fractionIdle = 0.1;
float idleAngle= ((maxAngle-minAngle)* fractionIdle)+minAngle;

//Variables d'états présents
float currentAngle, currentPourcent;
//bool isMoteurActif=false;
int etatMoteur=INACTIF;
bool editMode=false;
int currentMenu=PRINCIPAL;

//Variables pour les algorithmes de fenêtres glissantes
const int nbreDataWindow= 100;
//int dataInteger[nbreDataWindow];
float dataPourcent[nbreDataWindow];

//Ajout des variables de flag
int interuptFlag = 0, initFlag = 1;

//Variables compteurs
unsigned long previousMillis=0;
unsigned int interval=100;
int nbCycle=0;

const int maxEditBoxLength=5;
char editBox[maxEditBoxLength]="";
int editCount=0;

/* ========================================================================
** Fonctions
** ======================================================================== */

/* ------------------------------------------------------------------------
** name: displayScreen
** ------------------------------------------------------------------------
** input: disp : Le nom du menu à afficher (menu_t)
** output: none
** ------------------------------------------------------------------------
** Description: Affiche les éléments statiques de l'écran selon le menu sélectionné
** ------------------------------------------------------------------------ */
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
    
    case PRINCIPAL:
      lcdWriteStringAtPosition(0, 0, "AFFICHAGE PRINCIPAL");
      lcdWriteStringAtPosition(1, 0, "MOTEUR     = -");
      lcdWriteStringAtPosition(2, 0, "LEVIER(%)  = -");
      lcdWriteStringAtPosition(3, 0, "ANGLE(DEG) = -");
    break;
    
    case URGENCE :
      lcdWriteStringAtPosition(0, 0, "********************");
      lcdWriteStringAtPosition(1, 0, "*      URGENCE     *");
      lcdWriteStringAtPosition(2, 0, "* (APPUYER SUR OK) *");
      lcdWriteStringAtPosition(3, 0, "********************");
      break;
      
    case OPTION : 
      lcdWriteStringAtPosition(0, 0, "OPTIONS: 0- IDLE(%)");
      lcdWriteStringAtPosition(1, 0, "1-AJUSTER ANGLE MAX.");
      lcdWriteStringAtPosition(2, 0, "2-AJUSTER ANGLE MIN.");
      lcdWriteStringAtPosition(3, 0, "3-INFO. 4-DEBUG. ");
      break;
      
    case MAX_ANGLE_EDIT:
      lcdWriteStringAtPosition(0, 0, "ENTRER LA VALEUR DE");
      lcdWriteStringAtPosition(1, 0, "L'ANGLE MAXIMUM :");
      lcdWriteStringAtPosition(2, 0, "ANCIEN MAX.= ");
      lcdWriteStringAtPosition(3, 0, "NOUVEAU    = ");
      break;
      
    case MIN_ANGLE_EDIT:
      lcdWriteStringAtPosition(0, 0, "ENTRER LA VALEUR DE");
      lcdWriteStringAtPosition(1, 0, "L'ANGLE MINIMUM :");
      lcdWriteStringAtPosition(2, 0, "ANCIEN MIN.= ");
      lcdWriteStringAtPosition(3, 0, "NOUVEAU    = ");
      break;
    
    case INFO:
      lcdWriteStringAtPosition(0, 0, "INFORMATIONS :");
      lcdWriteStringAtPosition(1, 0, "ANGLE IDLE = ");
      lcdWriteStringAtPosition(2, 0, "ANGLE MIN. = ");
      lcdWriteStringAtPosition(3, 0, "ANGLE MAX. = ");
      break;
  
    case MENU_DEBUG:
      lcdWriteStringAtPosition(0, 0, "DEBUG INFO :");
      lcdWriteStringAtPosition(1, 0, "1- TEST MOTEUR");
      lcdWriteStringAtPosition(2, 0, "2- AJUSTEMENT MANUEL");
      lcdWriteStringAtPosition(3, 0, "3- INDICE PERFO.");
      break; 
  
    case DEBUG:
      lcdWriteStringAtPosition(0, 0, "DEBUG INFO :");
      lcdWriteStringAtPosition(1, 0, "Kops   = ");
      lcdWriteStringAtPosition(2, 0, "TEMPS  = ");
      lcdWriteStringAtPosition(3, 0, "Kops/s = ");
      break;
    
    case TEST_MOTEUR : 
      lcdWriteStringAtPosition(0, 0, "TEST MOTEUR :");
      lcdWriteStringAtPosition(1, 0, "1- 360 CW");
      lcdWriteStringAtPosition(2, 0, "2- 180 CW-180 CCW");
      lcdWriteStringAtPosition(3, 0, "3- 90 CW  4- 90 CCW");
      break;
      
    case AJUSTE_MOTEUR :  
      lcdWriteStringAtPosition(0, 0, "1- 5  degres CCW ");
      lcdWriteStringAtPosition(1, 0, "3- 5  degres CW ");
      lcdWriteStringAtPosition(2, 0, "4- 45 degres CCW ");
      lcdWriteStringAtPosition(3, 0, "6- 45 degres CW ");
      break;
     
    case INVALIDE :
      lcdWriteStringAtPosition(1, 0, "  ENTREE  INVALIDE  ");
      break;
      
    case VALIDE :
      lcdWriteStringAtPosition(1, 0, "    SAUVEGARDEE!    ");
      break;
     
    case IDLE_ANGLE_EDIT:
      lcdWriteStringAtPosition(0, 0, "ENTRER LA VALEUR DU");
      lcdWriteStringAtPosition(1, 0, "RATIO D'IDLE (%) :");
      lcdWriteStringAtPosition(2, 0, "ANCIEN MIN.= ");
      lcdWriteStringAtPosition(3, 0, "NOUVEAU    = ");
      break;  
  }  
}

/* ------------------------------------------------------------------------
** name: prepareDisplay
** ------------------------------------------------------------------------
** input: none
** output: none
** ------------------------------------------------------------------------
** Description: Affiche les éléments de départ sur l'écran
** ------------------------------------------------------------------------ */
void prepareDisplay(void)
{
  
  //Affiche le logo de l'équipe
  displayScreen(LOGO);
  delay(500);
  
  setLED(DEL_VERTE);
  delay(500);
  setLED(DEL_JAUNE);
  delay(500);
  setLED(DEL_ROUGE);
  delay(500);
  
  resetLED(DEL_VERTE);
  resetLED(DEL_JAUNE);
  resetLED(DEL_ROUGE);
  
  //Affiche l'affichage principal
  displayScreen(PRINCIPAL);
  delay(1000);
}

/* ------------------------------------------------------------------------
** name: getPourcentFromSlindingWindows
** ------------------------------------------------------------------------
** input: pourcent entre la donnée à ajouter dans la fênetre 
** output: La moyenne des <nbreDataWindow> pourcentages contenu dans le tableau de données de la fenètre glissante
** ------------------------------------------------------------------------
** Description: Fait la moyenne des <nbreDataWindow> pourcentages entrés dans la fonction
** selon l'algorithme de la fenêtre glissante
** ------------------------------------------------------------------------ */
float getPourcentFromSlindingWindows(float pourcent)
{  
  if(pourcent>=100)
    pourcent=100;
  float sum=0;
  
  //Tasse les plus vielles données vers le début de la fenêtre
  for(int i=0;i<nbreDataWindow-1;i++)
  {
    dataPourcent[i]=dataPourcent[i+1];
    sum += dataPourcent[i];  
  }
  
  //Met la nouvelle donnée dans la fenêtre  
  dataPourcent[nbreDataWindow-1]=pourcent;
  sum+=dataPourcent[nbreDataWindow-1];
  
  //On fait la moyenne 
  return sum/nbreDataWindow;
  
}



void updateDataLevier(void)
{
   currentPourcent = getPourcentFromSlindingWindows(readLevierPourcent());
  if(etatMoteur==ACTIF)
    currentAngle = (currentPourcent/100) * (maxAngle-minAngle)+ minAngle;
  else if(etatMoteur==IDLE_M)
    currentAngle = idleAngle;
  else  
    currentAngle = minAngle;
}   

void writeAngle(char key)
{
  
  if(key>='0'&&key<='9' && editCount<maxEditBoxLength)
  {
    editBox[editCount]=key;
    editCount++;
  }
  else if(key=='d' || key=='g')
  {
    editBox[editCount]='.';
    editCount++;
  }
  else if(key=='e' && editCount>0)
  {
    editCount--;
    editBox[editCount]=0;
  }
  else if(key=='o' && editCount>0)
  {  
    float angle=0.0;
    bool isValide = true, asPoint=false;
    
    Serial.println(editBox);
    for(int i=0; i<editCount; i++)
    {
      if(editBox[i]=='.')
      {
        if(!asPoint)
          asPoint=true;  
        else
          isValide=false;  
      }  
      
    }  
    
    if(sscanf(editBox,"%f",&angle)>=0 && isValide)
    {
      switch(currentMenu)
      {
        
      case MAX_ANGLE_EDIT:
        if(angle<minAngle || angle>360)
        {
          Serial.println("ECHEC");
          displayScreen(INVALIDE);
          delay(1000);
          isValide=false;
        }  
        else
        {
          Serial.println(angle);
          displayScreen(VALIDE);
          delay(1000);
          maxAngle=angle;
          idleAngle= ((maxAngle-minAngle)* fractionIdle)+minAngle; 
        }  
        break;
     
      case MIN_ANGLE_EDIT:
        if(angle>maxAngle || angle<0)
        {
          Serial.println("ECHEC");
          displayScreen(INVALIDE);
          delay(1000);
          isValide=false;
        }  
        else
          {
          Serial.println(angle);
          displayScreen(VALIDE);
          delay(1000);
          minAngle=angle;
          idleAngle= ((maxAngle-minAngle)* fractionIdle)+minAngle;
        } 
        break;
        
        case IDLE_ANGLE_EDIT:
        if(angle>100 || angle<0)
        {
          displayScreen(INVALIDE);
          delay(1000);
          isValide=false;
        }
        else
          {
          Serial.println(angle);
          displayScreen(VALIDE);
          delay(1000);
          fractionIdle=angle/100;
          idleAngle= ((maxAngle-minAngle)* fractionIdle)+minAngle;
        }   
        break;
        
      default:
        Serial.println("ECHEC");
        displayScreen(INVALIDE);
        delay(1000);
        isValide=false;
        break;
        
      } 
    }  
    else
    {
      Serial.println("ECHEC");
      displayScreen(INVALIDE);
      delay(1000);
      isValide=false;
    }
  }
  
  //Vérifier editCount
  if(editCount>maxEditBoxLength+1)
    editCount=maxEditBoxLength+1;
  else if(editCount<0)
    editCount=0;  
    
  
}   

void keyboardAction(char key)
{
  switch(currentMenu)
   {
     case PRINCIPAL:
     
       switch(key)
        {
          case 'o':
            switch(etatMoteur)
            {
              case INACTIF:
                etatMoteur=IDLE_M;
                break;
              
              case IDLE_M:
                etatMoteur=ACTIF;
                break;
            }
            
            break;
        
          case 's':
            switch(etatMoteur)
            {
              case ACTIF:
                etatMoteur=IDLE_M;
                break;
              
              case IDLE_M:
                etatMoteur=INACTIF;
                break;
            }
            break;
        
          case 'm':
            if(etatMoteur==ACTIF)
              etatMoteur=IDLE_M;
            currentMenu=OPTION;
            displayScreen(currentMenu);
          break;
        }  
       break;
     
     case OPTION:
       switch(key)
       {   
         case 'o':
         case 'm': 
         case 's':
            currentMenu=PRINCIPAL;
            displayScreen(currentMenu);
            break;
        
          case '1':
            currentMenu=MAX_ANGLE_EDIT;
            for(int i=0;i<maxEditBoxLength;i++)
              editBox[i]=0;
            editCount=0;
            displayScreen(currentMenu);
            break;
            
          case '2':
            currentMenu=MIN_ANGLE_EDIT;
            for(int i=0;i<maxEditBoxLength;i++)
              editBox[i]=0;
            editCount=0;
            displayScreen(currentMenu);
            break;
            
          case '3':
            currentMenu=INFO;
            displayScreen(currentMenu);
            break;
            
          case '4':
            currentMenu=MENU_DEBUG;
            displayScreen(currentMenu);
            break;
            
          case '0':
            currentMenu=IDLE_ANGLE_EDIT;
            for(int i=0;i<maxEditBoxLength;i++)
              editBox[i]=0;
            editCount=0;
            displayScreen(currentMenu);
            break;  
       }  
       break;

     case IDLE_ANGLE_EDIT:
       switch(key)
       { 
         case 'o':
           writeAngle(key);  
         case 's':
         case 'm':
           editMode=false;
           lcdUnderlineCursor(OFF);
           currentMenu=OPTION;
           displayScreen(currentMenu);
           break;
         default :
           //touche clavier pour editer
           editMode=true;
           lcdUnderlineCursor(ON);
           writeAngle(key);
           break;   
       }
       break;
     
     case MAX_ANGLE_EDIT:
       switch(key)
       { 
         case 'o':
           writeAngle(key);  
         case 's':
         case 'm':
           editMode=false;
           lcdUnderlineCursor(OFF);
           currentMenu=OPTION;
           displayScreen(currentMenu);
           break;
         default :
           //touche clavier pour editer
           editMode=true;
           lcdUnderlineCursor(ON);
           writeAngle(key);
           break;   
       }
       break;
     
     case MIN_ANGLE_EDIT:
       switch(key)
       { 
         case 'o':
           writeAngle(key);  
         case 's':
         case 'm':
           editMode=false;
           lcdUnderlineCursor(OFF);
           currentMenu=OPTION;
           displayScreen(currentMenu);
           break;
         default :
           //touche clavier pour editer
           editMode=true;
           lcdUnderlineCursor(ON);
           writeAngle(key);
           break;   
       }
       break;
     
     case DEBUG:
     switch(key)
       { 
         case 'o':  
         case 's':
         case 'm':
           currentMenu=OPTION;
           displayScreen(currentMenu);
           break;   
       }
       break;

     
     case INFO :
       switch(key)
       { 
         case 'o':  
         case 's':
         case 'm':
           currentMenu=OPTION;
           displayScreen(currentMenu);
           break;   
       }
       break;
     
     case MENU_DEBUG : 
     switch(key)
       {   
         case 'o':
         case 'm': 
         case 's':
            currentMenu=OPTION;
            displayScreen(currentMenu);
            break;
        
          case '1':
            currentMenu=TEST_MOTEUR;
            displayScreen(currentMenu);
            break;
            
          case '2':
            currentMenu=AJUSTE_MOTEUR;
            displayScreen(currentMenu);
            break;
            
          case '3':
            currentMenu=DEBUG;
            displayScreen(currentMenu);
            break;
       }  
       break;
     
     case TEST_MOTEUR : 
     switch(key)
     { 
         case 'o':
         case 'm': 
         case 's':
            currentMenu=MENU_DEBUG;
            displayScreen(currentMenu);
            break;
        
          case '1':
            moteurTourne360CW();
            break;
            
          case '2':
            moteurTourne(180, CW);
            delay(250);
            moteurTourne(180, CCW);
            break;
            
          case '3':
            moteurTourne(90, CW);
            break;
            
          case '4':
            moteurTourne(90, CCW);
            break;  
     }
     break; 
     
     case AJUSTE_MOTEUR : 
     switch(key)
     { 
         case 'o':
         case 'm': 
         case 's':
            currentMenu=MENU_DEBUG;
            displayScreen(currentMenu);
            break;
        
          case '1':
            moteurTourne(5, CCW);
            break;
            
          case '3':
            moteurTourne(5, CW);
            break;
            
          case '4':
            moteurTourne(45, CCW);
            break;
            
          case '6':
            moteurTourne(45, CW);
            break;  
     }
     break;  
   } 
}   

void gestionMenu(void)
{
   switch(currentMenu)
   {
     case PRINCIPAL:
       if(etatMoteur==ACTIF)
         lcdWriteStringAtPosition(1,13,"ACTIF  ");
       else if(etatMoteur==IDLE_M)
         lcdWriteStringAtPosition(1,13,"IDLE   ");
       else  
         lcdWriteStringAtPosition(1,13,"INACTIF");
         
       lcdWriteStringAtPosition(2,13,"      ");
       lcdWriteFloatAtPosition(2, 13, currentPourcent);
       lcdWriteStringAtPosition(3,13,"      ");
       lcdWriteFloatAtPosition(3, 13, currentAngle);
       break;
     
     case OPTION:
       //
       break;
     
     case MAX_ANGLE_EDIT:
       if(!editMode)
         lcdWriteFloatAtPosition(2, 13, maxAngle);
       else
       {
         lcdWriteStringAtPosition(3,13,"      ");
         lcdWriteStringAtPosition(3,13, editBox);
       }  
       break;
         
     case MIN_ANGLE_EDIT:
       if(!editMode)
         lcdWriteFloatAtPosition(2, 13, minAngle);
       else
       {
         lcdWriteStringAtPosition(3,13,"      ");
         lcdWriteStringAtPosition(3,13, editBox);
       }  
       break;
       
     case IDLE_ANGLE_EDIT:
       if(!editMode)
         lcdWriteFloatAtPosition(2, 13, fractionIdle*100);
       else
       {
         lcdWriteStringAtPosition(3,13,"      ");
         lcdWriteStringAtPosition(3,13, editBox);
       }  
       break;  
     
     case DEBUG:
       lcdWriteFloatAtPosition(1, 9, (float)nbCycle/1000);
       lcdWriteFloatAtPosition(2, 9, (float)millis()/1000);
       lcdWriteFloatAtPosition(3, 9, (float)nbCycle/(float)millis());
       break;
     
     case INFO:
       lcdWriteFloatAtPosition(1, 13, idleAngle);
       lcdWriteFloatAtPosition(2, 13, minAngle);
       lcdWriteFloatAtPosition(3, 13, maxAngle);
       break;  
   }
   
   if(etatMoteur!=INACTIF)
   {
     resetLED(PIN_POWER);
     setLED(PIN_CONTROL);
   }  
   else
   {
     setLED(PIN_POWER);
     resetLED(PIN_CONTROL);  
   }  
}  

void controleMoteur(void)
{
    moteurGoToAngle(currentAngle);
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
    
    //init Moteur
    moteurSetup();
    
    //Bouton d'urgence
    pinMode(PIN_KILL_SWITCH, INPUT);
  
    //Quand on clique sur le bouton, on met le signal à zéro (RISING PEUT ÊTRE CORRECT AUSSI)
    attachInterrupt(PIN_KILL_SWITCH, ISR_Emergency, FALLING); 
   
    prepareDisplay();
    
    for(int i = 0 ; i<nbreDataWindow;i++)
    {
      updateDataLevier(); 
    }  
}

void loop()
{
    unsigned long currentMillis = millis();
    char key;
   
    updateDataLevier();
    
    moteurGoToAngle(currentAngle);
 
    if((currentMillis-previousMillis)>interval)
    {
      //Mise à jour du compteur
      previousMillis=currentMillis;
    
      //Quoi mettre à jour
      keyboardAction(kpGetValue());
      gestionMenu();
    }
    
    //Traitement de l'interruption URGENCE
    if(interuptFlag==1)
    {
      
      etatMoteur=INACTIF;
      currentAngle=minAngle;
      moteurGoToAngle(currentAngle);
      
      displayScreen(URGENCE);
      
      resetLED(PIN_POWER);
      resetLED(PIN_CONTROL);
      
      //On fait flasher la DEL Erreur rapidement
      for(int i=0; i<20;i++)
      {
        setLED(PIN_ERROR);
        delay(50);
        
        resetLED(PIN_ERROR);
        delay(50);
      }
      setLED(PIN_ERROR);
     
      while(kpGetValue()!='o')
        delay(1);
       
      displayScreen(currentMenu);
      resetLED(PIN_ERROR);
      delay(100);
      
      previousMillis=currentMillis;
      interuptFlag = 0; //important de le faire ( et de le faire à la fin du processus)
    }  
    
    nbCycle++;
}

void ISR_Emergency ()
{
    //Le initFlag est à 1 seulement au début, car l'interrupt se 
    //déclanche toujours lorsqu'on active le ISR dans le setup()
    //On le remet à zéro et après le ISR marche comme il le faut.
    if(initFlag)
      initFlag=0;
    else
      interuptFlag = 1;
}
