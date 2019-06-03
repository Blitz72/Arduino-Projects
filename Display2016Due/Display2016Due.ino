#include <SPI.h>
#include <SD.h>

#define COLOR(r,g,b)     ((r)+((g)<<4)+((b)<<8))  //Color is 12-bit (4-bit each R, G, B)
#define black            COLOR(0,0,0)  
#define red              COLOR(0xf,0,0)  
#define green            COLOR(0,0xf,0)  
#define blue             COLOR(0,0,0xf)  
#define teal             COLOR(0,0xf,0xf)  
#define magenta          COLOR(0xf,0,0xf)
#define pink             COLOR(0xf,0x2,0xf)
#define yellow           COLOR(0xf,0xf,0)
#define purple           COLOR(0xa,0x0,0xf)
#define orange           COLOR(0xf,0x3,0x0)
#define ltOrange         COLOR(0xf,0x7,0x0)
#define warmWhite        COLOR(0xf,0x7,0x2)
#define white		 COLOR(0xd,0xd,0xd)
#define brown1           COLOR(0x3,0x1,0x1)  //adjusted to 3, 1, 1 for 2016 brown from 5, 3, 2 (2015)
#define brown2           COLOR(0x5,0x3,0x2)
#define olive            COLOR(0x3,0x8,0x0)  //85, 107, 47; adjusted to 3, 8, 0 for GE G35 lights
#define lightCount      48             //50, only need 48 out of 50 for 24 x 48 pixel display
#define lightCount2     50             //Using 50 for enumerateAll() so last 2 won't turn on
#define defaultIntensity      0xcc
#define delayShort      10      //6 orig.
#define delayLong       20      //12 orig.
#define delayShort_2    9      //3 orig.
#define delayLong_2     19      //16 orig.
#define delayEnd        31      //30 orig.
#define outRegC         0x17eff3fe

File myFile;

int delayTime1 = 1000;

