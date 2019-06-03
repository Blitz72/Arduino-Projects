#include <avr/power.h>

#define COLOR(r,g,b)     ((r)+((g)<<4)+((b)<<8))  //Color is 12-bit (4-bit each R, G, B)
#define black     COLOR(0,0,0)  
#define red          COLOR(0xf,0,0)  
#define green     COLOR(0,0xf,0)  
#define blue          COLOR(0,0,0xf)  
#define teal          COLOR(0,0xf,0xf)  
#define magenta     COLOR(0xf,0,0xf)
#define pink     COLOR(0xf,0x2,0xf)
#define yellow     COLOR(0xf,0xf,0)
#define purple     COLOR(0xa,0x0,0xf)
#define orange    COLOR(0xf,0x3,0x0)
#define warmWhite     COLOR(0xf,0x7,0x2)
#define white		COLOR(0xd, 0xd, 0xd)
#define defaultIntensity      0xCC
#define lightCount      15       //15 = 15L G55 Star
                                 //36 = 36L string set
                                 //50 = 50L string set

byte pin = 1;

int rgb[] = {COLOR(15, 0, 0), COLOR(15, 1, 0), COLOR(15, 2, 0), COLOR(15, 3, 0), COLOR(15, 4, 0), COLOR(15, 5, 0), COLOR(15, 6, 0), COLOR(15, 7, 0), COLOR(15, 8, 0), COLOR(15, 9, 0),
COLOR(15, 10, 0), COLOR(15, 11, 0), COLOR(15, 12, 0), COLOR(15, 13, 0), COLOR(15, 14, 0), COLOR(15, 15, 0), COLOR(14, 15, 0), COLOR(13, 15, 0), COLOR(12, 15, 0), COLOR(11, 15, 0),
COLOR(10, 15, 0), COLOR(9, 15, 0), COLOR(8, 15, 0), COLOR(7, 15, 0), COLOR(6, 15, 0), COLOR(5, 15, 0), COLOR(4, 15, 0), COLOR(3, 15, 0), COLOR(2, 15, 0), COLOR(1, 15, 0), COLOR(0, 15, 0),
COLOR(0, 15, 1), COLOR(0, 15, 2), COLOR(0, 15, 3), COLOR(0, 15, 4), COLOR(0, 15, 5), COLOR(0, 15, 6), COLOR(0, 15, 7), COLOR(0, 15, 8), COLOR(0, 15, 9), COLOR(0, 15, 10), COLOR(0, 15,11),
COLOR(0, 15, 12), COLOR(0, 15, 13), COLOR(0, 15, 14), COLOR(0, 15, 15), COLOR(0, 14, 15), COLOR(0, 13, 15), COLOR(0, 12, 15), COLOR(0, 11, 15), COLOR(0, 10, 15), COLOR(0, 9, 15),
COLOR(0, 8, 15), COLOR(0, 7, 15), COLOR(0, 6, 15), COLOR(0, 5, 15), COLOR(0, 4, 15), COLOR(0, 3, 15), COLOR(0, 2, 15), COLOR(0, 1, 15), COLOR(0, 0, 15), COLOR(1, 0, 15), COLOR(2, 0, 15),
COLOR(3, 0, 15), COLOR(4, 0, 15), COLOR(5, 0, 15), COLOR(6, 0, 15), COLOR(7, 0, 15), COLOR(8, 0, 15), COLOR(9, 0, 15), COLOR(10, 0, 15), COLOR(11, 0, 15), COLOR(12, 0, 15), COLOR(13, 0, 15),
COLOR(14, 0, 15), COLOR(15, 0, 15), COLOR(15, 0, 14), COLOR(15, 0, 13), COLOR(15, 0, 12), COLOR(15, 0, 11), COLOR(15, 0, 10), COLOR(15, 0, 9), COLOR(15, 0, 8), COLOR(15, 0, 7),
COLOR(15, 0, 6), COLOR(15, 0, 5), COLOR(15, 0, 4), COLOR(15, 0, 3), COLOR(15, 0, 2), COLOR(15, 0, 1)};

