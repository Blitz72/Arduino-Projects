#include "ST7565.h"

int ledPin =  13;    // LED connected to digital pin 13

// the LCD backlight is connected up to a pin so you can turn it on & off
#define BACKLIGHT_LED 10

// pin 9 - Serial data out (SID)
// pin 8 - Serial clock out (SCLK)
// pin 7 - Data/Command select (RS or A0)
// pin 6 - LCD reset (RST)
// pin 5 - LCD chip select (CS)
ST7565 glcd(9, 8, 7, 6, 5);

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
#define TIE_HEIGHT 64
#define TIE_WIDTH 128

// a bitmap of a 16x16 fruit icon
static unsigned char __attribute__ ((progmem)) logo16_glcd_bmp[]={
0x40, 0xc0, 0xe0, 0xe0, 0xe0, 0x60, 0x70, 0xfe, 0x9f, 0xfe, 0x70, 0x60, 0xe0, 0xe0, 0xe0, 0x60, 
0x00, 0x00, 0x00, 0x61, 0x7b, 0x3f, 0x1f, 0x09, 0x0f, 0x0d, 0x1b, 0x3f, 0x7f, 0x71, 0x00, 0x00, };

static unsigned char __attribute__ ((progmem)) TIE_bmp[]={
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,            //it works but image is upside down and reversed!
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x80, 0x80, 0x40, 0xa0, 0xa0, 0x50, 0x28, 0x28, 0x28, 0x28, 0x50, 0x50, 0xd0, 0x20, 0xa0, 0x60,
0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x1e, 0xe2, 0x1a, 0x74,
0x54, 0x94, 0xa8, 0xa8, 0x28, 0x50, 0x50, 0xb0, 0x60, 0xa0, 0x20, 0x40, 0x40, 0x40, 0x80, 0x80,
0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x30, 0xa8, 0xa8, 0xa4, 0x5a, 0x55,
0x52, 0x52, 0xa1, 0xa0, 0xa0, 0xa0, 0x40, 0xb0, 0x48, 0x34, 0xca, 0xb5, 0x8a, 0x85, 0x82, 0x01,
0x01, 0x01, 0x01, 0x81, 0x82, 0x42, 0x42, 0x42, 0x45, 0x45, 0x45, 0x8a, 0x8a, 0xff, 0x01, 0xfd,
0x05, 0x0a, 0x0a, 0x0a, 0x15, 0x15, 0x15, 0x2a, 0x2b, 0xa8, 0x53, 0x54, 0x9b, 0x95, 0x2a, 0xaa,      //0xa8 may be 0xab
0xaa, 0x52, 0x55, 0x55, 0xa5, 0xa5, 0xaa, 0x4a, 0x4a, 0x54, 0x94, 0x94, 0xa8, 0xa8, 0x50, 0x50,
0xa0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x27, 0x24, 0x25, 0x25, 0x48, 0x49, 0xcd,
0x4d, 0x95, 0xf6, 0x9e, 0xe3, 0x9d, 0xe3, 0x15, 0x9b, 0x8d, 0x4a, 0xc6, 0x06, 0x02, 0xf2, 0x8f,
0xd6, 0x23, 0xbb, 0x26, 0xd2, 0x8c, 0x88, 0xf0, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x03, 0xfc, 0x03,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1f, 0xe0, 0x1f, 0x00, 0x00, 0xc1, 0x3e,
0xc1, 0x3f, 0x01, 0x01, 0x02, 0x02, 0x02, 0x05, 0x05, 0x05, 0x0a, 0x0a, 0x0a, 0x0a, 0x15, 0x15,
0x15, 0x2a, 0x2a, 0x29, 0x52, 0x54, 0xd8, 0x10, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x62, 0xda, 0x5a, 0x52, 0xa4, 0xa4, 0xa4, 0xa5,
0x4a, 0x4a, 0x5f, 0x20, 0x5f, 0xa1, 0xff, 0xb8, 0xb9, 0x51, 0x32, 0x13, 0x20, 0x20, 0x27, 0x48,
0x75, 0xe2, 0x3e, 0x22, 0x25, 0x18, 0x08, 0x07, 0x00, 0x00, 0x00, 0xe0, 0x1f, 0xe8, 0x2b, 0x54,
0x54, 0x54, 0x54, 0x54, 0xa8, 0xa8, 0xa8, 0xa8, 0x53, 0x54, 0x5b, 0x44, 0x88, 0x88, 0xa7, 0xb0,
0x4f, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1f, 0xe0, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x0a, 0x36, 0x4a, 0xb2,
0x45, 0x85, 0x85, 0x85, 0x8a, 0x8a, 0x33, 0xce, 0x32, 0xc4, 0x34, 0xd4, 0x14, 0x28, 0x28, 0x28,
0x28, 0x50, 0x51, 0x52, 0x52, 0xa4, 0xa4, 0xa4, 0xa4, 0xf4, 0x1e, 0xe1, 0x1e, 0x01, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x80, 0x60, 0x90, 0x6c, 0x93, 0x6c, 0x12, 0x0d, 0x02, 0x02, 0x02, 0x02,
0x05, 0x05, 0x05, 0x05, 0x05, 0x0a, 0x0a, 0x0a, 0x0a, 0x15, 0x15, 0x15, 0x15, 0x2a, 0x2a, 0x2a,
0x2a, 0x54, 0xd4, 0x54, 0x14, 0xaf, 0x60, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x05, 0x05, 0x05, 0x04, 0x07, 0x04, 0x0b, 0x0a, 0x0a, 0x0a,
0x0a, 0x0a, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x2e, 0x2d, 0x2c, 0x2d, 0x2d, 0x2d, 0x5a, 0x5a,
0x5a, 0x5a, 0x8a, 0x7b, 0x14, 0x13, 0x14, 0x17, 0x14, 0x14, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0x50, 0x28, 0x14, 0x14,
0x0a, 0x05, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,};


