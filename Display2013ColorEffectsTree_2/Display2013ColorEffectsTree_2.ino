/*Based on Christmas Light Control by  Robert Quattlebaum <darco@deepdarc.com>
           Released November 27th, 2010
           <http://www.deepdarc.com/2010/11/27/hacking-christmas-lights/>
           
           Original C code by Robert Quattlebaum developed to run on an ATTiny13
           
           This version is meant to run on an Arduino Mega 2560 Rev. 3.
           The setup is 16, 50 light GE G35 strings. Each string's data line is
           connected to one of the PORTC and PORTL pins on the two row header on the
           far right-hand side of the Mega 2560 board.  All ground wires from the strings
           are connected to the Arduino's ground (the insulation of the ground on the G35 string has a ribbed edge).
           
           PCO -> D37        PL0 -> D49
           PC1 -> D36        PL1 -> D48
           PC2 -> D35        PL2 -> D47
           PC3 -> D34        PL3 -> D46
           PC4 -> D33        PL4 -> D45
           PC5 -> D32        PL5 -> D44
           PC6 -> D31        PL6 -> D43
           PC7 -> D30        PL7 -> D42
*/


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
#define lightCount      15
#define defaultIntensity      0xf5

int delayTime = 50;                    //used in firework functions
int brightness = 0;                    //used in FADE UP TREE section
int y = 0;                             //used in RGB COLOR SWIRL and GLOW sections
int value = 0;                         //used in RGB COLOR SWIRL and GLOW sections
int value2 = 0;                        //used in RGB COLOR SWIRL and GLOW sections

const int rgb[] = {COLOR(15, 0, 0), COLOR(15, 1, 0), COLOR(15, 2, 0), COLOR(15, 3, 0), COLOR(15, 4, 0), COLOR(15, 5, 0), COLOR(15, 6, 0), COLOR(15, 7, 0), COLOR(15, 8, 0), COLOR(15, 9, 0),
COLOR(15, 10, 0), COLOR(15, 11, 0), COLOR(15, 12, 0), COLOR(15, 13, 0), COLOR(15, 14, 0), COLOR(15, 15, 0), COLOR(14, 15, 0), COLOR(13, 15, 0), COLOR(12, 15, 0), COLOR(11, 15, 0),
COLOR(10, 15, 0), COLOR(9, 15, 0), COLOR(8, 15, 0), COLOR(7, 15, 0), COLOR(6, 15, 0), COLOR(5, 15, 0), COLOR(4, 15, 0), COLOR(3, 15, 0), COLOR(2, 15, 0), COLOR(1, 15, 0), COLOR(0, 15, 0),
COLOR(0, 15, 1), COLOR(0, 15, 2), COLOR(0, 15, 3), COLOR(0, 15, 4), COLOR(0, 15, 5), COLOR(0, 15, 6), COLOR(0, 15, 7), COLOR(0, 15, 8), COLOR(0, 15, 9), COLOR(0, 15, 10), COLOR(0, 15,11),
COLOR(0, 15, 12), COLOR(0, 15, 13), COLOR(0, 15, 14), COLOR(0, 15, 15), COLOR(0, 14, 15), COLOR(0, 13, 15), COLOR(0, 12, 15), COLOR(0, 11, 15), COLOR(0, 10, 15), COLOR(0, 9, 15),
COLOR(0, 8, 15), COLOR(0, 7, 15), COLOR(0, 6, 15), COLOR(0, 5, 15), COLOR(0, 4, 15), COLOR(0, 3, 15), COLOR(0, 2, 15), COLOR(0, 1, 15), COLOR(0, 0, 15), COLOR(1, 0, 15), COLOR(2, 0, 15),
COLOR(3, 0, 15), COLOR(4, 0, 15), COLOR(5, 0, 15), COLOR(6, 0, 15), COLOR(7, 0, 15), COLOR(8, 0, 15), COLOR(9, 0, 15), COLOR(10, 0, 15), COLOR(11, 0, 15), COLOR(12, 0, 15), COLOR(13, 0, 15),
COLOR(14, 0, 15), COLOR(15, 0, 15), COLOR(15, 0, 14), COLOR(15, 0, 13), COLOR(15, 0, 12), COLOR(15, 0, 11), COLOR(15, 0, 10), COLOR(15, 0, 9), COLOR(15, 0, 8), COLOR(15, 0, 7),
COLOR(15, 0, 6), COLOR(15, 0, 5), COLOR(15, 0, 4), COLOR(15, 0, 3), COLOR(15, 0, 2), COLOR(15, 0, 1)};

const int redFade[] = {COLOR(0, 0, 0), COLOR(1, 0, 0), COLOR(2, 0, 0), COLOR(3, 0, 0), COLOR(4, 0, 0), COLOR(5, 0, 0), COLOR(6, 0, 0), COLOR(7, 0, 0), COLOR(8, 0, 0), COLOR(9, 0, 0), 
COLOR(10, 0, 0), COLOR(11, 0, 0), COLOR(12, 0, 0), COLOR(13, 0, 0), COLOR(14, 0, 0), COLOR(15, 0, 0), COLOR(14, 0, 0), COLOR(13, 0, 0), COLOR(12, 0, 0), COLOR(11, 0, 0), COLOR(10, 0, 0),
COLOR(9, 0, 0), COLOR(8, 0, 0), COLOR(7, 0, 0), COLOR(6, 0, 0), COLOR(5, 0, 0), COLOR(4, 0, 0), COLOR(3, 0, 0), COLOR(2, 0, 0), COLOR(1, 0, 0)};

const int yellowFade[] = {COLOR(0, 0, 0), COLOR(1, 1, 0), COLOR(2, 2, 0), COLOR(3, 3, 0), COLOR(4, 4, 0), COLOR(5, 5, 0), COLOR(6, 6, 0), COLOR(7, 7, 0), COLOR(8, 8, 0), COLOR(9, 9, 0),
COLOR(10, 10, 0), COLOR(11, 11, 0), COLOR(12, 12, 0), COLOR(13, 13, 0), COLOR(14, 14, 0), COLOR(15, 15, 0), COLOR(14, 14, 0), COLOR(13, 13, 0), COLOR(12, 12, 0), COLOR(11, 11, 0),
COLOR(10, 10, 0), COLOR(9, 9, 0), COLOR(8, 8, 0), COLOR(7, 7, 0), COLOR(6, 6, 0), COLOR(5, 5, 0), COLOR(4, 4, 0), COLOR(3, 3, 0), COLOR(2, 2, 0), COLOR(1, 1, 0)};

const int greenFade[] = {COLOR(0, 0, 0), COLOR(0, 1, 0), COLOR(0, 2, 0), COLOR(0, 3, 0), COLOR(0, 4, 0), COLOR(0, 5, 0), COLOR(0, 6, 0), COLOR(0, 7, 0), COLOR(0, 8, 0), COLOR(0, 9, 0),
COLOR(0, 10, 0), COLOR(0, 11, 0), COLOR(0, 12, 0), COLOR(0, 13, 0), COLOR(0, 14, 0), COLOR(0, 15, 0), COLOR(0, 14, 0), COLOR(0, 13, 0), COLOR(0, 12, 0), COLOR(0, 11, 0), COLOR(0, 10, 0),
COLOR(0, 9, 0), COLOR(0, 8, 0), COLOR(0, 7, 0), COLOR(0, 6, 0), COLOR(0, 5, 0), COLOR(0, 4, 0), COLOR(0, 3, 0), COLOR(0, 2, 0), COLOR(0, 1, 0)};

const int tealFade[] = {COLOR(0, 0, 0), COLOR(0, 1, 1), COLOR(0, 2, 2), COLOR(0, 3, 3), COLOR(0, 4, 4), COLOR(0, 5, 5), COLOR(0, 6, 6), COLOR(0, 7, 7), COLOR(0, 8, 8), COLOR(0, 9, 9),
COLOR(0, 10, 10), COLOR(0, 11, 11), COLOR(0, 12, 12), COLOR(0, 13, 13), COLOR(0, 14, 14), COLOR(0, 15, 15), COLOR(0, 14, 14), COLOR(0, 13, 13), COLOR(0, 12, 12), COLOR(0, 11, 11),
COLOR(0, 10, 10), COLOR(0, 9, 9), COLOR(0, 8, 8), COLOR(0, 7, 7), COLOR(0, 6, 6), COLOR(0, 5, 5), COLOR(0, 4, 4), COLOR(0, 3, 3), COLOR(0, 2, 2), COLOR(0, 1, 1)};

const int blueFade[] = {COLOR(0, 0, 0), COLOR(0, 0, 1), COLOR(0, 0, 2), COLOR(0, 0, 3), COLOR(0, 0, 4), COLOR(0, 0, 5), COLOR(0, 0, 6), COLOR(0, 0, 7), COLOR(0, 0, 8), COLOR(0, 0, 9),
COLOR(0, 0, 10), COLOR(0, 0, 11), COLOR(0, 0, 12), COLOR(0, 0, 13), COLOR(0, 0, 14), COLOR(0, 0, 15), COLOR(0, 0, 14), COLOR(0, 0, 13), COLOR(0, 0, 12), COLOR(0, 0, 11), COLOR(0, 0, 10),
COLOR(0, 0, 9), COLOR(0, 0, 8), COLOR(0, 0, 7), COLOR(0, 0, 6), COLOR(0, 0, 5), COLOR(0, 0, 4), COLOR(0, 0, 3), COLOR(0, 0, 2), COLOR(0, 0, 1)};

const int magentaFade[] = {COLOR(0, 0, 0), COLOR(1, 0, 1), COLOR(2, 0, 2), COLOR(3, 0, 3), COLOR(4, 0, 4), COLOR(5, 0, 5), COLOR(6, 0, 6), COLOR(7, 0, 7), COLOR(8, 0, 8), COLOR(9, 0, 9),
COLOR(10, 0, 10), COLOR(11, 0, 11), COLOR(12, 0, 12), COLOR(13, 0, 13), COLOR(14, 0, 14), COLOR(15, 0, 15), COLOR(14, 0, 14), COLOR(13, 0, 13), COLOR(12, 0, 12), COLOR(11, 0, 11),
COLOR(10, 0, 10), COLOR(9, 0, 9), COLOR(8, 0, 8), COLOR(7, 0, 7), COLOR(6, 0, 6), COLOR(5, 0, 5), COLOR(4, 0, 4), COLOR(3, 0, 3), COLOR(2, 0, 2), COLOR(1, 0, 1)};

const int whiteFade[] = {COLOR(0, 0, 0), COLOR(1, 1, 1), COLOR(2, 2, 2), COLOR(3, 3, 3), COLOR(4, 4, 4), COLOR(5, 5, 5), COLOR(6, 6, 6), COLOR(7, 7, 7), COLOR(8, 8, 8), COLOR(9, 9, 9),
COLOR(10, 10, 10), COLOR(11, 11, 11), COLOR(12, 12, 12), COLOR(13, 13, 13), COLOR(14, 14, 14), COLOR(15, 15, 15), COLOR(14, 14, 14), COLOR(13, 13, 13), COLOR(12, 12, 12), COLOR(11, 11, 11),
COLOR(10, 10, 10), COLOR(9, 9, 9), COLOR(8, 8, 8), COLOR(7, 7, 7), COLOR(6, 6, 6), COLOR(5, 5, 5), COLOR(4, 4, 4), COLOR(3, 3, 3), COLOR(2, 2, 2), COLOR(1, 1, 1)};

/*const byte brt[] = {200, 199, 198, 197, 196, 195, 194, 193, 192, 191, 190, 189, 188, 187, 186, 185, 184, 183, 182, 181, 180, 179, 178, 177, 176, 175, 174, 173, 172, 171, 170, 169, 168, 167,
166, 165, 164, 163, 162, 161, 160, 159, 158, 157, 156, 155, 154, 153, 152, 151, 150, 149, 148, 147, 146, 145, 144, 143, 142, 141, 140, 139, 138, 137, 136, 135, 134, 133, 132, 131, 130, 129,
128, 127, 126, 125, 124, 123, 122, 121, 120, 119, 118, 117, 116, 115, 114, 113, 112, 111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109,
110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147,
148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185,
186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199};*/

void beginAll(){          //begins the data frame for all outputs on PORTC and PORTL
  PORTC = B11111111;
  PORTL = B11111111;
  delayMicroseconds(6);  //Output should be ~ 10uS long 
  PORTC = B00000000;
  PORTL = B00000000;
}

/*void beginOdd(){
  PORTC = B01010101;
  PORTL = B01010101;
  delayMicroseconds(6);  //Output should be ~ 10uS long 
  PORTC = B00000000;
  PORTL = B00000000;
}*/

void beginOdd(){          //begins the data frame for every other output on PORTC and PORTL (Odd and Even are arbitrary, just for function differentiation)
  PORTC = PORTC | B01010101;
  PORTL = PORTL | B01010101;
  delayMicroseconds(6);  //Output should be ~ 10uS long 
  PORTC = PORTC & B10101010;
  PORTL = PORTL & B10101010;
}

/*void beginEven(){
  PORTC = B10101010;
  PORTL = B10101010;
  delayMicroseconds(6);  //Output should be ~ 10uS long 
  PORTC = B00000000;
  PORTL = B00000000;
}*/

void beginEven(){         //begins the data frame for every other output on PORTC and PORTL (Odd and Even are arbitrary, just for function differentiation)
  PORTC = PORTC | B10101010;
  PORTL = PORTL | B10101010;
  delayMicroseconds(6);  //Output should be ~ 10uS long 
  PORTC = PORTC & B01010101;
  PORTL = PORTL & B01010101;
}

void oneAll(){            //defines a one for any bit in the data frame for all outputs
  PORTC = B00000000;
  PORTL = B00000000; 
  delayMicroseconds(12); //Output should be ~ 20uS long 
  PORTC = B11111111;
  PORTL = B11111111;
  delayMicroseconds(6);  //Output should be ~ 10uS long 
  PORTC = B00000000;
  PORTL = B00000000;
}

/*void oneOdd(){
  PORTC = B00000000;
  PORTL = B00000000; 
  delayMicroseconds(12); //Output should be ~ 20uS long 
  PORTC = B01010101;
  PORTL = B01010101;
  delayMicroseconds(6);  //Output should be ~ 10uS long 
  PORTC = B00000000;
  PORTL = B00000000;
}*/

