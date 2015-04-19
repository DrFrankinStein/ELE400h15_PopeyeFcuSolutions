/* ================ Led.h =================================================
** ELE-400 MÉTHODOLOGIE DE DESIGN EN GÉNIE ÉLECTRIQUE
** HIVER 2015
** Ecole de Technologie Supérieure
** ========================================================================

			TEAM:	PopoyeFcuSolution	
				
** ========================================================================
** RÉALISATION: Controleur de FCU	
** ========================================================================
** Written by: Philippe Soroka-Lavictoire
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

//Les pins qui nous sont disponibles sont les pins 41, 43, 45, 47, 49, 51

//sorties au moteur
#define PIN_PULSEMOTION		??		// pin reliée à la pin 2a du multifunction interface
#define PIN_DIRECTION		??		// pin reliée à la pin 3a du multifunction interface
#define PIN_BRIDGE_ENABLE	??		// pin reliée à la pin 4a du multifunction interface

//entrées au Arduino (retour du moteur)
#define PIN_ATTENTION_PLUS	??		//pin reliée à la pin 5a du multifunction interface
#define PIN_ATTENTION_MOINS	??		//pin reliée à la pin 6a du multifunction interface

/* ========================================================================
** Structure
** ======================================================================== */


/* ========================================================================
** Enummerations
** ======================================================================== */


/* ========================================================================
** Prototypes
** ======================================================================== */
//cette fonction sert à configurer les pin du moteur
void setupMoteur(void); 

/* ========================================================================
** End of  Moteur.h
** ======================================================================== */
#endif