uint32_t pixelData[48][12] = {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,  //0
                              0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,  //1
                              0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,  //2
                              0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,  //3
                              0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,  //4
                              0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,  //5
                              0x006c13c0, 0x006c13c0, 0x006c13c0, 0x006c13c0, 0x006c13c0, 0x006c13c0, 0x006c13c0, 0x006c13c0, 0x006c13c0, 0x006c13c0, 0x006c13c0, 0x006c13c0,  //6
                              0x01c1f3f0, 0x01c1f3f0, 0x01c1f3f0, 0x01c1f3f0, 0x01c1f3f0, 0x01c1f3f0, 0x01c1f3f0, 0x01c1f3f0, 0x01c1f3f0, 0x01c1f3f0, 0x01c1f3f0, 0x01c1f3f0,  //7
                              0x0703e03c, 0x0703e03c, 0x0703e03c, 0x0703e03c, 0x0703e03c, 0x0703e03c, 0x0703e03c, 0x0703e03c, 0x0703e03c, 0x0703e03c, 0x0703e03c, 0x0703e03c,  //8
                              0x1603000e, 0x1603000e, 0x1603000e, 0x1603000e, 0x1603000e, 0x1603000e, 0x1603000e, 0x1603000e, 0x1603000e, 0x1603000e, 0x1603000e, 0x1603000e,  //9
                              0x10000002, 0x10000002, 0x10000002, 0x10000002, 0x10000002, 0x10000002, 0x10000002, 0x10000002, 0x10000002, 0x10000002, 0x10000002, 0x10000002,  //10
                              0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,  //11
                              0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,  //12
                              0x01e001c0, 0x01e001c0, 0x01e001c0, 0x01e001c0, 0x01e001c0, 0x01e001c0, 0x01e001c0, 0x01e001c0, 0x01e001c0, 0x01e001c0, 0x01e001c0, 0x01e001c0,  //13
                              0x03280220, 0x03280220, 0x03280220, 0x03280220, 0x03280220, 0x03280220, 0x03280220, 0x03280220, 0x03280220, 0x03280220, 0x03280220, 0x03280220,  //14
                              0x020c0380, 0x020c0380, 0x020c0380, 0x020c0380, 0x020c0380, 0x020c0380, 0x020c0380, 0x020c0380, 0x020c0380, 0x020c0380, 0x020c0380, 0x020c0380,  //15
                              0x02021360, 0x02021360, 0x02021360, 0x02021360, 0x02021360, 0x02021360, 0x02021360, 0x02021360, 0x02021360, 0x02021360, 0x02021360, 0x02021360,  //16
                              0x03033230, 0x03033230, 0x03033230, 0x03033230, 0x03033230, 0x03033230, 0x03033230, 0x03033230, 0x03033230, 0x03033230, 0x03033230, 0x03033230,  //17
                              0x01812308, 0x01812308, 0x01812308, 0x01812308, 0x01812308, 0x01812308, 0x01812308, 0x01812308, 0x01812308, 0x01812308, 0x01812308, 0x01812308,  //18
                              0x00e0a184, 0x00e0a184, 0x00e0a184, 0x00e0a184, 0x00e0a184, 0x00e0a184, 0x00e0a184, 0x00e0a184, 0x00e0a184, 0x00e0a184, 0x00e0a184, 0x00e0a184,  //19
                              0x002ff0c4, 0x002ff0c4, 0x002ff0c4, 0x002ff0c4, 0x002ff0c4, 0x002ff0c4, 0x002ff0c4, 0x002ff0c4, 0x002ff0c4, 0x002ff0c4, 0x002ff0c4, 0x002ff0c4,  //20
                              0x0000d238, 0x0000d238, 0x0000d238, 0x0000d238, 0x0000d238, 0x0000d238, 0x0000d238, 0x0000d238, 0x0000d238, 0x0000d238, 0x0000d238, 0x0000d238,  //21
                              0x00004380, 0x00004380, 0x00004380, 0x00004380, 0x00004380, 0x00004380, 0x00004380, 0x00004380, 0x00004380, 0x00004380, 0x00004380, 0x00004380,  //22
                              0x00004180, 0x00004180, 0x00004180, 0x00004180, 0x00004180, 0x00004180, 0x00004180, 0x00004180, 0x00004180, 0x00004180, 0x00004180, 0x00004180,  //23
                              0x006e4000, 0x006e4000, 0x006e4000, 0x006e4000, 0x006e4000, 0x006e4000, 0x006e4000, 0x006e4000, 0x006e4000, 0x006e4000, 0x006e4000, 0x006e4000,  //24
                              0x00e39000, 0x00e39000, 0x00e39000, 0x00e39000, 0x00e39000, 0x00e39000, 0x00e39000, 0x00e39000, 0x00e39000, 0x00e39000, 0x00e39000, 0x00e39000,  //25
                              0x0180d3c0, 0x0180d3c0, 0x0180d3c0, 0x0180d3c0, 0x0180d3c0, 0x0180d3c0, 0x0180d3c0, 0x0180d3c0, 0x0180d3c0, 0x0180d3c0, 0x0180d3c0, 0x0180d3c0,  //26
                              0x03007270, 0x03007270, 0x03007270, 0x03007270, 0x03007270, 0x03007270, 0x03007270, 0x03007270, 0x03007270, 0x03007270, 0x03007270, 0x03007270,  //27
                              0x022c2118, 0x022c2118, 0x022c2118, 0x022c2118, 0x022c2118, 0x022c2118, 0x022c2118, 0x022c2118, 0x022c2118, 0x022c2118, 0x022c2118, 0x022c2118,  //28
                              0x02662184, 0x02662184, 0x02662184, 0x02662184, 0x02662184, 0x02662184, 0x02662184, 0x02662184, 0x02662184, 0x02662184, 0x02662184, 0x02662184,  //29
                              0x020130c4, 0x020130c4, 0x020130c4, 0x020130c4, 0x020130c4, 0x020130c4, 0x020130c4, 0x020130c4, 0x020130c4, 0x020130c4, 0x020130c4, 0x020130c4,  //30
                              0x03013038, 0x03013038, 0x03013038, 0x03013038, 0x03013038, 0x03013038, 0x03013038, 0x03013038, 0x03013038, 0x03013038, 0x03013038, 0x03013038,  //31
                              0x01030000, 0x01030000, 0x01030000, 0x01030000, 0x01030000, 0x01030000, 0x01030000, 0x01030000, 0x01030000, 0x01030000, 0x01030000, 0x01030000,  //32
                              0x00c60000, 0x00c60000, 0x00c60000, 0x00c60000, 0x00c60000, 0x00c60000, 0x00c60000, 0x00c60000, 0x00c60000, 0x00c60000, 0x00c60000, 0x00c60000,  //33
                              0x006c0000, 0x006c0000, 0x006c0000, 0x006c0000, 0x006c0000, 0x006c0000, 0x006c0000, 0x006c0000, 0x006c0000, 0x006c0000, 0x006c0000, 0x006c0000,  //34
                              0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,  //35
                              0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,  //36
                              0x10000002, 0x10000002, 0x10000002, 0x10000002, 0x10000002, 0x10000002, 0x10000002, 0x10000002, 0x10000002, 0x10000002, 0x10000002, 0x10000002,  //37
                              0x1600300e, 0x1600300e, 0x1600300e, 0x1600300e, 0x1600300e, 0x1600300e, 0x1600300e, 0x1600300e, 0x1600300e, 0x1600300e, 0x1600300e, 0x1600300e,  //38
                              0x0781f01c, 0x0781f01c, 0x0781f01c, 0x0781f01c, 0x0781f01c, 0x0781f01c, 0x0781f01c, 0x0781f01c, 0x0781f01c, 0x0781f01c, 0x0781f01c, 0x0781f01c,  //39
                              0x01e3e030, 0x01e3e030, 0x01e3e030, 0x01e3e030, 0x01e3e030, 0x01e3e030, 0x01e3e030, 0x01e3e030, 0x01e3e030, 0x01e3e030, 0x01e3e030, 0x01e3e030,  //40
                              0x006e03c0, 0x006e03c0, 0x006e03c0, 0x006e03c0, 0x006e03c0, 0x006e03c0, 0x006e03c0, 0x006e03c0, 0x006e03c0, 0x006e03c0, 0x006e03c0, 0x006e03c0,  //41
                              0x0007f200, 0x0007f200, 0x0007f200, 0x0007f200, 0x0007f200, 0x0007f200, 0x0007f200, 0x0007f200, 0x0007f200, 0x0007f200, 0x0007f200, 0x0007f200,  //42
                              0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,  //43
                              0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,  //44
                              0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,  //45
                              0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,  //46
                              0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000}; //47