void oneOdd(){             //defines a one for any bit in the data frame for every other output on PORTC and PORTL (Odd and Even are arbitrary, just for function differentiation)
  PORTC = PORTC & B10101010;
  PORTL = PORTL & B10101010; 
  delayMicroseconds(12); //Output should be ~ 20uS long 
  PORTC = PORTC | B01010101;
  PORTL = PORTL | B01010101;
  delayMicroseconds(6);  //Output should be ~ 10uS long 
  PORTC = PORTC & B10101010;
  PORTL = PORTL & B10101010;
}

/*void oneEven(){
  PORTC = B00000000;
  PORTL = B00000000; 
  delayMicroseconds(12); //Output should be ~ 20uS long 
  PORTC = B10101010;
  PORTL = B10101010;
  delayMicroseconds(6);  //Output should be ~ 10uS long 
  PORTC = B00000000;
  PORTL = B00000000;
}*/

void oneEven(){           //defines a one for any bit in the data frame for every other output on PORTC and PORTL (Odd and Even are arbitrary, just for function differentiation)
  PORTC = PORTC & B01010101;
  PORTL = PORTL & B01010101; 
  delayMicroseconds(12); //Output should be ~ 20uS long 
  PORTC = PORTC | B10101010;
  PORTL = PORTL | B10101010;
  delayMicroseconds(6);  //Output should be ~ 10uS long 
  PORTC = PORTC & B01010101;
  PORTL = PORTL & B01010101;
}

void zeroAll(){           //defines a zero for any bit in the data frame for all outputs
  PORTC = B00000000;
  PORTL = B00000000;
  delayMicroseconds(3);  //Output should be ~ 10uS long
  PORTC = B11111111;
  PORTL = B11111111;
  delayMicroseconds(16); //Output should be ~ 20uS long  
  PORTC = B00000000;
  PORTL = B00000000;
}

/*void zeroOdd(){
  PORTC = B00000000;
  PORTL = B00000000;
  delayMicroseconds(3);  //Output should be ~ 10uS long
  PORTC = B01010101;
  PORTL = B01010101;
  delayMicroseconds(16); //Output should be ~ 20uS long  
  PORTC = B00000000;
  PORTL = B00000000;
}*/

void zeroOdd(){           //defines a zero for any bit in the data frame for every other output on PORTC and PORTL (Odd and Even are arbitrary, just for function differentiation)
  PORTC = PORTC & B10101010;
  PORTL = PORTL & B10101010;
  delayMicroseconds(3);  //Output should be ~ 10uS long
  PORTC = PORTC | B01010101;
  PORTL = PORTL | B01010101;
  delayMicroseconds(16); //Output should be ~ 20uS long  
  PORTC = PORTC & B10101010;
  PORTL = PORTL & B10101010;
}

/*void zeroEven(){
  PORTC = B00000000;
  PORTL = B00000000;
  delayMicroseconds(3);  //Output should be ~ 10uS long
  PORTC = B10101010;
  PORTL = B10101010;
  delayMicroseconds(16); //Output should be ~ 20uS long  
  PORTC = B00000000;
  PORTL = B00000000;
}*/

void zeroEven(){          //defines a zero for any bit in the data frame for every other output on PORTC and PORTL (Odd and Even are arbitrary, just for function differentiation)
  PORTC = PORTC & B01010101;
  PORTL = PORTL & B01010101;
  delayMicroseconds(3);  //Output should be ~ 10uS long
  PORTC = PORTC | B10101010;
  PORTL = PORTL | B10101010;
  delayMicroseconds(16); //Output should be ~ 20uS long  
  PORTC = PORTC & B01010101;
  PORTL = PORTL & B01010101;
}

void endAll(){            //sets the data line LOW between data frames
  PORTC = B00000000;
  PORTL = B00000000;
  delayMicroseconds(30);
}

/*void endOdd(){
  PORTC = B00000000;
  PORTL = B00000000;
  delayMicroseconds(30);
}*/


void endOdd(){             //sets the data line LOW between data frames for every other output
  PORTC = PORTC & B10101010;
  PORTL = PORTL & B10101010;
  delayMicroseconds(30);
}

/*void endEven(){
  PORTC = B00000000;
  PORTL = B00000000;
  delayMicroseconds(30);
}*/

void endEven(){            //sets the data line LOW between data frames for every other output
  PORTC = PORTC & B01010101;
  PORTL = PORTL & B01010101;
  delayMicroseconds(30);
}

void enumerateAll(){       //addresses each bulb individually for all outputs
  noInterrupts();
  fillColorAll(0, lightCount, 204, black);
  interrupts();
}

void setColorAll(uint8_t led, uint8_t intensity, uint16_t color){                   //sets the color and intensity for a specific bulb on all outputs of PORTC and PORTL
  noInterrupts();
  uint8_t i;
  beginAll();
  for(i=6;i;i--,(led<<=1))
    if(led&(1<<5)) oneAll();
    else zeroAll();
  for(i=8;i;i--,(intensity<<=1))
    if(intensity&(1<<7)) oneAll();
    else zeroAll();
  for(i=12;i;i--,(color<<=1))
    if(color&(1<<11)) oneAll();
    else zeroAll();
  endAll();
  interrupts();
}

void setColorOdd(uint8_t led, uint8_t intensity, uint16_t color){                   //sets the color and intensity for a specific bulb on every other output of PORTC and PORTL
  noInterrupts();
  uint8_t i;
  beginOdd();
  for(i=6;i;i--,(led<<=1))
    if(led&(1<<5)) oneOdd();
    else zeroOdd();
  for(i=8;i;i--,(intensity<<=1))
    if(intensity&(1<<7)) oneOdd();
    else zeroOdd();
  for(i=12;i;i--,(color<<=1))
    if(color&(1<<11)) oneOdd();
    else zeroOdd();
  endOdd();
  interrupts();
}

void setColorEven(uint8_t led, uint8_t intensity, uint16_t color){                  //sets the color and intensity of a specific bulb on every other output of PORTC and PORTL
  noInterrupts();
  uint8_t i;
  beginEven();
  for(i=6;i;i--,(led<<=1))
    if(led&(1<<5)) oneEven();
    else zeroEven();
  for(i=8;i;i--,(intensity<<=1))
    if(intensity&(1<<7)) oneEven();
    else zeroEven();
  for(i=12;i;i--,(color<<=1))
    if(color&(1<<11)) oneEven();
    else zeroEven();
  endEven();
  interrupts();
}

void fillColorAll(uint8_t begin, uint8_t count, uint8_t intensity, uint16_t color){ //fills the string with a color and intensity starting from a specific bulb to the end of the string
  noInterrupts();                                                                   //for all outputs on PORTC and PORTL
  while(count--){
    setColorAll(begin++, intensity, color);
  }
  interrupts();
}

void fillColorOdd(uint8_t begin, uint8_t count, uint8_t intensity, uint16_t color){ //fills the string with a color and intensity starting from a specific bulb to the end of the string
  noInterrupts();                                                                   //for every other output on PORTC and PORTL
  while(count--){
    setColorOdd(begin++, intensity, color);
  }
  interrupts();
}

void fillColorEven(uint8_t begin, uint8_t count, uint8_t intensity, uint16_t color){ //fills the string with a color and intensity starting from a specific bulb to the end of the string
  noInterrupts();                                                                    //for every other output on PORTC and PORTL
  while(count--){
    setColorEven(begin++, intensity, color);
  }
  interrupts();
}

void rotateCW(int color1, int color2, int color3, int color4, int time, byte num){  //rotate 4 colors around the tree CW
  for(byte a = 0; a < num; a++){
    for(byte x = 0; x < 25; x++){
//      noInterrupts();                                                               //added "noInterrupts" and "interrupts()" to individual functions that need them, so shouldn't need
      setColorOdd(x, defaultIntensity, color1);                                     //to reiterate "noInterrupts()" but just in case...
      setColorOdd(x + 25, defaultIntensity, color2);
      setColorEven(x, defaultIntensity, color3);
      setColorEven(x + 25, defaultIntensity, color4);
    }
//    interrupts();
    delay(time);
    for(byte x = 0; x < 25; x++){
//      noInterrupts();
      setColorOdd(x, defaultIntensity, color2);
      setColorOdd(x + 25, defaultIntensity, color3);
      setColorEven(x, defaultIntensity, color4);
      setColorEven(x + 25, defaultIntensity, color1);
    }
//    interrupts();
    delay(time);
    for(byte x = 0; x < 25; x++){
//      noInterrupts();
      setColorOdd(x, defaultIntensity, color3);
      setColorOdd(x + 25, defaultIntensity, color4);
      setColorEven(x, defaultIntensity, color1);
      setColorEven(x + 25, defaultIntensity, color2);
    }
//    interrupts();
    delay(time);
    for(byte x = 0; x < 25; x++){
//      noInterrupts();
      setColorOdd(x, defaultIntensity, color4);
      setColorOdd(x + 25, defaultIntensity, color1);
      setColorEven(x, defaultIntensity, color2);
      setColorEven(x + 25, defaultIntensity, color3);
    }
//    interrupts();
    delay(time);
    }
}

void rotateCCW(int color1, int color2, int color3, int color4, int time, byte num){ //rotate 4 colors around the tree CCW
  for(byte a = 0; a < num; a++){
    for(byte x = 0; x < 25; x++){
//      noInterrupts();
      setColorOdd(x, defaultIntensity, color1);
      setColorOdd(x + 25, defaultIntensity, color2);
      setColorEven(x, defaultIntensity, color3);
      setColorEven(x + 25, defaultIntensity, color4);
    }
//    interrupts();
    delay(time);
    for(byte x = 0; x < 25; x++){
//      noInterrupts();
      setColorOdd(x, defaultIntensity, color4);
      setColorOdd(x + 25, defaultIntensity, color1);
      setColorEven(x, defaultIntensity, color2);
      setColorEven(x + 25, defaultIntensity, color3);
    }
//    interrupts();
    delay(time);
    for(byte x = 0; x < 25; x++){
//      noInterrupts();
      setColorOdd(x, defaultIntensity, color3);
      setColorOdd(x + 25, defaultIntensity, color4);
      setColorEven(x, defaultIntensity, color1);
      setColorEven(x + 25, defaultIntensity, color2);
    }
//    interrupts();
    delay(time);
    for(byte x = 0; x < 25; x++){
//      noInterrupts();
      setColorOdd(x, defaultIntensity, color2);
      setColorOdd(x + 25, defaultIntensity, color3);
      setColorEven(x, defaultIntensity, color4);
      setColorEven(x + 25, defaultIntensity, color1);
    }
//    interrupts();
    delay(time);
    }
}

