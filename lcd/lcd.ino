#include "lcd.h"

void setup() {
  Serial1.begin(9600);
}

void loop() {
  delay(100);
  Serial1.write("ABCDEFGHIJK");
  while(Serial.available() < 0);

}


