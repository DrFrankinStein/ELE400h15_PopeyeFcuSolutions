/* ================ Led.c =================================================
** ELE-400 MÉTHODOLOGIE DE DESIGN EN GÉNIE ÉLECTRIQUE
** HIVER 2015
** Ecole de Technologie Supérieure
** ========================================================================

			TEAM:	PopoyeFcuSolution	
				
** ========================================================================
** RÉALISATION: Controleur de FCU	
** ========================================================================
** Written by: Hortense Laure HOUENDJI
** ========================================================================
** Description: 
** ======================================================================== */ 


/* ========================================================================
** Include files 
** ======================================================================== */


/* ========================================================================
** Prototypes
** ======================================================================== */


/* ========================================================================
** Fonctions
** ======================================================================== */


/* ------------------------------------------------------------------------
** name:  setupLED
** ------------------------------------------------------------------------
** input: Led
** output: Pas de variable retournée
** ------------------------------------------------------------------------
** Description:cette fonction sert à configurer les pin des LEDs
** ------------------------------------------------------------------------ */
void setupLED()
{
  pinMode(PIN_POWER, OUTPUT);  // on configure les pins en mode outpout
  pinMode(PIN_CONNEXION, OUTPUT);  // on configure les pins en mode outpout
  pinMode(PIN_ERROR, OUTPUT);  // on configure les pins en mode outpout  
}

/* ------------------------------------------------------------------------
** name:  setLED
** ------------------------------------------------------------------------
** input: Pin, pinState
** output: Pas de variable retournée
** ------------------------------------------------------------------------
** Description:cette fonction Sert à allumer une LED
** ------------------------------------------------------------------------ */
void setLED(int Pin)
{
  //On configure la LED en mode hight
  digitalWrite(Pin, HIGH);
  
}

/* ------------------------------------------------------------------------
** name:  resetLED
** ------------------------------------------------------------------------
** input: Pin, pinState
** output: Pas de variable retournée
** ------------------------------------------------------------------------
** Description:Sert à éteindre une LED
** ------------------------------------------------------------------------ */
void resetLED(int Pin, int pinState)
{
  // on configure le LED en mode low
  digitalWrite(Pin, LOW);
}



/* ------------------------------------------------------------------------
** name:  isLEDsetted
** ------------------------------------------------------------------------
** input: Type_LED Led, ledState
** output: Pas de variable retournée
** ------------------------------------------------------------------------
** Description:vérifie si la led est allumée ou non et retourne la réponse 
** (Vrai ou faux)
** ------------------------------------------------------------------------ */
bool isLEDsetted(int Pin)
{
  int led_state = 0; // création d'une variable d'état de la LED
  
  led_state = digitalRead(Pin); // Lecture de l'état de la pin
  return led_state;  
}


/* ------------------------------------------------------------------------
** name:  blinkLED
** ------------------------------------------------------------------------
** input: Pin
** output: Pas de variable retournée
** ------------------------------------------------------------------------
** Description:Sert à changer l’état d’une LED (on à off et vive versa)
** ------------------------------------------------------------------------ */
void blinkLED(int Pin, bool led_state)
{
  if led_state = 0 // si la led est à l'état bas
  {
    digitalWrite(Pin, HIGH); // on la met à l'état haut
  }
  else // si elle est a l'état haut
  {
    digitalWrite(Pin, LOW); // on la met à l'état bas
  }   
}

/* ========================================================================
** End of  Led.c
** ======================================================================== */
