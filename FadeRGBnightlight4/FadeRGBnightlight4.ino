#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

unsigned int red_brightness = 0;            // initialize red to "on", common 5V anode so 0 is on, 255 is off
unsigned int green_brightness = 255;        // initialize green to "off", common 5V anode so 0 is on, 255 is off
unsigned int blue_brightness = 255;         // initialize blue to "off", common 5V anode so 0 is on, 255 is off
byte max_brightness = 0;                    // maximum brightness
byte brightness = 200;                      // amount to assign to max_brightness via potPinG
int inPin = 2;                              // push button input pin
int potPinR = 0;                            // analog input for red pot
int potPinG = 1;                            // analog input for green pot
int potPinB = 2;                            // analog input for blue pot
int redPin = 3;                             // PWM output for red cathode
int greenPin = 5;                           // PWM output for green cathode
int bluePin = 6;                            // PWM output for blue cathode
byte fadeAmount = 1;                        // how many points to fade the LED by
byte delayTime = 50;                        // delay time (ms) for dimming effect
byte delayMin = 0;                          // delay time min mapped from potPinR in progNum 1
byte delayMax = 50;                         // delay time max mapped from potPinR in progNum 1
byte progNum = 1;                           // mode number
boolean reading = HIGH;                     // reading from the push button on inPin


void setup()  {
  
  lcd.begin(20, 4);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(inPin, INPUT_PULLUP);
}


