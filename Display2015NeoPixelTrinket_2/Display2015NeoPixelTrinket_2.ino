#include <avr/power.h>
#include <Adafruit_NeoPixel.h>

#define outPin 0
#define defaultBrightness 150
#define fadeAmount 3
#define delayTime 3


Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, outPin, NEO_GRB + NEO_KHZ800);

void setup(){
  
  if (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  
  pinMode(outPin, OUTPUT);
  
  delay(500);
  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(defaultBrightness);
  
}
/*
void colorWipe(uint32_t color, uint8_t wait){
  for (byte i = 0; i < strip.numPixels(); i++){
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}
*/
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

void saberColor2(byte r, byte g, byte b){
  
  long colorArray2[6] = {strip.Color(r, g, b), strip.Color(r-20 < 0 ? 0 : r-50, g-50 < 0 ? 0 : g-50, b-50 < 0 ? 0 : b-50), strip.Color(r-75 < 0 ? 0 : r-75, g-75 < 0 ? 0 : g-75, b-75 < 0 ? 0 : b-75),
                         strip.Color(r-90 < 0 ? 0 : r-90, g-90 < 0 ? 0 : g-90, b-90 < 0 ? 0 : b-90), strip.Color(r-75 < 0 ? 0 : r-75, g-75 < 0 ? 0 : g-75, b-75 < 0 ? 0 : b-75),
                         strip.Color(r-40 < 0 ? 0 : r-50, g-50 < 0 ? 0 : g-50, b-50 < 0 ? 0 : b-50)};
  
  for (byte i = 0; i < strip.numPixels(); i++){
    strip.setPixelColor(i, colorArray2[i%6]);
    strip.show();
    delay(delayTime);
  }
  
  for (int x = 0; x < 200; x++){
    for (byte i = 0; i < strip.numPixels(); i++){
      uint32_t color = colorArray2[(i+x)%6];
      strip.setPixelColor(i, color);
      //strip.show();
    }
    strip.show();
    delay(100);
  }
  
  for (byte i = 0; i < strip.numPixels(); i++){
    strip.setPixelColor(strip.numPixels()-i-1, strip.Color(0, 0, 0));
    strip.show();
    delay(delayTime);
  }
  
}

void candyCane(){
  const long colorArray[6] = {strip.Color(255, 255, 255), strip.Color(255, 255, 255), strip.Color(255, 255, 255), strip.Color(255, 0, 0), strip.Color(255, 0, 0), strip.Color(255, 0, 0)};
  strip.setBrightness(defaultBrightness);
  for (int x = 0; x < 500; x++){
    for (byte i = 0; i < strip.numPixels(); i++){
      uint32_t color = colorArray[(i+x)%6];
      strip.setPixelColor(i, color);
      //strip.show();
    }
    strip.show();
    delay(50);
  }
  for (byte i = 0; i < strip.numPixels(); i++){
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    strip.show();
  }
  delay(500);
}

void rainbow(){
  for (byte i = 0; i < strip.numPixels(); i++) strip.setPixelColor(i, strip.Color(255, 0, 0));
  strip.show();
  for (int x = 0; x < 256; x++){
    for (byte i = 0; i < strip.numPixels(); i++){
      strip.setPixelColor(i, strip.Color(255, x, 0));
      strip.show();
    }
    //delay(10);
  }
  for (int x = 0; x < 256; x++){
    for (byte i = 0; i < strip.numPixels(); i++){
      strip.setPixelColor(i, strip.Color(255-x, 255, 0));
      strip.show();
    }
    //delay(10);
  }
  for (int x = 0; x < 256; x++){
    for (byte i = 0; i < strip.numPixels(); i++){
      strip.setPixelColor(i, strip.Color(0, 255-x, x));
      strip.show();
    }
    //delay(10);
  }
  for (int x = 0; x < 256; x++){
    for (byte i = 0; i < strip.numPixels(); i++){
      strip.setPixelColor(i, strip.Color(x, 0, 255));
      strip.show();
    }
    //delay(10);
  }
  for (int x = 0; x < 256; x++){
    for (byte i = 0; i < strip.numPixels(); i++){
      strip.setPixelColor(i, strip.Color(255, 0, 255-x));
      strip.show();
    }
    //delay(10);
  }
  
}
  

void loop(){
  
/*  saberColor(0, 255, 0);
  candyCane();
  saberColor(0, 0, 255);
  candyCane();
  saberColor(125, 0, 255);
  candyCane();
//  saberColor(strip.Color(255, 255, 0));
//  candyCane();
  saberColor(255, 0, 0);
  candyCane();
  */
  
//  strip.setBrightness(200);
  
/*  saberColor2(200, 0, 0);
  saberColor2(0, 200, 0);
  saberColor2(0, 0, 200);
  saberColor2(125, 0, 200);
  */
  
  rainbow();            
  
}