int redFade[] = {COLOR(15, 0, 0), COLOR(14, 0, 0), COLOR(13, 0, 0), COLOR(12, 0, 0), COLOR(11, 0, 0), COLOR(10, 0, 0), COLOR(9, 0, 0), COLOR(8, 0, 0), COLOR(7, 0, 0), COLOR(6, 0, 0),
COLOR(5, 0, 0), COLOR(4, 0, 0), COLOR(3, 0, 0), COLOR(2, 0, 0), COLOR(1, 0, 0), COLOR(0, 0, 0)};

int greenFade[] = {COLOR(0, 15, 0), COLOR(0, 14, 0), COLOR(0, 13, 0), COLOR(0, 12, 0), COLOR(0, 11, 0), COLOR(0, 10, 0), COLOR(0, 9, 0), COLOR(0, 8, 0), COLOR(0, 7, 0), COLOR(0, 6, 0),
COLOR(0, 5, 0), COLOR(0, 4, 0), COLOR(0, 3, 0), COLOR(0, 2, 0), COLOR(0, 1, 0), COLOR(0, 0, 0)};

int blueFade[] = {COLOR(0, 0, 15), COLOR(0, 0, 14), COLOR(0, 0, 13), COLOR(0, 0, 12), COLOR(0, 0, 11), COLOR(0, 0, 10), COLOR(0, 0, 9), COLOR(0, 0, 8), COLOR(0, 0, 7), COLOR(0, 0, 6),
COLOR(0, 0, 5), COLOR(0, 0, 4), COLOR(0, 0, 3), COLOR(0, 0, 2), COLOR(0, 0, 1), COLOR(0, 0, 0)};

int whiteFade[] = {COLOR(15, 15, 15), COLOR(14, 14, 14), COLOR(13, 13, 13), COLOR(12, 12, 12), COLOR(11, 11, 11), COLOR(10, 10, 10), COLOR(9, 9, 9), COLOR(8, 8, 8), COLOR(7, 7, 7),
COLOR(6, 6, 6), COLOR(5, 5, 5), COLOR(4, 4, 4), COLOR(3, 3, 3), COLOR(2, 2, 2), COLOR(1, 1, 1), COLOR(0, 0, 0)};

int value = 0;
int y = 0;

void enumerate(){
  noInterrupts();
  fillColor(0, lightCount, 0xCC, black);
  interrupts();
}

void begin(){
  digitalWrite(pin, HIGH);
  delayMicroseconds(6);          //
  digitalWrite(pin, LOW);
}

void one(){
//  noInterrupts();
  digitalWrite(pin, LOW);
  delayMicroseconds(12);
  digitalWrite(pin, HIGH);
  delayMicroseconds(6);
  digitalWrite(pin, LOW);
//  interrupts();
}

void zero(){
//  noInterrupts();
  digitalWrite(pin, LOW);
  delayMicroseconds(3);
  digitalWrite(pin, HIGH);
  delayMicroseconds(16);
  digitalWrite(pin, LOW);
//  interrupts();
}

void end(){
//  noInterrupts();
  digitalWrite(pin, LOW);
  delayMicroseconds(30);
//  interrupts();
}

void setColor(byte led, byte intensity, uint16_t color){
  noInterrupts();
  byte i;
  begin();
  for(i = 6; i; i--, (led <<= 1))
    if(led & (1<<5)) one();
    else zero();
  for(i = 8;i ; i--, (intensity <<= 1))
    if(intensity & (1 << 7)) one();
    else zero();
  for(i = 12; i; i--, (color <<= 1))
    if(color & (1 << 11)) one();
    else zero();
  end();
  interrupts();
}

void fillColor(byte begin, byte count, byte intensity, uint16_t color){
  noInterrupts();
  while(count--){
    setColor(begin++, intensity, color);
  }
  interrupts();
}

void setup(){
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  pinMode(pin, OUTPUT);
//  delay(500);
//  noInterrupts();
  enumerate();
//  interrupts();
}

void loop(){
  for(byte i = 0; i < 10; i++){
    fillColor(0, lightCount, defaultIntensity, red);
    delay(500);
    fillColor(0, lightCount, defaultIntensity, white);
    delay(500);
    fillColor(0, lightCount, defaultIntensity, green);
    delay(500);
    fillColor(0, lightCount, defaultIntensity, white);
    delay(500);
  }
  for(int x = 0; x < 900; x++){                                                     //RGB COLOR SWIRL
    while(y < lightCount){
      value = (x+y)%90;
      setColor(y, defaultIntensity, rgb[value]);
      y++;
    }
    y = 0;
  }

}