void loop() {
  
switch (progNum) {
  
  case 1:
  
    //red_brightness = constrain(red_brightness, 0, 255);
    analogWrite(redPin, red_brightness);
    //green_brightness = constrain(green_brightness, 0, 255);
    analogWrite(greenPin, green_brightness);
    //blue_brightness = constrain(blue_brightness, 0, 255);
    analogWrite(bluePin, blue_brightness);
    while (green_brightness > max_brightness) {
      max_brightness = map(analogRead(potPinG), 0, 1023, 0, brightness);
      red_brightness = max_brightness;
      //red_brightness = constrain(red_brightness, 0, 255);
      analogWrite(redPin, red_brightness);                                  //red is at 0 to start, so rewrite if max_brightness changes
      if (green_brightness < max_brightness) {
        green_brightness = max_brightness;
      }
      //green_brightness = constrain(green_brightness, 0, 255);
      analogWrite(greenPin, green_brightness);
      delayTime = map(analogRead(potPinR), 0, 1023, delayMin, delayMax);
      delay(delayTime);
      green_brightness = green_brightness - fadeAmount;
      reading = digitalRead(inPin);
      if (reading == LOW) { 
        progNum = progNum + 1;
        delay(250);
        goto bailout;
        break;
      }
      lcd.setCursor(0, 0);
      lcd.print("r = ");
      lcd.print(red_brightness);
      lcd.print("  ");
      lcd.setCursor(9, 0);
      lcd.print("dly = ");
      lcd.print(delayTime);
      lcd.print(" ");
      lcd.setCursor(0, 1);
      lcd.print("g = ");
      lcd.print(green_brightness);
      lcd.print("  ");
      lcd.print(" ");
      lcd.setCursor(9, 1);
      lcd.print("fade = ");
      lcd.print(fadeAmount);
      lcd.setCursor(0, 2);
      lcd.print("b = ");
      lcd.print(blue_brightness);
      lcd.print("  ");
      lcd.setCursor(9, 2);
      lcd.print("brt = ");
      lcd.print(max_brightness);
      lcd.print(" ");
      lcd.setCursor(0, 3);
      lcd.print("prog = ");
      lcd.print(progNum);
      lcd.print(" ");
    }
    while (red_brightness < 255) {
      max_brightness = map(analogRead(potPinG), 0, 1023, 0, brightness);
      green_brightness = max_brightness;
      //green_brightness = constrain(green_brightness, 0, 255);
      analogWrite(greenPin, green_brightness);                                    //green may be 0, so rewrite if max_brightness changes
      if (red_brightness < max_brightness) {
        red_brightness = max_brightness;
      }
      //red_brightness = constrain(red_brightness, 0, 255);
      analogWrite(redPin, red_brightness);
      delayTime = map(analogRead(potPinR), 0, 1023, delayMin, delayMax);
      delay(delayTime);
      red_brightness = red_brightness + fadeAmount;
      reading = digitalRead(inPin);
      if (reading == LOW) {
        progNum = progNum + 1;
        delay(250);
        goto bailout;
        break;
      }
      lcd.setCursor(0, 0);
      lcd.print("r = ");
      lcd.print(red_brightness);
      lcd.print("  ");
      lcd.setCursor(9, 0);
      lcd.print("dly = ");
      lcd.print(delayTime);
      lcd.print(" ");
      lcd.setCursor(0, 1);
      lcd.print("g = ");
      lcd.print(green_brightness);
      lcd.print("  ");
      lcd.print(" ");
      lcd.setCursor(9, 1);
      lcd.print("fade = ");
      lcd.print(fadeAmount);
      lcd.setCursor(0, 2);
      lcd.print("b = ");
      lcd.print(blue_brightness);
      lcd.print("  ");
      lcd.setCursor(9, 2);
      lcd.print("brt = ");
      lcd.print(max_brightness);
      lcd.print(" ");
      lcd.setCursor(0, 3);
      lcd.print("prog = ");
      lcd.print(progNum);
      lcd.print(" ");
    }
    while (blue_brightness > max_brightness) {
      max_brightness = map(analogRead(potPinG), 0, 1023, 0, brightness);
      green_brightness = max_brightness;
      //green_brightness = constrain(green_brightness, 0, 255);
      analogWrite(greenPin, green_brightness);                                  //green could still be 0, so rewrite if max_brightness changes
      if (blue_brightness < max_brightness) {
        blue_brightness = max_brightness;
      }
      //blue_brightness = constrain(blue_brightness, 0, 255);
      analogWrite(bluePin, blue_brightness);
      delayTime = map(analogRead(potPinR), 0, 1023, delayMin, delayMax);
      delay(delayTime);
      blue_brightness = blue_brightness - fadeAmount;
      reading = digitalRead(inPin);
      if (reading == LOW) {
        progNum = progNum + 1;
        delay(250);
        goto bailout;
        break;
      }
      lcd.setCursor(0, 0);
      lcd.print("r = ");
      lcd.print(red_brightness);
      lcd.print("  ");
      lcd.setCursor(9, 0);
      lcd.print("dly = ");
      lcd.print(delayTime);
      lcd.print(" ");
      lcd.setCursor(0, 1);
      lcd.print("g = ");
      lcd.print(green_brightness);
      lcd.print("  ");
      lcd.print(" ");
      lcd.setCursor(9, 1);
      lcd.print("fade = ");
      lcd.print(fadeAmount);
      lcd.setCursor(0, 2);
      lcd.print("b = ");
      lcd.print(blue_brightness);
      lcd.print("  ");
      lcd.setCursor(9, 2);
      lcd.print("brt = ");
      lcd.print(max_brightness);
      lcd.print(" ");
      lcd.setCursor(0, 3);
      lcd.print("prog = ");
      lcd.print(progNum);
      lcd.print(" ");
    }
    while (green_brightness < 255) {
      max_brightness = map(analogRead(potPinG), 0, 1023, 0, brightness);
      blue_brightness = max_brightness;
      //blue_brightness = constrain(blue_brightness, 0, 255);
      analogWrite(bluePin, blue_brightness);                                      //blue may be 0, so rewrite if max_brightness changes
      if (green_brightness < max_brightness) {
        green_brightness = max_brightness;
      }
      //green_brightness = constrain(green_brightness, 0, 255);
      analogWrite(greenPin, green_brightness);
      delayTime = map(analogRead(potPinR), 0, 1023, delayMin, delayMax);
      delay(delayTime);
      green_brightness = green_brightness + fadeAmount;
      reading = digitalRead(inPin);
      if (reading == LOW) {
        progNum = progNum + 1;
        delay(250);
        goto bailout;
        break;
      }
      lcd.setCursor(0, 0);
      lcd.print("r = ");
      lcd.print(red_brightness);
      lcd.print("  ");
      lcd.setCursor(9, 0);
      lcd.print("dly = ");
      lcd.print(delayTime);
      lcd.print(" ");
      lcd.setCursor(0, 1);
      lcd.print("g = ");
      lcd.print(green_brightness);
      lcd.print("  ");
      lcd.print(" ");
      lcd.setCursor(9, 1);
      lcd.print("fade = ");
      lcd.print(fadeAmount);
      lcd.setCursor(0, 2);
      lcd.print("b = ");
      lcd.print(blue_brightness);
      lcd.print("  ");
      lcd.setCursor(9, 2);
      lcd.print("brt = ");
      lcd.print(max_brightness);
      lcd.print(" ");
      lcd.setCursor(0, 3);
      lcd.print("prog = ");
      lcd.print(progNum);
      lcd.print(" ");
    }
    while (red_brightness > max_brightness) {
      max_brightness = map(analogRead(potPinG), 0, 1023, 0, brightness);
      blue_brightness = max_brightness;
      //blue_brightness = constrain(blue_brightness, 0, 255);
      analogWrite(bluePin, blue_brightness);                                    //blue could still be 0, so rewrite if max_brightness changes
      if (red_brightness < max_brightness) {
        red_brightness = max_brightness;
      }
      //red_brightness = constrain(red_brightness, 0, 255);
      analogWrite(redPin, red_brightness);
      delayTime = map(analogRead(potPinR), 0, 1023, delayMin, delayMax);
      delay(delayTime);
      red_brightness = red_brightness - fadeAmount;
      reading = digitalRead(inPin);
      if (reading == LOW) {
        progNum = progNum + 1;
        delay(250);
        goto bailout;
        break;
      }
      lcd.setCursor(0, 0);
      lcd.print("r = ");
      lcd.print(red_brightness);
      lcd.print("  ");
      lcd.setCursor(9, 0);
      lcd.print("dly = ");
      lcd.print(delayTime);
      lcd.print(" ");
      lcd.setCursor(0, 1);
      lcd.print("g = ");
      lcd.print(green_brightness);
      lcd.print("  ");
      lcd.print(" ");
      lcd.setCursor(9, 1);
      lcd.print("fade = ");
      lcd.print(fadeAmount);
      lcd.setCursor(0, 2);
      lcd.print("b = ");
      lcd.print(blue_brightness);
      lcd.print("  ");
      lcd.setCursor(9, 2);
      lcd.print("brt = ");
      lcd.print(max_brightness);
      lcd.print(" ");
      lcd.setCursor(0, 3);
      lcd.print("prog = ");
      lcd.print(progNum);
      lcd.print(" ");
    }
    while (blue_brightness < 255) {
      max_brightness = map(analogRead(potPinG), 0, 1023, 0, brightness);
      red_brightness = max_brightness;
      //red_brightness = constrain(red_brightness, 0, 255);
      analogWrite(redPin, red_brightness);                                    //red may be 0, so rewrite if max_brightness changes
      if (blue_brightness < max_brightness) {
        blue_brightness = max_brightness;
      }
      //blue_brightness = constrain(blue_brightness, 0, 255);
      analogWrite(bluePin, blue_brightness);
      delayTime = map(analogRead(potPinR), 0, 1023, delayMin, delayMax);
      delay(delayTime);
      blue_brightness = blue_brightness + fadeAmount;
      reading = digitalRead(inPin);
      if (reading == LOW) {
        progNum = progNum + 1;
        delay(250);
        goto bailout;
        break;
      }
      lcd.setCursor(0, 0);
      lcd.print("r = ");
      lcd.print(red_brightness);
      lcd.print("  ");
      lcd.setCursor(9, 0);
      lcd.print("dly = ");
      lcd.print(delayTime);
      lcd.print(" ");
      lcd.setCursor(0, 1);
      lcd.print("g = ");
      lcd.print(green_brightness);
      lcd.print("  ");
      lcd.print(" ");
      lcd.setCursor(9, 1);
      lcd.print("fade = ");
      lcd.print(fadeAmount);
      lcd.setCursor(0, 2);
      lcd.print("b = ");
      lcd.print(blue_brightness);
      lcd.print("  ");
      lcd.setCursor(9, 2);
      lcd.print("brt = ");
      lcd.print(max_brightness);
      lcd.print(" ");
      lcd.setCursor(0, 3);
      lcd.print("prog = ");
      lcd.print(progNum);
      lcd.print(" ");
      }
  break;

bailout:

  case 2:        // orange

    delayTime = 50;
    max_brightness = map(analogRead(potPinG), 0, 1023, 0, brightness);
    analogWrite(redPin, max_brightness);
    green_brightness = 175/255*(255 - max_brightness);
    analogWrite(greenPin, green_brightness);
    digitalWrite(bluePin, HIGH);
    reading = digitalRead(inPin);
      if (reading == LOW) {
        progNum = progNum + 1;
        delay(250);
      }
    delay(delayTime);
      lcd.setCursor(0, 0);
      lcd.print("r = ");
      lcd.print(red_brightness);
      lcd.print("  ");
      lcd.setCursor(9, 0);
      lcd.print("dly = ");
      lcd.print(delayTime);
      lcd.print(" ");
      lcd.setCursor(0, 1);
      lcd.print("g = ");
      lcd.print(green_brightness);
      lcd.print("  ");
      lcd.print(" ");
      lcd.setCursor(9, 1);
      lcd.print("fade = ");
      lcd.print(fadeAmount);
      lcd.setCursor(0, 2);
      lcd.print("b = ");
      lcd.print(blue_brightness);
      lcd.print("  ");
      lcd.setCursor(9, 2);
      lcd.print("brt = ");
      lcd.print(max_brightness);
      lcd.print(" ");
      lcd.setCursor(0, 3);
      lcd.print("prog = ");
      lcd.print(progNum);
      lcd.print(" ");
    break;
    
  case 3:        // yellow
    
    delay(50);
    max_brightness = map(analogRead(potPinG), 0, 1023, 0, brightness);
    analogWrite(redPin, max_brightness);
    analogWrite(greenPin, max_brightness);
    digitalWrite(bluePin, HIGH);
    reading = digitalRead(inPin);
      if (reading == LOW) {
        progNum = progNum + 1;
        delay(250);
      }
      lcd.setCursor(0, 0);
      lcd.print("r = ");
      lcd.print(red_brightness);
      lcd.print("  ");
      lcd.setCursor(9, 0);
      lcd.print("dly = ");
      lcd.print(delayTime);
      lcd.print(" ");
      lcd.setCursor(0, 1);
      lcd.print("g = ");
      lcd.print(green_brightness);
      lcd.print("  ");
      lcd.print(" ");
      lcd.setCursor(9, 1);
      lcd.print("fade = ");
      lcd.print(fadeAmount);
      lcd.setCursor(0, 2);
      lcd.print("b = ");
      lcd.print(blue_brightness);
      lcd.print("  ");
      lcd.setCursor(9, 2);
      lcd.print("brt = ");
      lcd.print(max_brightness);
      lcd.print(" ");
      lcd.setCursor(0, 3);
      lcd.print("prog = ");
      lcd.print(progNum);
      lcd.print(" ");
    break;
      
  case 4:        // green
    
    delay(50);
    max_brightness = map(analogRead(potPinG), 0, 1023, 0, brightness);
    digitalWrite(redPin, HIGH);
    analogWrite(greenPin, max_brightness);
    digitalWrite(bluePin, HIGH);
    reading = digitalRead(inPin);
      if (reading == LOW) {
        progNum = progNum + 1;
        delay(250);
      }
      lcd.setCursor(0, 0);
      lcd.print("r = ");
      lcd.print(red_brightness);
      lcd.print("  ");
      lcd.setCursor(9, 0);
      lcd.print("dly = ");
      lcd.print(delayTime);
      lcd.print(" ");
      lcd.setCursor(0, 1);
      lcd.print("g = ");
      lcd.print(green_brightness);
      lcd.print("  ");
      lcd.print(" ");
      lcd.setCursor(9, 1);
      lcd.print("fade = ");
      lcd.print(fadeAmount);
      lcd.setCursor(0, 2);
      lcd.print("b = ");
      lcd.print(blue_brightness);
      lcd.print("  ");
      lcd.setCursor(9, 2);
      lcd.print("brt = ");
      lcd.print(max_brightness);
      lcd.print(" ");
      lcd.setCursor(0, 3);
      lcd.print("prog = ");
      lcd.print(progNum);
      lcd.print(" ");
    break;
      
  case 5:        // teal
    
    delay(50);
    max_brightness = map(analogRead(potPinG), 0, 1023, 0, brightness);
    digitalWrite(redPin, HIGH);
    analogWrite(greenPin, max_brightness);
    analogWrite(bluePin, max_brightness);
    reading = digitalRead(inPin);
      if (reading == LOW) {
        progNum = progNum + 1;
        delay(250);
      }
      lcd.setCursor(0, 0);
      lcd.print("r = ");
      lcd.print(red_brightness);
      lcd.print("  ");
      lcd.setCursor(9, 0);
      lcd.print("dly = ");
      lcd.print(delayTime);
      lcd.print(" ");
      lcd.setCursor(0, 1);
      lcd.print("g = ");
      lcd.print(green_brightness);
      lcd.print("  ");
      lcd.print(" ");
      lcd.setCursor(9, 1);
      lcd.print("fade = ");
      lcd.print(fadeAmount);
      lcd.setCursor(0, 2);
      lcd.print("b = ");
      lcd.print(blue_brightness);
      lcd.print("  ");
      lcd.setCursor(9, 2);
      lcd.print("brt = ");
      lcd.print(max_brightness);
      lcd.print(" ");
      lcd.setCursor(0, 3);
      lcd.print("prog = ");
      lcd.print(progNum);
      lcd.print(" ");
    break;

  case 6:        // blue
    
    delay(50);
    max_brightness = map(analogRead(potPinG), 0, 1023, 0, brightness);
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, HIGH);
    analogWrite(bluePin, max_brightness);
    reading = digitalRead(inPin);
      if (reading == LOW) {
        progNum = progNum + 1;
        delay(250);
      }
      lcd.setCursor(0, 0);
      lcd.print("r = ");
      lcd.print(red_brightness);
      lcd.print("  ");
      lcd.setCursor(9, 0);
      lcd.print("dly = ");
      lcd.print(delayTime);
      lcd.print(" ");
      lcd.setCursor(0, 1);
      lcd.print("g = ");
      lcd.print(green_brightness);
      lcd.print("  ");
      lcd.print(" ");
      lcd.setCursor(9, 1);
      lcd.print("fade = ");
      lcd.print(fadeAmount);
      lcd.setCursor(0, 2);
      lcd.print("b = ");
      lcd.print(blue_brightness);
      lcd.print("  ");
      lcd.setCursor(9, 2);
      lcd.print("brt = ");
      lcd.print(max_brightness);
      lcd.print(" ");
      lcd.setCursor(0, 3);
      lcd.print("prog = ");
      lcd.print(progNum);
      lcd.print(" ");
    break;

  case 7:        // purple
    
    delay(50);
    max_brightness = map(analogRead(potPinG), 0, 1023, 0, brightness);
    red_brightness = 125/255*(255 - max_brightness);
    analogWrite(redPin, red_brightness);
    digitalWrite(greenPin, HIGH);
    analogWrite(bluePin, max_brightness);
    reading = digitalRead(inPin);
      if (reading == LOW) {
        progNum = progNum + 1;
        delay(250);
      }
      lcd.setCursor(0, 0);
      lcd.print("r = ");
      lcd.print(red_brightness);
      lcd.print("  ");
      lcd.setCursor(9, 0);
      lcd.print("dly = ");
      lcd.print(delayTime);
      lcd.print(" ");
      lcd.setCursor(0, 1);
      lcd.print("g = ");
      lcd.print(green_brightness);
      lcd.print("  ");
      lcd.print(" ");
      lcd.setCursor(9, 1);
      lcd.print("fade = ");
      lcd.print(fadeAmount);
      lcd.setCursor(0, 2);
      lcd.print("b = ");
      lcd.print(blue_brightness);
      lcd.print("  ");
      lcd.setCursor(9, 2);
      lcd.print("brt = ");
      lcd.print(max_brightness);
      lcd.print(" ");
      lcd.setCursor(0, 3);
      lcd.print("prog = ");
      lcd.print(progNum);
      lcd.print(" ");
    break;
    
  case 8:        // pink
    
    delay(50);
    analogWrite(redPin, max_brightness);
    green_brightness = 200/255*(255 - max_brightness);
    analogWrite(greenPin, green_brightness);
    blue_brightness = 50/255*(255 - max_brightness);
    analogWrite(bluePin, blue_brightness);
    reading = digitalRead(inPin);
      if (reading == LOW) {
        progNum = progNum + 1;
        delay(250);
      }
      lcd.setCursor(0, 0);
      lcd.print("r = ");
      lcd.print(red_brightness);
      lcd.print("  ");
      lcd.setCursor(9, 0);
      lcd.print("dly = ");
      lcd.print(delayTime);
      lcd.print(" ");
      lcd.setCursor(0, 1);
      lcd.print("g = ");
      lcd.print(green_brightness);
      lcd.print("  ");
      lcd.print(" ");
      lcd.setCursor(9, 1);
      lcd.print("fade = ");
      lcd.print(fadeAmount);
      lcd.setCursor(0, 2);
      lcd.print("b = ");
      lcd.print(blue_brightness);
      lcd.print("  ");
      lcd.setCursor(9, 2);
      lcd.print("brt = ");
      lcd.print(max_brightness);
      lcd.print(" ");
      lcd.setCursor(0, 3);
      lcd.print("prog = ");
      lcd.print(progNum);
      lcd.print(" ");
    break;
      
  case 9:        // white
    
    delay(50);
    analogWrite(redPin, max_brightness);      // I just typed this with my new wireless keyboard from Adafruit!
    analogWrite(greenPin, max_brightness);
    analogWrite(bluePin, max_brightness);
    reading = digitalRead(inPin);
      if (reading == LOW) {
        progNum = progNum + 1;
        delay(250);
      }
      lcd.setCursor(0, 0);
      lcd.print("r = ");
      lcd.print(red_brightness);
      lcd.print("  ");
      lcd.setCursor(9, 0);
      lcd.print("dly = ");
      lcd.print(delayTime);
      lcd.print(" ");
      lcd.setCursor(0, 1);
      lcd.print("g = ");
      lcd.print(green_brightness);
      lcd.print("  ");
      lcd.print(" ");
      lcd.setCursor(9, 1);
      lcd.print("fade = ");
      lcd.print(fadeAmount);
      lcd.setCursor(0, 2);
      lcd.print("b = ");
      lcd.print(blue_brightness);
      lcd.print("  ");
      lcd.setCursor(9, 2);
      lcd.print("brt = ");
      lcd.print(max_brightness);
      lcd.print(" ");
      lcd.setCursor(0, 3);
      lcd.print("prog = ");
      lcd.print(progNum);
      lcd.print(" ");
    break;

  case 10:

    delay(50);
    red_brightness = map(analogRead(potPinR), 0, 1023, 255, 0);    
    green_brightness = map(analogRead(potPinG), 0, 1023, 255, 0);                
    blue_brightness = map(analogRead(potPinB), 0, 1023, 255, 0);
    analogWrite(redPin, red_brightness);
    analogWrite(greenPin, green_brightness);
    analogWrite(bluePin, blue_brightness);
      reading = digitalRead(inPin);
      if (reading == LOW) {
        delay(250);
        red_brightness = 0;
        green_brightness = 255;
        blue_brightness = 255;
        progNum = 1;
      }
          lcd.setCursor(0, 0);
      lcd.print("r = ");
      lcd.print(red_brightness);
      lcd.print("  ");
      lcd.setCursor(9, 0);
      lcd.print("dly = ");
      lcd.print(delayTime);
      lcd.print(" ");
      lcd.setCursor(0, 1);
      lcd.print("g = ");
      lcd.print(green_brightness);
      lcd.print("  ");
      lcd.print(" ");
      lcd.setCursor(9, 1);
      lcd.print("fade = ");
      lcd.print(fadeAmount);
      lcd.setCursor(0, 2);
      lcd.print("b = ");
      lcd.print(blue_brightness);
      lcd.print("  ");
      lcd.setCursor(9, 2);
      lcd.print("brt = ");
      lcd.print(max_brightness);
      lcd.print(" ");
      lcd.setCursor(0, 3);
      lcd.print("prog = ");
      lcd.print(progNum);
      lcd.print(" ");
    break;
    
  }
}
