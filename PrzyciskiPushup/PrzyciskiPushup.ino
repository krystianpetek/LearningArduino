/*
 Name:		PrzyciskiPushup.ino
 Created:	11/6/2021 3:47:54 PM
 Author:	kryst
*/

int pinLED = 5;
int pinON = 8;
int pinOFF = 9;
int pinZIELONY = 12;
int ilosc = 0;

void setup()
{
    pinMode(pinLED, OUTPUT);
    pinMode(pinON, INPUT_PULLUP);
    pinMode(pinOFF, INPUT_PULLUP);
    pinMode(pinZIELONY, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    Serial.println(digitalRead(pinON));
    if (digitalRead(pinON) == LOW)
    {
        ilosc++;
        delay(200);
        switch (ilosc)
        {
        case 1: analogWrite(pinLED, 10);
            break;
        case 2: analogWrite(pinLED, 20);
            break;
        case 3: analogWrite(pinLED, 50);
            break;
        case 4: analogWrite(pinLED, 255);
            break;
        case 5: analogWrite(pinZIELONY, 255);
            break;
        }
    }
    if (digitalRead(pinOFF) == LOW)
    {
        ilosc--;
        delay(200);
        switch (ilosc)
        {
        case 0: analogWrite(pinLED, 0);
            break;
        case 1: analogWrite(pinLED, 10);
            break;
        case 2: analogWrite(pinLED, 20);
            break;
        case 3: analogWrite(pinLED, 50);
            break;
        case 4: analogWrite(pinLED, 255); analogWrite(pinZIELONY, 0);
            break;
        case 5: analogWrite(pinZIELONY, 255);
            break;
        }
    }
}
