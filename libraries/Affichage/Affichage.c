/* ================ Affichage.c ============================================
** ELE-400 MÉTHODOLOGIE DE DESIGN EN GÉNIE ÉLECTRIQUE
** HIVER 2015
** Ecole de Technologie Supérieure
** ========================================================================

			TEAM:	PopeyeFcuSolutions	
				
** ========================================================================
** REALISATION: Controleur de FCU	
** ========================================================================
** Writen by: Hortense Laure HOUENDJI
** ========================================================================
** Description: Ce document permet l'affichage des données sur l'écran LCD
** ======================================================================== */ 

 

/* ========================================================================
** Include files 
** ======================================================================== */
#include "Affichage.h"

/* ========================================================================
** Global variables
** ======================================================================== */

/* ========================================================================
** Prototypes
** ======================================================================== */

/* ========================================================================
** Fonctions
** ======================================================================== */

/* ------------------------------------------------------------------------
** name: setupScreen
** ------------------------------------------------------------------------
** input: Pins
** output: none
** ------------------------------------------------------------------------
** Description: Cette fonction permet de configurer les pins de l'écran LCD 
** et les configurations nécessaires pour bien faire fonctionner l'écran
** ------------------------------------------------------------------------ */
void setupScreen(int Pins){

/** Configurations des pins du arduino avec celles de l'écran **/
LiquidCrystal lcd(LCD_SPI_PIN);

/** Configuration des dimensions de l'écran (nombre de colonnes 
	et de lignes) **/
 lcd.begin(COLON_SIZE, ROW_SIZE); 
   
}

/* ------------------------------------------------------------------------
** name: clearScreen
** ------------------------------------------------------------------------
** input: none
** output: none
** ------------------------------------------------------------------------
** Description: Éfface l'écran
** ------------------------------------------------------------------------ */
void clearScreen(){
 
 // éfface l'écran et positionne le curseur au coin supérieur gauche
 lcd.clear() ;
  
}

/* ------------------------------------------------------------------------
** name: setScreenCursorPosition
** ------------------------------------------------------------------------
** input: colon_x (colonne); row_y(ligne)
** output: none
** ------------------------------------------------------------------------
** Description: met le curseur à la position voulue
** ------------------------------------------------------------------------ */
void setScreenCursorPosition(int colon_x,  int row_y){

 // positionne le curseur à la position demandée
lcd.setCursor(colon_x,  row_y);
  
}

/* ------------------------------------------------------------------------
** name: writeStringToScreen
** ------------------------------------------------------------------------
** input: colon_x (colonne); row_y(ligne), Texte
** output: none
** ------------------------------------------------------------------------
** Description: écrit le texte à partir de la position
** ------------------------------------------------------------------------ */
void writeStringToScreen(int colon_x,  int row_y,	char Texte){
  
// positionne le curseur à la position demandée
lcd.setCursor(colon_x,  row_y);

// écrire le texte à la position du curseur
lcd.print(Texte);
}

/* ========================================================================
** End of  Affichage.c
** ======================================================================== */



       

