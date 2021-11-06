/*
 Name:		RGBLosowanie.ino
 Created:	11/6/2021 3:43:12 PM
 Author:	kryst
*/

#define red 6
#define green 5
#define blue 3

void setup()
{
	pinMode(red, OUTPUT);
	pinMode(green, OUTPUT);
	pinMode(blue, OUTPUT);
	//digitalWrite(red,HIGH);
	//digitalWrite(green,HIGH);
	//digitalWrite(blue, HIGH);
}
void loop()
{
	analogWrite(red, random(0, 255));
	analogWrite(green, random(0, 255));
	analogWrite(blue, random(0, 255));
	delay(200);
}