void beginAll(){          //begins the data frame for all outputs on PIOC
  PIOC->PIO_ODSR = outRegC;
  delayMicroseconds(delayShort);  //Output should be ~ 10uS long
  PIOC->PIO_ODSR = 0x00;
}

void beginBitMask(uint32_t bitMask){          //begins the data frame for all outputs on PIOC
  PIOC->PIO_ODSR = outRegC & bitMask;
  delayMicroseconds(delayShort);  //Output should be ~ 10uS long
  PIOC->PIO_ODSR = 0x00;
}

void begin(int outPin){          //begins the data frame for all outputs on PIOC
  digitalWrite(outPin, HIGH);
  delayMicroseconds(delayShort);  //Output should be ~ 10uS long
  digitalWrite(outPin, LOW);
}

void zeroAll(){
  PIOC->PIO_ODSR = 0x00;
  delayMicroseconds(delayShort);  //Output should be ~ 10uS long
  PIOC->PIO_ODSR = outRegC;
  delayMicroseconds(delayLong); //Output should be ~ 20uS long
  PIOC->PIO_ODSR = 0x00;
}

void zeroBitMask(uint32_t bitMask){
  PIOC->PIO_ODSR = 0x00;
  delayMicroseconds(delayShort);  //Output should be ~ 10uS long
  PIOC->PIO_ODSR = outRegC & bitMask;
  delayMicroseconds(delayLong); //Output should be ~ 20uS long
  PIOC->PIO_ODSR = 0x00;
}

void zero(int outPin){
  digitalWrite(outPin, LOW);
  delayMicroseconds(delayShort);  //Output should be ~ 10uS long
  digitalWrite(outPin, HIGH);
  delayMicroseconds(delayLong); //Output should be ~ 20uS long
  digitalWrite(outPin, LOW);
}

void oneAll(){
  PIOC->PIO_ODSR = 0x00;
  delayMicroseconds(delayLong);    //Output should be ~ 20uS long
  PIOC->PIO_ODSR = outRegC;
  delayMicroseconds(delayShort);    //Output should be ~ 10uS long
  PIOC->PIO_ODSR = 0x00;
}

void oneBitMask(uint32_t bitMask){
  PIOC->PIO_ODSR = 0x00;
  delayMicroseconds(delayLong);    //Output should be ~ 20uS long
  PIOC->PIO_ODSR = outRegC & bitMask;
  delayMicroseconds(delayShort);    //Output should be ~ 10uS long
  PIOC->PIO_ODSR = 0x00;
}

void one(int outPin){
  digitalWrite(outPin, LOW);
  delayMicroseconds(delayLong);    //Output should be ~ 20uS long
  digitalWrite(outPin, HIGH);
  delayMicroseconds(delayShort);    //Output should be ~ 10uS long
  digitalWrite(outPin, LOW);
}

void zeroOne(uint32_t pixels){            //
  PIOC->PIO_ODSR = 0x00; 
  delayMicroseconds(delayShort); //Output should be ~ 10uS long (orig. 6, changed to 3 to match zeroAll() timing)
  PIOC->PIO_ODSR = ~pixels & outRegC;
  delayMicroseconds(delayShort_2);  //Output should be ~ 10uS long (orig. 6, changed to 9 to match zeroAll() timing)
  PIOC->PIO_ODSR = outRegC;
  delayMicroseconds(delayShort);  //Output should be ~ 10uS long (orig. 7)
}

void zeroOneBitMask(uint32_t pixels, uint32_t bitMask){            //
  PIOC->PIO_ODSR = 0x00; 
  delayMicroseconds(delayShort); //Output should be ~ 10uS long (orig. 6, changed to 3 to match zeroAll() timing)
  PIOC->PIO_ODSR = ~pixels & outRegC & bitMask;
  delayMicroseconds(delayShort_2);  //Output should be ~ 10uS long (orig. 6, changed to 9 to match zeroAll() timing)
  PIOC->PIO_ODSR = outRegC & bitMask;
  delayMicroseconds(delayShort);  //Output should be ~ 10uS long (orig. 7)
}

void endAll(){            //sets the data line LOW between data frames
  PIOC->PIO_ODSR = 0x00;
  delayMicroseconds(delayEnd);
}

void end(int outPin){            //sets the data line LOW between data frames
  digitalWrite(outPin, LOW);
  delayMicroseconds(delayEnd);
}



void enumerate(int outPin){       //addresses each bulb individually for all outputs
   fillColor(0, lightCount2, defaultIntensity, black, outPin);
}

void setColorAll(int led, int intensity, int color){
  noInterrupts();
  beginAll();
  
  for (int i = 6; i; i--, (led <<= 1))
    if (led & (1 << 5))
      oneAll();
    else
      zeroAll();
  
  for (int i = 8; i; i--, (intensity <<= 1))
    if (intensity & (1 << 7))
      oneAll();
    else
      zeroAll();
  
  for (int i = 12; i; i--, (color <<= 1))
    if (color & (1 << 11))
      oneAll();
    else
      zeroAll();
    
  endAll();
  interrupts();
}

