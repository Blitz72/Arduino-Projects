/******************************************************************
 This is an example for the Adafruit RA8875 Driver board for TFT displays
 ---------------> http://www.adafruit.com/products/1590
 The RA8875 is a TFT driver for up to 800x480 dotclock'd displays
 It is tested to work with displays in the Adafruit shop. Other displays
 may need timing adjustments and are not guanteed to work.
 
 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source hardware
 by purchasing products from Adafruit!
 
 Written by Limor Fried/Ladyada for Adafruit Industries.
 BSD license, check license.txt for more information.
 All text above must be included in any redistribution.
 ******************************************************************/

#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_RA8875.h"
#include <EEPROM.h>

//#include "font.h"
//#include "font2.h"
#include "bitmaps.h"
//#include "megaBitmaps.h"

//using namespace std;

// Library only supports hardware SPI at this time
// Connect SCLK to UNO Digital #13 (Hardware SPI clock)
// Connect MISO to UNO Digital #12 (Hardware SPI MISO)
// Connect MOSI to UNO Digital #11 (Hardware SPI MOSI)
// Connect SCLK to MEGA Digital #52 (Hardware SPI clock)
// Connect MISO to MEGA Digital #50 (Hardware SPI MISO)
// Connect MOSI to MEGA Digital #51 (Hardware SPI MOSI)

#define RA8875_INT 21 // MEGA 2560 R3 interrupt pins 2, 3, 18, 19, 20, 21; UNO R3 = 2, 3
#define RA8875_CS 53 // MEGA 2560 R3 = 53; UNO R3 = 10
#define RA8875_RESET 49 // MEGA 2560 R3 reset used is 49 which next to hardware SPI; UNO R3 reset was 9 next to hardware SPI

#define eePromAddress 0

#define red      RA8875_RED
//#define green    RA8875_GREEN
#define green    0x07a0         // just a bit darker than RA8875_GREEN
#define blue     RA8875_BLUE
#define yellow   RA8875_YELLOW
#define white    RA8875_WHITE
#define black    RA8875_BLACK
#define gray     0xe71c

Adafruit_RA8875 tft = Adafruit_RA8875(RA8875_CS, RA8875_RESET);
uint16_t tx, ty;
tsPoint_t       _tsLCDPoints[3]; 
tsPoint_t       _tsTSPoints[3]; 
tsMatrix_t      _tsMatrix;

struct CalibrationObject {
  int32_t An;
  int32_t Bn;
  int32_t Cn;
  int32_t Dn;
  int32_t En;
  int32_t Fn;
  int32_t divider;
  boolean calibrated;
};

//class ParkinMeter {
//  public:
//    byte address[4];
//    char mins[2];
//    char secs[2];
//    char status;
//    char latitude[5];
//    char longitude[5];
//    byte id;
//    void printInfo() {
//      
//    };
//    void updateInfo() {
//      
//    }
//};
//
//ParkingMeter meterArray[10] = {ParkingMeter(0), ParkingMeter(1), ParkingMeter(2)};

CalibrationObject cal;

//  ================================================================= SETUP ============================================================================


void setup() 
{
  Serial.begin(115200);
  Serial1.begin(115200);  // Xbee serial port
  
  Serial.println(F("RA8875 start"));

  /* Initialise the display using 'RA8875_480x272' or 'RA8875_800x480' */
  if (!tft.begin(RA8875_800x480)) {
    Serial.println(F("RA8875 Not Found!"));
    while (1);
  }

  Serial.println(F("Found RA8875"));

  tft.displayOn(true);
  tft.GPIOX(true);      // Enable TFT - display enable tied to GPIOX
  tft.PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
  tft.PWM1out(255);
  
  pinMode(RA8875_INT, INPUT);
  digitalWrite(RA8875_INT, HIGH);
  
  tft.touchEnable(true);

  EEPROM.get(eePromAddress, cal);

//  Serial.println(cal.An);
//  Serial.println(cal.Bn);
//  Serial.println(cal.Cn);
//  Serial.println(cal.Dn);
//  Serial.println(cal.En);
//  Serial.println(cal.Fn);
//  Serial.println(cal.divider);
//  Serial.println(cal.calibrated);

  for (int i = 0; i < 11; i++) {
    tft.drawRect(0, i*40, tft.width() - 1, 40, RA8875_WHITE);
  }
//  tft.drawRect(0, 0, tft.width() - 1, 40, RA8875_WHITE);
  tft.drawRect(0, 440, tft.width() - 1, 39, RA8875_WHITE);
  tft.fillRect(1, 1, tft.width() - 3, 38, gray);
  tft.fillRect(1, 441, tft.width() - 3, 37, gray);
  tft.textMode();
  tft.textEnlarge(1);
  tft.textSetCursor(20, 3);
  const char string[] = "LOCATION         SERIAL #      TIME LEFT";
  tft.textTransparent(RA8875_BLACK);
  tft.textWrite(string);

//  // drawArray(x position, y position, height, width, name of uint16_t array stored in flash);
//  uint32_t startTime = millis();
//  drawArray(650, 442, 36, 36, menuButton);
//  drawArray(700, 442, 36, 36, settingsButton);
//  drawArray(750, 442, 36, 36, closeButton);
//  uint32_t endTime = millis();
//  Serial.print("drawArray elapsed time: ");
//  Serial.println(endTime - startTime);  // 878 mS for menuButton, settingsButton, and closeButton

//  // drawArray2(x position, y position, height, width, name of uint16_t array stored in flash);
//  startTime = millis();
  drawArray2(10, 442, 36, 48, GE_Logo);
  drawArray2(700, 2, 36, 36, menuButton);
  drawArray2(750, 2, 36, 36, settingsButton);
//  drawArray2(750, 2, 36, 36, closeButton);
//  drawArray2(650, 442, 36, 36, lowBattIcon);
//  drawArray2(700, 442, 36, 36, medBattIcon);
//  drawArray2(750, 442, 36, 36, highBattIcon);
//  endTime = millis();
//  Serial.print("drawArray2 elapsed time: ");
//  Serial.println(endTime - startTime);  // 55 mS for menuButton, settingsButton, and closeButton

//  drawArray2(0, 0, 40, 800, NELA_Park_1);  //  800 x 480 array crashes compiler

}

