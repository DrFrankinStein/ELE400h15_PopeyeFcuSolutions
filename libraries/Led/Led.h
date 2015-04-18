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

//Pour éviter de déclarer ce fichier plus d'une fois
#ifndef LED_H
#define LED_H

/* ========================================================================
** Include files 
** ======================================================================== */
#include "pins_arduino.h"
#include "Arduino.h"	//Besoin de ce fichier pour utiliser les fonctions du Arduino
#include <stdbool.h>	//Besoin de ce fichier pour utiliser les type bool

/* ========================================================================
** Define
** ======================================================================== */
//TO CHANGE NAME
#define PIN_POWER 35    // pin PB26 relié à la led power
#define PIN_CONNEXION 37  // pin PA14 relié a la led connexion
#define PIN_ERROR 39    // pin PA15 relié à la led error
#define DEL_VERTE PIN_POWER
#define DEL_JAUNE PIN_CONNEXION
#define DEL_ROUGE PIN_ERROR

/** À enlever d'ici peut être **/
#define PIN_KILL_SWICTH 53        // pin reliée à la kill switch

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

//Sert à configurer une pin à un état voulu
void setLEDState(int Pin, bool state);

//vérifie si la led est allumée ou non et retourne la réponse (Vrai ou faux)
bool isLEDsetted(int Pin);

//Sert à changer l’état d’une LED (on à off et vive versa)
void blinkLED(int Pin); 

/* ========================================================================
** End of  Led.h
** ======================================================================== */
#endif