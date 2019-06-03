#include <SoftwareSerial.h>
#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
//#include <TinyGPS.h>

// Configuration information

//#define _SS_MAX_RX_BUFF 72

#define DEFAULT_MINUTES 15              // default 15 minutes, type integer
#define DEFAULT_SECONDS 0               // default 0 seconds, type integer
#define DEFAULT_SENSOR_READING 1000      // default 100, should be in the range 70 - 512, 512 = minimum sensor distance (20cm)
#define BEEPER_ENABLE true              // default true, (true, false) true enables tower light beeper

#define DISPLAY_ADDRESS 0x70
#define MPU_ADDRESS 0x68

#define sensorPin A0
#define greenPin 4
#define amberPin 5
#define redPin 6
#define buzzerPin 7

#define TX_ACK 0x01
#define NO_TX_ACK 0x00

//#define GPS_TESTING_INTERVAL 5000
//#define GPS_INTERVAL 60000

// Constructor for 7-segment display
Adafruit_7segment timerDisplay = Adafruit_7segment();

// Constructor for SoftwareSerial
SoftwareSerial xbeeSerial(10, 11); // RX, TX
//SoftwareSerial gpsSerial(12, 13); // RX, TX: For Mega2560 testing use 12, 13 otherwise use 8, 9 for Uno

// Constructor for TinyGPS
//TinyGPS gps;

int8_t minutes = DEFAULT_MINUTES;
int8_t seconds = DEFAULT_SECONDS;
int timer = (minutes * 100) + seconds;

float latitude = 41.54046; // NELA Security Parking = (41.54036 - 41.54056)
float longitude = -81.56100; // NELA Security Parking = (-81.56060 - -81.56141)

//uint32_t currentMillis = 0;
uint32_t previousMillis = 0;
//const uint32_t gpsInterval = GPS_TESTING_INTERVAL;

uint16_t sensorVal = 0;

bool blinkColon = false;
bool triggered = false;
const bool beeper = BEEPER_ENABLE;
bool isReset = true;



//  ----------------------------------------------------------------- SETUP ---------------------------------------------------------------------------

void setup() {

  Serial.begin(9600);
  xbeeSerial.begin(9600);  // Xbee serial port
//  gpsSerial.begin(9600);  // GPS serial port

  // Setup timer 7-segment display
  timerDisplay.begin(0x70);

  // Initialize relay module outputs
  // Arduino Port D controls digital pins D0, D1, D2, D3, D4, D5, D6, D7
  DDRD |= 0xf0;
  PORTD |= 0xf0;

  delay(50);

  xbeeSerial.listen();

  clearDisplay();

  delay(50);

  // 7 segment display test: check all LED segments, decimal point and colon dots on startup
  timerDisplay.print(8888, DEC);
  timerDisplay.writeDigitRaw(2, 0x1e);
  timerDisplay.writeDisplay();

  // Test relay module outputs on startup
  PORTD &= 0x0f;

  delay(500);

  PORTD |= 0xf0;

  clearDisplay();
  
}

//  ------------------------------------------------------------------ LOOP ----------------------------------------------------------------------------

