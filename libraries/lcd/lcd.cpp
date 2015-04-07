/* =================== lcd.cpp ============================================
** ELE-400 MÉTHODOLOGIE DE DESIGN EN GÉNIE ÉLECTRIQUE
** HIVER 2015
** Ecole de Technologie Supérieure
** ========================================================================

				Equipe:	PopeyeFcuSolutions	
				
** ========================================================================
** REALISATION: Controleur de FCU	
** ========================================================================
** Ecrit par: 	Vincent Prieur
** ========================================================================
** Description: Fonctions de controle de l'ecran LCD
** ======================================================================== */ 

/* ========================================================================
** Fichiers d'en-tetes 
** ======================================================================== */
#include "lcd.h"

/* ========================================================================
** Fonctions
** ======================================================================== */

/* ------------------------------------------------------------------------
** Nom: lcdInit
** ------------------------------------------------------------------------
** Entree(s): Aucune
** Sortie(s): Acune
** ------------------------------------------------------------------------
** Description: Initialise l'écran LCD. 
** ------------------------------------------------------------------------ */
void lcdInit()
{
  Serial1.begin(9600);		// LCD a 9600 Baud par defaut
  delay(100);				// Delai necessaire a l'initialisation
  lcdPwr(ON);				
  lcdClrScr();
}

/* ------------------------------------------------------------------------
** Nom: lcdWriteString
** ------------------------------------------------------------------------
** Entree(s): Chaine de caracteres de type string
** Sortie(s): Aucune
** ------------------------------------------------------------------------
** Description: Ecrit une chaine de caractere a l'ecran LCD
** ------------------------------------------------------------------------ */
void lcdWriteString(char *string)
{
	Serial1.write(string);
}

/* ------------------------------------------------------------------------
** Nom: lcdWriteConfigSpace
** ------------------------------------------------------------------------
** Entree(s):	Registre de configuration
				Mot de configuration
** Sortie(s):	Aucune
** ------------------------------------------------------------------------
** Description: Ecrit dans le registre de configuration
				*** Ne pas utiliser cette fonction directement ***
** ------------------------------------------------------------------------ */
void lcdWriteConfigSpace(unsigned char configReg, unsigned char configWord = 0)
{
    Serial1.write(CONFIG_SPACE_ADDRESS);
    Serial1.write(configReg);
    if(configWord)
    	Serial1.write(configWord);
    delay(4);
}

/* ------------------------------------------------------------------------
** Nom: lcdPwr
** ------------------------------------------------------------------------
** Entree(s): ON ou OFF
** Sortie(s): Aucune
** ------------------------------------------------------------------------
** Description: Allume ou eteint l'ecran
** ------------------------------------------------------------------------ */
void lcdPwr(unsigned char etat)
{
	if(etat)
		lcdWriteConfigSpace(DISPlAY_ON);
	else
		lcdWriteConfigSpace(DISPLAY_OFF);
}

/* ------------------------------------------------------------------------
** Nom: lcdSetCursor
** ------------------------------------------------------------------------
** Entree(s): Position du curseur 
** Sortie(s): Aucune
** ------------------------------------------------------------------------
** Description: Place le curseur a la position desire
				(Ex.: LIGNE1+1 pour la ligne 1, 2e caractere)
				*** Pour mettre le curseur a la LIGNE1, 1er caractere,
					utiliser lcdSetCursorHome(); ***
** ------------------------------------------------------------------------ */
void lcdSetCursor(unsigned char position)
{
	lcdWriteConfigSpace(SET_CURSOR, position);
}

/* ------------------------------------------------------------------------
** Nom: lcdSetCursorHome
** ------------------------------------------------------------------------
** Entree(s): Aucune
** Sortie(s): Aucune
** ------------------------------------------------------------------------
** Description: Place le curseur a la LIGNE1, 1er caractere
** ------------------------------------------------------------------------ */
void lcdSetCursorHome()
{
	lcdWriteConfigSpace(CURSOR_HOME);
}

/* ------------------------------------------------------------------------
** Nom: lcdUnderLineCursor
** ------------------------------------------------------------------------
** Entree(s): ON ou OFF
** Sortie(s): Aucune
** ------------------------------------------------------------------------
** Description: Souligne le curseur
** ------------------------------------------------------------------------ */
void lcdUnderlineCursor(unsigned char etat)
{
	if(etat)
		lcdWriteConfigSpace(UNDERLINE_ON);
	else
		lcdWriteConfigSpace(UNDERLINE_OFF);
}

