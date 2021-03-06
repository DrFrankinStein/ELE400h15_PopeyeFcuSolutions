/* ================ Clavier.h =============================================
** ELE-400 MÉTHODOLOGIE DE DESIGN EN GÉNIE ÉLECTRIQUE
** HIVER 2015
** Ecole de Technologie Supérieure
** ========================================================================
				TEAM:	PopeyeFcuSolutions
** ========================================================================
** REALISATION: Controleur de FCU
** ========================================================================
** Writen by: Francis Bergin
** ========================================================================
** Description: Header file of Clavier.cpp
** ======================================================================== */

#ifndef CLAVIER_H
#define CLAVIER_H

/* ========================================================================
** Includes
** ======================================================================== */

#include "Arduino.h"
#include "Keypad.h"


/* ========================================================================
** Defineconst
** ======================================================================== */

const int kpPin1 = 26;
const int kpPin2 = 27;
const int kpPin3 = 28;
const int kpPin4 = 29;
const int kpPin5 = 30;
const int kpPin6 = 31;
const int kpPin7 = 32;
const int kpPin8 = 33;

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns


/* ========================================================================
** Prototypes
** ======================================================================== */

char kpGetValue(void);


/* ========================================================================
** End of  Clavier.h
** ======================================================================== */

#endif