//  ================================================================== LOOP ============================================================================

void loop() {

delay(250);
  
} // end of loop()


//  ================================================================ FUNCTIONS =========================================================================

void serialEvent1() {

//  noInterrupts();

  byte address[4] = {0};

  char minArray[2] = "";
  char secArray[2] = "";
  
  char _status = 'R';
  
  char latArray[5] = "";
  char lonArray[5] = "";

  char battStatus = 'L';

  byte inByte;

  while (Serial1.available() > 0) {   // should be a receive packet frame 0x90

    inByte = Serial1.read();
    
//    (inByte == 0) ? Serial.print('0') : Serial.print(inByte, HEX);
//    Serial.print(", ");
    
    if (inByte == 0x7e) {
      for (int i = 0; i < 2; i++) {
        Serial1.read();               // discard length bytes
      }
      inByte = Serial1.read();
      if (inByte == 0x90) {
        for (int i = 0; i < 4; i++) {
          Serial1.read();               // discard bytes 4 - 7, first half of 64-bit address
        }
        for (int i = 0; i < 4; i++) {
          address[i] = Serial1.read();  // read offset 8 - 11, second half of 64-bit address
        }
        for (int i = 0; i < 3; i++) {
          Serial1.read();               // discard offset 12 - 14
        }
        
        minArray[0] = Serial1.read();   // time left from parking meter, offset 15
        minArray[1] = Serial1.read();
        secArray[0] = Serial1.read();
        secArray[1] = Serial1.read();
        
        _status = Serial1.read();
  
        for (int i = 0; i < 5; i++) {
          latArray[i] = Serial1.read();
        }
        for (int i = 0; i < 5; i++)  {
          lonArray[i] = Serial1.read();
        }

        battStatus = Serial1.read();
        
      }
    }
    
  }

  Serial.println();

//  interrupts();

  printInfo(address, minArray, secArray, _status, latArray, lonArray, battStatus);
  
  if (minArray[0] > 0x20 && minArray[0] < 0x7f && latArray[0] > 0x20 and latArray[0] < 0x7f &&
  lonArray[0] > 0x20 && lonArray[0] < 0x7f && lonArray[5] > 0x20 && lonArray[5] < 0x7f ) {
    updateInfo(address, minArray, secArray, _status, latArray, lonArray, battStatus);
  }

}


void printInfo(byte address[], char minutes[], char seconds[], char _status, char latitude[], char longitude[], char battStatus) {

  Serial.print(F("Address: "));
  for (int i = 0; i < 4; i++) {
    Serial.print(address[i], HEX);
  }
  Serial.println();
  
  Serial.print(F("Time left: ")); Serial.print(minutes[0]); Serial.print(minutes[1]);
  Serial.print(F(":")); Serial.print(seconds[0]); Serial.println(seconds[1]);
  
  Serial.print(F("Status: ")); Serial.println(_status);
  
  Serial.print(F("Position: 41."));
  for (int i = 0; i < 5; i++) {
    Serial.print(latitude[i]);
  }
  Serial.print(", -81.");
  for (int i = 0; i < 5; i++) {
    Serial.print(longitude[i]);
  }
  Serial.println();

  Serial.print("Battery Status: ");
  Serial.println(battStatus);
  
  Serial.println();
  
}


