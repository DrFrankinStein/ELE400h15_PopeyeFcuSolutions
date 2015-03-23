/* ================ adc.h ============================================
** ELE-400 MÉTHODOLOGIE DE DESIGN EN GÉNIE ÉLECTRIQUE
** HIVER 2015
** Ecole de Technologie Supérieure
** ========================================================================

				TEAM:	PopoyeFcuSolution	
				
** ========================================================================
** RÉALISATION: Controleur de FCU	
** ========================================================================
** Writen by: Julien Lemay
** ========================================================================
** Description: Header file of adc.c
** ======================================================================== */



/* ========================================================================
** Define
** ======================================================================== */

#define VOLTAGE_REFERENCE_ADC 3.3

/* ========================================================================
** Prototypes
** ======================================================================== */

void setupADC(int resolution);
void setResolutionADC(int resolution);
int readADCInteger(int sensorPin);
float readADCPourcent(int sensorPin);
float readADCReal(int sensorPin);



/* ========================================================================
** End of  adc.h
** ======================================================================== */