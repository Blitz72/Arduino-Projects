#include <SoftwareSerial.h>

SoftwareSerial xbeeSerial(0, 1);

#define battSensorPin 2

void setup() {
  
  // put your setup code here, to run once:
  xbeeSerial.begin(9600);
  pinMode(battSensorPin, OUTPUT);

}

void loop() {

  // put your main code here, to run repeatedly:
  int sensorReading = analogRead(battSensorPin);
  if (sensorReading < 900) {
    const char *message = "LOW BATTERY";
    xbeeTransmit(&message);
  }

  delay(300000);
  
}

void xbeeTransmit (char** msg) {

  byte zero = 0x00;
  
  xbeeSerial.write(0x7e);        // Start delimiter
  xbeeSerial.write(zero);        // Length 1, HIGH BYTE, Number of bytes between length and checksum
  xbeeSerial.write(0x1d);        // Length 2, LOW BYTE
  xbeeSerial.write(0x10);        // Frame ID: 10 = Transmit Request
  xbeeSerial.write(zero);     // Options: 0x00 = no response sent, 0x01 = coordinator will send a 0x8b transmit atatus

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

  uint32_t msgSum = 0;

  int i = 0;
  while (msg[i] != '\0') {
    xbeeSerial.write(msg[i]);
    msgSum += msg[i];
    i++;
  }

  // Checksum = 0xff - (0xff AND (sum of all bytes from offset 3 (frame type) to this byte))
  long sum = 0x10 +
             0xff +
             0xfe +
             msgSum;
             
  byte checksum = 0xff - byte(0xff & sum);

  xbeeSerial.write(checksum);

}