/* ------------------------------------------------------------------------
** Nom: lcdMoveCursor
** ------------------------------------------------------------------------
** Entree(s): LEFT ou RIGHT
** Sortie(s): Aucune
** ------------------------------------------------------------------------
** Description: Bouge le curseur de 1 case a droite ou a gauche
** ------------------------------------------------------------------------ */
void lcdMoveCursor(unsigned char etat)
{
	if(etat)
		lcdWriteConfigSpace(MOVE_LEFT);
	else
		lcdWriteConfigSpace(MOVE_RIGHT);
}

/* ------------------------------------------------------------------------
** Nom: lcdBlinkCursor
** ------------------------------------------------------------------------
** Entree(s): ON ou OFF
** Sortie(s): Aucune
** ------------------------------------------------------------------------
** Description: Fait clignoter le curseur
** ------------------------------------------------------------------------ */
void lcdBlinkignCursor(unsigned char etat)
{
	if(etat)
		lcdWriteConfigSpace(BLINKING_ON);
	else
		lcdWriteConfigSpace(BLINKING_OFF);
}

/* ------------------------------------------------------------------------
** Nom: lcdBackSpace
** ------------------------------------------------------------------------
** Entree(s): Aucune
** Sortie(s): Aucune
** ------------------------------------------------------------------------
** Description: Recule le curseur de 1 case et supprime le caractere
** ------------------------------------------------------------------------ */
void lcdBackSpace()
{
	lcdWriteConfigSpace(BACKSPACE);
}

/* ------------------------------------------------------------------------
** Nom: lcdClrScr
** ------------------------------------------------------------------------
** Entree(s): Aucune
** Sortie(s): Aucune
** ------------------------------------------------------------------------
** Description: Efface l'ecran
** ------------------------------------------------------------------------ */
void lcdClrScr()
{
	lcdWriteConfigSpace(CLEAR_SCREEN);
}

/* ------------------------------------------------------------------------
** Nom: lcdSetDisplayContrast
** ------------------------------------------------------------------------
** Entree(s): 1 @ 50
** Sortie(s): Aucune
** ------------------------------------------------------------------------
** Description: Ajuste le contraste (40 par defaut)
** ------------------------------------------------------------------------ */
void lcdSetDisplayContrast(unsigned char contrast)
{
	lcdWriteConfigSpace(SET_CONTRAST, contrast);
}

/* ------------------------------------------------------------------------
** Nom: lcdSetBackLightBrightness
** ------------------------------------------------------------------------
** Entree(s): 1 @ 8
** Sortie(s): Aucune
** ------------------------------------------------------------------------
** Description: Ajuste la luminosite (8 par defaut)
** ------------------------------------------------------------------------ */
void lcdSetBacklightBrightness(unsigned char brightness)
{
	lcdWriteConfigSpace(BKLGT_BRTNS, brightness);
}

/* ------------------------------------------------------------------------
** Nom: lcdShiftDisplay
** ------------------------------------------------------------------------
** Entree(s): LEFT ou RIGHT
** Sortie(s): Aucune
** ------------------------------------------------------------------------
** Description: Deplace toutes les lignes selon la direction de 1 case
** ------------------------------------------------------------------------ */
void lcdShiftDisplay(unsigned char etat)
{
	if(etat)
		lcdWriteConfigSpace(MOVE_DISP_LEFT);
	else
		lcdWriteConfigSpace(MOVE_DISP_RIGHT);
}

/* ------------------------------------------------------------------------
** Nom: lcdDisplayFirwareVersion
** ------------------------------------------------------------------------
** Entree(s): Aucune
** Sortie(s): Aucune
** ------------------------------------------------------------------------
** Description: Affiche le firmware de l'ecran
** ------------------------------------------------------------------------ */
void lcdDisplayFirmwareVersion()
{
	lcdWriteConfigSpace(DISP_FIRM_NUM);
}

/* ------------------------------------------------------------------------
** Nom: lcdDisplayBaudrate
** ------------------------------------------------------------------------
** Entree(s): Aucune
** Sortie(s): Aucune
** ------------------------------------------------------------------------
** Description: Affiche le baudrate de l'ecran
** ------------------------------------------------------------------------ */
void lcdDisplayBaudrate()
{
	lcdWriteConfigSpace(DISP_BAUDRATE);
}
/* ========================================================================
** Fin de lcd.cpp
** ======================================================================== */