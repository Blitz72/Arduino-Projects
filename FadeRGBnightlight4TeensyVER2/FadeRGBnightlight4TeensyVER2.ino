//#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
// LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

unsigned int red_brightness = 0;            // initialize red to "on", common 5V anode so 0 is on, 255 is off
unsigned int green_brightness = 255;        // initialize green to "off", common 5V anode so 0 is on, 255 is off
unsigned int blue_brightness = 255;         // initialize blue to "off", common 5V anode so 0 is on, 255 is off
unsigned int max_brightness = 175;                    // maximum brightness
unsigned int brightness = 255;                      // amount to assign to max_brightness via potPinG
byte inPin = 2;                              // push button input pin
byte potPinR = A0;                            // analog input for red pot
byte potPinG = A1;                            // analog input for green pot
byte potPinB = A2;                            // analog input for blue pot
byte redPin = 4;                             // PWM output for red cathode
byte greenPin = 5;                           // PWM output for green cathode
byte bluePin = 9;                            // PWM output for blue cathode
byte fadeAmount = 1;                        // how many points to fade the LED by
byte delayTime = 50;                        // delay time (ms) for dimming effect
byte delayMin = 5;                          // delay time min mapped from potPinR in progNum 1
byte delayMax = 50;                         // delay time max mapped from potPinR in progNum 1
byte progNum = 1;                           // mode number
boolean reading = HIGH;                     // reading from the push button on inPin


void setup()  {
  
//  lcd.begin(20, 4);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(inPin, INPUT_PULLUP);
  //red_brightness = constrain(red_brightness, 0, 255);
  brightness = map(analogRead(potPinB), 0, 1023, max_brightness, 0);
  analogWrite(redPin, brightness);
  //green_brightness = constrain(green_brightness, 0, 255);
  digitalWrite(greenPin, HIGH);
  //blue_brightness = constrain(blue_brightness, 0, 255);
  digitalWrite(bluePin, HIGH);
}