void loop() {
  
  sensorVal = analogRead(sensorPin);
  
  Serial.print("Sensor: ");
  Serial.println(sensorVal);

  // Check to see if a vehicle is present
  if (sensorVal > 100 && triggered == false) {
    
    delay(10000);
    if (analogRead(sensorPin) > DEFAULT_SENSOR_READING) {
      triggered = true;
    } else {
      triggered = false;
    }
    
  }

  // Check GPS coordinates while the meter is inactive
//  if (!triggered) {
//
//    gpsSerial.listen();
//    bool newData = false;
//
//    uint32_t currentMillis = millis();
//    if (currentMillis - previousMillis > gpsInterval) {
//      
//      Serial.println("Checking GPS coordinates...");
//
//      //if (gpsSerial.available() >= 0) {
//        Serial.println(gpsSerial.available());
//        if (gpsSerial.overflow()) Serial.println("Soft Serial Overflow");
//        while (gpsSerial.available()) {
//          char c = gpsSerial.read();
//          Serial.print(c);
//          if (gps.encode(c)) newData = true;
//        }
//      //}
//      
//      if (newData) {
//        float flat, flon;
//        uint32_t fix_age;
//        gps.f_get_position(&flat, &flon, &fix_age);
//        Serial.print(flat, 5);
//        Serial.print(", ");
//        Serial.println(flon, 5);
//      }
//      previousMillis = currentMillis;
//      
//    }
//    
//  }  // else {
////    xbeeSerial.listen();
////  }

  if (sensorVal <= DEFAULT_SENSOR_READING && triggered) {
    triggered = false;
  }

  if (triggered) {

    isReset = false;
    
    digitalWrite(redPin, HIGH);
//    digitalWrite(amberPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(buzzerPin, HIGH);
    
    if (timer <= 0){
      Serial.println("Time's up!");
      seconds = 0;
      timerDone();
    }

    if (timer <= 200) {
      if (blinkColon) {
        digitalWrite(greenPin, HIGH);
//        digitalWrite(amberPin, LOW);      // If tower light has amber light
      } else {
        digitalWrite(greenPin, LOW);
      }
    }
  
    if (seconds < 0) {
      seconds = 59;
      minutes--;
    }

    timer = (minutes * 100) + seconds;

    Serial.print("Time left: ");
    Serial.println(timer);

    timerDisplay.print(timer, DEC);
    
//    blinkColon = !blinkColon;
    if (timer % 2 == 0) blinkColon = true; else blinkColon = false;
    timerDisplay.drawColon(blinkColon);
    
    if (minutes == 0) {
      timerDisplay.writeDigitNum(1, 0, false);
      if (seconds < 10) {
        timerDisplay.writeDigitNum(3, 0, false);
      }
    }
    
    if (triggered) timerDisplay.writeDisplay();

    // Transmit timer and status to Security
    if (seconds % 5 == 0) XbeeTransmit(NO_TX_ACK, minutes, seconds, "A");

    delay(1000);
    seconds--;
    
  } else {
    resetTimer();
    delay(3000);
  }

//  if (!triggered) {
//    delay(3000);
//  }
  
}

//  ---------------------------------------------------------------- FUNCTIONS --------------------------------------------------------------------------

void timerDone() {
  
  while(triggered) {

//    xbeeSerial.listen();
    XbeeTransmit(TX_ACK, 0x00, 0x00, "X");
    
    if(analogRead(sensorPin) <= DEFAULT_SENSOR_READING) {
      resetTimer();
//    } else triggered = true;
    }
    
    digitalWrite(greenPin, HIGH);
    digitalWrite(amberPin, HIGH);
    digitalWrite(redPin, LOW);
    if (beeper) digitalWrite(buzzerPin, LOW);

    timerDisplay.drawColon(true);
    timerDisplay.writeDigitNum(1, 0, false);
    timerDisplay.writeDigitNum(3, 0, false);
    timerDisplay.writeDigitNum(4, 0, false);
    timerDisplay.writeDisplay();
    
    Serial.println("RED ON! BEEP!");
    
    delay(500);
    
    digitalWrite(redPin, HIGH);
    if (beeper) digitalWrite(buzzerPin, HIGH);

    clearDisplay();
    
    Serial.println("RED OFF!");
    
    delay(500);
    
  }
  
}


