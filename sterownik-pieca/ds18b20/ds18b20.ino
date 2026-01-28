#include <Wire.h>
#include <LiquidCrystal_I2C.h>
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

// Konfiguracja wyświetlacza LCD z I2C
// Adres I2C wyświetlacza (zwykle 0x27 lub 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup(void)
{
  Serial.begin(9600);
  sensors.begin();

  // Inicjalizacja LCD
  lcd.init();
  // Włączenie podświetlenia
  lcd.backlight();

   // Ustawienie pinu przycisku jako wejście
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Używam INPUT_PULLUP, aby uniknąć konieczności stosowania zewnętrznego rezystora
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

  // Wyczyszczenie wyświetlacza
  lcd.clear();

  // Odczyt temperatury i wyświetlanie z dwoma ostatnimi znakami adresu dla każdego czujnika
  for (int i = 0; i < sensors.getDeviceCount(); i++) {
    float temperature = sensors.getTempCByIndex(i);
    DeviceAddress address;
    if (sensors.getAddress(address, i)) {

      lcd.setCursor(0, i);
      lcd.print("Sensor ");
      printAddressEnd(address, lcd);
      lcd.print(": ");
      lcd.print(temperature);
      lcd.print((char)223); // Symbol stopnia
      lcd.print("C");

      // Serial.print("Temperatura czujnika ");
      // printAddressEnd(address, lcd);
      // Serial.print(": ");
      // Serial.print(temperature);
      // Serial.println("°C");
    }
  }
  // Serial.println();
  delay(5000); // Opóźnienie między odczytami
}

void printSensorAddresses() {
  // restart sensors init
  sensors.begin();
  Serial.println("Adresy czujników:");
  DeviceAddress deviceAddress;
  for (int i = 0; i < sensors.getDeviceCount(); i++) {
    if (sensors.getAddress(deviceAddress, i)) {
      Serial.print("Sensor ");
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

void printAddressEnd(DeviceAddress deviceAddress, LiquidCrystal_I2C &lcd) {
  // Wypisanie dwóch ostatnich znaków adresu czujnika
  if (deviceAddress[7] < 16) 
  {
    // Serial.print("0");
    lcd.print("0");
  }
  // Serial.print(deviceAddress[7], HEX);
  lcd.print(deviceAddress[7], HEX);
}