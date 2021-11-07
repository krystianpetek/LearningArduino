/*
 Name:		WyswietlaczTeksty.ino
 Created:	11/6/2021 9:51:56 PM
 Author:	kryst
*/

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
// the setup function runs once when you press reset or power the board
void setup() {
	lcd.init();
	lcd.backlight();
}

// the loop function runs over and over again until power down or reset
void loop() {
  
}
