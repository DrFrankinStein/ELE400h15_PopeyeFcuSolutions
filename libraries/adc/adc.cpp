/* ================ adc.cpp ============================================
** ELE-400 MÉTHODOLOGIE DE DESIGN EN GÉNIE ÉLECTRIQUE
** HIVER 2015
** Ecole de Technologie Supérieure
** ========================================================================

				TEAM:	PopeyeFcuSolutions	
				
** ========================================================================
** REALISATION: Controleur de FCU	
** ========================================================================
** Writen by: Julien Lemay
** ========================================================================
** Description: List of fonctions to control the ADC 
** ======================================================================== */ 



/* ========================================================================
** Include files 
** ======================================================================== */

#include "adc.h"

/* ========================================================================
** Global variables
** ======================================================================== */

int bitsResolution;

/* ========================================================================
** Fonctions
** ======================================================================== */

/* ------------------------------------------------------------------------
** name: setupADC
** ------------------------------------------------------------------------
** input: resolution : between 1 and 12 bits (12 bits max for Arduino Due)
** output: none
** ------------------------------------------------------------------------
** Description: Set bit resolution of the ADC and voltage reference to 0-3.3V
** ------------------------------------------------------------------------ */
void setupADC(int resolution)
{
	//analogReference(DEFAULT); 			//Set voltage reference to 0-3.3V
	setResolutionADC(resolution);
}

/* ------------------------------------------------------------------------
** name: setResolutionADC
** ------------------------------------------------------------------------
** input: resolution : between 1 and 12 bits (12 bits max for Arduino Due)
** output: none
** ------------------------------------------------------------------------
** Description: Set bit resolution of the ADC
** ------------------------------------------------------------------------ */
void setResolutionADC(int resolution)
{
	bitsResolution = resolution;
	analogReadResolution(resolution);	//Set resolution of ADC to "resolution" bits
}

/* ------------------------------------------------------------------------
** name: readADCInteger
** ------------------------------------------------------------------------
** input: sensorPin : Name of the pin oof the ADC (ex : A0)
** output: a integer value of n bits where n is the resolution of the ADC
** ------------------------------------------------------------------------
** Description:	Read value of ADC and return a integer value of n bits where n is the resolution of the ADC
** ------------------------------------------------------------------------ */
int readADCInteger(int sensorPin)
{
	return analogRead(sensorPin);
}

/* ------------------------------------------------------------------------
** name: readADCPourcent
** ------------------------------------------------------------------------
** input: sensorPin : Name of the pin oof the ADC (ex : A0)
** output: Pourcentage value of the value and the maximum value  
** ------------------------------------------------------------------------
** Description: Read value of ADC and return pourcentage relative to the maximum value of the ADC
** ------------------------------------------------------------------------ */
float readADCPourcent(int sensorPin)
{
	return readADCInteger(sensorPin) * 100 / pow(2,bitsResolution);
}

/* ------------------------------------------------------------------------
** name: readADCReal
** ------------------------------------------------------------------------
** input: sensorPin : Name of the pin of the ADC (ex : A0)
** output: A float value of the actual voltage
** ------------------------------------------------------------------------
** Description: Read value of ADC and return a float value of the voltage
** ------------------------------------------------------------------------ */
//
float readADCReal(int sensorPin)
{
	return readADCPourcent(sensorPin) * VOLTAGE_REFERENCE_ADC;
}

/* ------------------------------------------------------------------------
** name: readLevierInteger
** ------------------------------------------------------------------------
** input: None
** output: a integer value of n bits where n is the resolution of the ADC
** ------------------------------------------------------------------------
** Description:	Read value of ADC and return a integer value of n bits where n is the resolution of the ADC
** ------------------------------------------------------------------------ */

int readLevierInteger(void)
{
	return analogRead(ADC_PIN);
}

/* ------------------------------------------------------------------------
** name: readADCPourcent
** ------------------------------------------------------------------------
** input: sensorPin : Name of the pin oof the ADC (ex : A0)
** output: Pourcentage value of the value and the maximum value  
** ------------------------------------------------------------------------
** Description: Read value of ADC and return pourcentage relative to the maximum value of the ADC
** ------------------------------------------------------------------------ */

float readLevierPourcent(void)
{
	//return readADCInteger(ADC_PIN) * 100 / (pow(2,bitsResolution)-6);
	return readADCInteger(ADC_PIN) * 100 / ((pow(2,bitsResolution))*0.7);
}

/* ------------------------------------------------------------------------
** name: readADCReal
** ------------------------------------------------------------------------
** input: None
** output: A float value of the actual voltage
** ------------------------------------------------------------------------
** Description: Read value of ADC and return a float value of the voltage
** ------------------------------------------------------------------------ */

float readLevierReal(void)
{
	return readADCPourcent(ADC_PIN) * VOLTAGE_REFERENCE_ADC;
}

/* ========================================================================
** End of  Nom.c
** ======================================================================== */
