#include <Wire.h>

#define buttonPin 2

int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers
byte triggerVal = 0;
boolean state = false;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
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
