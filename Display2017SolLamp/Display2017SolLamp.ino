#include <Adafruit_NeoPixel.h>

#define outerPin 8                                //outer ring of Sol lamp
#define innerPin 9                                //inner ring of Sol lamp
#define outerPixelCount 176
#define innerPixelCount 158
#define colorTemp2K outer.Color(255, 137, 14)
#define colorTemp5K outer.Color(255, 255, 255)
#define colorTeal inner.Color(20, 255, 255)
#define colorRed inner.Color(255, 0, 0)
#define colorOrange inner.Color(255, 100, 0)
#define defaultBrightness 100

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel outer = Adafruit_NeoPixel(outerPixelCount, outerPin, NEO_GRB + NEO_KHZ800);    //outer ring of Sol lamp
Adafruit_NeoPixel inner = Adafruit_NeoPixel(innerPixelCount, innerPin, NEO_GRB + NEO_KHZ800);    //inner ring of Sol lamp

/*
uint32_t colorTemp2K[] = {outer.Color(0, 0, 0), outer.Color(32, 17, 1), outer.Color(64, 34, 2), outer.Color(96, 51, 4), outer.Color(128, 68, 6),
                          outer.Color(160, 85, 8), outer.Color(192, 102, 10), outer.Color(224, 119, 12), outer.Color(255, 137, 14)};

uint32_t colorTemp5K[] = {outer.Color(0, 0, 0), outer.Color(32, 32, 32), outer.Color(64, 64, 64), outer.Color(96, 96, 96), outer.Color(128, 128, 128),
                          outer.Color(160, 160, 160),outer.Color(192, 192, 192), outer.Color(224, 224, 224), outer.Color(255, 255, 255)};

uint32_t colorTeal[] = {inner.Color(0, 0, 0), inner.Color(0, 32, 32), inner.Color(0, 64, 64), inner.Color(0, 96, 96), inner.Color(0, 128, 128),
                        inner.Color(0, 160, 160),inner.Color(0, 192, 192), inner.Color(0, 224, 224), inner.Color(0, 255, 255)};

uint32_t colorRed[] = {inner.Color(0, 0, 0), inner.Color(32, 0, 0), inner.Color(64, 0, 0), inner.Color(96, 0, 0), inner.Color(128, 0, 0),
                        inner.Color(160, 0, 0),inner.Color(192, 0, 0), inner.Color(224, 0, 0), inner.Color(255, 0, 0)};
*/

uint32_t orangeBar[] = {inner.Color(0, 0, 0), inner.Color(85, 33, 0), inner.Color(170, 67, 0), colorOrange, colorOrange, colorOrange, colorOrange, colorOrange, colorOrange, colorOrange,
                        colorOrange, colorOrange, colorOrange, colorOrange, colorOrange, colorOrange, colorOrange, inner.Color(170, 67, 0), inner.Color(85, 33, 0), inner.Color(0, 0, 0)};

uint32_t tealBar[] = {inner.Color(0, 0, 0), inner.Color(7, 85, 85), inner.Color(14, 170, 170), colorTeal, colorTeal, colorTeal, colorTeal, colorTeal, colorTeal, colorTeal,
                        colorTeal, colorTeal, colorTeal, colorTeal, colorTeal, colorTeal, colorTeal, inner.Color(14, 170, 170), inner.Color(7, 85, 85), inner.Color(0, 0, 0)};
                        
uint16_t brightness = 0;
uint16_t dBrightness = 0;
boolean isSolOn = false;
boolean setTimer = false;
int16_t innerOffset = 1;
int16_t outerOffset = 0;

void setup() {
  Serial.begin(9600);
  outer.begin();
  outer.show(); // Initialize all pixels to 'off'
  inner.begin();
  inner.show(); // Initialize all pixels to 'off'

  inner.setBrightness(255);
  outer.setBrightness(255);

}

void loop() {
  
  blankInner();
  blankOuter();

  //available funcions:
  //'a' = turn Sol On/Off 5K
  //'b' = turn Sol On/Off 2K
  //'c' = dim Sol
  //'d' = timer function

  sol5KOn();
  for(int i = 0; i < 7; i++){
    rotateInnerCW();
  }
  blankInner();
  delay(2000);
  alexa('a');
  delay(3000);
  alexa('a');
  delay(3000);
  alexa('a');
  delay(3000);
  alexa('b');
  delay(3000);
  alexa('b');
  delay(3000);
  alexa('a');
  delay(2000);
  alexa('c');
  delay(2000);
  alexa('a');
  delay(3000);
  alexa('a');
  delay(2000);
  alexa('d');
  delay(2000);
  alexa('a');
  delay(3000);

}