void fireworkColor(int color){                                                      //firework of any COLOR(r, g, b)
  delayTime = 0;
  for(int x = 0; x < 28; x++){
//    noInterrupts();
    if(x < 25){
      setColorAll(x, defaultIntensity, COLOR(15, 9, 2));
      setColorAll(49-x, defaultIntensity, COLOR(15, 9, 2));
    }
    if(x < 26){
      setColorAll(x-1, defaultIntensity, COLOR(15, 9, 2));
      setColorAll(49-x+1, defaultIntensity, COLOR(15, 9, 2));
    }
    if(x < 27){
      setColorAll(x-2, defaultIntensity, COLOR(15, 9, 2));
      setColorAll(49-x+2, defaultIntensity, COLOR(15, 9, 2));
    }
    setColorAll(x-3, defaultIntensity, black);
    setColorAll(49-x+3, defaultIntensity, black);
//    interrupts();
    delay(delayTime);
    if(x < 11){
      delayTime = 0;
    }
    else if(x >= 15 && x < 22){
      delayTime +=10;
    }
    else if(x >= 22 && x < 28){
      delayTime += 25;
    }
  }
  delay(500);
  for(int x = 0; x < 3; x++){
//    noInterrupts();
    setColorOdd(random(22, 25), random(100, 255), color);
    setColorOdd(random(22, 25), random(100, 255), color);
    setColorOdd(random(25, 28), random(100, 255), color);
    setColorOdd(random(25, 28), random(100, 255), color);
    setColorEven(random(22, 25), random(100, 255), color);
    setColorEven(random(22, 25), random(100, 255), color);
    setColorEven(random(25, 28), random(100, 255), color);
    setColorEven(random(25, 28), random(100, 255), color);
//    interrupts();
    delay(random(50));
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, black);
//    interrupts();
  }
  for(int x = 0; x < 3; x++){
//    noInterrupts();
    setColorOdd(random(21, 24), random(100, 255), color);
    setColorOdd(random(21, 24), random(100, 255), color);
    setColorOdd(random(25, 29), random(100, 255), color);
    setColorOdd(random(25, 29), random(100, 255), color);
    setColorEven(random(21, 24), random(100, 255), color);
    setColorEven(random(21, 24), random(100, 255), color);
    setColorEven(random(25, 29), random(100, 255), color);
    setColorEven(random(25, 29), random(100, 255), color);
//    interrupts();
    delay(random(50));
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, black);
//    interrupts();
  }
  for(int x = 0; x < 3; x++){
//    noInterrupts();
    setColorOdd(random(20, 24), random(100, 255), color);
    setColorOdd(random(20, 24), random(100, 255), color);
    setColorOdd(random(20, 24), random(100, 255), color);
    setColorOdd(random(25, 30), random(100, 255), color);
    setColorOdd(random(25, 30), random(100, 255), color);
    setColorOdd(random(25, 30), random(100, 255), color);
    setColorEven(random(20, 24), random(100, 255), color);
    setColorEven(random(20, 24), random(100, 255), color);
    setColorEven(random(20, 24), random(100, 255), color);
    setColorEven(random(25, 30), random(100, 255), color);
    setColorEven(random(25, 30), random(100, 255), color);
    setColorEven(random(25, 30), random(100, 255), color);
//    interrupts();
    delay(random(50));
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, black);
//    interrupts();
  }
  for(int x = 0; x < 3; x++){
//    noInterrupts();
    setColorOdd(random(19, 24), random(100, 255), color);
    setColorOdd(random(19, 24), random(100, 255), color);
    setColorOdd(random(19, 24), random(100, 255), color);
    setColorOdd(random(25, 32), random(100, 255), color);
    setColorOdd(random(25, 32), random(100, 255), color);
    setColorOdd(random(25, 32), random(100, 255), color);
    setColorEven(random(19, 24), random(100, 255), color);
    setColorEven(random(19, 24), random(100, 255), color);
    setColorEven(random(19, 24), random(100, 255), color);
    setColorEven(random(25, 32), random(100, 255), color);
    setColorEven(random(25, 32), random(100, 255), color);
    setColorEven(random(25, 32), random(100, 255), color);
//    interrupts();
    delay(random(60));
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, black);
//    interrupts();
  }
  for(int x = 0; x < 3; x++){
//    noInterrupts();
    setColorOdd(random(18, 24), random(100, 255), color);
    setColorOdd(random(18, 24), random(100, 255), color);
    setColorOdd(random(18, 24), random(100, 255), color);
    setColorOdd(random(18, 24), random(100, 255), color);
    setColorOdd(random(25, 34), random(100, 255), color);
    setColorOdd(random(25, 34), random(100, 255), color);
    setColorOdd(random(25, 34), random(100, 255), color);
    setColorOdd(random(25, 34), random(100, 255), color);
    setColorEven(random(18, 24), random(100, 255), color);
    setColorEven(random(18, 24), random(100, 255), color);
    setColorEven(random(18, 24), random(100, 255), color);
    setColorEven(random(18, 24), random(100, 255), color);
    setColorEven(random(25, 34), random(100, 255), color);
    setColorEven(random(25, 34), random(100, 255), color);
    setColorEven(random(25, 34), random(100, 255), color);
    setColorEven(random(25, 34), random(100, 255), color);
//    interrupts();
    delay(random(60));
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, black);
//    interrupts();
  }
  for(int x = 0; x < 3; x++){
//    noInterrupts();
    setColorOdd(random(16, 24), random(100, 255), color);
    setColorOdd(random(16, 24), random(100, 255), color);
    setColorOdd(random(16, 24), random(100, 255), color);
    setColorOdd(random(16, 24), random(100, 255), color);
    setColorOdd(random(25, 36), random(100, 255), color);
    setColorOdd(random(25, 36), random(100, 255), color);
    setColorOdd(random(25, 36), random(100, 255), color);
    setColorOdd(random(25, 36), random(100, 255), color);
    setColorEven(random(16, 24), random(100, 255), color);
    setColorEven(random(16, 24), random(100, 255), color);
    setColorEven(random(16, 24), random(100, 255), color);
    setColorEven(random(16, 24), random(100, 255), color);
    setColorEven(random(25, 36), random(100, 255), color);
    setColorEven(random(25, 36), random(100, 255), color);
    setColorEven(random(25, 36), random(100, 255), color);
    setColorEven(random(25, 36), random(100, 255), color);
//    interrupts();
    delay(random(70));
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, black);
//    interrupts();
  }
  for(int x = 0; x < 4; x++){
//    noInterrupts();
    setColorOdd(random(14, 24), random(100, 255), color);
    setColorOdd(random(14, 24), random(100, 255), color);
    setColorOdd(random(14, 24), random(100, 255), color);
    setColorOdd(random(14, 24), random(100, 255), color);
    setColorOdd(random(14, 24), random(100, 255), color);
    setColorOdd(random(25, 38), random(100, 255), color);
    setColorOdd(random(25, 38), random(100, 255), color);
    setColorOdd(random(25, 38), random(100, 255), color);
    setColorOdd(random(25, 38), random(100, 255), color);
    setColorOdd(random(25, 38), random(100, 255), color);
    setColorEven(random(14, 24), random(100, 255), color);
    setColorEven(random(14, 24), random(100, 255), color);
    setColorEven(random(14, 24), random(100, 255), color);
    setColorEven(random(14, 24), random(100, 255), color);
    setColorEven(random(14, 24), random(100, 255), color);
    setColorEven(random(25, 38), random(100, 255), color);
    setColorEven(random(25, 38), random(100, 255), color);
    setColorEven(random(25, 38), random(100, 255), color);
    setColorEven(random(25, 38), random(100, 255), color);
    setColorEven(random(25, 38), random(100, 255), color);
//    interrupts();
    delay(random(70));
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, black);
//    interrupts();
  }
  for(int x = 0; x < 4; x++){
//    noInterrupts();
    setColorOdd(random(12, 24), random(100, 255), color);
    setColorOdd(random(12, 24), random(100, 255), color);
    setColorOdd(random(12, 24), random(100, 255), color);
    setColorOdd(random(12, 24), random(100, 255), color);
    setColorOdd(random(12, 24), random(100, 255), color);
    setColorOdd(random(25, 40), random(100, 255), color);
    setColorOdd(random(25, 40), random(100, 255), color);
    setColorOdd(random(25, 40), random(100, 255), color);
    setColorOdd(random(25, 40), random(100, 255), color);
    setColorOdd(random(25, 40), random(100, 255), color);
    setColorEven(random(12, 24), random(100, 255), color);
    setColorEven(random(12, 24), random(100, 255), color);
    setColorEven(random(12, 24), random(100, 255), color);
    setColorEven(random(12, 24), random(100, 255), color);
    setColorEven(random(12, 24), random(100, 255), color);
    setColorEven(random(25, 40), random(100, 255), color);
    setColorEven(random(25, 40), random(100, 255), color);
    setColorEven(random(25, 40), random(100, 255), color);
    setColorEven(random(25, 40), random(100, 255), color);
    setColorEven(random(25, 40), random(100, 255), color);
//    interrupts();
    delay(random(80));
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, black);
//    interrupts();
  }
  for(int x = 0; x < 4; x++){
//    noInterrupts();
    setColorOdd(random(10, 24), random(100, 255), color);
    setColorOdd(random(10, 24), random(100, 255), color);
    setColorOdd(random(10, 24), random(100, 255), color);
    setColorOdd(random(10, 24), random(100, 255), color);
    setColorOdd(random(10, 24), random(100, 255), color);
    setColorOdd(random(10, 24), random(100, 255), color);
    setColorOdd(random(25, 42), random(100, 255), color);
    setColorOdd(random(25, 42), random(100, 255), color);
    setColorOdd(random(25, 42), random(100, 255), color);
    setColorOdd(random(25, 42), random(100, 255), color);
    setColorOdd(random(25, 42), random(100, 255), color);
    setColorOdd(random(25, 42), random(100, 255), color);
    setColorEven(random(10, 24), random(100, 255), color);
    setColorEven(random(10, 24), random(100, 255), color);
    setColorEven(random(10, 24), random(100, 255), color);
    setColorEven(random(10, 24), random(100, 255), color);
    setColorEven(random(10, 24), random(100, 255), color);
    setColorEven(random(10, 24), random(100, 255), color);
    setColorEven(random(25, 42), random(100, 255), color);
    setColorEven(random(25, 42), random(100, 255), color);
    setColorEven(random(25, 42), random(100, 255), color);
    setColorEven(random(25, 42), random(100, 255), color);
    setColorEven(random(25, 42), random(100, 255), color);
    setColorEven(random(25, 42), random(100, 255), color);
//    interrupts();
    delay(random(80));
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, black);
//    interrupts();
  }
  for(int x = 0; x < 5; x++){
//    noInterrupts();
    setColorOdd(random(8, 24), random(100, 255), color);
    setColorOdd(random(8, 24), random(100, 255), color);
    setColorOdd(random(8, 24), random(100, 255), color);
    setColorOdd(random(8, 24), random(100, 255), color);
    setColorOdd(random(8, 24), random(100, 255), color);
    setColorOdd(random(8, 24), random(100, 255), color);
    setColorOdd(random(8, 24), random(100, 255), color);
    setColorOdd(random(25, 44), random(100, 255), color);
    setColorOdd(random(25, 44), random(100, 255), color);
    setColorOdd(random(25, 44), random(100, 255), color);
    setColorOdd(random(25, 44), random(100, 255), color);
    setColorOdd(random(25, 44), random(100, 255), color);
    setColorOdd(random(25, 44), random(100, 255), color);
    setColorOdd(random(25, 44), random(100, 255), color);
    setColorEven(random(8, 24), random(100, 255), color);
    setColorEven(random(8, 24), random(100, 255), color);
    setColorEven(random(8, 24), random(100, 255), color);
    setColorEven(random(8, 24), random(100, 255), color);
    setColorEven(random(8, 24), random(100, 255), color);
    setColorEven(random(8, 24), random(100, 255), color);
    setColorEven(random(8, 24), random(100, 255), color);
    setColorEven(random(25, 44), random(100, 255), color);
    setColorEven(random(25, 44), random(100, 255), color);
    setColorEven(random(25, 44), random(100, 255), color);
    setColorEven(random(25, 44), random(100, 255), color);
    setColorEven(random(25, 44), random(100, 255), color);
    setColorEven(random(25, 44), random(100, 255), color);
    setColorEven(random(25, 44), random(100, 255), color);
//    interrupts();
    delay(random(100));
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, black);
//    interrupts();
  }
  for(int x = 0; x < 5; x++){
//    noInterrupts();
    setColorOdd(random(6, 24), random(100, 255), color);
    setColorOdd(random(6, 24), random(100, 255), color);
    setColorOdd(random(6, 24), random(100, 255), color);
    setColorOdd(random(6, 24), random(100, 255), color);
    setColorOdd(random(6, 24), random(100, 255), color);
    setColorOdd(random(6, 24), random(100, 255), color);
    setColorOdd(random(6, 24), random(100, 255), color);
    setColorOdd(random(6, 24), random(100, 255), color);
    setColorOdd(random(25, 46), random(100, 255), color);
    setColorOdd(random(25, 46), random(100, 255), color);
    setColorOdd(random(25, 46), random(100, 255), color);
    setColorOdd(random(25, 46), random(100, 255), color);
    setColorOdd(random(25, 46), random(100, 255), color);
    setColorOdd(random(25, 46), random(100, 255), color);
    setColorOdd(random(25, 46), random(100, 255), color);
    setColorOdd(random(25, 46), random(100, 255), color);
    setColorEven(random(6, 24), random(100, 255), color);
    setColorEven(random(6, 24), random(100, 255), color);
    setColorEven(random(6, 24), random(100, 255), color);
    setColorEven(random(6, 24), random(100, 255), color);
    setColorEven(random(6, 24), random(100, 255), color);
    setColorEven(random(6, 24), random(100, 255), color);
    setColorEven(random(6, 24), random(100, 255), color);
    setColorEven(random(6, 24), random(100, 255), color);
    setColorEven(random(25, 46), random(100, 255), color);
    setColorEven(random(25, 46), random(100, 255), color);
    setColorEven(random(25, 46), random(100, 255), color);
    setColorEven(random(25, 46), random(100, 255), color);
    setColorEven(random(25, 46), random(100, 255), color);
    setColorEven(random(25, 46), random(100, 255), color);
    setColorEven(random(25, 46), random(100, 255), color);
    setColorEven(random(25, 46), random(100, 255), color);
//    interrupts();
    delay(random(100));
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, black);
//    interrupts();
  }
  for(int x = 0; x < 6; x++){
//    noInterrupts();
    setColorOdd(random(3, 24), random(100, 255), color);
    setColorOdd(random(3, 24), random(100, 255), color);
    setColorOdd(random(3, 24), random(100, 255), color);
    setColorOdd(random(3, 24), random(100, 255), color);
    setColorOdd(random(3, 24), random(100, 255), color);
    setColorOdd(random(3, 24), random(100, 255), color);
    setColorOdd(random(3, 24), random(100, 255), color);
    setColorOdd(random(3, 24), random(100, 255), color);
    setColorOdd(random(25, 49), random(100, 255), color);
    setColorOdd(random(25, 49), random(100, 255), color);
    setColorOdd(random(25, 49), random(100, 255), color);
    setColorOdd(random(25, 49), random(100, 255), color);
    setColorOdd(random(25, 49), random(100, 255), color);
    setColorOdd(random(25, 49), random(100, 255), color);
    setColorOdd(random(25, 49), random(100, 255), color);
    setColorOdd(random(25, 49), random(100, 255), color);
    setColorEven(random(3, 24), random(100, 255), color);
    setColorEven(random(3, 24), random(100, 255), color);
    setColorEven(random(3, 24), random(100, 255), color);
    setColorEven(random(3, 24), random(100, 255), color);
    setColorEven(random(3, 24), random(100, 255), color);
    setColorEven(random(3, 24), random(100, 255), color);
    setColorEven(random(3, 24), random(100, 255), color);
    setColorEven(random(3, 24), random(100, 255), color);
    setColorEven(random(25, 49), random(100, 255), color);
    setColorEven(random(25, 49), random(100, 255), color);
    setColorEven(random(25, 49), random(100, 255), color);
    setColorEven(random(25, 49), random(100, 255), color);
    setColorEven(random(25, 49), random(100, 255), color);
    setColorEven(random(25, 49), random(100, 255), color);
    setColorEven(random(25, 49), random(100, 255), color);
    setColorEven(random(25, 49), random(100, 255), color);
//    interrupts();
    delay(random(150));
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, black);
//    interrupts();
  }
}

void fireworkColorSpan(int start, int span){                                        //int start is the beginning of the range of values in the rgb[] array you want to use
  delayTime = 0;                                                                    //i.e. if start == 0 then the first color used == rgb[0]
  for(int x = 0; x < 28; x++){                                                      //int span is the amount of values to be used from the rgb[] array
//    noInterrupts();
    if(x < 25){
      setColorAll(x, defaultIntensity, COLOR(15, 9, 2));
      setColorAll(49-x, defaultIntensity, COLOR(15, 9, 2));
    }
    if(x < 26){
      setColorAll(x-1, defaultIntensity, COLOR(15, 9, 2));
      setColorAll(49-x+1, defaultIntensity, COLOR(15, 9, 2));
    }
    if(x < 27){
      setColorAll(x-2, defaultIntensity, COLOR(15, 9, 2));
      setColorAll(49-x+2, defaultIntensity, COLOR(15, 9, 2));
    }
    setColorAll(x-3, defaultIntensity, black);
    setColorAll(49-x+3, defaultIntensity, black);
//    interrupts();
    delay(delayTime);
    if(x < 11){
      delayTime = 0;
    }
    else if(x >= 15 && x < 22){
      delayTime +=10;
    }
    else if(x >= 22 && x < 28){
      delayTime += 25;
    }
  }
  delay(500);
  for(int x = 0; x < 3; x++){
//    noInterrupts();
    setColorOdd(random(22, 25), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(22, 25), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 28), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 28), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(22, 25), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(22, 25), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 28), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 28), random(100, 255), random(rgb[start], rgb[start + span]));