void setColor(int led, int intensity, int color, int pin){
  noInterrupts();
  begin(pin);
  
  for (int i = 6; i; i--, (led <<= 1))
    if (led & (1 << 5))
      one(pin);
    else
      zero(pin);
  
  for (int i = 8; i; i--, (intensity <<= 1))
    if (intensity & (1 << 7))
      one(pin);
    else
      zero(pin);
  
  for (int i = 12; i; i--, (color <<= 1))
    if (color & (1 << 11))
      one(pin);
    else
      zero(pin);
    
  end(pin);
  interrupts();
}

void setColorPixels(int led, int intensity){
  int _led = led;
  beginAll();
  
  for (int i = 6; i; i--, (led <<= 1))
    if (led & (1 << 5))
      oneAll();
    else
      zeroAll();
  
  for (int i = 8; i; i--, (intensity <<= 1))
    if (intensity & (1 << 7))
      oneAll();
    else
      zeroAll();
  
  for (int i = 0; i<12; i++){
    zeroOne(pixelData[_led][i]);
  }
    
  endAll();
}

void setColorPinBitMask(int led, int intensity, uint32_t pin, int color){  //pin must be a single output on PIOC, i.e.: first available string from top is 0x00000002
  int _led = led;
  beginBitMask(pin);
  
  for (int i = 6; i; i--, (led <<= 1))
    if (led & (1 << 5))
      oneBitMask(pin);
    else
      zeroBitMask(pin);
  
  for (int i = 8; i; i--, (intensity <<= 1))
    if (intensity & (1 << 7))
      oneBitMask(pin);
    else
      zeroBitMask(pin);
  
  for (int i = 12; i; i--, (color <<= 1))
    if (color & (1 << 11))
      oneBitMask(pin);
    else
      zeroBitMask(pin);
    
  endAll();
}

void fillColorAll(uint8_t beginBulb, uint8_t count, uint8_t intensity, uint16_t color){ //fills the string with a color and intensity starting from a specific bulb to the end of the string
  noInterrupts();                                                                       //for all outputs on PIOC
  while(count--){
    setColorAll(beginBulb++, intensity, color);  
  }
  interrupts();
}

void fillColor(uint8_t beginBulb, uint8_t count, uint8_t intensity, uint16_t color, int pin){ //fills the string with a color and intensity starting from a specific bulb to the end of the string
  noInterrupts();                                                                             //for all outputs on PIOC
  while(count--){
    setColor(beginBulb++, intensity, color, pin);  
  }
  interrupts();
}

void GELogo(){
  myFile = SD.open("disp_16/GELogo32.txt", FILE_READ);          //test to see how data is parsed out after writing
  if (!myFile) Serial.println("Error opening file!");
  unsigned long startTime = millis();
  if (myFile){
    for(int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        pixelData[i][j] = myFile.read();
        pixelData[i][j] += myFile.read() << 8;
        pixelData[i][j] += myFile.read() << 16;
        pixelData[i][j] += myFile.read() << 24;
        //Serial.print(pixelData[i][j], HEX);    //comment out for speed test or actual usage
        //if (j < 11) Serial.print(", ");        //comment out for speed test or actual usage
        //if (j == 11) Serial.println();         //comment out for speed test or actual usage
      }
    }
  }
  myFile.close();
  noInterrupts();
  for(int i = 0; i < lightCount; i++){
    setColorAll(i, 0, 0);
  }
  for(int x = 0; x <= defaultIntensity; x++){
    for(int i = 0; i < lightCount; i++){
      setColorPixels(i, x);
    }
  }
  interrupts();
}

void tree1(){
  myFile = SD.open("disp_16/tree132.txt", FILE_READ);          //test to see how data is parsed out after writing
  //if (!myFile) Serial.println("Error opening file!");
  if (myFile){
    for(int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        pixelData[i][j] = myFile.read();
        pixelData[i][j] += myFile.read() << 8;
        pixelData[i][j] += myFile.read() << 16;
        pixelData[i][j] += myFile.read() << 24;
      }
    }
  }
  for(int i =0; i< lightCount; i++){
    setColorPixels(i, defaultIntensity);
  }
}

void tree2(){
  myFile = SD.open("disp_16/tree232.txt", FILE_READ);          //test to see how data is parsed out after writing
  //if (!myFile) Serial.println("Error opening file!");
  if (myFile){
    for(int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        pixelData[i][j] = myFile.read();
        pixelData[i][j] += myFile.read() << 8;
        pixelData[i][j] += myFile.read() << 16;
        pixelData[i][j] += myFile.read() << 24;
      }
    }
  }
  for(int i =0; i< lightCount; i++){
    setColorPixels(i, defaultIntensity);
  }
}

void tree3(){
  myFile = SD.open("disp_16/tree332.txt", FILE_READ);          //test to see how data is parsed out after writing
  //if (!myFile) Serial.println("Error opening file!");
  if (myFile){
    for(int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        pixelData[i][j] = myFile.read();
        pixelData[i][j] += myFile.read() << 8;
        pixelData[i][j] += myFile.read() << 16;
        pixelData[i][j] += myFile.read() << 24;
      }
    }
  }
  for(int i =0; i< lightCount; i++){
    setColorPixels(i, defaultIntensity);
  }
}

