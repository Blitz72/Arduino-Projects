#include <Ultrasonic.h>

#define modePin       3
#define greenPin      4
#define amberPin      5
#define redPin        6
#define PIRpin        8
#define sensorTrig    9
#define sensorEcho    10
#define powerPin      15  //Analog 1
#define adjustPin     A4
//#define groundPin     19

Ultrasonic ultrasonic(sensorTrig, sensorEcho); // (Trig PIN,Echo PIN)

int delayTime = 300;
int PIRstatus = 0;
int distance = 0;
int modeStatus = 1;
int adjustVal = 0;
int x = 0;
int deadZone = 2;
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;

void modeSelect() {
  if (digitalRead(modePin) == LOW){
    modeStatus = 1;
  }
  else {
    modeStatus = 2;
  }
}

void setup() {
  pinMode(powerPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(amberPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(PIRpin, INPUT);
  pinMode(sensorTrig, OUTPUT);
  pinMode(sensorEcho, INPUT);
  pinMode(modePin, INPUT_PULLUP);
  pinMode(adjustPin, INPUT);
  pinMode(powerPin, OUTPUT);
//  pinMode(groundPin, OUTPUT);
  attachInterrupt(1, modeSelect, CHANGE);
  digitalWrite(powerPin, HIGH);
//  digitalWrite(groundPin, LOW);
  digitalWrite(redPin, LOW);
  digitalWrite(amberPin, LOW);
  digitalWrite(greenPin, LOW);
  delay(5000);
  digitalWrite(redPin, HIGH);
  digitalWrite(amberPin, HIGH);
  digitalWrite(greenPin, HIGH);
  previousMillis = 1000;
//  DDRB = DDRB | 0x07;
//  PORTB = PORTB & 0xf8
}

void loop() {
  modeSelect();
  switch (modeStatus){
    case 1:
    PIRstatus = digitalRead(PIRpin);
    if (PIRstatus == HIGH) {
      x = analogRead(adjustPin);
      adjustVal = map(x, 0, 1023, 200, 20);
      distance = ultrasonic.Ranging(CM);
      if (distance > (adjustVal + 30 + deadZone)) {
        digitalWrite(greenPin, LOW);
        digitalWrite(amberPin, HIGH);
        digitalWrite(redPin, HIGH);
      }
      else if ((distance > (adjustVal + deadZone)) && (distance <= (adjustVal + 30 - deadZone))) {
        digitalWrite(amberPin, LOW);
        digitalWrite(greenPin, HIGH);
        digitalWrite(redPin, HIGH);
      }
      else if (distance <= (adjustVal)) {
        digitalWrite(redPin, LOW);
        digitalWrite(amberPin, HIGH);
        digitalWrite(greenPin, HIGH);
      }
      delay(delayTime);
    }
    else {
      digitalWrite(redPin, HIGH);
      digitalWrite(amberPin, HIGH);
      digitalWrite(greenPin, HIGH);
    }
    previousMillis = millis();
    break;
    case 2:
    PIRstatus = digitalRead(PIRpin);
    if (PIRstatus == HIGH) {
      currentMillis = millis();
      if (currentMillis - previousMillis < 15000){
        digitalWrite(greenPin, LOW);  //green ON
        digitalWrite(amberPin, HIGH);
        digitalWrite(redPin, HIGH);
      }
      if ((currentMillis - previousMillis > 15000) && (currentMillis - previousMillis < 20000)) {
        digitalWrite(amberPin, LOW);  //amber ON
        digitalWrite(greenPin, HIGH);
      }
      if ((currentMillis - previousMillis > 20000) && (currentMillis - previousMillis < 30000)) {
        digitalWrite(redPin, LOW);  //red ON
        digitalWrite(amberPin, HIGH);
      }
      if (currentMillis - previousMillis > 30000) {
        digitalWrite(redPin, HIGH);
        previousMillis = millis();
      }
    }
    break;
  }
}
