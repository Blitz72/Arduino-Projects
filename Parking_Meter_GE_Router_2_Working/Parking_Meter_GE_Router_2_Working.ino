#include <SoftwareSerial.h>
#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include <TinyGPS.h>

// Configuration information

#define DEFAULT_MINUTES 15              // default 15 minutes, type integer
#define DEFAULT_SECONDS 0               // default 0 seconds, type integer
#define DEFAULT_SENSOR_READING 100      // default 100, should be in the range 70 - 512, 512 = minimum sensor distance (20cm)
#define BEEPER_ENABLE false              // default true, (true, false) true enables tower light beeper
#define TX_ACK 0x01
#define NO_TX_ACK 0x00
#define LOW_BATTERY_LIMIT 500           // R1 = 106.5kOkms, R2 = 39.6kOhms; ~14.5 volts = Analog In of ~800
#define MID_BATTERY_LIMIT 600

#define GPS_TESTING_INTERVAL 20000
#define GPS_INTERVAL 300000  // time in mS: 5 minutes
#define GPS_SERIAL_TIMEOUT 2000

#define RESET_TIMEOUT 30000

#define DISPLAY_ADDRESS 0x70
#define MPU_ADDRESS 0x68

#define sensorPin A0
#define battSensor A1
#define greenPin 4
#define amberPin 5
#define redPin 6
#define buzzerPin 7

// Constructor for 7-segment display
Adafruit_7segment timerDisplay = Adafruit_7segment();

// Constructor for SoftwareSerial
SoftwareSerial xbeeSerial(10, 11); // RX, TX
SoftwareSerial gpsSerial(12, 13); // RX, TX: For Mega2560 testing use 12, 13 or use 8, 9 for Uno if needed

// Constructor for TinyGPS
TinyGPS gps;

//const byte coordinator[] PROGMEM = {0x00, 0x13, 0xa2, 0x00, 0x41, 0x8a, 0x36, 0xd5};

int8_t minutes = DEFAULT_MINUTES;
int8_t seconds = DEFAULT_SECONDS;
int timer = (minutes * 100) + seconds;

float latitude = 41.54046; // NELA Security Parking = (41.54036 - 41.54056)
float longitude = -81.56100; // NELA Security Parking = (-81.56060 - -81.56141)

//uint32_t currentMillis = 0;
uint32_t gpsPreviousMillis = 0;
uint32_t resetPreviousMillis = 0;

uint16_t sensorVal = 0;

bool blinkColon = false;
bool triggered = false;
const bool beeper = BEEPER_ENABLE;
bool isReset = true;

char latArray[6];
char longArray[6];

char battStatus = 'L';


//  ================================================================= SETUP ============================================================================

void setup() {

  Serial.begin(9600);
  xbeeSerial.begin(9600);  // Xbee serial port
  gpsSerial.begin(9600);  // GPS serial port

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

  convertLatLong(latitude, longitude);
  
}

//  ================================================================== LOOP ============================================================================

void loop() {

  checkBatt();
  sensorVal = analogRead(sensorPin);

  Serial.println();
  Serial.print(F("Sensor: "));
  Serial.println(sensorVal);

  // Check to see if a vehicle is present
  if (sensorVal > DEFAULT_SENSOR_READING && triggered == false) {
    
    delay(10000);
    if (analogRead(sensorPin) > DEFAULT_SENSOR_READING) {
      triggered = true;
    } else {
      triggered = false;
    }
    
  }

  // Check GPS coordinates while the meter is inactive
  if (!triggered) {
    
    uint32_t gpsCurrentMillis = millis();
    if (gpsCurrentMillis - gpsPreviousMillis > GPS_TESTING_INTERVAL) {
      checkGPS();
      gpsPreviousMillis = gpsCurrentMillis;
    }
    
  }

  if (sensorVal <= DEFAULT_SENSOR_READING && triggered) {
    triggered = false;
  }

  if (triggered) {

    isReset = false;
    digitalWrite(redPin, HIGH);
//    digitalWrite(amberPin, HIGH);       // If tower light has amber light
    digitalWrite(greenPin, LOW);
    digitalWrite(buzzerPin, HIGH);

    if (timer <= 200) {
      if (blinkColon) {
        digitalWrite(greenPin, HIGH);
//        digitalWrite(amberPin, LOW);    // If tower light has amber light
      } else {
        digitalWrite(greenPin, LOW);
      }
    }
  
    if (seconds < 0) {
      seconds = 59;
      minutes--;
    }

    timer = (minutes * 100) + seconds;

    Serial.print(F("Time left: "));
    Serial.println(timer);

    timerDisplay.print(timer, DEC);

    // Transmit timer and status to Security
    if (seconds % 5 == 0) xbeeTransmit(NO_TX_ACK, minutes, seconds, 'A');

    if (timer <= 0){
      Serial.println(F("Time's up!"));
      seconds = 0;
      timerDone();
    }
    
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

    delay(1000);
    seconds--;
    
  } else {
    resetTimer();
    delay(3000);
  }
  
}

