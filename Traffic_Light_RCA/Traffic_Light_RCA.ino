

void setup() {
  DDRB = DDRB | 0x07; //0x01 = red (PB0), 0x02 = yellow (PB1), 0x04 = green (PB2)
}

void loop() {
  trafficLight();
  priceIsRight();
  trafficLight();
  rock_N_Roll();
}

void trafficLight() {
  for (int i = 0; i < 5; i++) {
    PORTB &= ~0x01;
    PORTB |= 0x04;
    delay(10000);
    PORTB &= ~0x04;
    PORTB |= 0x02;
    delay(3000);
    PORTB &= ~0x02;
    PORTB |= 0x01;
    delay(6000);
  }
}

void priceIsRight() {
  for (int i = 20; i < 121; i++) {
    if (i % 3 == 1) {
      PORTB &= ~0x04;
      PORTB |= 0x01;
    }
    if (i % 3 == 2) {
      PORTB &= ~0x01;
      PORTB |= 0x02;
    }
    if (i % 3 == 0) {
      PORTB &= ~0x02;
      PORTB |= 0x04;
    }
    delay(i * 2);
  }
  delay(1000);
}

void rock_N_Roll() {
  
  int delayTime = 175;
  
  for ( int i = 0; i < 4; i++) {
    PORTB |= 0x06;  // beat 1
    delay(delayTime - 110);
    PORTB &= ~0x02;
    delay(70);
    PORTB &= ~0x07;
    delay(delayTime * 3 + 40);
    
    PORTB |= 0x07;  // beat 2
    delay(delayTime - 110);
    PORTB &= ~0x01;
    delay(70);
    PORTB &= ~0x02;
    delay(40);
    PORTB &= ~0x07;
    delay(delayTime * 2 + 25);
    PORTB |= 0x04;
    delay(delayTime - 80);
    PORTB &= ~0x01;
    delay(45);
    
    PORTB |= 0x06;  // beat 3
    delay(delayTime - 110);
    PORTB &= ~0x02;
    delay(70);
    PORTB &= ~0x07;
    delay(delayTime + 40);
    PORTB |= 0x04; // beat 3-and
    delay(delayTime);
    PORTB &= ~0x07;
    delay(delayTime);
    
    PORTB |= 0x07;  // beat 4
    delay(delayTime - 110);
    PORTB &= ~0x01;
    delay(70);
    PORTB &= ~0x02;
    delay(40);
    PORTB &= ~0x07;
    delay(delayTime * 3);
  }
}