void resetTimer() {

//  xbeeSerial.listen();
  triggered = false;
  
  digitalWrite(redPin, HIGH);
  digitalWrite(amberPin, HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(buzzerPin, HIGH);

  minutes = DEFAULT_MINUTES;
  seconds = DEFAULT_SECONDS;
  
  clearDisplay();

  if (!isReset) {
    
    XbeeTransmit(TX_ACK, 0x00, 0x00, "R");

    // if Xbee Coordinator recieves timer reset transmission
    // then set isReset to true
    if (xbeeSerial.available() > 0) {
      char inByte;
      for (int i = 0; i < 7; i++) {
        byte discard = xbeeSerial.read();
      }
      if (xbeeSerial.read() == 0x00) {
        isReset = true;
      } else {
        resetTimer();
      }
    }
    
  }
  
}


void clearDisplay() {

  timerDisplay.writeDigitRaw(0, 0x00);
  timerDisplay.writeDigitRaw(1, 0x00);
  timerDisplay.writeDigitRaw(3, 0x00);
  timerDisplay.writeDigitRaw(4, 0x00);
  timerDisplay.drawColon(false);
  timerDisplay.writeDisplay();
  
}


void XbeeTransmit (byte options, byte mins, byte secs, char _status) {

  byte zero = 0x00;

  char minutesArray[2];
  char secondsArray[2];

  char latArray[5];
  char longArray[5];

  if (mins < 10) {
    minutesArray[0] = '0';
    minutesArray[1] = mins + '0';
  } else {
    String strMins = String(mins);
    strMins.toCharArray(minutesArray, 2);
  }

  if (secs < 10) {
    secondsArray[0] = '0';
    secondsArray[1] = secs + '0';
  } else {
    String strSecs = String(secs);
    strSecs.toCharArray(secondsArray, 2);
  }

  int intPart = int(latitude);
  int decPart = latitude - intPart;
  uint16_t nlat = decPart * 100000;

  intPart = int(longitude);
  decPart = longitude - intPart;
  uint16_t nlong = decPart *100000;

  String strLat = String(nlat, 5);
  strLat.toCharArray(latArray, 5);

  String strLong = String(nlong, 5);
  strLong.toCharArray(longArray, 5);
  
  xbeeSerial.write(0x7e);        // Start delimiter
  xbeeSerial.write(zero);        // Length 1, HIGH BYTE, Number of bytes between length and checksum
  xbeeSerial.write(0x1d);        // Length 2, LOW BYTE
  xbeeSerial.write(0x10);        // Frame ID: 10 = Transmit Request
  xbeeSerial.write(options);     // Options: 0 = no response sent
  
  xbeeSerial.write(zero);        // Address High, 0x00000000 = TX to Coordinator, 0x0000ffff = broadcast TX
  xbeeSerial.write(zero);
  xbeeSerial.write(zero);
  xbeeSerial.write(zero);
  xbeeSerial.write(zero);        // Address Low
  xbeeSerial.write(zero);
  xbeeSerial.write(zero);        
  xbeeSerial.write(zero);
  
  xbeeSerial.write(0xff);        // 16-bit Address High: 0xfffc = broadcast to all routers
  xbeeSerial.write(0xfe);        // 16-bit Address Low: 0xfffe = 16-bit address unknown
  
  xbeeSerial.write(zero);        //Braoadcast Radius: 0 = max no. of hops
  xbeeSerial.write(zero);        //Options: 1 = disable retries, 20 = EN APS encryp, 40 = use extended TX timeout
  
//  xbeeSerial.write(minutesArray[0]);
//  xbeeSerial.write(minutesArray[1]);
//  xbeeSerial.write(secondsArray[0]);
//  xbeeSerial.write(secondsArray[1]);

  xbeeSerial.write(minutesArray, 2);
  xbeeSerial.write(secondsArray, 2);
  
  xbeeSerial.write(_status);
  
  xbeeSerial.write(latArray, 5);
  xbeeSerial.write(longArray, 5);

  // Checksum = 0xff - (0xff AND (sum of all bytes from offset 3 (frame type) to this byte))
  long sum = 0x10 +
             0xff +
             0xfe +
             minutesArray[0] +
             minutesArray[1] +
             secondsArray[0] +
             secondsArray[1] +
             _status +
             latArray[0] +
             latArray[1] +
             latArray[2] +
             latArray[3] +
             latArray[4] +
             latArray[5] +
             longArray[0] +
             longArray[1] +
             longArray[2] +
             longArray[3] +
             longArray[4] +
             longArray[5];
             
//  Serial.println(sum, HEX);
  byte FFandSum = 0xff & sum;
  
//  Serial.println(FFandSum, HEX);
  byte checksum = 0xff - byte(FFandSum);

  xbeeSerial.write(checksum);
  
//  Serial.println(checksum, HEX);
  
}