void alexa(char functionName){
  int offset = 0;
  int wait = 12;
  dBrightness = 20;
  brightness = 255;
  inner.setBrightness(brightness);
  colorWipeInner(colorTeal);                                          //color wipe teal from both sides to meet at top
  delay(2000);
  Serial.println(functionName);                                       //perform requested function
  switch (functionName) {
    case 'a':
      sol5KOn();
      break;
    case 'b':
      sol2KOn();
      break;
    case 'c':
      dimSol();
      break;
    case 'd':
      setTimer = true;
      break;
  }
  delay(300);
  for(int i = 0; i < 180/dBrightness; i++){                           //ramp brightness down
    inner.setBrightness(brightness -= dBrightness);
    inner.show();
    delay(wait);
  }
  for(int i = 0; i < 180/dBrightness; i++){                           //ramp brightness up
    inner.setBrightness(brightness += dBrightness);
    inner.show();
    delay(wait);
  }
  for(int i = 0; i < 180/dBrightness; i++){                           //ramp brightness down
    inner.setBrightness(brightness -= dBrightness);
    inner.show();
    delay(wait);
  }
  for(int i = 0; i < 180/dBrightness; i++){                           //ramp brightness up
    inner.setBrightness(brightness += dBrightness);
    inner.show();
    delay(wait);
  }
  inner.setBrightness(255);
  for(int i = 0; i < inner.numPixels(); i++){                         //set inner ring to white
    inner.setPixelColor(i, colorTemp5K);
  }
  inner.show();
  delay(500);
  for(int i = 0; i < inner.numPixels(); i++){                         //set inner ring to teal
    inner.setPixelColor(i, colorTeal);
  }
  inner.show();
  colorWipeInnerReverse(inner.Color(0, 0, 0));
  if(setTimer){
    delay(500);
    timer(10);
    setTimer = false;
  }
}

void sol5KOn(){
  if (!isSolOn){
    for(int i = 0; i < outer.numPixels(); i++){
      outer.setPixelColor(i, colorTemp5K);
    }
    outer.show();
    isSolOn = true;
  } else {
    blankOuter();
    isSolOn = false;
  }
}

void sol2KOn(){
  if (!isSolOn){
    for(int i = 0; i < outer.numPixels(); i++){
      outer.setPixelColor(i, colorTemp2K);
    }
    outer.show();
    isSolOn = true;
  } else {
    blankOuter();
    isSolOn = false;
  }
}

void dimSol(){
  outer.setBrightness(90);
  for(int i = 0; i < outer.numPixels(); i++){
    outer.setPixelColor(i, colorTemp5K);
  }
  outer.show();
  outer.setBrightness(255);
}

void colorWipeOuter(uint32_t color){
  int wait = 0;
  for(int i = 0; i < outer.numPixels()/2; i++) {
    outer.setPixelColor(i, color);
    outer.setPixelColor(outer.numPixels()-(outerOffset)-i, color);
    outer.show();
    delay(wait);
  }
}

void colorWipeOuterReverse(uint32_t color){
  int wait = 0;
  for(int i = outer.numPixels()/2; i >= 0; i--) {
    outer.setPixelColor(i, color);
    outer.setPixelColor(outer.numPixels()-outerOffset-i, color);
    outer.show();
    delay(wait);
  }
  blankOuter();
}

void colorWipeInner(uint32_t color) {
  int wait = 0;
  for(int i = 0; i < inner.numPixels()/2; i++) {
    inner.setPixelColor(i, color);
    inner.setPixelColor(inner.numPixels()-(innerOffset)-i, color);
    inner.show();
    delay(wait);
  }
  inner.show();
}

void colorWipeInnerReverse(uint32_t color) {
  int wait = 0;
  for(int i = inner.numPixels()/2; i >= 0; i--) {
    inner.setPixelColor(i, color);
    inner.setPixelColor(inner.numPixels()-innerOffset-i, color);
    inner.show();
    delay(wait);
  }
  blankInner();
}

void blankOuter() {
  for(int i = 0; i < outer.numPixels() + outerOffset + 20; i++) {
    outer.setPixelColor(i, outer.Color(0, 0, 0));
  }
  outer.show();
}

void blankInner() {
  for(int i = 0; i < inner.numPixels() + innerOffset + 20; i++) {
    inner.setPixelColor(i, inner.Color(0, 0, 0));
  }
  inner.show();
}

void rotateInnerCW() {
  int offset = 0;
  int wait = 0;
  for(int i = 0; i < inner.numPixels()+25; i++) {
    inner.setPixelColor(i, inner.Color(255, 100, 0));
    inner.setPixelColor(i-20, inner.Color(0, 0, 0));
    inner.show();
    delay(wait);
  }
  inner.show();
}

void timer(uint16_t seconds){
  int offset = 8;
  int wait = 990;
  int value = (inner.numPixels()-offset*2)/seconds + 1;
//  for(int i = offset; i < value*seconds; i++){
//    inner.setPixelColor(i, colorTeal);
//  }
  inner.show();
  for(int i = seconds; i >= 0; i--){
    for(int j = offset; j < value*i; j++){
      inner.setPixelColor(j, colorTeal);
    }
    for(int k = value*i + offset; k < inner.numPixels(); k++){
      inner.setPixelColor(k, inner.Color(0, 0, 0));
    }
    inner.show();
    delay(wait);
  }
  blankInner();
}

/*
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
*/


