#include <AFMotor.h>
#include <SoftwareSerial.h>
#define rxPin 2
#define txPin 3

AF_DCMotor lewyPrzod(1);
AF_DCMotor lewyTyl(2);
AF_DCMotor prawyPrzod(3);
AF_DCMotor prawyTyl(4);

SoftwareSerial bt(rxPin, txPin);

void predkosc(int predkosc) {
  lewyPrzod.setSpeed(predkosc);
  lewyTyl.setSpeed(predkosc);
  prawyPrzod.setSpeed(predkosc);
  prawyTyl.setSpeed(predkosc);
}
enum kierunek {
  stop = 0,
  przod = 1,
  tyl = 2,
  lewo = 3,
  prawo = 4
};

void setup() {
  digitalWrite(13, HIGH);
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  predkosc(255);
  Serial.begin(9600);
  bt.begin(9600);
}

void loop() {
  if(bt.available()>0){
    Serial.println(bt.read());
  }
  kierunek war;
  //ruch(war = lewo);
  
  int X, Y;
  X = analogRead(A0);
  Y = analogRead(A1);
  //  Serial.print("x = ");
  //  Serial.print(X);
  //  Serial.print(" y = ");
  //  Serial.println(Y);

  ruchJoy(X, Y);
  delay(100);
}

void ruchJoy(int x, int y) {

  lewyPrzod.run(RELEASE);
  lewyTyl.run(RELEASE);
  prawyPrzod.run(RELEASE);
  prawyTyl.run(RELEASE);

  if (x > 70 || x < 50) {

    if (x > 70) { // tyl
      lewyPrzod.run(BACKWARD);
      lewyTyl.run(BACKWARD);
      prawyPrzod.run(BACKWARD);
      prawyTyl.run(BACKWARD);
    }
    else if (x < 50) { // przod
      lewyPrzod.run(FORWARD);
      lewyTyl.run(FORWARD);
      prawyPrzod.run(FORWARD);
      prawyTyl.run(FORWARD);
    }
  }
  else if ( y > 70 || y < 50) {

    if (y > 70) { // prawo
      lewyPrzod.run(FORWARD);
      lewyTyl.run(FORWARD);
      prawyPrzod.run(BACKWARD);
      prawyTyl.run(BACKWARD);
    }
    else if (y < 50) { // lewo
      lewyPrzod.run(BACKWARD);
      lewyTyl.run(BACKWARD);
      prawyPrzod.run(FORWARD);
      prawyTyl.run(FORWARD);
    }
  }

}


void ruch(int x)
{
  if (x == 1 ) { // przod
    lewyPrzod.run(FORWARD);
    lewyTyl.run(FORWARD);
    prawyPrzod.run(FORWARD);
    prawyTyl.run(FORWARD);
  }
  else if (x == 2) { // tyl
    lewyPrzod.run(BACKWARD);
    lewyTyl.run(BACKWARD);
    prawyPrzod.run(BACKWARD);
    prawyTyl.run(BACKWARD);
  }
  else if (x == 3) { // lewo
    lewyPrzod.run(BACKWARD);
    lewyTyl.run(BACKWARD);
    prawyPrzod.run(FORWARD);
    prawyTyl.run(FORWARD);
  }
  else if (x == 4) { // prawo
    lewyPrzod.run(FORWARD);
    lewyTyl.run(FORWARD);
    prawyPrzod.run(BACKWARD);
    prawyTyl.run(BACKWARD);
  }
  else { // stop
    lewyPrzod.run(RELEASE);
    lewyTyl.run(RELEASE);
    prawyPrzod.run(RELEASE);
    prawyTyl.run(RELEASE);
  }

}
