#include "lcd.h"
#include <arduino.h>

void lcdInit()
{
  delay(100);
  lcdPwr(ON);
  lcdClrScr();
}

void lcdWriteString(unsigned char *string)
{
	Serial1.write(string);
}

void lcdWriteConfigSpace(unsigned char configReg, unsigned char configWord = 0)
{
    Serial1.write(CONFIG_SPACE_ADDRESS);
    Serial1.write(configReg);
    if(configWord)
    	Serial1.write(configWord);
    delay(4);
}

void lcdPwr(unsigned char etat)
{
	if(etat)
		lcdWriteConfigSpace(DISPlAY_ON);
	else
		lcdWriteConfigSpace(DISPLAY_OFF);
}

void lcdSetCursor(unsigned char position)
{
	lcdWriteConfigSpace(SET_CURSOR, position);
}

void lcdSetCursorHome()
{
	lcdWriteConfigSpace(CURSOR_HOME);
}

void lcdUnderlineCursor(unsigned char etat)
{
	if(etat)
		lcdWriteConfigSpace(UNDERLINE_ON);
	else
		lcdWriteConfigSpace(UNDERLINE_OFF);
}

void lcdMoveCursor(unsigned char etat)
{
	if(etat)
		lcdWriteConfigSpace(MOVE_LEFT);
	else
		lcdWriteConfigSpace(MOVE_RIGHT);
}

void lcdBlinkignCursor(unsigned char etat)
{
	if(etat)
		lcdWriteConfigSpace(BLINKING_ON);
	else
		lcdWriteConfigSpace(BLINKING_OFF);
}

void lcdBackSpace()
{
	lcdWriteConfigSpace(BACKSPACE);
}

void lcdClrScr()
{
	lcdWriteConfigSpace(CLEAR_SCREEN);
}

void lcdSetDisplayContrast(unsigned char contrast)
{
	lcdWriteConfigSpace(SET_CONTRAST, contrast);
}

void lcdSetBacklightBrightness(unsigned char brightness)
{
	lcdWriteConfigSpace(BKLGT_BRTNS, brightness);
}

void lcdShiftDisplay(unsigned char etat)
{
	if(etat)
		lcdWriteConfigSpace(MOVE_DISP_LEFT);
	else
		lcdWriteConfigSpace(MOVE_DISP_RIGHT);
}

void lcdDisplayFirmwareVersion()
{
	lcdWriteConfigSpace(DISP_FIRM_NUM);
}

void lcdDisplayBaudrate()
{
	lcdWriteConfigSpace(DISP_BAUDRATE);
}
