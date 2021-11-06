/*
 Name:		Wyswietlacz_Joystick_LED.ino
 Created:	11/6/2021 3:50:27 PM
 Author:	kryst
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

int osX = A7;
int osY = A6;
int joyPrzycisk = 52;

int xLedPrawo = 7;
int yLedGora = 6;
int xLedLewo = 5;
int yLedDol = 4;
int joyPrzyciskLed = 31;

void setup()
{
	//SWITCHE
	pinMode(10, INPUT_PULLUP);
	pinMode(11, INPUT_PULLUP);
	pinMode(12, OUTPUT);

	//JOYSTICK
	pinMode(osX, INPUT);
	pinMode(osY, INPUT);
	pinMode(joyPrzycisk, INPUT_PULLUP);
	pinMode(53, OUTPUT);
	digitalWrite(53, HIGH);

	// SWIATLA_JOYSTICK
	pinMode(xLedLewo, OUTPUT);
	pinMode(xLedPrawo, OUTPUT);
	pinMode(yLedGora, OUTPUT);
	pinMode(yLedDol, OUTPUT);
	pinMode(joyPrzyciskLed, OUTPUT);

	Serial.begin(9600);
	lcd.init(); // initialize the lcd
	lcd.backlight();
	lcd.setCursor(0, 0);
	lcd.print("Krystian");
	lcd.setCursor(0, 1);
	lcd.print("Petek");
	delay(2000);
	lcd.clear();
	lcd.noBacklight();
	delay(1000);
	lcd.backlight();
	lcd.setCursor(0, 1);
	lcd.print("OFF");
}

bool zmiana = false;
bool wcisniety = false;
void loop()
{

	if (zmiana)
		digitalWrite(12, HIGH);
	else
		digitalWrite(12, LOW);

	if (digitalRead(10) == 0)
		zmiana = true;

	if (digitalRead(11) == 0)
		zmiana = false;

	if (digitalRead(10) == 0 || digitalRead(11) == 0)
	{
		wcisniety = true;
		if (zmiana)
		{
			lcd.clear();
			lcd.setCursor(0, 0);
			lcd.print("ON");
		}
		else
		{
			lcd.clear();
			lcd.setCursor(0, 1);
			lcd.print("OFF");
		}
	}

	int x = analogRead(osX);
	int y = analogRead(osY);

	if (x < 200)
	{
		lcd.setCursor(8, 1);
		lcd.print("LEWO");
	}
	else if (x > 900)
	{
		lcd.setCursor(8, 1);
		lcd.print("PRAWO");
	}
	else
	{
		lcd.setCursor(8, 1);
		lcd.print("      ");
	}

	if (y < 200)
	{
		lcd.setCursor(8, 0);
		lcd.print("GORA");
	}
	else if (y > 900)
	{
		lcd.setCursor(8, 0);
		lcd.print("DOL");
	}
	else
	{
		lcd.setCursor(8, 0);
		lcd.print("      ");
	}



	if (x < 508)
	{
		int wartoscXLewo = (-1) * (x / 2) - 1;
		analogWrite(xLedLewo, wartoscXLewo);
		//Serial.println(wartoscXLewo);
	}
	else digitalWrite(xLedLewo, LOW);

	if (x > 511)
	{
		int wartoscXPrawo = x / 2;
		//digitalWrite(xLedPrawo,HIGH);
		analogWrite(xLedPrawo, wartoscXPrawo);
		//Serial.println(wartoscXPrawo);
	}
	else digitalWrite(xLedPrawo, LOW);



	if (y < 516)
	{
		int wartoscYGora = (-1) * (y / 2) - 1;
		// OGRANICZENIE WARTOSCI -1 do -255
		if (wartoscYGora < -255) wartoscYGora = -255;
		if (wartoscYGora > -1) wartoscYGora--;

		analogWrite(yLedGora, wartoscYGora);
		//Serial.println(wartoscYGora);

	}
	else {
		digitalWrite(yLedGora, LOW);
	}
	if (y > 517)
	{
		int wartoscYDol = y / 2;
		analogWrite(yLedDol, wartoscYDol);
		//Serial.println(wartoscYDol);
	}
	else {
		digitalWrite(yLedDol, LOW);
	}

	//Serial.println(digitalRead(joyPrzycisk));

	if (digitalRead(joyPrzycisk) == 0)
	{
		digitalWrite(joyPrzyciskLed, HIGH);
	}
	else {
		digitalWrite(joyPrzyciskLed, LOW);
	}
	//Serial.println("Os X: ");
	//Serial.print(x);
	//Serial.println();
   // Serial.println("Os Y: ");
   // Serial.print(y);

	delay(50);
}