//    interrupts();
    delay(random(50));
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, black);
//    interrupts();
  }
  for(int x = 0; x < 3; x++){
//    noInterrupts();
    setColorOdd(random(21, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(21, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 29), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 29), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(21, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(21, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 29), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 29), random(100, 255), random(rgb[start], rgb[start + span]));
//    interrupts();
    delay(random(50));
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, black);
//    interrupts();
  }
  for(int x = 0; x < 3; x++){
//    noInterrupts();
    setColorOdd(random(20, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(20, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(20, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 30), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 30), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 30), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(20, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(20, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(20, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 30), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 30), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 30), random(100, 255), random(rgb[start], rgb[start + span]));
//    interrupts();
    delay(random(50));
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, black);
//    interrupts();
  }
  for(int x = 0; x < 3; x++){
//    noInterrupts();
    setColorOdd(random(19, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(19, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(19, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 32), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 32), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 32), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(19, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(19, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(19, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 32), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 32), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 32), random(100, 255), random(rgb[start], rgb[start + span]));
//    interrupts();
    delay(random(60));
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, black);
//    interrupts();
  }
  for(int x = 0; x < 3; x++){
//    noInterrupts();
    setColorOdd(random(18, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(18, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(18, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(18, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 34), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 34), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 34), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 34), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(18, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(18, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(18, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(18, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 34), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 34), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 34), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 34), random(100, 255), random(rgb[start], rgb[start + span]));
//    interrupts();
    delay(random(60));
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, black);
//    interrupts();
  }
  for(int x = 0; x < 3; x++){
//    noInterrupts();
    setColorOdd(random(16, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(16, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(16, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(16, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 36), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 36), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 36), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 36), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(16, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(16, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(16, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(16, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 36), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 36), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 36), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 36), random(100, 255), random(rgb[start], rgb[start + span]));
//    interrupts();
    delay(random(70));
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, black);
//    interrupts();
  }
  for(int x = 0; x < 4; x++){
//    noInterrupts();
    setColorOdd(random(14, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(14, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(14, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(14, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(14, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 38), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 38), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 38), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 38), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 38), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(14, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(14, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(14, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(14, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(14, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 38), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 38), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 38), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 38), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 38), random(100, 255), random(rgb[start], rgb[start + span]));
//    interrupts();
    delay(random(70));
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, black);
//    interrupts();
  }
  for(int x = 0; x < 4; x++){
//    noInterrupts();
    setColorOdd(random(12, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(12, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(12, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(12, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(12, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 40), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 40), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 40), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 40), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 40), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(12, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(12, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(12, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(12, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(12, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 40), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 40), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 40), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 40), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 40), random(100, 255), random(rgb[start], rgb[start + span]));
//    interrupts();
    delay(random(80));
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, black);
//    interrupts();
  }
  for(int x = 0; x < 4; x++){
//    noInterrupts();
    setColorOdd(random(10, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(10, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(10, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(10, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(10, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(10, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 42), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 42), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 42), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 42), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 42), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 42), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(10, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(10, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(10, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(10, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(10, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(10, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 42), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 42), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 42), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 42), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 42), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 42), random(100, 255), random(rgb[start], rgb[start + span]));
//    interrupts();
    delay(random(80));
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, black);
//    interrupts();
  }
  for(int x = 0; x < 5; x++){
//    noInterrupts();
    setColorOdd(random(8, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(8, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(8, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(8, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(8, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(8, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(8, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 44), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 44), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 44), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 44), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 44), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 44), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 44), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(8, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(8, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(8, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(8, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(8, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(8, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(8, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 44), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 44), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 44), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 44), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 44), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 44), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 44), random(100, 255), random(rgb[start], rgb[start + span]));
//    interrupts();
    delay(random(100));
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, black);
//    interrupts();
  }
  for(int x = 0; x < 5; x++){
//    noInterrupts();
    setColorOdd(random(6, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(6, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(6, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(6, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(6, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(6, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(6, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(6, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 46), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 46), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 46), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 46), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 46), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 46), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 46), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 46), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(6, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(6, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(6, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(6, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(6, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(6, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(6, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(6, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 46), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 46), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 46), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 46), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 46), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 46), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 46), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 46), random(100, 255), random(rgb[start], rgb[start + span]));
//    interrupts();
    delay(random(100));
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, black);
//    interrupts();
  }
  for(int x = 0; x < 6; x++){
//    noInterrupts();
    setColorOdd(random(3, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(3, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(3, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(3, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(3, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(3, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(3, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(3, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 49), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 49), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 49), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 49), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 49), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 49), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 49), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorOdd(random(25, 49), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(3, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(3, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(3, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(3, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(3, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(3, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(3, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(3, 24), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 49), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 49), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 49), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 49), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 49), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 49), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 49), random(100, 255), random(rgb[start], rgb[start + span]));
    setColorEven(random(25, 49), random(100, 255), random(rgb[start], rgb[start + span]));
//    interrupts();
    delay(random(150));
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, black);
//    interrupts();
  }
}

void fireworkRgb(){                                                                 //randomly generated multi-color firework
  delayTime = 0;
  for(int x = 0; x < 28; x++){
//    noInterrupts();
    if(x < 25){
      setColorAll(x, defaultIntensity, COLOR(15, 9, 2));
      setColorAll(49-x, defaultIntensity, COLOR(15, 9, 2));
    }
    if(x < 26){
      setColorAll(x-1, defaultIntensity, COLOR(15, 9, 2));
      setColorAll(49-x+1, defaultIntensity, COLOR(15, 9, 2));
    }
    if(x < 27){
      setColorAll(x-2, defaultIntensity, COLOR(15, 9, 2));
      setColorAll(49-x+2, defaultIntensity, COLOR(15, 9, 2));
    }
    setColorAll(x-3, defaultIntensity, black);
    setColorAll(49-x+3, defaultIntensity, black);
//    interrupts();
    delay(delayTime);
    if(x < 11){
      delayTime = 0;
    }
    else if(x >= 15 && x < 22){
      delayTime +=10;
    }
    else if(x >= 22 && x < 28){
      delayTime += 25;
    }
  }
  delay(500);
  for(int x = 0; x < 3; x++){
//    noInterrupts();
    setColorOdd(random(22, 25), random(100, 255), rgb[random(90)]);
    setColorOdd(random(22, 25), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 28), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 28), random(100, 255), rgb[random(90)]);
    setColorEven(random(22, 25), random(100, 255), rgb[random(90)]);
    setColorEven(random(22, 25), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 28), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 28), random(100, 255), rgb[random(90)]);
//    interrupts();
    delay(random(50));
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, black);
//    interrupts();
  }
  for(int x = 0; x < 3; x++){
//    noInterrupts();
    setColorOdd(random(21, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(21, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 29), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 29), random(100, 255), rgb[random(90)]);
    setColorEven(random(21, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(21, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 29), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 29), random(100, 255), rgb[random(90)]);
//    interrupts();
    delay(random(50));
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, black);
//    interrupts();
  }
  for(int x = 0; x < 3; x++){
//    noInterrupts();
    setColorOdd(random(20, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(20, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(20, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 30), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 30), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 30), random(100, 255), rgb[random(90)]);
    setColorEven(random(20, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(20, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(20, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 30), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 30), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 30), random(100, 255), rgb[random(90)]);
//    interrupts();
    delay(random(60));
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, black);
//    interrupts();
  }
  for(int x = 0; x < 3; x++){
//    noInterrupts();
    setColorOdd(random(18, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(18, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(18, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 33), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 33), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 33), random(100, 255), rgb[random(90)]);
    setColorEven(random(18, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(18, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(18, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 33), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 33), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 33), random(100, 255), rgb[random(90)]);
//    interrupts();
    delay(random(60));
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, black);
//    interrupts();
  }
  for(int x = 0; x < 3; x++){
//    noInterrupts();
    setColorOdd(random(16, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(16, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(16, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(16, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(16, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 36), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 36), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 36), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 36), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 36), random(100, 255), rgb[random(90)]);
    setColorEven(random(16, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(16, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(16, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(16, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(16, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 36), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 36), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 36), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 36), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 36), random(100, 255), rgb[random(90)]);
//    interrupts();
    delay(random(70));
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, black);
//    interrupts();
  }
  for(int x = 0; x < 3; x++){
//    noInterrupts();
    setColorOdd(random(14, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(14, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(14, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(14, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(14, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 38), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 38), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 38), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 38), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 38), random(100, 255), rgb[random(90)]);
    setColorEven(random(14, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(14, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(14, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(14, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(14, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 38), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 38), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 38), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 38), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 38), random(100, 255), rgb[random(90)]);
//    interrupts();
    delay(random(70));
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, black);
//    interrupts();
  }
  for(int x = 0; x < 4; x++){
//    noInterrupts();
    setColorOdd(random(12, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(12, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(12, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(12, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(12, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(12, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 40), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 40), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 40), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 40), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 40), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 40), random(100, 255), rgb[random(90)]);
    setColorEven(random(12, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(12, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(12, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(12, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(12, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(12, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 40), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 40), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 40), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 40), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 40), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 40), random(100, 255), rgb[random(90)]);
//    interrupts();
    delay(random(100));
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, black);
//    interrupts();
  }
  for(int x = 0; x < 4; x++){
//    noInterrupts();
    setColorOdd(random(10, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(10, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(10, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(10, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(10, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(10, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 42), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 42), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 42), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 42), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 42), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 42), random(100, 255), rgb[random(90)]);
    setColorEven(random(10, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(10, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(10, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(10, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(10, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(10, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 42), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 42), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 42), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 42), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 42), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 42), random(100, 255), rgb[random(90)]);
//    interrupts();
    delay(random(100));
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, black);
//    interrupts();
  }
  for(int x = 0; x < 4; x++){
//    noInterrupts();
    setColorOdd(random(8, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(8, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(8, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(8, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(8, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(8, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(8, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 44), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 44), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 44), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 44), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 44), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 44), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 44), random(100, 255), rgb[random(90)]);
    setColorEven(random(8, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(8, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(8, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(8, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(8, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(8, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(8, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 44), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 44), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 44), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 44), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 44), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 44), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 44), random(100, 255), rgb[random(90)]);
//    interrupts();
    delay(random(150));
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, black);
//    interrupts();
  }
  for(int x = 0; x < 4; x++){
//    noInterrupts();
    setColorOdd(random(5, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(5, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(5, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(5, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(5, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(5, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(5, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 48), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 48), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 48), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 48), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 48), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 48), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 48), random(100, 255), rgb[random(90)]);
    setColorEven(random(5, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(5, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(5, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(5, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(5, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(5, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(5, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 48), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 48), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 48), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 48), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 48), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 48), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 48), random(100, 255), rgb[random(90)]);
//    interrupts();
    delay(random(150));
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, black);
//    interrupts();
  }
  for(int x = 0; x < 5; x++){
//    noInterrupts();
    setColorOdd(random(0, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(0, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(0, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(0, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(0, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(0, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(0, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(0, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(0, 24), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 50), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 50), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 50), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 50), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 50), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 50), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 50), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 50), random(100, 255), rgb[random(90)]);
    setColorOdd(random(25, 50), random(100, 255), rgb[random(90)]);
    setColorEven(random(0, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(0, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(0, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(0, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(0, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(0, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(0, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(0, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(0, 24), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 50), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 50), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 50), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 50), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 50), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 50), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 50), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 50), random(100, 255), rgb[random(90)]);
    setColorEven(random(25, 50), random(100, 255), rgb[random(90)]);
//    interrupts();
    delay(random(200));
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, black);
//    interrupts();
  }
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------SETUP----------------------------------------------------------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void setup() {
  DDRC = B11111111;          //set all PORTC pins to be outputs
  DDRL = B11111111;          //set all PORTL pins to be outputs
  delay(500);
  noInterrupts();            //Leaving the "noInterrupts(), interrupts()" in even though they are redundant, proper enumeration is critical
  enumerateAll();            //Enumerate lights on string to enable individual bulb addressing
  interrupts();
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------LOOP-----------------------------------------------------------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void loop() {

  for(byte x = 0; x < 20; x++){
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, red);
//    interrupts();
    delay(200);
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, white);
//    interrupts();
    delay(200);
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, green);
//    interrupts();
    delay(200);
//    noInterrupts();
    fillColorAll(0, lightCount, defaultIntensity, white);
