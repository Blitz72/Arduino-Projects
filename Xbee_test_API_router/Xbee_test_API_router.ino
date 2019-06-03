byte valA = 0;
byte valC = 0;
byte valL = 0;
byte inByte = 0;

void setup() {
  Serial1.begin(9600);
  delay(5000);

}

void loop() {
  if (Serial1.available() > 0){
    inByte = Serial.read();
    if (inByte == 0x7E){
      for(int i = 0; i < 17; i++){
        byte discard = Serial1.read();
      }
      valA = Serial1.read();
      valC = Serial1.read();
      valL = Serial1.read();
    }
  }
}
