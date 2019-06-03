/*Based on Christmas Light Control by  Robert Quattlebaum <darco@deepdarc.com>
           Released November 27th, 2010
           <http://www.deepdarc.com/2010/11/27/hacking-christmas-lights/>
           
           Original C code by Robert Quattlebaum developed to run on an ATTiny13
           
           This version is meant to run on an Arduino Mega 2560 Rev. 3.
           The setup is 16, 50 light GE G35 strings. Each string's data line is
           connected to the PORTC and PORTL pins on the two row header on the
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
#define lightCount      50
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

}
