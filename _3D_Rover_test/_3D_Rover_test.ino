/*********************************************************************
This is an example for our nRF8001 Bluetooth Low Energy Breakout

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/1697

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Kevin Townsend/KTOWN  for Adafruit Industries.
MIT license, check LICENSE for more information
All text above, and the splash screen below must be included in any redistribution
*********************************************************************/

// This version uses the internal data queing so you can treat it like Serial (kinda)!

#include <SPI.h>
#include "Adafruit_BLE_UART.h"
#include <Wire.h>
#include <Adafruit_MotorShield.h>
//#include "utility/Adafruit_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M3
Adafruit_DCMotor *myMotor = AFMS.getMotor(3);
// You can also make another motor on port M4
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(4);

// Connect CLK/MISO/MOSI to hardware SPI
// e.g. On UNO & compatible: CLK = 13, MISO = 12, MOSI = 11
#define ADAFRUITBLE_REQ 8
#define ADAFRUITBLE_RDY 2     // This should be an interrupt pin, on Uno thats #2 or #3
#define ADAFRUITBLE_RST 7

char string[2] = {0};
int index = 0;
boolean switch5 = false;
boolean switch6 = false;
boolean switch7 = false;
boolean switch8 = false;

Adafruit_BLE_UART BTLEserial = Adafruit_BLE_UART(ADAFRUITBLE_REQ, ADAFRUITBLE_RDY, ADAFRUITBLE_RST);
/**************************************************************************/
/*!
    Configure the Arduino and start advertising with the radio
*/
/**************************************************************************/
void setup(void)
{ 
  Serial.begin(9600);
  //while(!Serial); // Leonardo/Micro should wait for serial init
  Serial.println(F("Adafruit Bluefruit Low Energy nRF8001 Print echo demo"));

  
  
  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  delay(250);
  myMotor->setSpeed(150);
  myMotor->run(FORWARD);
  // turn on motor
  myMotor->run(RELEASE);
  delay(100);
  myMotor2->setSpeed(150);
  myMotor2->run(FORWARD);
  // turn on motor
  myMotor2->run(RELEASE);
  delay(250);
  BTLEserial.setDeviceName("ROVER3D"); /* 7 characters max! */
  BTLEserial.begin();
  
  myMotor->setSpeed(255);
  myMotor2->setSpeed(255);
}

/**************************************************************************/
/*!
    Constantly checks for new events on the nRF8001
*/
/**************************************************************************/
aci_evt_opcode_t laststatus = ACI_EVT_DISCONNECTED;

void loop()
{
  // Tell the nRF8001 to do whatever it should be working on.
  BTLEserial.pollACI();

  // Ask what is our current status
  aci_evt_opcode_t status = BTLEserial.getState();
  // If the status changed....
  if (status != laststatus) {
    // print it out!
    if (status == ACI_EVT_DEVICE_STARTED) {
        Serial.println(F("* Advertising started"));
    }
    if (status == ACI_EVT_CONNECTED) {
        Serial.println(F("* Connected!"));
    }
    if (status == ACI_EVT_DISCONNECTED) {
        Serial.println(F("* Disconnected or advertising timed out"));
    }
    // OK set the last status change to this one
    laststatus = status;
  }

  if (status == ACI_EVT_CONNECTED) {
    // Lets see if there's any data for us!
    if (BTLEserial.available()) {
      Serial.print("* "); Serial.print(BTLEserial.available()); Serial.println(F(" bytes available from BTLE"));
    }
    
    // OK while we still have something to read, get a character and print it out
    while (BTLEserial.available()) {
      char c = BTLEserial.read();
      Serial.print(c);
      if (c == 'B') index = 2;
      if (index < 2) string[index] = c;
      index--;
    }
    
    if ((string[1] - '0' == 5) && (string[0] - '0' == 1)) switch5 = true;
    if ((string[1] - '0' == 5) && (string[0] - '0' == 0)) switch5 = false;
    if ((string[1] - '0' == 6) && (string[0] - '0' == 1)) switch6 = true;
    if ((string[1] - '0' == 6) && (string[0] - '0' == 0)) switch6 = false;
    if ((string[1] - '0' == 7) && (string[0] - '0' == 1)) switch7 = true;
    if ((string[1] - '0' == 7) && (string[0] - '0' == 0)) switch7 = false;
    if ((string[1] - '0' == 8) && (string[0] - '0' == 1)) switch8 = true;
    if ((string[1] - '0' == 8) && (string[0] - '0' == 0)) switch8 = false;
    
    //Serial.print(string[1]); Serial.println(string[0]);
    
    if (switch5) Serial.println("Button 5");
    if (switch6) Serial.println("Button 6");
    if (switch7) Serial.println("Button 7");
    if (switch8) Serial.println("Button 8");
    
    if (switch5) roverForward();
    if (switch6) roverBackward();
    if (switch7) roverLeft();
    if (switch8) roverRight();
    if (!switch5 && !switch6 && !switch7 && !switch8) roverStop();

    // Next up, see if we have any data to get from the Serial console

    /*
    if (Serial.available()) {
      // Read a line from Serial
      Serial.setTimeout(100); // 100 millisecond timeout
      String s = Serial.readString();

      // We need to convert the line to bytes, no more than 20 at this time
      uint8_t sendbuffer[20];
      s.getBytes(sendbuffer, 20);
      char sendbuffersize = min(20, s.length());

      Serial.print(F("\n* Sending -> \"")); Serial.print((char *)sendbuffer); Serial.println("\"");

      // write the data
      BTLEserial.write(sendbuffer, sendbuffersize);
    }
    */
  }
}

void roverForward(){
  //myMotor->setSpeed(255);
  myMotor->run(FORWARD);
  //myMotor2->setSpeed(255);
  myMotor2->run(FORWARD);
}

void roverStop(){
  myMotor->run(RELEASE);
  myMotor2->run(RELEASE);
}

void roverBackward(){
  //myMotor->setSpeed(255);
  myMotor->run(BACKWARD);
  //myMotor2->setSpeed(255);
  myMotor2->run(BACKWARD);
}

void roverLeft(){
  //myMotor->setSpeed(255);
  myMotor->run(BACKWARD);
  //myMotor2->setSpeed(255);
  myMotor2->run(FORWARD);
}

void roverRight(){
  //myMotor->setSpeed(255);
  myMotor->run(FORWARD);
  //myMotor2->setSpeed(255);
  myMotor2-> run(BACKWARD);
}

