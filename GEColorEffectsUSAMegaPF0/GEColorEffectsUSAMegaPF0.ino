#include <avr/power.h>

#define lightCount 50  //Total # of lights on string (usually 50, 48, or 36)

#define COLOR(r,g,b)     ((r)+((g)<<4)+((b)<<8))  //Color is 12-bit (4-bit each R, G, B)
#define black            COLOR(0,0,0)
#define red              COLOR(0xf,0,0)
#define darkRed          COLOR(0x3, 0, 0)
#define green            COLOR(0,0xf,0)
#define darkGreen        COLOR(0, 0x2, 0)
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


const int delayTime = 5000;

int color = 0;

const int flagColors[50] = {red, white, blue, white, red, white, black, blue, white, red, white, blue, white, red, white, blue, white, red, white, blue, white,
                            red, white, black, blue, white, red, white, blue, white, red, white, blue, white, red, white, blue, white, red, white, blue, white,
                            red, white, blue, white, red, white, red, white};

const int armyGreen[50] = {green, darkGreen, green, darkGreen, green, darkGreen, black, green, darkGreen, green, darkGreen, green, darkGreen, green, darkGreen, green, darkGreen,
                           green, darkGreen, green, darkGreen, green, darkGreen, black, green, darkGreen, green, darkGreen, green, darkGreen, green, darkGreen, green, darkGreen,
                           green, darkGreen, green, darkGreen, green, darkGreen, green, darkGreen, green, darkGreen, green, darkGreen, green, darkGreen, green, darkGreen};

const int navyBlue[50] = {blue, gold, blue, gold, blue, gold, black, blue, gold, blue, gold, blue, gold, blue, gold, blue, gold, blue, gold, blue, gold, blue, gold, black, blue,
                          gold, blue, gold, blue, gold, blue, gold, blue, gold, blue, gold, blue, gold, blue, gold, blue, gold, blue, gold, blue, gold, blue, gold,
                          blue, gold};

const int airForce[50] = {blue, silver, blue, silver, blue, silver, black, blue, silver, blue, silver, blue, silver, blue, silver, blue, silver, blue, silver, blue, silver, blue,
                          silver, black, blue, silver, blue, silver, blue, silver, blue, silver, blue, silver, blue, silver, blue, silver, blue, silver, blue, silver,
                          blue, silver, blue, silver, blue, silver, blue, silver};

const int marines[50] = {darkRed, gold, darkRed, gold, darkRed, gold, black, darkRed, gold, darkRed, gold, darkRed, gold, darkRed, gold, darkRed, gold, darkRed, gold, darkRed,
                         gold, darkRed, gold, black, darkRed, gold, darkRed, gold, darkRed, gold, darkRed, gold, darkRed, gold, darkRed, gold, darkRed, gold, darkRed, gold,
                         darkRed, gold, darkRed, gold, darkRed, gold, darkRed, gold, darkRed, gold};

const int coastGuard[50] = {orange, white, orange, white, orange, white, black, orange, white, orange, white, orange, white, orange, white, orange, white, orange, white, orange,
                            white, orange, white, black, orange, white, orange, white, orange, white, orange, white, orange, white, orange, white, orange, white, orange, white,
                            orange, white, orange, white, orange, white, orange, white, orange, white};


void zero(){
  PORTF = PORTF & 0xfe;
  delayMicroseconds(10);
  PORTF = PORTF | 0x01;
  delayMicroseconds(20);
  PORTF = PORTF & 0xfe;
}

void one(){
  PORTF = PORTF & 0xfe;
  delayMicroseconds(20);
  PORTF = PORTF | 0x01;
  delayMicroseconds(10);
  PORTF = PORTF & 0xfe;
}

void beginGE(){
  PORTF = PORTF | 0x01;
  delayMicroseconds(10);
  PORTF = PORTF & 0xfe;
}

void endGE(){
  PORTF = PORTF & 0xfe;
  delayMicroseconds(31);
}

void setColor(byte led, byte intensity, uint16_t color){
  uint8_t i;
   beginGE();
   for(i = 6; i; i--, (led <<= 1))
      if(led & (1 << 5))
         one();
      else
         zero();
  
   for(i = 8; i; i--, (intensity <<= 1))
      if(intensity & (1 << 7))
         one();
      else
         zero();
  
   for(i = 12; i; i--, (color <<= 1))
      if(color & (1 << 11))
         one();
      else
         zero();
   endGE();
}


void setup() {
  
  if (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  
  DDRF = DDRF | 0x01;

  delay(500);
  
  for (byte i = 0; i < lightCount; i++){
    noInterrupts();
    setColor(i, 0xcc, black);
    interrupts();
  }
  
}

void loop() {
  
/*  for (int i = 0; i < lightCount; i++){
    noInterrupts();
    setColor(i, 0xcc, flagColors[i]);
    interrupts();
  }
  delay(delayTime);
  for (int i = 0; i < lightCount; i++){
    noInterrupts();
    setColor(i, 0xcc, armyGreen[i]);
    interrupts();
  }
  delay(delayTime);
  delay(delayTime);
  delay(delayTime);
  for (int i = 0; i < lightCount; i++){
    noInterrupts();
    setColor(i, 0xcc, navyBlue[i]);
    interrupts();
  }
  delay(delayTime);
  for (int i = 0; i < lightCount; i++){
    noInterrupts();
    setColor(i, 0xcc, airForce[i]);
    interrupts();
  }
  delay(delayTime);
  for (int i = 0; i < lightCount; i++){
    noInterrupts();
    setColor(i, 0xcc, marines[i]);
    interrupts();
  }
  delay(delayTime);
  delay(delayTime);
  for (int i = 0; i < lightCount; i++){
    noInterrupts();
    setColor(i, 0xcc, coastGuard[i]);
    interrupts();
  }
  delay(delayTime);
  */
  noInterrupts();
  for (byte i = 0; i < lightCount; i++){
    if (i%2 == 1) color = white;
    if (i%4 == 0) color = red;
    if (i%4 == 2) color = blue;
    setColor(i, 0xcc, color);
  }
  interrupts();
  
  delay(delayTime);
  
  noInterrupts();
  for (byte i = 0; i < lightCount; i++){
    if (i%2 == 0) color = green;
    else color = green;
    setColor(i, 0xcc, color);
  }
  interrupts();
  
  delay(delayTime*3);
  
  noInterrupts();
  for (byte i = 0; i < lightCount; i++){
    if (i%2 == 0) color = blue;
    else color = gold;
    setColor(i, 0xcc, color);
  }
  interrupts();
  
  delay(delayTime);
  
  noInterrupts();
  for (byte i = 0; i < lightCount; i++){
    if (i%2 == 0) color = blue;
    else color = silver;
    setColor(i, 0xcc, color);
  }
  interrupts();
  
  delay(delayTime);
  
  noInterrupts();
  for (byte i = 0; i < lightCount; i++){
    if (i%2 == 0) color = red;
    else color = gold;
    setColor(i, 0xcc, color);
  }
  interrupts();
  
  delay(delayTime*2);
  
  noInterrupts();
  for (byte i = 0; i < lightCount; i++){
    if (i%2 == 0) color = orange;
    else color = white;
    setColor(i, 0xcc, color);
  }
  interrupts();
  
  delay(delayTime);
  
}
