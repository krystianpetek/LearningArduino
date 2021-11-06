/*
 Name:		JoystickLED.ino
 Created:	11/6/2021 3:48:50 PM
 Author:	kryst
*/

int osX = A0;
int osY = A1;
int joyPrzycisk = 4;
int xLedLewo = 9;
int xLedPrawo = 10;
int yLedGora = 11;
int yLedDol = 6;
int joyPrzyciskLed = 13;

void setup() {
    Serial.begin(9600);

    pinMode(osX, INPUT);
    pinMode(osY, INPUT);
    pinMode(joyPrzycisk, INPUT_PULLUP);

    pinMode(xLedLewo, OUTPUT);
    pinMode(xLedPrawo, OUTPUT);

    pinMode(yLedGora, OUTPUT);
    pinMode(yLedDol, OUTPUT);

    pinMode(joyPrzyciskLed, OUTPUT);
}

void loop() {
    int x = analogRead(osX);
    int y = analogRead(osY);

    if (x < 508)
    {
        int wartoscXLewo = (-1) * (x / 2) - 1;
        analogWrite(xLedLewo, wartoscXLewo);
    }
    else digitalWrite(xLedLewo, LOW);

    if (x > 511)
    {
        int wartoscXPrawo = x / 2;
        analogWrite(xLedPrawo, wartoscXPrawo);
    }
    else digitalWrite(xLedPrawo, LOW);



    if (y < 516)
    {
        int wartoscYGora = (-1) * (y / 2) - 1;
        // OGRANICZENIE WARTOSCI -1 do -255
        if (wartoscYGora < -255) wartoscYGora = -255;
        if (wartoscYGora > -1) wartoscYGora--;

        analogWrite(yLedGora, wartoscYGora);
    }
    else 
    {
        digitalWrite(yLedGora, LOW);
    }
    if (y > 517)
    {
        int wartoscYDol = y / 2;
        analogWrite(yLedDol, wartoscYDol);
    }
    else 
    {
        digitalWrite(yLedDol, LOW);
    }

    if (digitalRead(joyPrzycisk) == 0)
    {
        digitalWrite(joyPrzyciskLed, HIGH);
    }
    else 
    {
        digitalWrite(joyPrzyciskLed, LOW);
    }
    delay(50);

}