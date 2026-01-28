int incomingByte = 0;

void setup() {
  Serial.begin(9600);

}

void loop() {
  if(Serial.available()> 0){
    // incomingByte = Serial.read();
incomingByte = analogRead(A6);
    Serial.print('i received:');
    Serial.println(incomingByte, DEC);
  }

}
