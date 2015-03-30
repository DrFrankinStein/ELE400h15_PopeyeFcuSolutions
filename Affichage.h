

/* ================ Affichage.h ============================================
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
** Description: Document responsable de l'affichage sur l'écran LCD
** ======================================================================== */

/* ========================================================================
** Include files 
** ======================================================================== */

/* ========================================================================
** Defines
** ======================================================================== */
#define LCD_SPI_PIN		24		/** La pin 24 du arduino est connectée à la 
									pin SPI du LCD **/
#define LCD_SDO_PIN		11		/** La pin 11 du arduino est connectée à la 
									pin SDO du LCD **/
#define LCD_CLK_PIN		13		/**La pin 13 du arduino est connectée à la 
									pin serial clock du LCD **/
#define LCD_DATA_PIN	12		/** La pin 12 du arduino est connectée à la 
								pin correspondant au serial data du LCD **/
#define ROW_SIZE		4		/** Nombre de lignes de l'écran **/
#define COLON_SIZE		20			/** Nombres de colonnes de l'écran **/

/* ========================================================================
** Enumerations & Structures
** ======================================================================== */

/* ========================================================================
** Prototypes
** ======================================================================== */

/* cette fonction sert à configurer les pins de l’écran LCD et les 
configurations nécessaires pour bien faire fonctionner l’écran */
void setupScreen(int Pins); 

/* Vide l’écran et met le curseur en haut à gauche */
void clearScreen();

/* met le curseur à la position voulue */
void setScreenCursorPosition(int colon_x,  int row_y);

/* écrit le texte à partir de la position (x,y) */
void writeStringToScreen(int colon_x,  int row_y,  Texte);
       


/* ========================================================================
** End of  Affichage.h
** ======================================================================== */
