/* ================ Led.cpp =================================================
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


/* ========================================================================
** Include files 
** ======================================================================== */

#include "Moteur.h" 

const int delai = 1;
const float un_degre = 51200/360;
const float degre180 = 51200/2;
const float degre0 = 0;

float currentMoteurAngle = 0;




/* ========================================================================
** Prototypes
** ======================================================================== */


/* ========================================================================
** Fonctions
** ======================================================================== */


/* ------------------------------------------------------------------------
** name:  setupMoteur
** ------------------------------------------------------------------------
** input: wat
** output: wat
** ------------------------------------------------------------------------
** Description: wat
** ------------------------------------------------------------------------ */
void moteurSetup(void)
{
  pinMode(PIN_PULSE, OUTPUT);	
  pinMode(PIN_DIRECTION, OUTPUT);
  pinMode(PIN_BRIDGE_ENABLE, INPUT);  
}

/* ------------------------------------------------------------------------
** name:  tourneMoteur
** ------------------------------------------------------------------------
** input: wat
** output: wat
** ------------------------------------------------------------------------
** Description: wat
** ------------------------------------------------------------------------ */ 
void moteurTourne(float angle, int direction) 
{  
	digitalWrite(PIN_DIRECTION, direction);
	
	int mesure = (int)(un_degre*angle);
	
	for(int i = 0; i<(mesure);i++)
	{
		digitalWrite(PIN_PULSE, HIGH);
		delayMicroseconds(delai);
		digitalWrite(PIN_PULSE, LOW);
	}	
}

void moteurTourne360CW(void)
{
	moteurTourne(360, CW);
}

void moteurGoToAngle(float angle)
{
	if(angle>=360)
		angle=360;
	
	float tmpAngle = angle - currentMoteurAngle;
	int direction;
	
	if(tmpAngle>0)
		direction = CW;
	else
	{
		direction = CCW;
		tmpAngle=-tmpAngle;
	}	
	
	moteurTourne(tmpAngle, direction);
	currentMoteurAngle = angle;
			
}

/* ========================================================================
** End of  Moteur.cpp
** ======================================================================== */
