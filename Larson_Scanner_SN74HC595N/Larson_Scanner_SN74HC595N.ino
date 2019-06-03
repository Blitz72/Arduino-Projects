byte latchPin = 5;
byte clockPin = 6;
byte dataPin = 4;
byte leds = 0;
byte j = 0;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  leds = 0;
  updateShiftRegister();
  delay(500);
  for(byte i = 0; i < 8; i++) {
    bitSet(leds, i);
    j = i - 2;
    if (j < 0) {
      j = 0;
    }
    bitClear(leds, j);
    updateShiftRegister();
    delay(45);
  }
  for (byte i = 8; i > 0; i--) {
    bitSet(leds, i - 1);
    j = i + 2;
    if (j > 7) {
      j = 7;
    }
    bitClear(leds, j);
    updateShiftRegister();
    delay(45);
  }
}

void updateShiftRegister() {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, leds);
  digitalWrite(latchPin, HIGH);
}