void updateInfo(byte address[], char minutes[], char seconds[], char _status, char latitude[], char longitude[], char battStatus) {

  uint16_t bgColor;
  uint16_t textColor;
  
  int mins = (minutes[0] - 0x30) * 10;
  mins += minutes[1] - 0x30;

  int secs = (seconds[0] - 0x30) * 10;
  secs += seconds[1] - 0x30;

  int timer = mins * 100 + secs;

  if (_status == 'R') {
    bgColor = blue;
    textColor = white;
  } else if (_status == 'A') {
    if (timer > 500) {
      bgColor = green;
      textColor = black;
    }
    if (timer > 0 && timer <= 500) {
      bgColor = yellow;
      textColor = black;
    }
    if (timer <= 0) {
      bgColor = red;
      textColor = white;
    }
  } else if (_status == 'X') {
    bgColor = red;
    textColor = white;
  }

  uint16_t _latitude = (latitude[0] - 0x30) * 10000;   // convert latitude char array into uinsigned integer
  _latitude += (latitude[1] - 0x30) * 1000;
  _latitude += (latitude[2] - 0x30) * 100;
  _latitude += (latitude[3] - 0x30) * 10;
  _latitude += (latitude[4] - 0x30);

  uint16_t _longitude = (longitude[0] - 0x30) * 10000;   // convert longitude char array into uinsigned integer
  _longitude += (longitude[1] - 0x30) * 1000;
  _longitude += (longitude[2] - 0x30) * 100;
  _longitude += (longitude[3] - 0x30) * 10;
  _longitude += (longitude[4] - 0x30);

  tft.drawRect(0, 40, tft.width() - 1, 40, white);
  tft.fillRect(1, 41, tft.width() - 3, 38, bgColor);

  tft.textSetCursor(20, 43);
  tft.textTransparent(textColor);
  if (_latitude >= 54036 && _latitude <= 54056 && _longitude >= 56060 && _longitude <= 56141) {
    tft.textWrite("SECURITY");
  } else {
    tft.textWrite("NELA PARK");
  }
  
  tft.textSetCursor(290, 43);
  tft.textTransparent(textColor);

  // convert hex values of the address to ascii for easy prining in the tft.textWrite() function
  
  byte add[8] = {0};
  
//  ((address[0] >> 4) < 10) ? add[0] = (address[0] >> 4) + 0x30 : add[0] = (address[0] >> 4) + 0x37;
//  ((address[0] & 0x0f) < 10) ? add[1] = (address[0] & 0x0f) + 0x30 : add[1] = (address[0] & 0x0f) + 0x37;
//  ((address[1] >> 4) < 10) ? add[2] = (address[1] >> 4) + 0x30 : add[2] = (address[1] >> 4) + 0x37;
//  ((address[1] & 0x0f) < 10) ? add[3] = (address[1] & 0x0f) + 0x30 : add[3] = (address[1] & 0x0f) + 0x37;
//  ((address[2] >> 4) < 10) ? add[4] = (address[2] >> 4) + 0x30 : add[4] = (address[2] >> 4) + 0x37;
//  ((address[2] & 0x0f) < 10) ? add[5] = (address[2] & 0x0f) + 0x30 : add[5] = (address[2] & 0x0f) + 0x37;
//  ((address[3] >> 4) < 10) ? add[6] = (address[3] >> 4) + 0x30 : add[6] = (address[3] >> 4) + 0x37;
//  ((address[3] & 0x0f) < 10) ? add[7] = (address[3] & 0x0f) + 0x30 : add[7] = (address[3] & 0x0f) + 0x37;

  for (int i = 0; i < 4; i++) {
    ((address[i] >> 4) < 10) ? add[i*2] = (address[i] >> 4) + 0x30 : add[i*2] = (address[i] >> 4) + 0x37;
    ((address[i] & 0x0f) < 10) ? add[i*2+1] = (address[i] & 0x0f) + 0x30 : add[i*2+1] = (address[i] & 0x0f) + 0x37;
  }

  tft.textWrite(add, 8);
  
  tft.textSetCursor(520, 43);
  tft.fillRect(520, 43, 100, 35, bgColor);
  tft.textTransparent(textColor);

  if (_status == 'A' || _status == 'X') {
    tft.textWrite(minutes, 2);
    tft.textWrite(":");
    tft.textWrite(seconds, 2);
  } else if (_status == 'R') {
    tft.textWrite("INACTIVE");
  }
  
  switch (battStatus) {
    case 'H':
      drawArray2(435, 48, 24, 36, highBattIcon);
      break;
    case 'M':
      drawArray2(435, 48, 24, 36, medBattIcon);
      break;
    case 'L':
      drawArray2(435, 48, 24, 36, lowBattIcon);
      break;
  }
  
}


//void drawArray(int x, int y, int h, int w, uint16_t * file) {
//
//  tft.graphicsMode();
//
//  for (int row = y; row < y + h; row++) {
//    for (int col = x; col < x + w; col++) {
//      tft.drawPixel(col, row, pgm_read_word(file));
//      file++;
//    }
//  }
//
//  tft.textMode();
//  
//}


void drawArray2(int x, int y, int h, int w, uint16_t * file) {

  uint16_t buff[w] = {};
  
  tft.graphicsMode();
  
  for (int row = y; row < y + h; row++) {
    for (int i = 0; i < w; i++) {
      buff[i] = pgm_read_word(file);
      file++;
    }
    tft.drawPixels(buff, w, x, row);
  }

  tft.textMode();
  
}
