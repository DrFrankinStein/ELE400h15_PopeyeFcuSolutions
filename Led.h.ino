/* ================ Led.h =================================================
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
#include "pins_arduino.h"
* ========================================================================
** Define
** ======================================================================== */
#define PIN_POWER 22    // pin PB26 relié à la led power
#define PIN_CONNEXION 23  // pin PA14 relié a la led connexion
#define PIN_ERROR 3    // pin PA15 relié à la led error

/* ========================================================================
** Structure
** ======================================================================== */


/* ========================================================================
** Enummeration
** ======================================================================== */
// déclaration du type de led
/*typedef enum  
{
  POWER, 
  CONNEXION,
  ERREUR
}Type_LED; // 3 types de led*/

/* ========================================================================
** Prototypes
** ======================================================================== */
//cette fonction sert à configurer les pin des LEDs
void setupLED(void); 

//Sert à allumer une LED
void setLED(int Pin);

//Sert à éteindre une LED
void resetLED(int Pin);

//vérifie si la led est allumée ou non et retourne la réponse (Vrai ou faux)
bool isLEDsetted(Pin);

//Sert à changer l’état d’une LED (on à off et vive versa)
void blinkLED(int Pin, bool led_state); 

/* ========================================================================
** End of  Led.h
** ======================================================================== */
