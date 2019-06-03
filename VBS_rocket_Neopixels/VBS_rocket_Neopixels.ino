#include <avr/power.h>
#include <Adafruit_NeoPixel.h>

#define inPin 4
#define outPin 9
#define defaultBrightness 255
#define fadeAmount 3
#define delayTime 3

Adafruit_NeoPixel strip = Adafruit_NeoPixel(300, outPin, NEO_GRB + NEO_KHZ800);

const long colorArray1[6] = {strip.Color(255, 255, 255), strip.Color(100, 100, 255), strip.Color(50, 50, 255), strip.Color(25, 25, 255), strip.Color(50, 50, 255), strip.Color(100, 100, 255)};                             

const long colorArray2[20] = {strip.Color(255, 0, 0), strip.Color(255, 25, 0), strip.Color(255, 50, 0), strip.Color(255, 75, 0), strip.Color(255, 100, 0), strip.Color(255, 125, 0), 
                              strip.Color(255, 150, 0), strip.Color(255, 175, 0), strip.Color(255, 200, 0), strip.Color(255, 225, 0), strip.Color(255, 255, 0), strip.Color(255, 225, 0), 
                              strip.Color(255, 200, 0), strip.Color(255, 175, 0), strip.Color(255, 150, 0), strip.Color(255, 125, 0), strip.Color(255, 100, 0), strip.Color(255, 75, 0), 
                              strip.Color(255, 50, 0), strip.Color(255, 25, 0)};


void setup(){
  pinMode(outPin, OUTPUT);
  
  delay(500);
  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(defaultBrightness);
  
}

/*
void saberColor(byte r, byte g, byte b){
//  byte fadeAmount = 3;
//  byte delayTime = 3;
  for (byte i = 0; i < strip.numPixels(); i++){
    strip.setPixelColor(i, strip.Color(r, g, b));
    strip.show();
    delay(delayTime);
  }
  byte brightness = defaultBrightness;
  
  for(byte x = 0; x < 4; x++){
    for (byte i = 0; i < 20; i++){
      strip.setBrightness(brightness += fadeAmount);
      strip.show();
      delay(25);
    }
//    strip.setBrightness(255);
//    strip.show();
//    delay(10);
//    strip.setBrightness(defaultBrightness);
    for (byte i = 0; i < 40; i++){
      strip.setBrightness(brightness -= fadeAmount);
      strip.show();
      delay(25);
    }
    for (byte i = 0; i < 20; i++){
      strip.setBrightness(brightness += fadeAmount);
      strip.show();
      delay(25);
    }
    strip.setBrightness(defaultBrightness);
    for (byte i = 0; i < 20; i++){
      strip.setBrightness(brightness += fadeAmount);
      strip.show();
      delay(25);
    }
//    strip.setBrightness(255);
//    strip.show();
//    delay(20);
//    strip.setBrightness(defaultBrightness);
    for (byte i = 0; i < 40; i++){
      strip.setBrightness(brightness -= fadeAmount);
      strip.show();
      delay(25);
    }
    for (byte i = 0; i < 20; i++){
      strip.setBrightness(brightness += fadeAmount);
      strip.show();
      delay(25);
    }
  }
  
  for (byte i = 0; i < strip.numPixels(); i++){
    strip.setPixelColor(strip.numPixels()-i-1, strip.Color(0, 0, 0));
    strip.show();
    delay(delayTime);
  }
  strip.setBrightness(defaultBrightness);
  delay(500);
}
*/

void exhaustColor(){
  int x = defaultBrightness;
  strip.setBrightness(defaultBrightness);
  delay(4000);  //ignition starts 4 seconds into launch sequence
  //ignition sequence (blue/white color); needs to be about 5 to 6 seconds
  for (int x = 0; x < 50; x++){
    for (byte i = 0; i < strip.numPixels(); i++){
      uint32_t color = colorArray1[(i+x)%6];
      strip.setPixelColor(i, color);
      //strip.show();
    }
    strip.show();
    delay(33);
  }
  //liftoff sequence (red/orange/yellow color); should start 10 sec into launch sequence
  for (int x = 0; x < 100; x++){
    for (byte i = 0; i < strip.numPixels(); i++){
      uint32_t color = colorArray2[(i+x)%20];
      strip.setPixelColor(i, color);
      //strip.show();
    }
    strip.show();
    delay(33);
  }
  for (byte i = 0; i < strip.numPixels(); i++){
    strip.setPixelColor(i, strip.Color(255, 125, 0));
    //strip.show();
  }
  strip.show();
  while(x){
    strip.setBrightness(x);
    strip.show();
    x -= 5;
  }
    
}
  

void loop(){
  if(digitalRead(inPin == LOW)){
    exhaustColor();
  }
  
}
