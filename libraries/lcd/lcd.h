#ifndef LCD_H
#define LCD_H
// Fichier d'en-tete pour l'ecran a cristaux liquides

#include "Arduino.h"

void lcdInit();
void lcdWriteString(const char *string);
void lcdWriteConfigSpace(const char configReg, const char configWord);
void lcdPwr(unsigned char etat);
void lcdSetCursor(unsigned char position);
void lcdSetCursorHome();
void lcdUnderlineCursor(unsigned char etat);
void lcdMoveCursor(unsigned char etat);
void lcdBlinkignCursor(unsigned char etat);
void lcdBackSpace();
void lcdClrScr();
void lcdSetDisplayContrast(unsigned char contrast);
void lcdSetBacklightBrightness(unsigned char brightness);
void lcdShiftDisplay(unsigned char etat);
void lcdDisplayFirmwareVersion();
void lcdDisplayBaudrate();

bool lcdWriteStringAtPosition(unsigned int ligne, unsigned int colonne, const char *string);
bool lcdWriteIntegerAtPosition(unsigned int ligne, unsigned int colonne, int entier);
bool lcdWriteFloatAtPosition(unsigned int ligne, unsigned int colonne, float flottant);


// Adresse de l'espace de configuration
#define CONFIG_SPACE_ADDRESS 0xFE

// Adresses des registres de l'espace de configuration
#define DISPlAY_ON		0x41
#define DISPLAY_OFF		0x42
#define SET_CURSOR		0x45
#define CURSOR_HOME		0x46
#define UNDERLINE_ON	0x47
#define UNDERLINE_OFF	0x48
#define MOVE_LEFT		0x49
#define MOVE_RIGHT		0x4A
#define BLINKING_ON		0x4B
#define BLINKING_OFF	0x4C
#define BACKSPACE		0x4E
#define CLEAR_SCREEN	0x51
#define SET_CONTRAST	0x52
#define BKLGT_BRTNS		0x53
#define LOAD_CSTM_CHAR	0x54
#define MOVE_DISP_LEFT	0x55
#define MOVE_DISP_RIGHT	0x56
#define CHANGE_BAUDRATE	0x61
#define CHANGE_I2C_ADDR	0x62
#define DISP_FIRM_NUM	0x70
#define DISP_BAUDRATE	0x71
#define DISP_I2C_ADDR	0x72

#define ON 	0x01
#define OFF 0x00

#define LEFT 	0x01
#define RIGHT 	0x00

//Nombre de caractères dans l'écran
#define DISPLAY_CHAR_LENGTH 80

//Adresse des lignes dans la matrice de l'écran
#define LIGNE1 	0x00
#define LIGNE2	0x40
#define LIGNE3	0x14
#define LIGNE4  0x54
	
#endif