void tree4(){
  myFile = SD.open("disp_16/tree432.txt", FILE_READ);          //test to see how data is parsed out after writing
  //if (!myFile) Serial.println("Error opening file!");
  if (myFile){
    for(int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        pixelData[i][j] = myFile.read();
        pixelData[i][j] += myFile.read() << 8;
        pixelData[i][j] += myFile.read() << 16;
        pixelData[i][j] += myFile.read() << 24;
      }
    }
  }
  for(int i =0; i< lightCount; i++){
    setColorPixels(i, defaultIntensity);
  }
}
void tree5(){
  myFile = SD.open("disp_16/tree532.txt", FILE_READ);          //test to see how data is parsed out after writing
  //if (!myFile) Serial.println("Error opening file!");
  if (myFile){
    for(int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        pixelData[i][j] = myFile.read();
        pixelData[i][j] += myFile.read() << 8;
        pixelData[i][j] += myFile.read() << 16;
        pixelData[i][j] += myFile.read() << 24;
      }
    }
  }
  for(int i =0; i< lightCount; i++){
    setColorPixels(i, defaultIntensity);
  }
}

void tree6(){
  myFile = SD.open("disp_16/tree632.txt", FILE_READ);          //test to see how data is parsed out after writing
  //if (!myFile) Serial.println("Error opening file!");
  if (myFile){
    for(int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        pixelData[i][j] = myFile.read();
        pixelData[i][j] += myFile.read() << 8;
        pixelData[i][j] += myFile.read() << 16;
        pixelData[i][j] += myFile.read() << 24;
      }
    }
  }
  for(int i =0; i< lightCount; i++){
    setColorPixels(i, defaultIntensity);
  }
}

void tree7(){
  myFile = SD.open("disp_16/tree732.txt", FILE_READ);          //test to see how data is parsed out after writing
  //if (!myFile) Serial.println("Error opening file!");
  if (myFile){
    for(int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        pixelData[i][j] = myFile.read();
        pixelData[i][j] += myFile.read() << 8;
        pixelData[i][j] += myFile.read() << 16;
        pixelData[i][j] += myFile.read() << 24;
      }
    }
  }
  for(int i =0; i< lightCount; i++){
    setColorPixels(i, defaultIntensity);
  }
}

void tree8(){
  myFile = SD.open("disp_16/tree832.txt", FILE_READ);          //test to see how data is parsed out after writing
  //if (!myFile) Serial.println("Error opening file!");
  if (myFile){
    for(int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        pixelData[i][j] = myFile.read();
        pixelData[i][j] += myFile.read() << 8;
        pixelData[i][j] += myFile.read() << 16;
        pixelData[i][j] += myFile.read() << 24;
      }
    }
  }
  for(int i =0; i< lightCount; i++){
    setColorPixels(i, defaultIntensity);
  }
}

void tree9(){
  myFile = SD.open("disp_16/tree932.txt", FILE_READ);          //test to see how data is parsed out after writing
  //if (!myFile) Serial.println("Error opening file!");
  if (myFile){
    for(int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        pixelData[i][j] = myFile.read();
        pixelData[i][j] += myFile.read() << 8;
        pixelData[i][j] += myFile.read() << 16;
        pixelData[i][j] += myFile.read() << 24;
      }
    }
  }
  for(int i =0; i< lightCount; i++){
    setColorPixels(i, defaultIntensity);
  }
}

void tree10(){
  myFile = SD.open("disp_16/tree1032.txt", FILE_READ);          //test to see how data is parsed out after writing
  //if (!myFile) Serial.println("Error opening file!");
  if (myFile){
    for(int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        pixelData[i][j] = myFile.read();
        pixelData[i][j] += myFile.read() << 8;
        pixelData[i][j] += myFile.read() << 16;
        pixelData[i][j] += myFile.read() << 24;
      }
    }
  }
  for(int i =0; i< lightCount; i++){
    setColorPixels(i, defaultIntensity);
  }
}

void tree11(){
  myFile = SD.open("disp_16/tree1132.txt", FILE_READ);          //test to see how data is parsed out after writing
  //if (!myFile) Serial.println("Error opening file!");
  if (myFile){
    for(int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        pixelData[i][j] = myFile.read();
        pixelData[i][j] += myFile.read() << 8;
        pixelData[i][j] += myFile.read() << 16;
        pixelData[i][j] += myFile.read() << 24;
      }
    }
  }
  for(int i =0; i< lightCount; i++){
    setColorPixels(i, defaultIntensity);
  }
}

void tree12(){
  myFile = SD.open("disp_16/tree1232.txt", FILE_READ);          //test to see how data is parsed out after writing
  //if (!myFile) Serial.println("Error opening file!");
  if (myFile){
    for(int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        pixelData[i][j] = myFile.read();
        pixelData[i][j] += myFile.read() << 8;
        pixelData[i][j] += myFile.read() << 16;
        pixelData[i][j] += myFile.read() << 24;
      }
    }
  }
  for(int i =0; i< lightCount; i++){
    setColorPixels(i, defaultIntensity);
  }
}

void tree13(){
  myFile = SD.open("disp_16/tree1332.txt", FILE_READ);          //test to see how data is parsed out after writing
  //if (!myFile) Serial.println("Error opening file!");
  if (myFile){
    for(int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        pixelData[i][j] = myFile.read();
        pixelData[i][j] += myFile.read() << 8;
        pixelData[i][j] += myFile.read() << 16;
        pixelData[i][j] += myFile.read() << 24;
      }
    }
  }
  for(int i =0; i< lightCount; i++){
    setColorPixels(i, defaultIntensity);
  }
}