//    interrupts();
    delay(200);
  }

  fillColorAll(0, lightCount, 200, black);
  
  for(int x = 0; x < 900; x++){                                                     //RGB COLOR SWIRL
//    noInterrupts();
    while(y < lightCount){
      value = (x+y)%90;
      setColorAll(y, defaultIntensity, rgb[value]);
      y++;
    }
//    interrupts();
    y = 0;
  }
  
  fillColorAll(0, lightCount, defaultIntensity, black);
  
  for(int a = 0; a < 25; a++){                                                      //UP & DOWN ALL RED
//    noInterrupts();
    setColorAll(a, 200, red);
    setColorAll(49-a, 200, red);
    setColorAll(a-1, 180, red);
    setColorAll(49-a+1, 180, red);
    setColorAll(a-2, 160, red);
    setColorAll(49-a+2, 160, red);
    setColorAll(a-3, 140, red);
    setColorAll(49-a+3, 140, red);
    setColorAll(a-4, 120, red);
    setColorAll(49-a+4, 120, red);
    setColorAll(a-5, 100, red);
    setColorAll(49-a+5, 100, red);
    setColorAll(a-6, 80, red);
    setColorAll(49-a+6, 80, red);
    setColorAll(a-7, 60, red);
    setColorAll(49-a+7, 60, red);
    setColorAll(a-8, 40, red);
    setColorAll(49-a+8, 40, red);
    setColorAll(a-9, 20, red);
    setColorAll(49-a+9, 20, red);
    setColorAll(a-10, 0, red);
    setColorAll(49-a+10, 0, red);
//    interrupts();
//    delay(5);
  }
  
  fillColorAll(0, lightCount, defaultIntensity, black);
  
  for(int a = 0; a < 25; a++){
//    noInterrupts();
    setColorAll(24-a, 200, red);
    setColorAll(25+a, 200, red);
    setColorAll(24-a+1, 180, red);
    setColorAll(25+a-1, 180, red);
    setColorAll(24-a+2, 160, red);
    setColorAll(25+a-2, 160, red);
    setColorAll(24-a+3, 140, red);
    setColorAll(25+a-3, 140, red);
    setColorAll(24-a+4, 120, red);
    setColorAll(25+a-4, 120, red);
    setColorAll(24-a+5, 100, red);
    setColorAll(25+a-5, 100, red);
    setColorAll(24-a+6, 80, red);
    setColorAll(25+a-6, 80, red);
    setColorAll(24-a+7, 60, red);
    setColorAll(25+a-7, 60, red);
    setColorAll(24-a+8, 40, red);
    setColorAll(25+a-8, 40, red);
    setColorAll(24-a+9, 20, red);
    setColorAll(25+a-9, 20, red);
    setColorAll(24-a+10, 0, red);
    setColorAll(25+a-10, 0, red);
//    interrupts();
//    delay(5);
  }
  
  fillColorAll(0, lightCount, defaultIntensity, black);
  
  for(int a = 0; a < 25; a++){                                                      //UP & DOWN ALL ORANGE
//    noInterrupts();
    setColorAll(a, 200, orange);
    setColorAll(49-a, 200, orange);
    setColorAll(a-1, 180, orange);
    setColorAll(49-a+1, 180, orange);
    setColorAll(a-2, 160, orange);
    setColorAll(49-a+2, 160, orange);
    setColorAll(a-3, 140, orange);
    setColorAll(49-a+3, 140, orange);
    setColorAll(a-4, 120, orange);
    setColorAll(49-a+4, 120, orange);
    setColorAll(a-5, 100, orange);
    setColorAll(49-a+5, 100, orange);
    setColorAll(a-6, 80, orange);
    setColorAll(49-a+6, 80, orange);
    setColorAll(a-7, 60, orange);
    setColorAll(49-a+7, 60, orange);
    setColorAll(a-8, 40, orange);
    setColorAll(49-a+8, 40, orange);
    setColorAll(a-9, 20, orange);
    setColorAll(49-a+9, 20, orange);
    setColorAll(a-10, 0, orange);
    setColorAll(49-a+10, 0, orange);
//    interrupts();
//    delay(5);
  }
  
  fillColorAll(0, lightCount, defaultIntensity, black);
  
  for(int a = 0; a < 25; a++){
//    noInterrupts();
    setColorAll(24-a, 200, orange);
    setColorAll(25+a, 200, orange);
    setColorAll(24-a+1, 180, orange);
    setColorAll(25+a-1, 180, orange);
    setColorAll(24-a+2, 160, orange);
    setColorAll(25+a-2, 160, orange);
    setColorAll(24-a+3, 140, orange);
    setColorAll(25+a-3, 140, orange);
    setColorAll(24-a+4, 120, orange);
    setColorAll(25+a-4, 120, orange);
    setColorAll(24-a+5, 100, orange);
    setColorAll(25+a-5, 100, orange);
    setColorAll(24-a+6, 80, orange);
    setColorAll(25+a-6, 80, orange);
    setColorAll(24-a+7, 60, orange);
    setColorAll(25+a-7, 60, orange);
    setColorAll(24-a+8, 40, orange);
    setColorAll(25+a-8, 40, orange);
    setColorAll(24-a+9, 20, orange);
    setColorAll(25+a-9, 20, orange);
    setColorAll(24-a+10, 0, orange);
    setColorAll(25+a-10, 0, orange);
//    interrupts();
//    delay(5);
  }
  
  fillColorAll(0, lightCount, defaultIntensity, black);
  
  for(int a = 0; a < 25; a++){                                                      //UP & DOWN ALL YELLOW
//    noInterrupts();
    setColorAll(a, 200, yellow);
    setColorAll(49-a, 200, yellow);
    setColorAll(a-1, 180, yellow);
    setColorAll(49-a+1, 180, yellow);
    setColorAll(a-2, 160, yellow);
    setColorAll(49-a+2, 160, yellow);
    setColorAll(a-3, 140, yellow);
    setColorAll(49-a+3, 140, yellow);
    setColorAll(a-4, 120, yellow);
    setColorAll(49-a+4, 120, yellow);
    setColorAll(a-5, 100, yellow);
    setColorAll(49-a+5, 100, yellow);
    setColorAll(a-6, 80, yellow);
    setColorAll(49-a+6, 80, yellow);
    setColorAll(a-7, 60, yellow);
    setColorAll(49-a+7, 60, yellow);
    setColorAll(a-8, 40, yellow);
    setColorAll(49-a+8, 40, yellow);
    setColorAll(a-9, 20, yellow);
    setColorAll(49-a+9, 20, yellow);
    setColorAll(a-10, 0, yellow);
    setColorAll(49-a+10, 0, yellow);
//    interrupts();
//    delay(5);
  }
  
  fillColorAll(0, lightCount, defaultIntensity, black);
  
  for(int a = 0; a < 25; a++){
//    noInterrupts();
    setColorAll(24-a, 200, yellow);
    setColorAll(25+a, 200, yellow);
    setColorAll(24-a+1, 180, yellow);
    setColorAll(25+a-1, 180, yellow);
    setColorAll(24-a+2, 160, yellow);
    setColorAll(25+a-2, 160, yellow);
    setColorAll(24-a+3, 140, yellow);
    setColorAll(25+a-3, 140, yellow);
    setColorAll(24-a+4, 120, yellow);
    setColorAll(25+a-4, 120, yellow);
    setColorAll(24-a+5, 100, yellow);
    setColorAll(25+a-5, 100, yellow);
    setColorAll(24-a+6, 80, yellow);
    setColorAll(25+a-6, 80, yellow);
    setColorAll(24-a+7, 60, yellow);
    setColorAll(25+a-7, 60, yellow);
    setColorAll(24-a+8, 40, yellow);
    setColorAll(25+a-8, 40, yellow);
    setColorAll(24-a+9, 20, yellow);
    setColorAll(25+a-9, 20, yellow);
    setColorAll(24-a+10, 0, yellow);
    setColorAll(25+a-10, 0, yellow);
//    interrupts();
//    delay(5);
  }
  
  fillColorAll(0, lightCount, defaultIntensity, black);
  
  for(int a = 0; a < 25; a++){                                                      //UP & DOWN ALL GREEN
//    noInterrupts();
    setColorAll(a, 200, green);
    setColorAll(49-a, 200, green);
    setColorAll(a-1, 180, green);
    setColorAll(49-a+1, 180, green);
    setColorAll(a-2, 160, green);
    setColorAll(49-a+2, 160, green);
    setColorAll(a-3, 140, green);
    setColorAll(49-a+3, 140, green);
    setColorAll(a-4, 120, green);
    setColorAll(49-a+4, 120, green);
    setColorAll(a-5, 100, green);
    setColorAll(49-a+5, 100, green);
    setColorAll(a-6, 80, green);
    setColorAll(49-a+6, 80, green);
    setColorAll(a-7, 60, green);
    setColorAll(49-a+7, 60, green);
    setColorAll(a-8, 40, green);
    setColorAll(49-a+8, 40, green);
    setColorAll(a-9, 20, green);
    setColorAll(49-a+9, 20, green);
    setColorAll(a-10, 0, green);
    setColorAll(49-a+10, 0, green);
//    interrupts();
//    delay(5);
  }
  
  fillColorAll(0, lightCount, defaultIntensity, black);
  
    for(int a = 0; a < 25; a++){
//    noInterrupts();
    setColorAll(24-a, 200, green);
    setColorAll(25+a, 200, green);
    setColorAll(24-a+1, 180, green);
    setColorAll(25+a-1, 180, green);
    setColorAll(24-a+2, 160, green);
    setColorAll(25+a-2, 160, green);
    setColorAll(24-a+3, 140, green);
    setColorAll(25+a-3, 140, green);
    setColorAll(24-a+4, 120, green);
    setColorAll(25+a-4, 120, green);
    setColorAll(24-a+5, 100, green);
    setColorAll(25+a-5, 100, green);
    setColorAll(24-a+6, 80, green);
    setColorAll(25+a-6, 80, green);
    setColorAll(24-a+7, 60, green);
    setColorAll(25+a-7, 60, green);
    setColorAll(24-a+8, 40, green);
    setColorAll(25+a-8, 40, green);
    setColorAll(24-a+9, 20, green);
    setColorAll(25+a-9, 20, green);
    setColorAll(24-a+10, 0, green);
    setColorAll(25+a-10, 0, green);
//    interrupts();
//    delay(5);
  }
  
  fillColorAll(0, lightCount, defaultIntensity, black);
  
  for(int a = 0; a < 25; a++){                                                      //UP & DOWN ALL BLUE
//    noInterrupts();
    setColorAll(a, 200, blue);
    setColorAll(49-a, 200, blue);
    setColorAll(a-1, 180, blue);
    setColorAll(49-a+1, 180, blue);
    setColorAll(a-2, 160, blue);
    setColorAll(49-a+2, 160, blue);
    setColorAll(a-3, 140, blue);
    setColorAll(49-a+3, 140, blue);
    setColorAll(a-4, 120, blue);
    setColorAll(49-a+4, 120, blue);
    setColorAll(a-5, 100, blue);
    setColorAll(49-a+5, 100, blue);
    setColorAll(a-6, 80, blue);
    setColorAll(49-a+6, 80, blue);
    setColorAll(a-7, 60, blue);
    setColorAll(49-a+7, 60, blue);
    setColorAll(a-8, 40, blue);
    setColorAll(49-a+8, 40, blue);
    setColorAll(a-9, 20, blue);
    setColorAll(49-a+9, 20, blue);
    setColorAll(a-10, 0, blue);
    setColorAll(49-a+10, 0, blue);
//    interrupts();
//    delay(5);
  }
  
  fillColorAll(0, lightCount, defaultIntensity, black);
  
  for(int a = 0; a < 25; a++){
//    noInterrupts();
    setColorAll(24-a, 200, blue);
    setColorAll(25+a, 200, blue);
    setColorAll(24-a+1, 180, blue);
    setColorAll(25+a-1, 180, blue);
    setColorAll(24-a+2, 160, blue);
    setColorAll(25+a-2, 160, blue);
    setColorAll(24-a+3, 140, blue);
    setColorAll(25+a-3, 140, blue);
    setColorAll(24-a+4, 120, blue);
    setColorAll(25+a-4, 120, blue);
    setColorAll(24-a+5, 100, blue);
    setColorAll(25+a-5, 100, blue);
    setColorAll(24-a+6, 80, blue);
    setColorAll(25+a-6, 80, blue);
    setColorAll(24-a+7, 60, blue);
    setColorAll(25+a-7, 60, blue);
    setColorAll(24-a+8, 40, blue);
    setColorAll(25+a-8, 40, blue);
    setColorAll(24-a+9, 20, blue);
    setColorAll(25+a-9, 20, blue);
    setColorAll(24-a+10, 0, blue);
    setColorAll(25+a-10, 0, blue);
//    interrupts();
//    delay(5);
  }
  
  fillColorAll(0, lightCount, defaultIntensity, black);
  
  for(int a = 0; a < 25; a++){                                                      //UP & DOWN ALL PURPLE
//    noInterrupts();
    setColorAll(a, 200, purple);
    setColorAll(49-a, 200, purple);
    setColorAll(a-1, 180, purple);
    setColorAll(49-a+1, 180, purple);
    setColorAll(a-2, 160, purple);
    setColorAll(49-a+2, 160, purple);
    setColorAll(a-3, 140, purple);
    setColorAll(49-a+3, 140, purple);
    setColorAll(a-4, 120, purple);
    setColorAll(49-a+4, 120, purple);
    setColorAll(a-5, 100, purple);
    setColorAll(49-a+5, 100, purple);
    setColorAll(a-6, 80, purple);
    setColorAll(49-a+6, 80, purple);
    setColorAll(a-7, 60, purple);
    setColorAll(49-a+7, 60, purple);
    setColorAll(a-8, 40, purple);
    setColorAll(49-a+8, 40, purple);
    setColorAll(a-9, 20, purple);
    setColorAll(49-a+9, 20, purple);
    setColorAll(a-10, 0, purple);
    setColorAll(49-a+10, 0, purple);
//    interrupts();
//    delay(5);
  }
  
  fillColorAll(0, lightCount, defaultIntensity, black);
  
  for(int a = 0; a < 25; a++){
//    noInterrupts();
    setColorAll(24-a, 200, purple);
    setColorAll(25+a, 200, purple);
    setColorAll(24-a+1, 180, purple);
    setColorAll(25+a-1, 180, purple);
    setColorAll(24-a+2, 160, purple);
    setColorAll(25+a-2, 160, purple);
    setColorAll(24-a+3, 140, purple);
    setColorAll(25+a-3, 140, purple);
    setColorAll(24-a+4, 120, purple);
    setColorAll(25+a-4, 120, purple);
    setColorAll(24-a+5, 100, purple);
    setColorAll(25+a-5, 100, purple);
    setColorAll(24-a+6, 80, purple);
    setColorAll(25+a-6, 80, purple);
    setColorAll(24-a+7, 60, purple);
    setColorAll(25+a-7, 60, purple);
    setColorAll(24-a+8, 40, purple);
    setColorAll(25+a-8, 40, purple);
    setColorAll(24-a+9, 20, purple);
    setColorAll(25+a-9, 20, purple);
    setColorAll(24-a+10, 0, purple);
    setColorAll(25+a-10, 0, purple);
//    interrupts();
//    delay(5);
  }
  
  fillColorAll(0, lightCount, defaultIntensity, black);
  
  for(int a = 0; a < 25; a++){                                                      //UP ODD & DOWN EVEN RED
//    noInterrupts();
    setColorEven(a, 200, red);
    setColorEven(49-a, 200, red);
    setColorOdd(24-a, 200, black);
    setColorOdd(25+a, 200, black);
    setColorEven(a-1, 180, red);
    setColorEven(49-a+1, 180, red);
    setColorOdd(24-a+1, 180, black);
    setColorOdd(25+a-1, 180, black);
    setColorEven(a-2, 160, red);
    setColorEven(49-a+2, 160, red);
    setColorOdd(24-a+2, 160, black);
    setColorOdd(25+a-2, 160, black);
    setColorEven(a-3, 140, red);
    setColorEven(49-a+3, 140, red);
    setColorOdd(24-a+3, 140, black);
    setColorOdd(25+a-3, 140, black);
    setColorEven(a-4, 120, red);
    setColorEven(49-a+4, 120, red);
    setColorOdd(24-a+4, 120, black);
    setColorOdd(25+a-4, 120, black);
    setColorEven(a-5, 100, red);
    setColorEven(49-a+5, 100, red);
    setColorOdd(24-a+5, 100, black);
    setColorOdd(25+a-5, 100, black);
    setColorEven(a-6, 80, red);
    setColorEven(49-a+6, 80, red);
    setColorOdd(24-a+6, 80, black);
    setColorOdd(25+a-6, 80, black);
    setColorEven(a-7, 60, red);
    setColorEven(49-a+7, 60, red);
    setColorOdd(24-a+7, 60, black);
    setColorOdd(25+a-7, 60, black);
    setColorEven(a-8, 40, red);
    setColorEven(49-a+8, 40, red);
    setColorOdd(24-a+8, 40, black);
    setColorOdd(25+a-8, 40, black);
    setColorEven(a-9, 20, red);
    setColorEven(49-a+9, 20, red);
    setColorOdd(24-a+9, 20, black);
    setColorOdd(25+a-9, 20, black);
    setColorEven(a-10, 0, red);
    setColorEven(49-a+10, 0, red);
    setColorOdd(24-a+10, 0, black);
    setColorOdd(25+a-10, 0, black);
//    interrupts();
//    delay(5);
  }
  
  for(int a = 0; a < 25; a++){
//    noInterrupts();
    setColorOdd(a, 200, red);
    setColorOdd(49-a, 200, red);
    setColorEven(24-a, 200, red);
    setColorEven(25+a, 200, red);
    setColorOdd(a-1, 180, red);
    setColorOdd(49-a+1, 180, red);
    setColorEven(24-a+1, 180, red);
    setColorEven(25+a-1, 180, red);
    setColorOdd(a-2, 160, red);
    setColorOdd(49-a+2, 160, red);
    setColorEven(24-a+2, 160, red);
    setColorEven(25+a-2, 160, red);
    setColorOdd(a-3, 140, red);
    setColorOdd(49-a+3, 140, red);
    setColorEven(24-a+3, 140, red);
    setColorEven(25+a-3, 140, red);
    setColorOdd(a-4, 120, red);
    setColorOdd(49-a+4, 120, red);
    setColorEven(24-a+4, 120, red);
    setColorEven(25+a-4, 120, red);
    setColorOdd(a-5, 100, red);
    setColorOdd(49-a+5, 100, red);
    setColorEven(24-a+5, 100, red);
    setColorEven(25+a-5, 100, red);
    setColorOdd(a-6, 80, red);
    setColorOdd(49-a+6, 80, red);
    setColorEven(24-a+6, 80, red);
    setColorEven(25+a-6, 80, red);
    setColorOdd(a-7, 60, red);
    setColorOdd(49-a+7, 60, red);
    setColorEven(24-a+7, 60, red);
    setColorEven(25+a-7, 60, red);
    setColorOdd(a-8, 40, red);
    setColorOdd(49-a+8, 40, red);
    setColorEven(24-a+8, 40, red);
    setColorEven(25+a-8, 40, red);
    setColorOdd(a-9, 20, red);
    setColorOdd(49-a+9, 20, red);
    setColorEven(24-a+9, 20, red);
    setColorEven(25+a-9, 20, red);
    setColorOdd(a-10, 0, red);
    setColorOdd(49-a+10, 0, red);
    setColorEven(24-a+10, 0, red);
    setColorEven(25+a-10, 0, red);
//    interrupts();
//    delay(5);
  }
  
  fillColorAll(0, lightCount, defaultIntensity, black);
  
  for(int a = 0; a < 25; a++){
//    noInterrupts();
    setColorEven(a, 200, red);
    setColorEven(49-a, 200, red);
    setColorOdd(24-a, 200, red);
    setColorOdd(25+a, 200, red);
    setColorEven(a-1, 180, red);
    setColorEven(49-a+1, 180, red);
    setColorOdd(24-a+1, 180, red);
    setColorOdd(25+a-1, 180, red);
    setColorEven(a-2, 160, red);
    setColorEven(49-a+2, 160, red);
    setColorOdd(24-a+2, 160, red);
    setColorOdd(25+a-2, 160, red);
    setColorEven(a-3, 140, red);
    setColorEven(49-a+3, 140, red);
    setColorOdd(24-a+3, 140, red);
    setColorOdd(25+a-3, 140, red);
    setColorEven(a-4, 120, red);
    setColorEven(49-a+4, 120, red);
    setColorOdd(24-a+4, 120, red);
    setColorOdd(25+a-4, 120, red);
    setColorEven(a-5, 100, red);
    setColorEven(49-a+5, 100, red);
    setColorOdd(24-a+5, 100, red);
    setColorOdd(25+a-5, 100, red);
    setColorEven(a-6, 80, red);
    setColorEven(49-a+6, 80, red);
    setColorOdd(24-a+6, 80, red);
    setColorOdd(25+a-6, 80, red);
    setColorEven(a-7, 60, red);
    setColorEven(49-a+7, 60, red);
    setColorOdd(24-a+7, 60, red);
    setColorOdd(25+a-7, 60, red);
    setColorEven(a-8, 40, red);
    setColorEven(49-a+8, 40, red);
    setColorOdd(24-a+8, 40, red);
    setColorOdd(25+a-8, 40, red);
    setColorEven(a-9, 20, red);
    setColorEven(49-a+9, 20, red);
    setColorOdd(24-a+9, 20, red);
    setColorOdd(25+a-9, 20, red);
    setColorEven(a-10, 0, red);
    setColorEven(49-a+10, 0, red);
    setColorOdd(24-a+10, 0, red);
    setColorOdd(25+a-10, 0, red);
//    interrupts();
//    delay(5);
  }
  
  fillColorAll(0, lightCount, defaultIntensity, black);
  
  for(int a = 0; a < 25; a++){                                                      //UP ODD & DOWN EVEN ORANGE
//    noInterrupts();
    setColorOdd(a, 200, orange);
    setColorOdd(49-a, 200, orange);
    setColorEven(24-a, 200, orange);
    setColorEven(25+a, 200, orange);
    setColorOdd(a-1, 180, orange);
    setColorOdd(49-a+1, 180, orange);
    setColorEven(24-a+1, 180, orange);
    setColorEven(25+a-1, 180, orange);
    setColorOdd(a-2, 160, orange);
    setColorOdd(49-a+2, 160, orange);
    setColorEven(24-a+2, 160, orange);
    setColorEven(25+a-2, 160, orange);
    setColorOdd(a-3, 140, orange);
    setColorOdd(49-a+3, 140, orange);
    setColorEven(24-a+3, 140, orange);
    setColorEven(25+a-3, 140, orange);
    setColorOdd(a-4, 120, orange);
    setColorOdd(49-a+4, 120, orange);
    setColorEven(24-a+4, 120, orange);
    setColorEven(25+a-4, 120, orange);
    setColorOdd(a-5, 100, orange);
    setColorOdd(49-a+5, 100, orange);
    setColorEven(24-a+5, 100, orange);
    setColorEven(25+a-5, 100, orange);
    setColorOdd(a-6, 80, orange);
    setColorOdd(49-a+6, 80, orange);
    setColorEven(24-a+6, 80, orange);
    setColorEven(25+a-6, 80, orange);
    setColorOdd(a-7, 60, orange);
    setColorOdd(49-a+7, 60, orange);
    setColorEven(24-a+7, 60, orange);
    setColorEven(25+a-7, 60, orange);
    setColorOdd(a-8, 40, orange);
    setColorOdd(49-a+8, 40, orange);
    setColorEven(24-a+8, 40, orange);
    setColorEven(25+a-8, 40, orange);
    setColorOdd(a-9, 20, orange);
    setColorOdd(49-a+9, 20, orange);
    setColorEven(24-a+9, 20, orange);
    setColorEven(25+a-9, 20, orange);
    setColorOdd(a-10, 0, orange);
    setColorOdd(49-a+10, 0, orange);
    setColorEven(24-a+10, 0, orange);
    setColorEven(25+a-10, 0, orange);
//    interrupts();
//    delay(5);
  }
  
  fillColorAll(0, lightCount, defaultIntensity, black);
  
  for(int a = 0; a < 25; a++){
//    noInterrupts();
    setColorEven(a, 200, orange);
    setColorEven(49-a, 200, orange);
    setColorOdd(24-a, 200, orange);
    setColorOdd(25+a, 200, orange);
    setColorEven(a-1, 180, orange);
    setColorEven(49-a+1, 180, orange);
    setColorOdd(24-a+1, 180, orange);
    setColorOdd(25+a-1, 180, orange);
    setColorEven(a-2, 160, orange);
    setColorEven(49-a+2, 160, orange);
    setColorOdd(24-a+2, 160, orange);
    setColorOdd(25+a-2, 160, orange);
    setColorEven(a-3, 140, orange);
    setColorEven(49-a+3, 140, orange);
    setColorOdd(24-a+3, 140, orange);
    setColorOdd(25+a-3, 140, orange);
    setColorEven(a-4, 120, orange);
    setColorEven(49-a+4, 120, orange);
    setColorOdd(24-a+4, 120, orange);
    setColorOdd(25+a-4, 120, orange);
    setColorEven(a-5, 100, orange);
    setColorEven(49-a+5, 100, orange);
    setColorOdd(24-a+5, 100, orange);
    setColorOdd(25+a-5, 100, orange);
    setColorEven(a-6, 80, orange);
    setColorEven(49-a+6, 80, orange);
    setColorOdd(24-a+6, 80, orange);
    setColorOdd(25+a-6, 80, orange);
    setColorEven(a-7, 60, orange);
    setColorEven(49-a+7, 60, orange);
    setColorOdd(24-a+7, 60, orange);
    setColorOdd(25+a-7, 60, orange);
    setColorEven(a-8, 40, orange);
    setColorEven(49-a+8, 40, orange);
    setColorOdd(24-a+8, 40, orange);
    setColorOdd(25+a-8, 40, orange);
    setColorEven(a-9, 20, orange);
    setColorEven(49-a+9, 20, orange);
    setColorOdd(24-a+9, 20, orange);
    setColorOdd(25+a-9, 20, orange);
    setColorEven(a-10, 0, orange);
    setColorEven(49-a+10, 0, orange);
    setColorOdd(24-a+10, 0, orange);
    setColorOdd(25+a-10, 0, orange);
//    interrupts();
//    delay(5);
  }
  
  fillColorAll(0, lightCount, defaultIntensity, black);
  
  for(int a = 0; a < 25; a++){                                                      //UP ODD & DOWN EVEN YELLOW
//    noInterrupts();
    setColorOdd(a, 200, yellow);
    setColorOdd(49-a, 200, yellow);
    setColorEven(24-a, 200, yellow);
    setColorEven(25+a, 200, yellow);
    setColorOdd(a-1, 180, yellow);
    setColorOdd(49-a+1, 180, yellow);
    setColorEven(24-a+1, 180, yellow);
    setColorEven(25+a-1, 180, yellow);
    setColorOdd(a-2, 160, yellow);
    setColorOdd(49-a+2, 160, yellow);
    setColorEven(24-a+2, 160, yellow);
    setColorEven(25+a-2, 160, yellow);
    setColorOdd(a-3, 140, yellow);
    setColorOdd(49-a+3, 140, yellow);
    setColorEven(24-a+3, 140, yellow);
    setColorEven(25+a-3, 140, yellow);
    setColorOdd(a-4, 120, yellow);
    setColorOdd(49-a+4, 120, yellow);
    setColorEven(24-a+4, 120, yellow);
    setColorEven(25+a-4, 120, yellow);
    setColorOdd(a-5, 100, yellow);
    setColorOdd(49-a+5, 100, yellow);
    setColorEven(24-a+5, 100, yellow);
    setColorEven(25+a-5, 100, yellow);
    setColorOdd(a-6, 80, yellow);
    setColorOdd(49-a+6, 80, yellow);
    setColorEven(24-a+6, 80, yellow);
    setColorEven(25+a-6, 80, yellow);
    setColorOdd(a-7, 60, yellow);
    setColorOdd(49-a+7, 60, yellow);
    setColorEven(24-a+7, 60, yellow);
    setColorEven(25+a-7, 60, yellow);
    setColorOdd(a-8, 40, yellow);
    setColorOdd(49-a+8, 40, yellow);
    setColorEven(24-a+8, 40, yellow);
    setColorEven(25+a-8, 40, yellow);
    setColorOdd(a-9, 20, yellow);
    setColorOdd(49-a+9, 20, yellow);
    setColorEven(24-a+9, 20, yellow);
    setColorEven(25+a-9, 20, yellow);
    setColorOdd(a-10, 0, yellow);
    setColorOdd(49-a+10, 0, yellow);
    setColorEven(24-a+10, 0, yellow);
    setColorEven(25+a-10, 0, yellow);
//    interrupts();
//    delay(5);
  }
  
  fillColorAll(0, lightCount, defaultIntensity, black);
  
  for(int a = 0; a < 25; a++){
//    noInterrupts();
    setColorEven(a, 200, yellow);
    setColorEven(49-a, 200, yellow);
    setColorOdd(24-a, 200, yellow);
    setColorOdd(25+a, 200, yellow);
    setColorEven(a-1, 180, yellow);
    setColorEven(49-a+1, 180, yellow);
    setColorOdd(24-a+1, 180, yellow);
    setColorOdd(25+a-1, 180, yellow);
    setColorEven(a-2, 160, yellow);
    setColorEven(49-a+2, 160, yellow);
    setColorOdd(24-a+2, 160, yellow);
    setColorOdd(25+a-2, 160, yellow);
    setColorEven(a-3, 140, yellow);
    setColorEven(49-a+3, 140, yellow);
    setColorOdd(24-a+3, 140, yellow);
    setColorOdd(25+a-3, 140, yellow);
    setColorEven(a-4, 120, yellow);
    setColorEven(49-a+4, 120, yellow);
    setColorOdd(24-a+4, 120, yellow);
    setColorOdd(25+a-4, 120, yellow);
    setColorEven(a-5, 100, yellow);
    setColorEven(49-a+5, 100, yellow);
    setColorOdd(24-a+5, 100, yellow);
    setColorOdd(25+a-5, 100, yellow);
    setColorEven(a-6, 80, yellow);
    setColorEven(49-a+6, 80, yellow);
    setColorOdd(24-a+6, 80, yellow);
    setColorOdd(25+a-6, 80, yellow);
    setColorEven(a-7, 60, yellow);
    setColorEven(49-a+7, 60, yellow);
    setColorOdd(24-a+7, 60, yellow);
    setColorOdd(25+a-7, 60, yellow);
    setColorEven(a-8, 40, yellow);
    setColorEven(49-a+8, 40, yellow);
    setColorOdd(24-a+8, 40, yellow);
    setColorOdd(25+a-8, 40, yellow);
    setColorEven(a-9, 20, yellow);
    setColorEven(49-a+9, 20, yellow);
    setColorOdd(24-a+9, 20, yellow);
    setColorOdd(25+a-9, 20, yellow);
    setColorEven(a-10, 0, yellow);
    setColorEven(49-a+10, 0, yellow);
    setColorOdd(24-a+10, 0, yellow);
    setColorOdd(25+a-10, 0, yellow);
//    interrupts();
//    delay(5);
  }
  
  fillColorAll(0, lightCount, defaultIntensity, black);
  
  for(int a = 0; a < 25; a++){                                                      //UP ODD & DOWN EVEN GREEN
//    noInterrupts();
    setColorOdd(a, 200, green);
    setColorOdd(49-a, 200, green);
    setColorEven(24-a, 200, green);
    setColorEven(25+a, 200, green);
    setColorOdd(a-1, 180, green);
    setColorOdd(49-a+1, 180, green);
    setColorEven(24-a+1, 180, green);
    setColorEven(25+a-1, 180, green);
    setColorOdd(a-2, 160, green);
    setColorOdd(49-a+2, 160, green);
    setColorEven(24-a+2, 160, green);
    setColorEven(25+a-2, 160, green);
    setColorOdd(a-3, 140, green);
    setColorOdd(49-a+3, 140, green);
    setColorEven(24-a+3, 140, green);
    setColorEven(25+a-3, 140, green);
    setColorOdd(a-4, 120, green);
    setColorOdd(49-a+4, 120, green);
    setColorEven(24-a+4, 120, green);
    setColorEven(25+a-4, 120, green);
    setColorOdd(a-5, 100, green);
    setColorOdd(49-a+5, 100, green);
    setColorEven(24-a+5, 100, green);
    setColorEven(25+a-5, 100, green);
    setColorOdd(a-6, 80, green);
    setColorOdd(49-a+6, 80, green);
    setColorEven(24-a+6, 80, green);
    setColorEven(25+a-6, 80, green);
    setColorOdd(a-7, 60, green);
    setColorOdd(49-a+7, 60, green);
    setColorEven(24-a+7, 60, green);
    setColorEven(25+a-7, 60, green);
    setColorOdd(a-8, 40, green);
    setColorOdd(49-a+8, 40, green);
    setColorEven(24-a+8, 40, green);
    setColorEven(25+a-8, 40, green);
    setColorOdd(a-9, 20, green);
    setColorOdd(49-a+9, 20, green);
    setColorEven(24-a+9, 20, green);
    setColorEven(25+a-9, 20, green);
    setColorOdd(a-10, 0, green);
    setColorOdd(49-a+10, 0, green);
    setColorEven(24-a+10, 0, green);
    setColorEven(25+a-10, 0, green);
//    interrupts();
//    delay(5);
  }
  
  fillColorAll(0, lightCount, defaultIntensity, black);
  
  for(int a = 0; a < 25; a++){
//    noInterrupts();
    setColorEven(a, 200, green);
    setColorEven(49-a, 200, green);
    setColorOdd(24-a, 200, green);
    setColorOdd(25+a, 200, green);
    setColorEven(a-1, 180, green);
    setColorEven(49-a+1, 180, green);
    setColorOdd(24-a+1, 180, green);
    setColorOdd(25+a-1, 180, green);
    setColorEven(a-2, 160, green);
    setColorEven(49-a+2, 160, green);
    setColorOdd(24-a+2, 160, green);
    setColorOdd(25+a-2, 160, green);
    setColorEven(a-3, 140, green);
    setColorEven(49-a+3, 140, green);
    setColorOdd(24-a+3, 140, green);
    setColorOdd(25+a-3, 140, green);
    setColorEven(a-4, 120, green);
    setColorEven(49-a+4, 120, green);
    setColorOdd(24-a+4, 120, green);
    setColorOdd(25+a-4, 120, green);
    setColorEven(a-5, 100, green);
    setColorEven(49-a+5, 100, green);
    setColorOdd(24-a+5, 100, green);
    setColorOdd(25+a-5, 100, green);
    setColorEven(a-6, 80, green);
    setColorEven(49-a+6, 80, green);
    setColorOdd(24-a+6, 80, green);
    setColorOdd(25+a-6, 80, green);
    setColorEven(a-7, 60, green);
    setColorEven(49-a+7, 60, green);
    setColorOdd(24-a+7, 60, green);
    setColorOdd(25+a-7, 60, green);
    setColorEven(a-8, 40, green);
    setColorEven(49-a+8, 40, green);
    setColorOdd(24-a+8, 40, green);
    setColorOdd(25+a-8, 40, green);
    setColorEven(a-9, 20, green);
    setColorEven(49-a+9, 20, green);
    setColorOdd(24-a+9, 20, green);
    setColorOdd(25+a-9, 20, green);
    setColorEven(a-10, 0, green);
    setColorEven(49-a+10, 0, green);
    setColorOdd(24-a+10, 0, green);
    setColorOdd(25+a-10, 0, green);
//    interrupts();
//    delay(5);
  }
  
  fillColorAll(0, lightCount, defaultIntensity, black);
  
  for(int a = 0; a < 25; a++){                                                      //UP ODD & DOWN EVEN BLUE
//    noInterrupts();
    setColorOdd(a, 200, blue);
    setColorOdd(49-a, 200, blue);
    setColorEven(24-a, 200, blue);
    setColorEven(25+a, 200, blue);
    setColorOdd(a-1, 180, blue);
    setColorOdd(49-a+1, 180, blue);
    setColorEven(24-a+1, 180, blue);
    setColorEven(25+a-1, 180, blue);
    setColorOdd(a-2, 160, blue);
    setColorOdd(49-a+2, 160, blue);
    setColorEven(24-a+2, 160, blue);
    setColorEven(25+a-2, 160, blue);
    setColorOdd(a-3, 140, blue);
    setColorOdd(49-a+3, 140, blue);
    setColorEven(24-a+3, 140, blue);
    setColorEven(25+a-3, 140, blue);
    setColorOdd(a-4, 120, blue);
    setColorOdd(49-a+4, 120, blue);
    setColorEven(24-a+4, 120, blue);
    setColorEven(25+a-4, 120, blue);
    setColorOdd(a-5, 100, blue);
    setColorOdd(49-a+5, 100, blue);
    setColorEven(24-a+5, 100, blue);
    setColorEven(25+a-5, 100, blue);
    setColorOdd(a-6, 80, blue);
    setColorOdd(49-a+6, 80, blue);
    setColorEven(24-a+6, 80, blue);
    setColorEven(25+a-6, 80, blue);
    setColorOdd(a-7, 60, blue);
    setColorOdd(49-a+7, 60, blue);
    setColorEven(24-a+7, 60, blue);
    setColorEven(25+a-7, 60, blue);
    setColorOdd(a-8, 40, blue);
    setColorOdd(49-a+8, 40, blue);
    setColorEven(24-a+8, 40, blue);
    setColorEven(25+a-8, 40, blue);
    setColorOdd(a-9, 20, blue);
    setColorOdd(49-a+9, 20, blue);
    setColorEven(24-a+9, 20, blue);
    setColorEven(25+a-9, 20, blue);
    setColorOdd(a-10, 0, blue);
    setColorOdd(49-a+10, 0, blue);
    setColorEven(24-a+10, 0, blue);
    setColorEven(25+a-10, 0, blue);
//    interrupts();
//    delay(5);
  }
  
  fillColorAll(0, lightCount, defaultIntensity, black);
  
  for(int a = 0; a < 25; a++){
//    noInterrupts();
    setColorEven(a, 200, blue);
    setColorEven(49-a, 200, blue);
    setColorOdd(24-a, 200, blue);
    setColorOdd(25+a, 200, blue);
    setColorEven(a-1, 180, blue);
    setColorEven(49-a+1, 180, blue);
    setColorOdd(24-a+1, 180, blue);
    setColorOdd(25+a-1, 180, blue);
    setColorEven(a-2, 160, blue);
    setColorEven(49-a+2, 160, blue);
    setColorOdd(24-a+2, 160, blue);
    setColorOdd(25+a-2, 160, blue);
    setColorEven(a-3, 140, blue);
    setColorEven(49-a+3, 140, blue);
    setColorOdd(24-a+3, 140, blue);
    setColorOdd(25+a-3, 140, blue);
    setColorEven(a-4, 120, blue);
    setColorEven(49-a+4, 120, blue);
    setColorOdd(24-a+4, 120, blue);
    setColorOdd(25+a-4, 120, blue);
    setColorEven(a-5, 100, blue);
    setColorEven(49-a+5, 100, blue);
    setColorOdd(24-a+5, 100, blue);
    setColorOdd(25+a-5, 100, blue);
    setColorEven(a-6, 80, blue);
    setColorEven(49-a+6, 80, blue);
    setColorOdd(24-a+6, 80, blue);
    setColorOdd(25+a-6, 80, blue);
    setColorEven(a-7, 60, blue);
    setColorEven(49-a+7, 60, blue);
    setColorOdd(24-a+7, 60, blue);
    setColorOdd(25+a-7, 60, blue);
    setColorEven(a-8, 40, blue);
    setColorEven(49-a+8, 40, blue);
    setColorOdd(24-a+8, 40, blue);
    setColorOdd(25+a-8, 40, blue);
    setColorEven(a-9, 20, blue);
    setColorEven(49-a+9, 20, blue);
    setColorOdd(24-a+9, 20, blue);
    setColorOdd(25+a-9, 20, blue);
    setColorEven(a-10, 0, blue);
    setColorEven(49-a+10, 0, blue);
    setColorOdd(24-a+10, 0, blue);
    setColorOdd(25+a-10, 0, blue);
//    interrupts();
//    delay(5);
  }
  
  fillColorAll(0, lightCount, defaultIntensity, black);
  
  for(int a = 0; a < 25; a++){                                                      //UP ODD & DOWN EVEN PURPLE
//    noInterrupts();
    setColorOdd(a, 200, purple);
    setColorOdd(49-a, 200, purple);
    setColorEven(24-a, 200, purple);
    setColorEven(25+a, 200, purple);
    setColorOdd(a-1, 180, purple);
    setColorOdd(49-a+1, 180, purple);
    setColorEven(24-a+1, 180, purple);
    setColorEven(25+a-1, 180, purple);
    setColorOdd(a-2, 160, purple);
    setColorOdd(49-a+2, 160, purple);
    setColorEven(24-a+2, 160, purple);
    setColorEven(25+a-2, 160, purple);
    setColorOdd(a-3, 140, purple);
    setColorOdd(49-a+3, 140, purple);
    setColorEven(24-a+3, 140, purple);
    setColorEven(25+a-3, 140, purple);
    setColorOdd(a-4, 120, purple);
    setColorOdd(49-a+4, 120, purple);
    setColorEven(24-a+4, 120, purple);
    setColorEven(25+a-4, 120, purple);
    setColorOdd(a-5, 100, purple);
    setColorOdd(49-a+5, 100, purple);
    setColorEven(24-a+5, 100, purple);
    setColorEven(25+a-5, 100, purple);
    setColorOdd(a-6, 80, purple);
    setColorOdd(49-a+6, 80, purple);
    setColorEven(24-a+6, 80, purple);
    setColorEven(25+a-6, 80, purple);
    setColorOdd(a-7, 60, purple);
    setColorOdd(49-a+7, 60, purple);
    setColorEven(24-a+7, 60, purple);
    setColorEven(25+a-7, 60, purple);
    setColorOdd(a-8, 40, purple);
    setColorOdd(49-a+8, 40, purple);
    setColorEven(24-a+8, 40, purple);
    setColorEven(25+a-8, 40, purple);
    setColorOdd(a-9, 20, purple);
    setColorOdd(49-a+9, 20, purple);
    setColorEven(24-a+9, 20, purple);
    setColorEven(25+a-9, 20, purple);
    setColorOdd(a-10, 0, purple);
    setColorOdd(49-a+10, 0, purple);
    setColorEven(24-a+10, 0, purple);
    setColorEven(25+a-10, 0, purple);
//    interrupts();
//    delay(5);
  }
  
  fillColorAll(0, lightCount, defaultIntensity, black);
  
  for(int a = 0; a < 25; a++){
//    noInterrupts();
    setColorEven(a, 200, purple);
    setColorEven(49-a, 200, purple);
    setColorOdd(24-a, 200, purple);
    setColorOdd(25+a, 200, purple);
    setColorEven(a-1, 180, purple);
    setColorEven(49-a+1, 180, purple);
    setColorOdd(24-a+1, 180, purple);
    setColorOdd(25+a-1, 180, purple);
    setColorEven(a-2, 160, purple);
    setColorEven(49-a+2, 160, purple);
    setColorOdd(24-a+2, 160, purple);
    setColorOdd(25+a-2, 160, purple);
    setColorEven(a-3, 140, purple);
    setColorEven(49-a+3, 140, purple);
    setColorOdd(24-a+3, 140, purple);
    setColorOdd(25+a-3, 140, purple);
    setColorEven(a-4, 120, purple);
    setColorEven(49-a+4, 120, purple);
    setColorOdd(24-a+4, 120, purple);
    setColorOdd(25+a-4, 120, purple);
    setColorEven(a-5, 100, purple);
    setColorEven(49-a+5, 100, purple);
    setColorOdd(24-a+5, 100, purple);
    setColorOdd(25+a-5, 100, purple);
    setColorEven(a-6, 80, purple);
    setColorEven(49-a+6, 80, purple);
    setColorOdd(24-a+6, 80, purple);
    setColorOdd(25+a-6, 80, purple);
    setColorEven(a-7, 60, purple);
    setColorEven(49-a+7, 60, purple);
    setColorOdd(24-a+7, 60, purple);
    setColorOdd(25+a-7, 60, purple);
    setColorEven(a-8, 40, purple);
    setColorEven(49-a+8, 40, purple);
    setColorOdd(24-a+8, 40, purple);
    setColorOdd(25+a-8, 40, purple);
    setColorEven(a-9, 20, purple);
    setColorEven(49-a+9, 20, purple);
    setColorOdd(24-a+9, 20, purple);
    setColorOdd(25+a-9, 20, purple);
    setColorEven(a-10, 0, purple);
    setColorEven(49-a+10, 0, purple);
    setColorOdd(24-a+10, 0, purple);
    setColorOdd(25+a-10, 0, purple);
//    interrupts();
//    delay(5);
  }
  
  fillColorAll(0, lightCount, defaultIntensity, black);
  
  for(byte a = 0; a < 12; a++){                                                     //RGB WHOLE TREE    orig. a < 4, using delay(33)
    for(byte i = 0; i < 90; i++){
//      noInterrupts();
      fillColorAll(0, lightCount, defaultIntensity, rgb[i]);
//      interrupts();
//      delay(33);
    }
  }
