#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pin podłączenia przycisku
#define BUTTON_PIN 3

LiquidCrystal_I2C lcd(0x27, 16, 2); // Adjust the 0x27 address if needed

volatile bool dataReceived = false;
String receivedMessage = "";

volatile bool backlight = false;
volatile int timer;

bool pompCoState = false;
bool pompCwuState = false;

// void receiveEvent(int bytes) {

//   char message[20];
//   int i = 0;
//   while(Wire.available()) { // Loop through all received bytes
//     message[i++] = Wire.read(); // Receive byte as a character
//   }
//   message[i] = '\0'; // Null terminate the string

// Serial.println(message);

//   // lcd.clear();
//   // lcd.setCursor(0, 0);
//   // lcd.print(message);
// }

void receiveEvent(int bytes) {
  receivedMessage = ""; // String to store the received message
  while (0 < Wire.available()) { // Loop through all received bytes
    char c = Wire.read(); // Receive byte as a character
    receivedMessage += c; // Add received character to string
  }
    dataReceived = true; // Set the flag to true

  // if (bytes == sizeof(float)) { // Make sure we receive exactly an int size of bytes
      
  //     float receivedTemp;
      
  //     Wire.readBytes((char*)&receivedTemp, sizeof(receivedTemp)); // Read the incoming bytes

  //   }
  }


void backlightOn(){
  backlight = true;
  timer = 0;
  lcd.backlight();
  Serial.println("Backlight ON");
}

void backlightOff(){
  backlight = false;
  timer = 0;
  lcd.noBacklight();
  Serial.println("Backlight OFF");
}

void setup() {
  // Wire.begin(8); // Join I2C bus with address #8
  // Wire.onReceive(receiveEvent); // Register event

  Serial.begin(9600);
  Serial.println("Arduino started");

  lcd.init(); // Initialize the LCD
  backlightOn();
  lcd.print("Device 2 started");

  delay(5000);
  
  lcd.clear();

  pinMode(BUTTON_PIN, INPUT_PULLUP); // Używam INPUT_PULLUP, aby uniknąć konieczności stosowania zewnętrznego rezystora
}

void getPompState() {
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Pompa CO: ");
  if(pompCoState)
  {
    lcd.print("ON");
  }
  else{
    lcd.print("OFF");
  }

  lcd.setCursor(0, 1);
  lcd.print("Pompa CWU: ");
  if(pompCwuState)
  {
    lcd.print("ON");
  }
  else{
    lcd.print("OFF");
  }

  delay(5000);
  
  lcd.clear();
}

void loop(void)
{
  if (digitalRead(BUTTON_PIN) == LOW) { // Naciśnięcie przycisku
    // Wypisanie adresów czujników
    
    backlightOn();

    delay(500); // Opóźnienie, aby uniknąć wielokrotnego odczytu

    if(digitalRead(BUTTON_PIN) == LOW)
    {
      getPompState();
    }
  }

  if(backlight && timer < 15)
  {
    timer++;
    delay(500);
  }

  if(timer >= 15)
  {
    backlightOff();
  }

 if (dataReceived) {
    Serial.println(receivedMessage); // Debug print

    if(receivedMessage[8] == '0' && receivedMessage[9] == '2')
    {
      lcd.setCursor(0, 0);
      lcd.print(receivedMessage); // Now safe to print
    }
    else if (receivedMessage[8] == '9' && receivedMessage[9] == 'D') {
      lcd.setCursor(0, 1);
      lcd.print(receivedMessage); // Now safe to print
    }

    if(receivedMessage.endsWith("On"))
    {
      pompCoState = true;
    }
    if(receivedMessage.endsWith("Off"))
    {
      pompCoState = false;
    }
    
    dataReceived = false; // Reset the flag

  }
    delay(1000);
}
