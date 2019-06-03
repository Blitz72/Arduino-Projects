byte valA = 0xff;
byte valC = 0xff;
byte valL = 0xff;

long previousMillis = 0;
long timeout = 10000;

void sendSerial(){
  Serial.print("Hello!");
}

void setup() {
  Serial.begin(9600);
  Serial1.begin(57600);
  DDRA = 0xff;
  DDRC = 0xff;
  DDRL = 0xff;
  PORTA = 0xff;
  PORTC = 0xff;
  PORTL = 0xff;
  delay(30000);
  

}

void loop() {
/*  while(Serial1.available() == 0){
    PORTA = 0xff;
    PORTC = 0xff;
    PORTL = 0xff;
  }*/
  
  if (Serial1.available() > 20){
    previousMillis = millis();
    byte inByte = Serial1.read();
    if (inByte == 0x7E){
//      Serial.println(inByte, HEX);
      for(byte i = 0; i < 14; i++){
        byte discard = Serial1.read();
//        Serial.println(discard, HEX);
      }
      valA = Serial1.read();
      valC = Serial1.read();
      valL = Serial1.read();
//      Serial.print("valA = ");
//      Serial.println(valA, HEX);
//      Serial.print("valC = ");
//      Serial.println(valC, HEX);
//      Serial.print("valL = ");
//      Serial.println(valL, HEX);
    }
  }
  PORTA = valA;
  PORTC = valC;
  PORTL = valL;
  if ((!Serial) || (Serial.available() < 5)) {
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis > timeout) {
      PORTA = 0xff;
      PORTC = 0xff;
      PORTL = 0xff;
    }
  }
}