/*  for(byte a = 0; a < 4; a++){                                                    //RGB ODD & EVEN (SO-SO EFFECT)
    for(byte i = 0; i < 90; i++){
      noInterrupts();
      fillColorOdd(0, lightCount, 200, rgb[i]);
      fillColorEven(0, lightCount, 200, rgb[89-i]);
      interrupts();
//      delay(500);
    }
  }*/
  
  
  
  fillColorAll(0, lightCount, defaultIntensity, black);

  delayTime = 90;                                                                   //ROTATE CW & CCW ACCEL & DECEL RGB
  int fadeAmount = -2;
  for(int y = 0; y < 90; y++){
    for(byte x = 0; x < 25; x++){
//      noInterrupts();
      setColorOdd(x, defaultIntensity, rgb[y%90]);
      setColorOdd(x + 25, defaultIntensity, black);
      setColorEven(x, defaultIntensity, black);
      setColorEven(x + 25, defaultIntensity, black);
    }
//    interrupts();
    delay(delayTime);
    delayTime = delayTime + fadeAmount;
    if(delayTime <= 0  || delayTime >= 90) fadeAmount = -fadeAmount;
    for(byte x = 0; x < 25; x++){
//      noInterrupts();
      setColorOdd(x, defaultIntensity, black);
      setColorOdd(x + 25, defaultIntensity, black);
      setColorEven(x, defaultIntensity, black);
      setColorEven(x + 25, defaultIntensity, rgb[y%90]);
    }
//    interrupts();
    delay(delayTime);
    delayTime = delayTime + fadeAmount;
    if(delayTime <= 0  || delayTime >= 90) fadeAmount = -fadeAmount;
    for(byte x = 0; x < 25; x++){
//      noInterrupts();
      setColorOdd(x, defaultIntensity, black);
      setColorOdd(x + 25, defaultIntensity, black);
      setColorEven(x, defaultIntensity, rgb[y%90]);
      setColorEven(x + 25, defaultIntensity, black);
    }
//    interrupts();
    delay(delayTime);
    delayTime = delayTime + fadeAmount;
    if(delayTime <= 0  || delayTime >= 90) fadeAmount = -fadeAmount;
    for(byte x = 0; x < 25; x++){
//      noInterrupts();
      setColorOdd(x, defaultIntensity, black);
      setColorOdd(x + 25, defaultIntensity, rgb[y%90]);
      setColorEven(x, defaultIntensity, black);
      setColorEven(x + 25, defaultIntensity, black);
    }
//    interrupts();
    delay(delayTime);
    delayTime = delayTime + fadeAmount;
    if(delayTime <= 0  || delayTime >= 90) fadeAmount = -fadeAmount;
  }
  delayTime = 90;
  fadeAmount = -1;
  for(int y = 0; y < 90; y++){
    for(byte x = 0; x < 25; x++){
//      noInterrupts();
      setColorOdd(x, defaultIntensity, rgb[y%90]);
      setColorOdd(x + 25, defaultIntensity, black);
      setColorEven(x, defaultIntensity, black);
      setColorEven(x + 25, defaultIntensity, black);
    }
//    interrupts();
    delay(delayTime);
    delayTime = delayTime + fadeAmount;
    if(delayTime <= 0  || delayTime >= 90) fadeAmount = -fadeAmount;
    for(byte x = 0; x < 25; x++){
//      noInterrupts();
      setColorOdd(x, defaultIntensity, black);
      setColorOdd(x + 25, defaultIntensity, rgb[y%90]);
      setColorEven(x, defaultIntensity, black);
      setColorEven(x + 25, defaultIntensity, black);
    }
//    interrupts();
    delay(delayTime);
    delayTime = delayTime + fadeAmount;
    if(delayTime <= 0  || delayTime >= 90) fadeAmount = -fadeAmount;
    for(byte x = 0; x < 25; x++){
//      noInterrupts();
      setColorOdd(x, defaultIntensity, black);
      setColorOdd(x + 25, defaultIntensity, black);
      setColorEven(x, defaultIntensity, rgb[y%90]);
      setColorEven(x + 25, defaultIntensity, black);
    }
//    interrupts();
    delay(delayTime);
    delayTime = delayTime + fadeAmount;
    if(delayTime <= 0  || delayTime >= 90) fadeAmount = -fadeAmount;
    for(byte x = 0; x < 25; x++){
//      noInterrupts();
      setColorOdd(x, defaultIntensity, black);
      setColorOdd(x + 25, defaultIntensity, black);
      setColorEven(x, defaultIntensity, black);
      setColorEven(x + 25, defaultIntensity, rgb[y%90]);
    }
//    interrupts();
    delay(delayTime);
    delayTime = delayTime + fadeAmount;
    if(delayTime <= 0  || delayTime >= 90) fadeAmount = -fadeAmount;
  }
  
  fillColorAll(0, lightCount, defaultIntensity, black);
  
  for(int x = 0; x < 25; x++){                                                      //FADE UP TREE RED
    for(brightness = 0; brightness < 256; brightness++){
//      noInterrupts();
      setColorAll(x, brightness, red);
      setColorAll(49-x, brightness, red);
//      interrupts();
    }
  }
  brightness = 255;
  for(int x = 0; x < 25; x++){
    for(brightness = 0; brightness < 256; brightness++){
//      noInterrupts();
      setColorAll(x, 255 - brightness, red);
      setColorAll(49-x, 255 - brightness, red);
//      interrupts();
    }
  }
  
  fillColorAll(0, lightCount, defaultIntensity, black);
  
  for(int x = 0; x < 25; x++){                                                      //FADE UP TREE ORANGE
    for(brightness = 0; brightness < 256; brightness++){
//      noInterrupts();
      setColorAll(x, brightness, orange);
      setColorAll(49-x, brightness, orange);
//      interrupts();
    }
  }
  brightness = 255;
  for(int x = 0; x < 25; x++){
    for(brightness = 0; brightness < 256; brightness++){
//      noInterrupts();
      setColorAll(x, 255 - brightness, orange);
      setColorAll(49-x, 255 - brightness, orange);
//      interrupts();
    }
  }
  
  fillColorAll(0, lightCount, defaultIntensity, black);
  
  for(int x = 0; x < 25; x++){                                                      //FADE UP TREE YELLOW
    for(brightness = 0; brightness < 256; brightness++){
//      noInterrupts();
      setColorAll(x, brightness, yellow);
      setColorAll(49-x, brightness, yellow);
//      interrupts();
    }
  }
  brightness = 255;
  for(int x = 0; x < 25; x++){
    for(brightness = 0; brightness < 256; brightness++){
//      noInterrupts();
      setColorAll(x, 255 - brightness, yellow);
      setColorAll(49-x, 255 - brightness, yellow);
//      interrupts();
    }
  }
  
  fillColorAll(0, lightCount, defaultIntensity, black);
  
  for(int x = 0; x < 25; x++){                                                      //FADE UP TREE GREEN
    for(brightness = 0; brightness < 256; brightness++){
//      noInterrupts();
      setColorAll(x, brightness, green);
      setColorAll(49-x, brightness, green);
//      interrupts();
    }
  }
  brightness = 255;
  for(int x = 0; x < 25; x++){
    for(brightness = 0; brightness < 256; brightness++){
//      noInterrupts();
      setColorAll(x, 255 - brightness, green);
      setColorAll(49-x, 255 - brightness, green);
//      interrupts();
    }
  }
  
  fillColorAll(0, lightCount, defaultIntensity, black);
  
  for(int x = 0; x < 25; x++){                                                      //FADE UP TREE BLUE
    for(brightness = 0; brightness < 256; brightness++){
//      noInterrupts();
      setColorAll(x, brightness, blue);
      setColorAll(49-x, brightness, blue);
//      interrupts();
    }
  }
  brightness = 255;
  for(int x = 0; x < 25; x++){
    for(brightness = 0; brightness < 256; brightness++){
//      noInterrupts();
      setColorAll(x, 255 - brightness, blue);
      setColorAll(49-x, 255 - brightness, blue);
//      interrupts();
    }
  }
  
  fillColorAll(0, lightCount, defaultIntensity, black);
  
  for(int x = 0; x < 25; x++){                                                      //FADE UP TREE PURPLE
    for(brightness = 0; brightness < 256; brightness++){
//      noInterrupts();
      setColorAll(x, brightness, purple);
      setColorAll(49-x, brightness, purple);
//      interrupts();
    }
  }
  brightness = 255;
  for(int x = 0; x < 25; x++){
    for(brightness = 0; brightness < 256; brightness++){
//      noInterrupts();
      setColorAll(x, 255 - brightness, purple);
      setColorAll(49-x, 255 - brightness, purple);
//      interrupts();
    }
  }

  fillColorAll(0, lightCount, defaultIntensity, black);

  rotateCW(pink, black, black, black, 100, 2);                                      //ROTATE DIFFERENT COLORS AROUND TREE CW & CCW
  rotateCW(red, black, black, black, 100, 2);
  rotateCCW(orange, black, black, black, 100, 2);
  rotateCW(yellow, black, black, black, 100, 2);
  rotateCCW(green, black, black, black, 100, 2);
  rotateCW(teal, black, black, black, 100, 2);
  rotateCCW(blue, black, black, black, 100, 2);
  rotateCW(purple, black, black, black, 100, 2);
  rotateCCW(white, black, black, black, 100, 2);
  rotateCCW(magenta, black, black, black, 100, 2);
  rotateCW(red, white, green, white, 100, 20);
  rotateCCW(red, white, green, white, 100, 20);
  
  fillColorAll(0, lightCount, defaultIntensity, black);
  
  for(int y = 0; y < 900; y++){                                                     //COLOR SWIRL UP TREE (COOL!!!)
    for(int x = 0; x < 25; x++){
//      noInterrupts();
      setColorAll(x, 200, rgb[(x+y)%90]);
      setColorAll(49-x, 200, rgb[(x+y)%90]);
//      interrupts();
    }
  }
  