void tree14(){
  myFile = SD.open("disp_16/tree1432.txt", FILE_READ);          //test to see how data is parsed out after writing
  //if (!myFile) Serial.println("Error opening file!");
  if (myFile){
    for(int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        pixelData[i][j] = myFile.read();
        pixelData[i][j] += myFile.read() << 8;
        pixelData[i][j] += myFile.read() << 16;
        pixelData[i][j] += myFile.read() << 24;
      }
    }
  }
  for(int i =0; i< lightCount; i++){
    setColorPixels(i, defaultIntensity);
  }
}

void tree15(){
  myFile = SD.open("disp_16/tree1532.txt", FILE_READ);          //test to see how data is parsed out after writing
  //if (!myFile) Serial.println("Error opening file!");
  if (myFile){
    for(int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        pixelData[i][j] = myFile.read();
        pixelData[i][j] += myFile.read() << 8;
        pixelData[i][j] += myFile.read() << 16;
        pixelData[i][j] += myFile.read() << 24;
      }
    }
  }
  for(int i =0; i< lightCount; i++){
    setColorPixels(i, defaultIntensity);
  }
}

void tree16(){
  myFile = SD.open("disp_16/tree1632.txt", FILE_READ);          //test to see how data is parsed out after writing
  //if (!myFile) Serial.println("Error opening file!");
  if (myFile){
    for(int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        pixelData[i][j] = myFile.read();
        pixelData[i][j] += myFile.read() << 8;
        pixelData[i][j] += myFile.read() << 16;
        pixelData[i][j] += myFile.read() << 24;
      }
    }
  }
  for(int i =0; i< lightCount; i++){
    setColorPixels(i, defaultIntensity);
  }
}

void tree17(){
  myFile = SD.open("disp_16/tree1732.txt", FILE_READ);          //test to see how data is parsed out after writing
  //if (!myFile) Serial.println("Error opening file!");
  if (myFile){
    for(int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        pixelData[i][j] = myFile.read();
        pixelData[i][j] += myFile.read() << 8;
        pixelData[i][j] += myFile.read() << 16;
        pixelData[i][j] += myFile.read() << 24;
      }
    }
  }
  for(int i =0; i< lightCount; i++){
    setColorPixels(i, defaultIntensity);
  }
}

void tree18(){
  myFile = SD.open("disp_16/tree1832.txt", FILE_READ);          //test to see how data is parsed out after writing
  //if (!myFile) Serial.println("Error opening file!");
  if (myFile){
    for(int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        pixelData[i][j] = myFile.read();
        pixelData[i][j] += myFile.read() << 8;
        pixelData[i][j] += myFile.read() << 16;
        pixelData[i][j] += myFile.read() << 24;
      }
    }
  }
  for(int i =0; i< lightCount; i++){
    setColorPixels(i, defaultIntensity);
  }
}

void tree19(){
  myFile = SD.open("disp_16/tree1932.txt", FILE_READ);          //test to see how data is parsed out after writing
  //if (!myFile) Serial.println("Error opening file!");
  if (myFile){
    for(int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        pixelData[i][j] = myFile.read();
        pixelData[i][j] += myFile.read() << 8;
        pixelData[i][j] += myFile.read() << 16;
        pixelData[i][j] += myFile.read() << 24;
      }
    }
  }
  for(int i =0; i< lightCount; i++){
    setColorPixels(i, defaultIntensity);
  }
}

void tree20(){
  myFile = SD.open("disp_16/tree2032.txt", FILE_READ);          //test to see how data is parsed out after writing
  //if (!myFile) Serial.println("Error opening file!");
  if (myFile){
    for(int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        pixelData[i][j] = myFile.read();
        pixelData[i][j] += myFile.read() << 8;
        pixelData[i][j] += myFile.read() << 16;
        pixelData[i][j] += myFile.read() << 24;
      }
    }
  }
  for(int i =0; i< lightCount; i++){
    setColorPixels(i, defaultIntensity);
  }
}

void tree21(){
  myFile = SD.open("disp_16/tree2132.txt", FILE_READ);          //test to see how data is parsed out after writing
  //if (!myFile) Serial.println("Error opening file!");
  if (myFile){
    for(int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        pixelData[i][j] = myFile.read();
        pixelData[i][j] += myFile.read() << 8;
        pixelData[i][j] += myFile.read() << 16;
        pixelData[i][j] += myFile.read() << 24;
      }
    }
  }
  for(int i =0; i< lightCount; i++){
    setColorPixels(i, defaultIntensity);
  }
}

void tree22(){
  myFile = SD.open("disp_16/tree2232.txt", FILE_READ);          //test to see how data is parsed out after writing
  //if (!myFile) Serial.println("Error opening file!");
  if (myFile){
    for(int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        pixelData[i][j] = myFile.read();
        pixelData[i][j] += myFile.read() << 8;
        pixelData[i][j] += myFile.read() << 16;
        pixelData[i][j] += myFile.read() << 24;
      }
    }
  }
  for(int i =0; i< lightCount; i++){
    setColorPixels(i, defaultIntensity);
  }
}

