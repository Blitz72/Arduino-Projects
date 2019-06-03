#include <TMRpcm_PLDuino.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <PLDuino.h>
#include <PLDTouch.h>
#include <PLDuinoGUI.h>
#include <using_namespace_PLDuinoGUI.h>
#include <DS3232RTC.h>
#include <Time.h>
#include <TimeLib.h>
#include <Wire.h>
#include "utils.h"

#define VERSION "1.2.2.0"

class Flasher
{
  // Class Member Variables
  // These are initialized at startup
  int ledPin;      // the number of the LED pin
  long OnTime;     // milliseconds of on-time
  long OffTime;    // milliseconds of off-time
 
  // These maintain the current state
  int ledState;                 // ledState used to set the LED
  unsigned long previousMillis;   // will store last time LED was updated
 
  // Constructor - creates a Flasher 
  // and initializes the member variables and state
  public:
  Flasher(int pin, long on, long off)
  {
  ledPin = pin;
  pinMode(ledPin, OUTPUT);     
    
  OnTime = on;
  OffTime = off;
  
  ledState = LOW; 
  previousMillis = 0;
  }
 
  void Update()
  {
    // check to see if it's time to change the state of the LED
    unsigned long currentMillis = millis();
     
    if((ledState == HIGH) && (currentMillis - previousMillis >= OnTime))
    {
      ledState = LOW;  // Turn it off
      previousMillis = currentMillis;  // Remember the time
      digitalWrite(ledPin, ledState);  // Update the actual LED
    }
    else if ((ledState == LOW) && (currentMillis - previousMillis >= OffTime))
    {
      ledState = HIGH;  // turn it on
      previousMillis = currentMillis;   // Remember the time
      digitalWrite(ledPin, ledState);   // Update the actual LED
    }
  }
};
 
 
Flasher led1(39, 1000, 1000);
Flasher led2(41, 500, 500);

boolean isReset = true;
boolean leftFilled = true;
boolean rightFilled = false;

Adafruit_ILI9341 tft = Adafruit_ILI9341(PLDuino::LCD_CS, PLDuino::LCD_DC);
PLDTouch touch(PLDuino::TOUCH_CS, PLDuino::TOUCH_IRQ);
TMRpcm tmrpcm;
Sd2Card card; bool card_initialized;

/*
void blinkLED()
{
  for(int i=0; i<3; ++i)
  {
    digitalWrite(PLDuino::LED_PIN, LOW); delay(200);
    digitalWrite(PLDuino::LED_PIN, HIGH); delay(200);
  }
}


void test();
void demo();
RunMode selectMode (RunMode defmode);
void testWiFi();
*/

void setup()
{
  // A convenient macro which prints start-up messages to both LCD and Serial.
  #define LOG(msg) { tft.println(msg); Serial.println(msg); }
  
  // Set pin modes and initialize stuff
  // NB: This line is necessary in all sketches which use PLDuino library stuff.
  PLDuino::init();

/*
  // Signal that the demo firmware is started.
  blinkLED();
*/

  // Power-on LCD and set it up
  PLDuino::enableLCD();
  tft.begin();
  tft.setRotation(3);

  // Setup serials. Serial2 is connected to ESP-02 Wi-Fi module.
  Serial.begin(115200);
  Serial2.begin(115200);
  
  // Print version info.
  tft.fillScreen(ILI9341_BLACK);
  LOG("PLDuino firmware v" VERSION ", built " __DATE__)
  LOG("")

  // We need to initialize SD card at startup!
  LOG("Initializing SD card...")
  card_initialized = card.init(SPI_HALF_SPEED, PLDuino::SD_CS);
  if (!SD.begin(PLDuino::SD_CS))
    LOG("ERROR: Can't initialize SD card!")

  // Initializing touch screen.
  LOG("Initializing touch...")
  touch.init(1);

  // Initializing real-time clock.
  LOG("Initializing RTC...")
  setSyncProvider(RTC.get);
  if (timeStatus() != timeSet)
    LOG("ERROR: Unable to sync with the RTC")
  
  // Setup speaker pin to play sounds.
  tmrpcm.speakerPin = 9;
  
  // Initialization is complete. 
  LOG("")
  LOG("Initialization complete.")
  LOG("")
  LOG("-- Touch to keep the log on screen --")
  delay(1500);
  while(touch.dataAvailable()) touch.read();
  tft.fillScreen(ILI9341_BLACK);

/*
  bool testmode = false;
  for(int i=1; i<8; ++i)
    testmode |= !digitalRead(30+i);
  switch(showModeSelectionScreen(testmode? MODE_TEST : MODE_DEMO))
  {
    case MODE_DEMO:
      demo();
      break;
    case MODE_TEST:
      test();
      break;
    case MODE_WIFI:
      testWiFi();
      break;
    default:
      Serial.println("Unknown mode. Running demo.");
      demo();
      break;
  }
*/
/*
  playSound(tmrpcm, "Apollo2.wav");
  delay(250);
  playSound(tmrpcm, "Bubbles.wav");
  delay(250);
  playSound(tmrpcm, "Bubbling.wav");
  delay(250);
  playSound(tmrpcm, "LgBubble.wav");
  delay(250);
  playSound(tmrpcm, "PwrDown.wav");
  delay(250);
  playSound(tmrpcm, "PwrFail.wav");
  delay(250);
  playSound(tmrpcm, "R2D2.wav");
  delay(250);
  //playSound(tmrpcm, "R2D2too.wav");
  playSound(tmrpcm, "TOSalert.wav");
  delay(250);
  playSound(tmrpcm, "TOSdoor.wav");
  delay(250);
  playSound(tmrpcm, "Wrench.wav");
*/
}