void loop() {
  
switch (progNum) {
  
  case 1:
  
    while (green_brightness > brightness) {
      //green_brightness = constrain(green_brightness, 0, 255);
      brightness = map(analogRead(potPinB), 0, 1023, max_brightness, 0);
      analogWrite(redPin, brightness);
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

/*      lcd.setCursor(0, 0);
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
      lcd.print(" ");            */
    }
    while (red_brightness < 255) {
      //green_brightness = constrain(green_brightness, 0, 255);
      brightness = map(analogRead(potPinB), 0, 1023, max_brightness, 0);
      analogWrite(greenPin, brightness);
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
/*      lcd.setCursor(0, 0);
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
      lcd.print(" ");                  */
    }
    while (blue_brightness > brightness) {
      //blue_brightness = constrain(blue_brightness, 0, 255);
      brightness = map(analogRead(potPinB), 0, 1023, max_brightness, 0);
      analogWrite(greenPin, brightness);
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
/*      lcd.setCursor(0, 0);
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
      lcd.print(" ");                    */
    }
    while (green_brightness < 255) {
      //green_brightness = constrain(green_brightness, 0, 255);
      brightness = map(analogRead(potPinB), 0, 1023, max_brightness, 0);
      if (green_brightness < brightness){
        green_brightness = brightness;
      }
      analogWrite(bluePin, brightness);
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
/*      lcd.setCursor(0, 0);
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
      lcd.print(" ");                    */
    }
    while (red_brightness > brightness) {
      //red_brightness = constrain(red_brightness, 0, 255);
      brightness = map(analogRead(potPinB), 0, 1023, max_brightness, 0);
      analogWrite(bluePin, brightness);
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
/*      lcd.setCursor(0, 0);
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
      lcd.print(" ");                    */
    }
    while (blue_brightness < 255) {
      //blue_brightness = constrain(blue_brightness, 0, 255);
      brightness = map(analogRead(potPinB), 0, 1023, max_brightness, 0);
      if (blue_brightness < brightness){
        blue_brightness = brightness;
      }
      analogWrite(redPin, red_brightness);
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
/*      lcd.setCursor(0, 0);
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
      lcd.print(" ");                    */
      }
  break;

bailout:

  case 2:        // orange

    delayTime = 50;
    brightness = map(analogRead(potPinB), 0, 1023, max_brightness, 0);
    analogWrite(redPin, brightness);
    green_brightness = 180+(brightness/3);
    analogWrite(greenPin, green_brightness);
    digitalWrite(bluePin, HIGH);
    reading = digitalRead(inPin);
      if (reading == LOW) {
        progNum = progNum + 1;
        delay(250);
      }
    delay(delayTime);
/*      lcd.setCursor(0, 0);
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
      lcd.print(" ");                    */
    break;
    
  case 3:        // yellow
    
    delay(50);
    brightness = map(analogRead(potPinB), 0, 1023, max_brightness, 0);
    analogWrite(redPin, brightness);
    analogWrite(greenPin, brightness);
    digitalWrite(bluePin, HIGH);
    reading = digitalRead(inPin);
      if (reading == LOW) {
        progNum = progNum + 1;
        delay(250);
      }
/*      lcd.setCursor(0, 0);
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
      lcd.print(" ");                    */
    break;
      
  case 4:        // green
    
    delay(50);
    brightness = map(analogRead(potPinB), 0, 1023, max_brightness, 0);
    digitalWrite(redPin, HIGH);
    analogWrite(greenPin, brightness);
    digitalWrite(bluePin, HIGH);
    reading = digitalRead(inPin);
      if (reading == LOW) {
        progNum = progNum + 1;
        delay(250);
      }
/*      lcd.setCursor(0, 0);
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
      lcd.print(" ");                    */
    break;
      
  case 5:        // teal
    
    delay(50);
    brightness = map(analogRead(potPinB), 0, 1023, max_brightness, 0);
    digitalWrite(redPin, HIGH);
    analogWrite(greenPin, brightness);
    analogWrite(bluePin, brightness);
    reading = digitalRead(inPin);
      if (reading == LOW) {
        progNum = progNum + 1;
        delay(250);
      }
/*      lcd.setCursor(0, 0);
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
      lcd.print(" ");                    */
    break;

  case 6:        // blue
    
    delay(50);
    brightness = map(analogRead(potPinB), 0, 1023, max_brightness, 0);
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, HIGH);
    analogWrite(bluePin, brightness);
    reading = digitalRead(inPin);
      if (reading == LOW) {
        progNum = progNum + 1;
        delay(250);
      }
/*      lcd.setCursor(0, 0);
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
      lcd.print(" ");                    */
    break;

  case 7:        // purple
    
    delay(50);
    brightness = map(analogRead(potPinB), 0, 1023, max_brightness, 0);
    analogWrite(redPin, brightness);
    digitalWrite(greenPin, HIGH);
    analogWrite(bluePin, brightness);
    reading = digitalRead(inPin);
      if (reading == LOW) {
        progNum = progNum + 1;
        delay(250);
      }
/*      lcd.setCursor(0, 0);
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
      lcd.print(" ");                    */
    break;
    
  case 8:        // pink
    
    delay(50);
    brightness = map(analogRead(potPinB), 0, 1023, max_brightness, 0);
    analogWrite(redPin, brightness);
    green_brightness = 200+(brightness/4);
    analogWrite(greenPin, green_brightness);
    blue_brightness = 50+brightness;
    analogWrite(bluePin, blue_brightness);
    reading = digitalRead(inPin);
      if (reading == LOW) {
        progNum = progNum + 1;
        delay(250);
      }
/*      lcd.setCursor(0, 0);
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
      lcd.print(" ");                    */
    break;
      
  case 9:        // white
    
    delay(50);
    brightness = map(analogRead(potPinB), 0, 1023, max_brightness, 0);
    analogWrite(redPin, brightness);      // I just typed this with my new wireless keyboard from Adafruit!
    analogWrite(greenPin, brightness);
    analogWrite(bluePin, brightness);
    reading = digitalRead(inPin);
      if (reading == LOW) {
        progNum = progNum + 1;
        delay(250);
      }
/*      lcd.setCursor(0, 0);
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
      lcd.print(" ");                    */
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
        red_brightness = brightness;
        digitalWrite(greenPin, HIGH);
        digitalWrite(bluePin, HIGH);
        progNum = 1;
      }
/*      lcd.setCursor(0, 0);
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
      lcd.print(" ");                    */
    break;
    
  }
}
