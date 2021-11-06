/*
 Name:		Sketch1.ino
 Created:	11/6/2021 3:35:04 PM
 Author:	kryst
*/

int led = 13;
void setup() {
    pinMode(led, OUTPUT);
    //pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    digitalWrite(led, HIGH);
    delay(1000);
    digitalWrite(led, LOW);
    delay(200);
}
