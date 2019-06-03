#include <avr/power.h>

#define lightCount 1  //Total # of lights on string (usually 50, 48, or 36 or up to 64 for a custom string!)

#define COLOR(r,g,b)     ((r)+((g)<<4)+((b)<<8))  //Color is 12-bit (4-bit each R, G, B)
#define black            COLOR(0,0,0)
#define red              COLOR(0xf,0,0)
#define darkRed          COLOR(0x3, 0, 0)
#define green            COLOR(0,0xf,0)
#define darkGreen        COLOR(0, 0x3, 0)
#define blue             COLOR(0,0,0xf)
#define teal             COLOR(0,0xf,0xf)
#define magenta          COLOR(0xf,0,0xf)
#define pink             COLOR(0xf,0x2,0xf)
#define yellow           COLOR(0xf,0xf,0)
#define gold             COLOR(0xf, 0xd, 0)
#define purple           COLOR(0xa,0x0,0xf)
#define orange           COLOR(0xf,0x3,0x0)
#define warmWhite        COLOR(0xf,0x7,0x2)
#define white		 COLOR(0xd, 0xd, 0xd)
#define brown            COLOR(0x5, 0x3, 0x2)
#define silver           COLOR(0x3, 0x3, 0x3)

#define resetPin 3  //3 for ProTrinket, 2 for Trinket

int color = black;
byte portB_outputs = 0x01;
int delayTime = 10000;




void zero(byte portPin){
  PORTB = PORTB & ~portPin;
  delayMicroseconds(10);
  PORTB = PORTB | portPin;
  delayMicroseconds(20);
  PORTB = PORTB & ~portPin;
}

void one(byte portPin){
  PORTB = PORTB & ~portPin;
  delayMicroseconds(20);
  PORTB = PORTB | portPin;
  delayMicroseconds(10);
  PORTB = PORTB & ~portPin;
}

void beginGE(byte portPin){
  PORTB = PORTB | portPin;
  delayMicroseconds(10);
  PORTB = PORTB & ~portPin;
}

void endGE(byte portPin){
  PORTB = PORTB & ~portPin;
  delayMicroseconds(31);
}

void setColor(byte _pin, byte led, byte intensity, uint16_t color){
  noInterrupts();
  uint8_t i;
   beginGE(_pin);
   for(i = 6; i; i--, (led <<= 1))
      if(led & (1 << 5))
         one(_pin);
      else
         zero(_pin);
  
   for(i = 8; i; i--, (intensity <<= 1))
      if(intensity & (1 << 7))
         one(_pin);
      else
         zero(_pin);
  
   for(i = 12; i; i--, (color <<= 1))
      if(color & (1 << 11))
         one(_pin);
      else
         zero(_pin);
   endGE(_pin);
   interrupts();
}

int candleArray[] = {COLOR(15, 15, 0), COLOR(15, 15, 0), COLOR(15, 15, 0), COLOR(15, 15, 0), COLOR(15, 15, 0), COLOR(15, 15, 0), COLOR(15, 15, 0), COLOR(15, 15, 0),
                     COLOR(15, 15, 0), COLOR(15, 15, 0), COLOR(15, 15, 0), COLOR(15, 15, 0), COLOR(15, 15, 0), COLOR(15, 15, 0), COLOR(15, 15, 0), COLOR(15, 15, 0),
                     COLOR(15, 15, 0), COLOR(15, 15, 0), COLOR(15, 15, 0), COLOR(15, 15, 0), COLOR(15, 15, 0), COLOR(15, 15, 0), COLOR(15, 15, 0), COLOR(15, 15, 0)};

int colorTemp3000 = COLOR(0xe, 0x7, 0x3);
int colorTemp2000 = COLOR(0xf, 0x7, 0x1);



void setup() {
  
  if (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  
  digitalWrite(resetPin, HIGH);
  
  delay(500);
  
  DDRB = DDRB | portB_outputs;  //current value = 0x01 so only first pin on PORTB will be enabled
  
  delay(500);
  
  for (byte i = 0; i < lightCount; i++){
    noInterrupts();  //critical timing, especially during enumeration, so redundancy may be OK
    setColor(0x01, i, 0xcc, black);
    interrupts();
  }
  
}





void loop(){
  setColor(0x01, 0, 0xcc, colorTemp2000);
  delay(5000);
  setColor(0x01, 0, 0xcc, colorTemp3000);
  delay(5000);
  setColor(0x01, 0, 0xc0, white);
  delay(5000);
  
}