//  fireworkColor(red);
//  delay(500);
//  fireworkColorSpan(0, 16);                                                         //FIREWORKS
//  delay(500);
  fireworkRgb();
  delay(500);
//  fireworkColor(blue);
//  delay(500);
//  fireworkColorSpan(24, 16);
//  delay(500);
  fireworkRgb();
  delay(500);
//  fireworkColor(yellow);
//  delay(500);
//  fireworkColorSpan(61, 16);
//  delay(500);
  fireworkRgb();
  delay(500);
//  fireworkColor(orange);
//  delay(500);
//  fireworkRgb();
//  delay(500);
//  fireworkColor(purple);
//  delay(500);
//  fireworkRgb();
//  delay(500);
//  fireworkColor(green);
//  delay(500);
//  fireworkRgb();
//  delay(500);
  
  fillColorAll(0, lightCount, 200, black);
  
  for(int x = 0; x < 300; x++){                                                     //STAGGERED GLOWING EFFECT RED
//    noInterrupts();
    while(y < lightCount){
      value = (x+y)%30;
      value2 = (x+y+12)%30;
      setColorOdd(y, defaultIntensity, redFade[value]);
      setColorEven(y, defaultIntensity, redFade[value2]);
      y++;
    }
//    interrupts();
    y = 0;
  }
  
  for(int x = 0; x < 300; x++){                                                     //STAGGERED GLOWING EFFECT WHITE
//    noInterrupts();
    while(y < lightCount){
      value = (x+y)%30;
      value2 = (x+y+12)%30;
      setColorOdd(y, defaultIntensity, whiteFade[value]);
      setColorEven(y, defaultIntensity, whiteFade[value2]);
      y++;
    }
//    interrupts();
    y = 0;
  }
  
  for(int x = 0; x < 300; x++){                                                     //STAGGERED GLOWING EFFECT GREEN
//    noInterrupts();
    while(y < lightCount){
      value = (x+y)%30;
      value2 = (x+y+12)%30;
      setColorOdd(y, defaultIntensity, greenFade[value]);
      setColorEven(y, defaultIntensity, greenFade[value2]);
      y++;
    }
//    interrupts();
    y = 0;
  }
  
  for(int x = 0; x < 300; x++){                                                     //STAGGERED GLOWING EFFECT WHITE
//    noInterrupts();
    while(y < lightCount){
      value = (x+y)%30;
      value2 = (x+y+12)%30;
      setColorOdd(y, defaultIntensity, whiteFade[value]);
      setColorEven(y, defaultIntensity, whiteFade[value2]);
      y++;
    }
//    interrupts();
    y = 0;
  }
  
  for(int y = 0; y < 150; y++){                                                     //GLOWING EFFECT UP TREE RED
    for(int x = 0; x < 25; x++){
//      noInterrupts();
      setColorAll(x, defaultIntensity, redFade[(x+y)%30]);
      setColorAll(49-x, defaultIntensity, redFade[(x+y)%30]);
//      interrupts();
    }
  }
  
  for(int y = 0; y < 150; y++){                                                     //GLOWING EFFECT UP TREE YELLOW
    for(int x = 0; x < 25; x++){
//      noInterrupts();
      setColorAll(x, defaultIntensity, yellowFade[(x+y)%30]);
      setColorAll(49-x, defaultIntensity, yellowFade[(x+y)%30]);
//      interrupts();
    }
  }
  
  for(int y = 0; y < 150; y++){                                                     //GLOWING EFFECT UP TREE GREEN
    for(int x = 0; x < 25; x++){
//      noInterrupts();
      setColorAll(x, defaultIntensity, greenFade[(x+y)%30]);
      setColorAll(49-x, defaultIntensity, greenFade[(x+y)%30]);
//      interrupts();
    }
  }
  
  for(int y = 0; y < 150; y++){                                                     //GLOWING EFFECT UP TREE TEAL
    for(int x = 0; x < 25; x++){
//      noInterrupts();
      setColorAll(x, defaultIntensity, tealFade[(x+y)%30]);
      setColorAll(49-x, defaultIntensity, tealFade[(x+y)%30]);
//      interrupts();
    }
  }
  
  for(int y = 0; y < 150; y++){                                                     //GLOWING EFFECT UP TREE BLUE
    for(int x = 0; x < 25; x++){
//      noInterrupts();
      setColorAll(x, defaultIntensity, blueFade[(x+y)%30]);
      setColorAll(49-x, defaultIntensity, blueFade[(x+y)%30]);
//      interrupts();
    }
  }
  
  for(int y = 0; y < 150; y++){                                                     //GLOWING EFFECT UP TREE MAGENTA
    for(int x = 0; x < 25; x++){
//      noInterrupts();
      setColorAll(x, defaultIntensity, magentaFade[(x+y)%30]);
      setColorAll(49-x, defaultIntensity, magentaFade[(x+y)%30]);
//      interrupts();
    }
  }

/*  for(int y = 50; y < 256; y++){                                                  //change in intensity for glow effect (DOESN'T WORK WELL)
//    noInterrupts();
    fillColorAll(0, lightCount, y, red);
//    interrupts();
  }
  for(int y = 255; y > 50; y--){
//    noInterrupts();
    fillColorAll(0, lightCount, y, red);
//    interrupts();
  }
 
  fillColorAll(0, lightCount, defaultIntensity, black);
*/  
}