void tree23(){
  myFile = SD.open("disp_16/tree2332.txt", FILE_READ);          //test to see how data is parsed out after writing
  //if (!myFile) Serial.println("Error opening file!");
  if (myFile){
    for(int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        pixelData[i][j] = myFile.read();
        pixelData[i][j] += myFile.read() << 8;
        pixelData[i][j] += myFile.read() << 16;
        pixelData[i][j] += myFile.read() << 24;
      }
    }
  }
  for(int i =0; i< lightCount; i++){
    setColorPixels(i, defaultIntensity);
  }
}

void tree24(){
  myFile = SD.open("disp_16/tree2432.txt", FILE_READ);          //test to see how data is parsed out after writing
  //if (!myFile) Serial.println("Error opening file!");
  if (myFile){
    for(int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        pixelData[i][j] = myFile.read();
        pixelData[i][j] += myFile.read() << 8;
        pixelData[i][j] += myFile.read() << 16;
        pixelData[i][j] += myFile.read() << 24;
      }
    }
  }
  for(int i =0; i< lightCount; i++){
    setColorPixels(i, defaultIntensity);
  }
}

void tree25(){
  myFile = SD.open("disp_16/tree2532.txt", FILE_READ);          //test to see how data is parsed out after writing
  //if (!myFile) Serial.println("Error opening file!");
  if (myFile){
    for(int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        pixelData[i][j] = myFile.read();
        pixelData[i][j] += myFile.read() << 8;
        pixelData[i][j] += myFile.read() << 16;
        pixelData[i][j] += myFile.read() << 24;
      }
    }
  }
  for(int i =0; i< lightCount; i++){
    setColorPixels(i, defaultIntensity);
  }
}

void tree26(){
  myFile = SD.open("disp_16/tree2632.txt", FILE_READ);          //test to see how data is parsed out after writing
  //if (!myFile) Serial.println("Error opening file!");
  if (myFile){
    for(int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        pixelData[i][j] = myFile.read();
        pixelData[i][j] += myFile.read() << 8;
        pixelData[i][j] += myFile.read() << 16;
        pixelData[i][j] += myFile.read() << 24;
      }
    }
  }
  for(int i =0; i< lightCount; i++){
    setColorPixels(i, defaultIntensity);
  }
}

void tree27(){
  myFile = SD.open("disp_16/tree2732.txt", FILE_READ);          //test to see how data is parsed out after writing
  //if (!myFile) Serial.println("Error opening file!");
  if (myFile){
    for(int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        pixelData[i][j] = myFile.read();
        pixelData[i][j] += myFile.read() << 8;
        pixelData[i][j] += myFile.read() << 16;
        pixelData[i][j] += myFile.read() << 24;
      }
    }
  }
  for(int i =0; i< lightCount; i++){
    setColorPixels(i, defaultIntensity);
  }
}

void tree28(){
  myFile = SD.open("disp_16/tree2832.txt", FILE_READ);          //test to see how data is parsed out after writing
  //if (!myFile) Serial.println("Error opening file!");
  if (myFile){
    for(int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        pixelData[i][j] = myFile.read();
        pixelData[i][j] += myFile.read() << 8;
        pixelData[i][j] += myFile.read() << 16;
        pixelData[i][j] += myFile.read() << 24;
      }
    }
  }
  for(int i =0; i< lightCount; i++){
    setColorPixels(i, defaultIntensity);
  }
}