void loop(){
  if(digitalRead(30) == LOW) launch();
  if(digitalRead(31) == LOW) cancel();
  if(digitalRead(32) == LOW) resetPnl();
  if(digitalRead(33) == LOW && leftFilled == false) fillLeft();
  if(digitalRead(34) == LOW && rightFilled == false) fillRight();
  if(digitalRead(35) == LOW) adjust1();
  if(digitalRead(36) == LOW) adjust2();
}


void launch(){
  if(isReset == true){
    digitalWrite(38, HIGH);
    //uint32_t timeout = 1000;
    //uint32_t currentMillis = millis();
    digitalWrite(PLDuino::RELAY1, HIGH);
    tmrpcm.play("Apollo2.wav");
    while(tmrpcm.isPlaying()){
      led1.Update();
    }
  }
  digitalWrite(38, LOW);
  digitalWrite(39, LOW);
  digitalWrite(PLDuino::RELAY1, LOW);
}

void cancel(){
  isReset = false;
  digitalWrite(40, HIGH);
  playSound(tmrpcm, "TOSalert.wav");
  tmrpcm.play("PwrDown.wav");
  while(tmrpcm.isPlaying()){
    led2.Update();
  }
  delay(500);
  digitalWrite(41, HIGH);
  while(isReset == false){
    if(digitalRead(32) == LOW){
      isReset = true;
      digitalWrite(40, LOW);
      digitalWrite(41, LOW);
      playSound(tmrpcm, "R2D2.wav");
      break;
    }
  }
}

void resetPnl(){
  isReset = true;
  playSound(tmrpcm, "R2D2.wav");
}

void fillLeft(){
  if (leftFilled == false){
    int randNum = random(2);
    switch (randNum) {
      case 0:
        playSound(tmrpcm, "Bubbles.wav");
        break;
      case 1:
        playSound(tmrpcm, "LgBubble.wav");
        break;
    }
  }
  leftFilled = true;
  rightFilled = false;
}


void fillRight(){
  if (rightFilled == false){
    int randNum = random(2);
    switch (randNum) {
      case 0:
        playSound(tmrpcm, "Bubbling.wav");
        break;
      case 1:
        playSound(tmrpcm, "LgBubble.wav");
        break;
    }
  }
  rightFilled = true;
  leftFilled = false;
}

void adjust1(){
  int randNum = random(2);
  switch (randNum) {
    case 0:
      playSound(tmrpcm, "SaberOff.wav");
      break;
    case 1:
      playSound(tmrpcm, "Wrench.wav");
      break;
  }
}

void adjust2(){
  int randNum = random(2);
  switch (randNum) {
    case 0:
      playSound(tmrpcm, "TOSdoor.wav");
      break;
    case 1:
      playSound(tmrpcm, "Wrench.wav");
      break;
  }
}