//  =============================================================== FUNCTIONS ==========================================================================

//  --------------------------------------------------------------- timerDone --------------------------------------------------------------------------
void timerDone() {

  byte counter = 0;
  
  while(triggered) {

    if (counter % 6 == 0) {
      Serial.println();
      xbeeTransmit(TX_ACK, 0, 0, 'X');
      counter = 1;
      while (xbeeSerial.available() > 0) {
//        Serial.print(xbeeSerial.read(), HEX);
//        Serial.print(", ");
        char inByte = xbeeSerial.read();
        if (inByte == 0x7e) {
          for (int i = 0; i < 7; i++) {
            xbeeSerial.read();
          }
          inByte = xbeeSerial.read();
          Serial.print(F("Tx status: "));
          Serial.println(inByte, HEX);
          (!inByte) ? Serial.println(F("TX Success!")) : Serial.println(F("TX Failure!"));
        }
//        xbeeSerial.read();
      }
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
    
//    Serial.println("RED ON! BEEP!");
    
    delay(500);
    
    digitalWrite(redPin, HIGH);
    if (beeper) digitalWrite(buzzerPin, HIGH);

    clearDisplay();
    
//    Serial.println("RED OFF!");
    
    delay(500);

    counter++;

    if(analogRead(sensorPin) <= DEFAULT_SENSOR_READING) {
      resetTimer();
//    } else triggered = true;
    }
    
  }
  
}


//  --------------------------------------------------------------- resetTimer -------------------------------------------------------------------------
void resetTimer() {

//  xbeeSerial.listen();

  uint32_t resetCurrentMillis = millis();
  if (!isReset || (resetCurrentMillis - resetPreviousMillis > RESET_TIMEOUT)) {
    
    xbeeTransmit(TX_ACK, 0x00, 0x00, 'R');
    while (xbeeSerial.available() > 0) {
//      Serial.print(xbeeSerial.read(), HEX);
//      Serial.print(", ");
      char inByte = xbeeSerial.read();
      if (inByte == 0x7e) {
        for (int i = 0; i < 7; i++) {
          xbeeSerial.read();
        }
        inByte = xbeeSerial.read();
        Serial.print(F("Tx status: "));
        Serial.println(inByte, HEX);
        if (!inByte) {
          Serial.println(F("TX Success!"));
          isReset = true;
          resetPreviousMillis = resetCurrentMillis;
        } else {
          Serial.println(F("TX Failure!"));
          resetTimer();
        }
      }
      xbeeSerial.read();
    }
    
  }

  triggered = false;
  
  digitalWrite(redPin, HIGH);
  digitalWrite(amberPin, HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(buzzerPin, HIGH);

  minutes = DEFAULT_MINUTES;
  seconds = DEFAULT_SECONDS;
  
  clearDisplay();
  
}


//  -------------------------------------------------------------- clearDisplay ------------------------------------------------------------------------
void clearDisplay() {

  timerDisplay.writeDigitRaw(0, 0x00);
  timerDisplay.writeDigitRaw(1, 0x00);
  timerDisplay.writeDigitRaw(3, 0x00);
  timerDisplay.writeDigitRaw(4, 0x00);
  timerDisplay.drawColon(false);
  timerDisplay.writeDisplay();
  
}


//  -------------------------------------------------------------- xbeeTransmit ------------------------------------------------------------------------
void xbeeTransmit (byte options, byte mins, byte secs, char _status) {

  noInterrupts();

  byte zero = 0x00;

  char minutesArray[2];
  char secondsArray[2];

  minutesArray[0] = mins / 10 + '0';
  minutesArray[1] = mins % 10 + '0';

  secondsArray[0] = secs / 10 + '0';
  secondsArray[1] = secs % 10 + '0';
  
  xbeeSerial.write(0x7e);        // Start delimiter
  xbeeSerial.write(zero);        // Length 1, HIGH BYTE, Number of bytes between length and checksum
  xbeeSerial.write(0x1e);        // Length 2, LOW BYTE
  xbeeSerial.write(0x10);        // Frame ID: 10 = Transmit Request
  xbeeSerial.write(options);     // Options: 0x00 = no response sent, 0x01 = coordinator will send a 0x8b transmit atatus

//  xbeeSerial.write(coordinator, 8);
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

  xbeeSerial.write(minutesArray, 2);
  xbeeSerial.write(secondsArray, 2);
  
  xbeeSerial.write(_status);
  
  xbeeSerial.write(latArray, 5);
  xbeeSerial.write(longArray, 5);

  xbeeSerial.write(battStatus);

  // Checksum = 0xff - (0xff AND (sum of all bytes from offset 3 (frame type) to this byte))
  long sum = 0x10 +
             options +
             0xff +
             0xfe +
             minutesArray[0] +
             minutesArray[1] +
             secondsArray[0] +
             secondsArray[1] +
             _status;
  for (int i = 0; i < 5; i++) {
    sum += latArray[i];
    sum += longArray[i];
  }
  sum += battStatus;
  
  byte checksum = 0xff - byte(0xff & sum);

  xbeeSerial.write(checksum);

//  Serial.write(coordinator, 8);
  Serial.print(options);
  Serial.print(", ");
  Serial.write(minutesArray, 2);
  Serial.print(':');
  Serial.write(secondsArray, 2);
  Serial.print(", ");
  
  Serial.print(_status);
  Serial.print(", ");
  
  Serial.write(latArray, 5);
  Serial.print(", ");
  
  Serial.write(longArray, 5);
  Serial.print(", ");

  Serial.print(battStatus);
  Serial.print(", ");
  
  Serial.println(checksum, HEX);

  interrupts();
  
}


//  ------------------------------------------------------------ convertLatLong ------------------------------------------------------------------------
void convertLatLong(float _latitude, float _longitude) {
  
  float decPart = _latitude - int(_latitude);
  float flat = decPart * 100000;
  if (flat < 0) flat *= -1;

  decPart = _longitude - int(_longitude);
  float flong = decPart *100000;
  if (flong < 0) flong *= -1;

  uint16_t lat32 = uint16_t(flat) + 1;
  uint16_t long32 = uint16_t(flong) + 1;

  String(lat32).toCharArray(latArray, 6);
  String(long32).toCharArray(longArray, 6);
  
}


//  -------------------------------------------------------------- checkGPS ----------------------------------------------------------------------------
void checkGPS() {

  bool newData = false;
  
  gpsSerial.listen();
  Serial.println(F("Checking GPS coordinates... **!**!**!**!**!**!!**!**!**!**!**!**!**!**!**!**"));
  uint32_t gpsSerialCurrentMillis = millis();
  while(!newData) {
    (millis() - gpsSerialCurrentMillis > GPS_SERIAL_TIMEOUT) ? newData = true : newData = false;
    if (gpsSerial.available() >= 0) {
//      Serial.println(gpsSerial.available());
//      if (gpsSerial.overflow()) Serial.println("Soft Serial Overflow");
      while (gpsSerial.available()) {
        char c = gpsSerial.read();
//        Serial.print(c);
        if (gps.encode(c)) newData = true;
      }
    }
  }
  
  if (newData) {
    float flat, flon;
    uint32_t fix_age;
    gps.f_get_position(&flat, &flon, &fix_age);
    Serial.print(flat, 5);
    Serial.print(", ");
    Serial.println(flon, 5);
    if (flat > 41.0 && flat < 42.0) {
      latitude = flat;
    }
    if (flon < -81.0 && flon > -82.0) {
      longitude = flon;
    }
  }
  convertLatLong(latitude, longitude);
  xbeeSerial.listen();
}


//  -------------------------------------------------------------- checkBatt ---------------------------------------------------------------------------
void checkBatt() {
  
  int battAnalogIn = analogRead(battSensor);
  Serial.print("Battery analog reading: ");
  Serial.println(battAnalogIn);
  float batt = battAnalogIn * 0.018125;
  Serial.print("Battery Voltage = ");
  Serial.println(batt, 2);
  Serial.print("Battery Status TX char: ");
  Serial.println(battStatus);
  
  if (battAnalogIn < LOW_BATTERY_LIMIT) {
    battStatus = 'L';
  } else if (battAnalogIn >= LOW_BATTERY_LIMIT && battAnalogIn < MID_BATTERY_LIMIT) {
    battStatus = 'M';
  } else if (battAnalogIn >= MID_BATTERY_LIMIT) {
    battStatus = 'H';
  }
  
}


// converts decimal part of the float returned by gps into a char array
//char // pass pointer to character array


// void calcPayload(){
//   //Serialize payload before sending to xbeeTransmit()
// }
