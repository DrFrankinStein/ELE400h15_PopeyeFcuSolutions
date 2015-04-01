/* ================ adc.h ============================================
** ELE-400 MÉTHODOLOGIE DE DESIGN EN GÉNIE ÉLECTRIQUE
** HIVER 2015
** Ecole de Technologie Supérieure
** ========================================================================

				TEAM:	PopeyeFcuSolutions	
				
** ========================================================================
** RÉALISATION: Controleur de FCU	
** ========================================================================
** Writen by: Julien Lemay
** ========================================================================
** Description: Header file of adc.c
** ======================================================================== */

#ifndef ADC_H
#define ADC_H

/* ========================================================================
** Define
** ======================================================================== */

#define VOLTAGE_REFERENCE_ADC 0.033
#define ADC_PIN A11

/* ========================================================================
** Includes
** ======================================================================== */

#include <stdbool.h> 
#include "Arduino.h"

/* ========================================================================
** Prototypes
** ======================================================================== */

void setupADC(int resolution);
void setResolutionADC(int resolution);
/*int readADCInteger(int sensorPin);
float readADCPourcent(int sensorPin);
float readADCReal(int sensorPin);*/

int readLevierInteger(void);
float readLevierPourcent(void);
float readLevierReal(void);



/* ========================================================================
** End of  adc.h
** ======================================================================== */

#endif