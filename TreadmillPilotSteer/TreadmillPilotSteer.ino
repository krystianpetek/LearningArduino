#include <IRremote.h>

const int PIN = 7;
IRrecv irrecv(PIN);
decode_results keys;

void setup() {
  irrecv.enableIRIn();
  Serial.begin(9600);
  irrecv.blink13(true);
}

void loop() {
  if (irrecv.decode(&keys)) {


    switch (keys.value) {
      // breaks
      case 0xFFFFFFFF:
      case 0xFF:
        break;

      case 0x3D9AE3F7:
      case 0xFF18E7:
        Serial.println("UP");
        break;
      
      case 0xFF10EF:
      case 0x8C22657B:
        Serial.println("LEFT");
        break;
      
      case 0xFF5AA5:
      case 0x449E79F:
        Serial.println("RIGHT");
        break;

      case 0xFF4AB5:
      case 0x1BC0157B:
        Serial.println("DOWN");
        break;

      case 0xFF38C7:
      case 0x488F3CBB:
        Serial.println("OK");
        break;

      case 0xE318261B:
      case 0xFFA25D:
        Serial.println("1");
        break;

      case 0x511DBB:
      case 0xFF629D:
        Serial.println("2");
        break;

      case 0xFFE21D:
      case 0xEE886D7F:
        Serial.println("3");
        break;

      case 0xC4EE8C19:
      Serial.println("TV: UP");
      break;
      
      case 0xBA3BBBB5:
      Serial.println("TV: LEFT");
      break;
      
      case 0x526E78FB:
      Serial.println("TV: DOWN");
      break;
      
      case 0x78ADAABB:
      Serial.println("TV: RIGHT");
      break;

      default:
        Serial.println(keys.value, HEX);
        break;
    }
    irrecv.resume();
  }
}
