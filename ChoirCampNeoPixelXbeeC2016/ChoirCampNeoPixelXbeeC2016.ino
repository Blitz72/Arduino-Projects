#include <SoftwareSerial.h>
#include <Wire.h>

#define buttonPin 2

int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers
byte triggerVal = 0;
boolean state = false;

SoftwareSerial mySerial(11, 3); // RX, TX

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  mySerial.begin(9600);
  
//  Serial.begin(9600);
//  while (!Serial) {
//    ; // wait for serial port to connect. Needed for native USB port only
//  }
}

void loop(void) {
  
  int reading = digitalRead(buttonPin);
  
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        state = !state;
        if (state == true) triggerVal = B01110010;
        else triggerVal = !triggerVal;
        Serial.write(triggerVal);
      }
    }
  }
  lastButtonState = reading;
}
