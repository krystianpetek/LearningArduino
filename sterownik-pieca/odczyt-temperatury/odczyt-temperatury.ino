#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Pin podłączenia czujników
#define ONE_WIRE_BUS 2
// Ustawienie komunikacji OneWire
OneWire oneWire(ONE_WIRE_BUS);
// Przekazanie referencji oneWire do Dallas Temperature.
DallasTemperature sensors(&oneWire);

// Pin podłączenia przycisku
#define BUTTON_PIN 3

// Pin sterujący pompą CO
#define PUMP_CO_PIN 4

// pin sterujuacy pompą CWU
#define PUMP_CWU_PIN 5

// Sterowanie pompą CO
const float tempCO_On = 30.0; // temperatura włączenia CO
const float tempCO_Off = 28.0; // temperatura wyłączenia CO

void setup(void)
{
  Serial.begin(9600);
  Serial.println("started arduino 1");
  sensors.begin();

  Wire.begin(); // Join I2C bus

   // Ustawienie pinu przycisku jako wejście
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Używam INPUT_PULLUP, aby uniknąć konieczności stosowania zewnętrznego rezystora

  // Ustawienie pinu pomp jako wyjście.
  pinMode(PUMP_CO_PIN, OUTPUT);
  digitalWrite(PUMP_CO_PIN, LOW); // Ustawienie domyślnego stanu przekaźnika na wyłączony.
}

void loop(void)
{ 
  // Sprawdzenie, czy przycisk został naciśnięty
  if (digitalRead(BUTTON_PIN) == LOW) { // Naciśnięcie przycisku
    // Wypisanie adresów czujników
    printSensorAddresses();
    delay(500); // Opóźnienie, aby uniknąć wielokrotnego odczytu
  }

  sensors.requestTemperatures(); // Wywołanie odczytu temperatury dla wszystkich czujników

  // Odczyt temperatury i wyświetlanie z dwoma ostatnimi znakami adresu dla każdego czujnika
  for (int i = 0; i < sensors.getDeviceCount(); i++) {
    float temperature = sensors.getTempCByIndex(i);
    DeviceAddress address;
    if (sensors.getAddress(address, i)) {

      String message = "Czujnik ";
      String sensorNumber = getAddressEnd(address);
      message += sensorNumber;
      message += " ";
      message += temperature;

      Wire.beginTransmission(8); // Assuming the slave address is 8
      
      for (int i = 0; i < message.length(); i++) {
        Wire.write(message[i]); // Send each character of the string
      }
      
      Wire.endTransmission();
      
      // Wire.write((byte*)&tempC, sizeof(tempC)); // Send temperature as bytes
  
      Serial.print("sended: ");
      Serial.println(message);

      if(sensorNumber == "02")
      {
        if (temperature >= tempCO_On && digitalRead(PUMP_CO_PIN) != HIGH) {
          digitalWrite(PUMP_CO_PIN, HIGH); // Włącz pompę CO (przekaźnik aktywowany wysokim stanem).
          String pumpCo = "PompaCO On";
          Serial.println(pumpCo);

          Wire.beginTransmission(8);
          for (int i = 0; i < pumpCo.length(); i++) {
            Wire.write(pumpCo[i]); // Send each character of the string
          }
          Wire.endTransmission();
          
        } else if (temperature <= tempCO_Off && digitalRead(PUMP_CO_PIN) != LOW) {
          digitalWrite(PUMP_CO_PIN, LOW); // Wyłącz pompę CO.
          String pumpCo = "PompaCO Off";
          Serial.println(pumpCo);

          Wire.beginTransmission(8);
          for (int i = 0; i < pumpCo.length(); i++) {
            Wire.write(pumpCo[i]); // Send each character of the string
          }
          Wire.endTransmission();

        }
      }

      if(sensorNumber == "9D")
      {

      }
    }
    delay(2000); // Opóźnienie między odczytami
  }
}

void printSensorAddresses() {
  // restart sensors init
  sensors.begin();
  Serial.println("Adresy czujników:");
  DeviceAddress deviceAddress;
  for (int i = 0; i < sensors.getDeviceCount(); i++) {
    if (sensors.getAddress(deviceAddress, i)) {
      Serial.print("Czujnik ");
      Serial.print(i);
      Serial.print(": ");
      for (uint8_t j = 0; j < 8; j++) {
        if (deviceAddress[j] < 16) Serial.print("0");
        Serial.print(deviceAddress[j], HEX);
      }
      Serial.println();
    }
  }
  Serial.println();
}


String getAddressEnd(DeviceAddress deviceAddress) {
  String address = "";

  char hexadecimalnum [5];
  sprintf(hexadecimalnum, "%02X", deviceAddress[7]);
  
  address += hexadecimalnum;

  return address;
}
