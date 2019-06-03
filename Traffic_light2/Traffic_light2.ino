#include <NewPing.h>

#define modePin       3
#define greenPin      4
#define amberPin      5
#define redPin        6
#define PIRpin        8
#define sensorTrig    9
#define sensorEcho    10
#define maxDistance   450
#define adjustPin     A0

NewPing sonar(sensorTrig, sensorEcho, maxDistance); // (Trig PIN,Echo PIN)

// Sets the delay time between sensor reads
int delayTime = 300;
//byte PIRstatus = 0;
int distance = 0;
byte modeStatus = 2;
int sensorAdjustValue = 0;
int adjustVal = 0;
int deadZone = 1;
int amberDistance = 50;
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;

void modeSelect(){
  if (digitalRead(modePin) == LOW){
    modeStatus = 1;
  }
  else if (digitalRead(modePin) == HIGH) {
    modeStatus = 2;
  }
}

void setup(){
  Serial.begin(9600);
  pinMode(greenPin, OUTPUT);
  pinMode(amberPin, OUTPUT);
  pinMode(redPin, OUTPUT);
//  pinMode(PIRpin, INPUT);
  pinMode(sensorTrig, OUTPUT);
  pinMode(sensorEcho, INPUT);
  pinMode(modePin, INPUT_PULLUP);
  pinMode(adjustPin, INPUT);
  attachInterrupt(1, modeSelect, CHANGE);
  digitalWrite(redPin, LOW);
  digitalWrite(amberPin, LOW);
  digitalWrite(greenPin, LOW);
  delay(2000);
  digitalWrite(redPin, HIGH);
  digitalWrite(amberPin, HIGH);
  digitalWrite(greenPin, HIGH);
  delay(500);
//  previousMillis = 5000;
}

void loop(){
  modeSelect();
  switch (modeStatus){
    case 1:
    // Check to see if we have motion
//    PIRstatus = digitalRead(PIRpin);
//    if (PIRstatus == HIGH){
      // Uses the potentiometer connected to the adjustPin to set the "stop" distance
      sensorAdjustValue = analogRead(adjustPin);
      adjustVal = map(sensorAdjustValue, 0, 1023, 20, 200);
//      distance = sonar.ping_cm();
      distance = sonar.ping_median(5)/58.5;
      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.println(" cm");
      if (distance > (adjustVal + amberDistance + deadZone)){
        digitalWrite(greenPin, LOW);
        digitalWrite(amberPin, HIGH);
        digitalWrite(redPin, HIGH);
      }
      else if ((distance > (adjustVal + deadZone)) && (distance <= (adjustVal + amberDistance - deadZone))){
        digitalWrite(amberPin, LOW);
        digitalWrite(greenPin, HIGH);
        digitalWrite(redPin, HIGH);
      }
      else if (distance <= adjustVal && distance != 0){
        digitalWrite(redPin, LOW);
        digitalWrite(amberPin, HIGH);
        digitalWrite(greenPin, HIGH);
      }
      else if (distance == 0) {   //distance greater then maxDistance is returned as 0
        digitalWrite(redPin, HIGH);
        digitalWrite(amberPin, HIGH);
        digitalWrite(greenPin, HIGH);
      }
      delay(delayTime);
//    }
//    else {
//      digitalWrite(redPin, HIGH);
//      digitalWrite(amberPin, HIGH);
//      digitalWrite(greenPin, HIGH);
//    }
//    previousMillis = millis();
    break;
    case 2:
//    PIRstatus = digitalRead(PIRpin);
//    if (PIRstatus == HIGH){
      currentMillis = millis();
      if (currentMillis - previousMillis > 0 && (currentMillis - previousMillis < 10000)){
        digitalWrite(greenPin, LOW);  //green ON
        digitalWrite(amberPin, HIGH);
        digitalWrite(redPin, HIGH);
      }
      else if ((currentMillis - previousMillis > 10000) && (currentMillis - previousMillis < 13000)){
        digitalWrite(amberPin, LOW);  //amber ON
        digitalWrite(greenPin, HIGH);
        digitalWrite(redPin, HIGH);
      }
      else if ((currentMillis - previousMillis > 13000) && (currentMillis - previousMillis < 18000)){
        digitalWrite(redPin, LOW);  //red ON
        digitalWrite(amberPin, HIGH);
        digitalWrite(greenPin, HIGH);
      }
      else if (currentMillis - previousMillis > 18000){
        digitalWrite(redPin, HIGH);
        previousMillis = millis();
      }
//    }
    break;
  }
}
    