void treeLights(){
  myFile = SD.open("disp_16/tree2832.txt", FILE_READ);          //test to see how data is parsed out after writing
  //if (!myFile) Serial.println("Error opening file!");
  if (myFile){
    for(int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        pixelData[i][j] = myFile.read();
        pixelData[i][j] += myFile.read() << 8;
        pixelData[i][j] += myFile.read() << 16;
        pixelData[i][j] += myFile.read() << 24;
      }
    }
  }
  for(int i =0; i< lightCount; i++){
    setColorPixels(i, defaultIntensity);
  }
  for(int x = 0; x < defaultIntensity; x++){
    setColorPinBitMask(23, x, 0x02, blue);  //setColorPinBitMask(led, intensity, string to bitMask, color of LED
    setColorPinBitMask(20 , x, 0x08, red);  //setColorPinBitMask(led, intensity, string to bitMask, color of LED
    setColorPinBitMask(26 , x, 0x08, yellow);  //setColorPinBitMask(led, intensity, string to bitMask, color of LED
    setColorPinBitMask(18 , x, 0x10, orange);  //setColorPinBitMask(led, intensity, string to bitMask, color of LED
    setColorPinBitMask(20 , x, 0x40, magenta);  //setColorPinBitMask(led, intensity, string to bitMask, color of LED
    setColorPinBitMask(30 , x, 0x40, red);  //setColorPinBitMask(led, intensity, string to bitMask, color of LED
    setColorPinBitMask(22 , x, 0x80, green);  //setColorPinBitMask(led, intensity, string to bitMask, color of LED
    setColorPinBitMask(29 , x, 0x100, green);  //setColorPinBitMask(led, intensity, string to bitMask, color of LED
    setColorPinBitMask(15 , x, 0x200, blue);  //setColorPinBitMask(led, intensity, string to bitMask, color of LED
    setColorPinBitMask(25 , x, 0x200, red);  //setColorPinBitMask(led, intensity, string to bitMask, color of LED
    setColorPinBitMask(32 , x, 0x200, blue);  //setColorPinBitMask(led, intensity, string to bitMask, color of LED
    setColorPinBitMask(20 , x, 0x2000, orange);  //setColorPinBitMask(led, intensity, string to bitMask, color of LED
    setColorPinBitMask(29 , x, 0x2000, yellow);  //setColorPinBitMask(led, intensity, string to bitMask, color of LED
    setColorPinBitMask(16 , x, 0x4000, red);  //setColorPinBitMask(led, intensity, string to bitMask, color of LED
    setColorPinBitMask(26 , x, 0x8000, orange);  //setColorPinBitMask(led, intensity, string to bitMask, color of LED
    setColorPinBitMask(22 , x, 0x10000, blue);  //setColorPinBitMask(led, intensity, string to bitMask, color of LED
    setColorPinBitMask(19 , x, 0x40000, yellow);  //setColorPinBitMask(led, intensity, string to bitMask, color of LED
    setColorPinBitMask(30 , x, 0x40000, magenta);  //setColorPinBitMask(led, intensity, string to bitMask, color of LED
    setColorPinBitMask(15 , x, 0x80000, magenta);  //setColorPinBitMask(led, intensity, string to bitMask, color of LED
    setColorPinBitMask(26 , x, 0x80000, green);  //setColorPinBitMask(led, intensity, string to bitMask, color of LED
    setColorPinBitMask(33 , x, 0x80000, blue);  //setColorPinBitMask(led, intensity, string to bitMask, color of LED
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////// SETUP //////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);
  delay(500);
//  REG_PIOC_WPMR = ~outRegC;
//  PMC->PMC_PCER0 = 0xffffffff;
  
//  PIOC->PIO_SCIFSR = outRegC;
//  PIOB->PIO_PER = PIO_PB27;
  for (int x = 3; x < 10; x++){
    pinMode(x, OUTPUT);
  }
  for (int x = 33; x < 42; x++){
    pinMode(x, OUTPUT);
  }
  for (int x = 44; x < 52; x++){
    pinMode(x, OUTPUT);
  }


  PIOC->PIO_PER = outRegC;
  PIOC->PIO_OWER = outRegC;
  PIOC->PIO_OER = outRegC;
  PIOC->PIO_IDR = outRegC;
  PIOC->PIO_PUDR = outRegC;
  //PIOC->PIO_ABSR = outRegC;
  //PIOC->PIO_OWSR = outRegC;
  Serial.print("OWSR = ");
  Serial.println(PIOC->PIO_OWSR, HEX);
  
  noInterrupts();
  
  for (int x = 3; x < 10; x++){
    //pinMode(x, OUTPUT);
    enumerate(x);
  }
  for (int x = 33; x < 42; x++){
    //pinMode(x, OUTPUT);
    enumerate(x);
  }
  for (int x = 44; x < 52; x++){
    //pinMode(x, OUTPUT);
    enumerate(x);
  }
  
  interrupts();

  
  fillColorAll(0, lightCount, defaultIntensity, white);
  delay(2000);
  
  pinMode(52, OUTPUT);
  SD.begin(52);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////// LOOP //////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
void loop() {
/*  
  fillColorAll(0, lightCount, defaultIntensity, red);
  delay(500);
  fillColorAll(0, lightCount, defaultIntensity, white);
  delay(500);
  fillColorAll(0, lightCount, defaultIntensity, green);
  delay(500);
  fillColorAll(0, lightCount, defaultIntensity, white);
  delay(500);
*/
/*
  fillColorAll(0, lightCount, defaultIntensity, red);
  delay(2000);
  fillColorAll(0, lightCount, defaultIntensity, orange);
  delay(2000);
  fillColorAll(0, lightCount, defaultIntensity, ltOrange);
  delay(2000);
  fillColorAll(0, lightCount, defaultIntensity, yellow);
  delay(2000);
*/
/*  
  noInterrupts();
  for (int x = 0; x < lightCount; x++){
    setColorPixels(x, defaultIntensity);
  }
  interrupts();
  delay(2000);
*/

  GELogo();
  delay(5000);
  
  tree1();
  delay(delayTime1);
  tree2();
  delay(delayTime1);
  tree3();
  delay(delayTime1);
  tree4();
  delay(delayTime1);
  tree5();
  delay(delayTime1);
  tree6();
  delay(delayTime1);
  tree7();
  delay(delayTime1);
  tree8();
  delay(delayTime1);
  tree9();
  delay(delayTime1);
  tree10();
  delay(delayTime1);
  tree11();
  delay(delayTime1);
  tree12();
  delay(delayTime1);
  tree13();
  delay(delayTime1);
  tree14();
  delay(delayTime1);
  tree15();
  delay(delayTime1);
  tree16();
  delay(delayTime1);
  tree17();
  delay(delayTime1);
  tree18();
  delay(delayTime1);
  tree19();
  delay(delayTime1);
  tree20();
  delay(delayTime1);
  tree21();
  delay(delayTime1);
  tree22();
  delay(delayTime1);
  tree23();
  delay(delayTime1);
  tree24();
  delay(delayTime1);
  tree25();
  delay(delayTime1);
  tree26();
  delay(delayTime1);
  tree27();
  delay(delayTime1);
  tree28();
  delay(delayTime1);

}