// The setup() method runs once, when the sketch starts
void setup()   {                
  Serial.begin(9600);

  Serial.print(freeRam());
  
  // turn on backlight
  pinMode(BACKLIGHT_LED, OUTPUT);
  digitalWrite(BACKLIGHT_LED, HIGH);

  // initialize and set the contrast to 0x18
  glcd.begin(0x18);

//while(1){
  glcd.display(); // show splashscreen
  delay(2000);
  glcd.clear();
//}
  // draw a single pixel
  glcd.setpixel(10, 10, BLACK);
  glcd.display();        // show the changes to the buffer
  delay(2000);
  glcd.clear();


  for (byte y = 0; y < 64; y++) {
    for (byte x = 0; x < 128; x++){
      if (x % 5 == 0 && y % 5 == 0){
        glcd.setpixel(x, y, BLACK);
      }
    }
  }
  glcd.display();
  delay(2000);
  glcd.clear();
  
  // draw many lines
  testdrawline();
  glcd.display();       // show the lines
  delay(2000);
  glcd.clear();

  // draw rectangles
  testdrawrect();
  glcd.display();
  delay(2000);
  glcd.clear();

  // draw multiple rectangles
  testfillrect();
  glcd.display();
  delay(2000);
  glcd.clear();

  // draw mulitple circles
  testdrawcircle();
  glcd.display();
  delay(2000);
  glcd.clear();

  // draw a black circle, 10 pixel radius, at location (32,32)
  glcd.fillcircle(32, 32, 10, BLACK);
  glcd.display();
  delay(2000);
  glcd.clear();

  // draw the first ~120 characters in the font
  testdrawchar();
  glcd.display();
  delay(2000);
  glcd.clear();

  // draw a string at location (0,0)
  glcd.drawstring(0, 0, "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation");
  glcd.display();
  delay(2000);
  glcd.clear();

while(1){
  glcd.drawbitmap(0, 0, TIE_bmp, TIE_WIDTH, TIE_HEIGHT, BLACK);
  glcd.display();
  delay(10000);
  glcd.clear();
}

  // draw a bitmap icon and 'animate' movement
//  testdrawbitmap(logo16_glcd_bmp, LOGO16_GLCD_HEIGHT, LOGO16_GLCD_WIDTH);
}


void loop()                     
{}

// this handy function will return the number of bytes currently free in RAM, great for debugging!   
int freeRam(void)
{
  extern int  __bss_end; 
  extern int  *__brkval; 
  int free_memory; 
  if((int)__brkval == 0) {
    free_memory = ((int)&free_memory) - ((int)&__bss_end); 
  }
  else {
    free_memory = ((int)&free_memory) - ((int)__brkval); 
  }
  return free_memory; 
} 


#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

void testdrawbitmap(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  uint8_t icons[NUMFLAKES][3];
  srandom(666);     // whatever seed
 
  // initialize
  for (uint8_t f=0; f< NUMFLAKES; f++) {
    icons[f][XPOS] = random() % 128;
    icons[f][YPOS] = 0;
    icons[f][DELTAY] = random() % 5 + 1;
  }

  while (1) {
    // draw each icon
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      glcd.drawbitmap(icons[f][XPOS], icons[f][YPOS], logo16_glcd_bmp, w, h, BLACK);
    }
    glcd.display();
    delay(200);
    
    // then erase it + move it
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      glcd.drawbitmap(icons[f][XPOS], icons[f][YPOS],  logo16_glcd_bmp, w, h, 0);
      // move it
      icons[f][YPOS] += icons[f][DELTAY];
      // if its gone, reinit
      if (icons[f][YPOS] > 64) {
	icons[f][XPOS] = random() % 128;
	icons[f][YPOS] = 0;
	icons[f][DELTAY] = random() % 5 + 1;
      }
    }
  }
}


void testdrawchar(void) {
  for (uint8_t i=0; i < 168; i++) {
    glcd.drawchar((i % 21) * 6, i/21, i);
  }    
}

void testdrawcircle(void) {
  for (uint8_t i=0; i<64; i+=2) {
    glcd.drawcircle(63, 31, i, BLACK);
  }
}


void testdrawrect(void) {
  for (uint8_t i=0; i<64; i+=2) {
    glcd.drawrect(i, i, 128-i, 64-i, BLACK);
  }
}

void testfillrect(void) {
  for (uint8_t i=0; i<64; i++) {
      // alternate colors for moire effect
    glcd.fillrect(i, i, 128-i, 64-i, i%2);
  }
}

void testdrawline() {
  for (uint8_t i=0; i<128; i+=4) {
    glcd.drawline(0, 0, i, 63, BLACK);
  }
  for (uint8_t i=0; i<64; i+=4) {
    glcd.drawline(0, 0, 127, i, BLACK);
  }

  glcd.display();
  delay(1000);

  for (uint8_t i=0; i<128; i+=4) {
    glcd.drawline(i, 63, 0, 0, WHITE);
  }
  for (uint8_t i=0; i<64; i+=4) {
    glcd.drawline(127, i, 0, 0, WHITE);
  }
}
