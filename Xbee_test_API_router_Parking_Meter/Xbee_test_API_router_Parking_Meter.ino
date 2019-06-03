#include <SoftwareSerial.h>

#define DEFAULT_MINUTES 15              // default 15 minutes, type integer
#define DEFAULT_SECONDS 0               // default 0 seconds, type integer

SoftwareSerial XbeeSerial(10, 11);  // RX, TX

int minutes = DEFAULT_MINUTES;
int seconds = DEFAULT_SECONDS;
int timer = (minutes * 100) + seconds;
byte zero = 0x00;

void XbeeTransmit (byte mins, byte secs, char _status) {
  
  char _minutesArray[3];
  char _secondsArray[3];

  if (mins < 10) {
    _minutesArray[0] = '0';
    _minutesArray[1] = mins + '0';
  } else {
    String strMins = String(mins);
    strMins.toCharArray(_minutesArray, 3);
  }

  if (secs < 10) {
    _secondsArray[0] = '0';
    _secondsArray[1] = secs + '0';
  } else {
    String strSecs = String(secs);
    strSecs.toCharArray(_secondsArray, 3);
  }
  
  XbeeSerial.write(0x7e);        //Start delimiter
  XbeeSerial.write(zero);        //Length 1
  XbeeSerial.write(0x13);        //Length 2
  XbeeSerial.write(0x10);        //Frame ID: 10 = Transmit Request
  XbeeSerial.write(zero);        //Options: 0 = no response sent
  XbeeSerial.write(zero);        //Address High
  XbeeSerial.write(zero);
  XbeeSerial.write(zero);
  XbeeSerial.write(zero);
  XbeeSerial.write(zero);        //Address Low
  XbeeSerial.write(zero);
  XbeeSerial.write(zero);        //0xffff = broadcast TX
  XbeeSerial.write(zero);
  XbeeSerial.write(0xff);        //16-bit Address High: 0xfffc = broadcast to all routers
  XbeeSerial.write(0xfe);        //16-bit Address Low: 0xfffe = 16-bit address unknown
  XbeeSerial.write(zero);        //Braoadcast Radius: 0 = max no. of hops
  XbeeSerial.write(zero);        //Options: 1 = disable ACK, 20 = EN encryp, 40 = use extended TX timeout
  XbeeSerial.write(_minutesArray[0]);
  XbeeSerial.write(_minutesArray[1]);
  XbeeSerial.write(_secondsArray[0]);
  XbeeSerial.write(_secondsArray[1]);
  XbeeSerial.write(_status);
//  Serial1.write(0x48);        //RF Payload
//  Serial1.write(0x65);
//  Serial1.write(0x6c);
//  Serial1.write(0x6c);
//  Serial1.write(0x6f);
//  Serial1.write(0x21);
  long sum = 0x10 + 0xff + 0xfe + _minutesArray[0] + _minutesArray[1] + _secondsArray[0] + _secondsArray[1] + _status;
//  Serial.println(sum, HEX);
  byte FFandSum = 0xff & sum;
//  Serial.println(FFandSum, HEX);
  byte checksum = 0xff - byte(FFandSum);
  XbeeSerial.write(checksum);
  Serial.println(checksum, HEX);
  
}

void setup() {

  Serial.begin(9600);
  
//  Serial1.begin(9600);

  XbeeSerial.begin(9600);

  delay(250);

}

void loop() {

  char _status;

  uint8_t inByte;

  if (seconds < 0) {
    seconds = 59;
    minutes--;
  }

  if (minutes > 0 && seconds >= 0) _status = 'A';
  else if (minutes == 0 && seconds == 0) _status = 'X';

  if (seconds % 5 == 0) XbeeTransmit(minutes, seconds, _status);
  Serial.println(minutes * 100 + seconds);

  delay(1000);

  seconds--;

  if (Serial1.available() > 10){
    while (Serial1.available() > 0) {
      inByte = Serial1.read();
      Serial.println(inByte, HEX);
    }
  }

}
