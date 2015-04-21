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
#ifndef MOTEUR_H
#define MOTEUR_H

/* ========================================================================
** Include files 
** ======================================================================== */
#include "pins_arduino.h"
#include "Arduino.h"	//Besoin de ce fichier pour utiliser les fonctions du Arduino
#include <stdbool.h>	//Besoin de ce fichier pour utiliser les type bool

/* ========================================================================
** Define
** ======================================================================== */


//Les pins qui nous sont disponibles sont les pins 42, 44, 46, 48, 50, 52
//sorties au moteur
#define PIN_PULSE			7		//PA19, pin reliée à la pin 2a du multifunction interface
#define PIN_DIRECTION		6		//PC19, pin reliée à la pin 3a du multifunction interface
#define PIN_BRIDGE_ENABLE	5		//PC17, pin reliée à la pin 4a du multifunction interface

//Les pins qui nous sont disponibles sont les pins 41, 43, 45, 47, 49, 51
//entrées au Arduino (retour de l'encodeur à quadrature)
#define PIN_A_PLUS			41		//pin reliée à la pin 1b du multifunction interface
#define PIN_A_MOINS			43		//pin reliée à la pin 2b du multifunction interface

#define PIN_B_PLUS			45		//pin reliée à la pin 3b du multifunction interface
#define PIN_B_MOINS			47		//pin reliée à la pin 4b du multifunction interface

#define PIN_INDEX_PLUS		49		//pin reliée à la pin 5b du multifunction interface
#define PIN_INDEX_MOINS		51		//pin reliée à la pin 6b du multifunction interface

/* ========================================================================
** Structure
** ======================================================================== */


/* ========================================================================
** Enummerations
** ======================================================================== */
enum DIR {
	CCW,		//0, counter clockwise
	CW			//1, clockwise
};

/* ========================================================================
** Prototypes
** ======================================================================== */
//cette fonction sert à configurer les pin du moteur
void moteurSetup(void);
void moteurTourne(float angle, int direction);
void moteurTourne360CW(void);
void moteurGoToAngle(float angle);

/* ========================================================================
** End of  Moteur.h
** ======================================================================== */
#endif