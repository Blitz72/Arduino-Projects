#include <Adafruit_NeoPixel.h>

#define pixelPin 3
#define SSRPin1 5
#define SSRPin2 6
#define pixels 300  //two strings of 5 meters each with 30 pixels per meter

byte brightness = 150;
byte stripBrightness = 255;
byte fadeAmount = 4;
boolean timeout = false;
boolean triggered = false;
int debounceDelay = 50;
long timerStart = 0;
long timerMax = 45000;
long previousMillis = 0;
byte charVal = B01110010;

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(pixels, pixelPin, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  delay(5000);  //allow Xbee radio to settle
  timerStart = millis();
  strip.setBrightness(stripBrightness);
  pinMode(SSRPin1, OUTPUT);
  pinMode(SSRPin2, OUTPUT);
  //triggered = true;  //comment out for Xbee operation
}

void loop() {
  
  if (Serial.available()){
    byte ch = Serial.read();
    if (ch == charVal) {
      triggered = true;
      timeout = false;
      timerStart = millis();
    }
    else triggered = false;
  }
  
  if ((triggered) && (!timeout)) {
    if (millis() - timerStart < 500) {
      for(uint8_t i=0; i<10; i++){
        for(uint16_t i=0; i<strip.numPixels(); i++){
          if ((i%3) == 0) strip.setPixelColor(i, strip.Color(0, 0, 255));
          else strip.setPixelColor(i, strip.Color(150, 150, 150));
        }
        strip.show();
        digitalWrite(SSRPin1, HIGH);
        digitalWrite(SSRPin2, LOW);
        delay(random(50, 100));
        for(uint16_t i=0; i<strip.numPixels(); i++){
          strip.setPixelColor(i, strip.Color(0, 0, 0));
        }
        strip.show();
        digitalWrite(SSRPin1, LOW);
        digitalWrite(SSRPin2, HIGH);
        delay(random(50, 200));
      }
    }
  }
    //Fade section
/*  if (triggered && !timeout) {
    for(uint16_t i=0; i<strip.numPixels(); i++){
      if ((i%3) == 0) strip.setPixelColor(i, strip.Color(0, 0, 255-brightness));
      else strip.setPixelColor(i, strip.Color(150-brightness, 150-brightness, 150-brightness));
    }
    strip.show();
    delay(10);
    if ((brightness == 0) || (brightness == 120)) fadeAmount = -fadeAmount;
    brightness = brightness - fadeAmount;
  }*/
  
  
  if (triggered && !timeout){
    digitalWrite(SSRPin1, HIGH);
    digitalWrite(SSRPin2, HIGH);
    colorWipeTest(strip.Color(brightness, brightness, brightness), 0);
    for (int x=stripBrightness; x >= 0; x-=5){
      for (int i = 0; i < strip.numPixels(); i++){
        strip.setBrightness(x);
      }
      strip.show();
      //delay(5);
    }
    
    //delay(50);
    brightness = 150;
    strip.setBrightness(stripBrightness);
  }

  if (millis() - timerStart > timerMax) {
    timeout = true;
    triggered = false;
    for(uint16_t i=0; i<strip.numPixels(); i++){
      strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show();
    digitalWrite(SSRPin1, LOW);
    digitalWrite(SSRPin2, LOW);
  }
  
  if (triggered == false) {
    digitalWrite(SSRPin1, LOW);
    digitalWrite(SSRPin2, LOW);
  }
}


//-------------------Functions------------------------------------------------------------



// Fill the dots one after the other with a color
void colorWipeTest(uint32_t c, uint8_t wait) {
  for(uint16_t i=78; i<strip.numPixels()/2; i+=2) {
    if ((i%4) == 0) strip.setPixelColor(i, strip.Color(0, 0, 255));
    else strip.setPixelColor(i, c);
    if (((strip.numPixels()-1-i) % 3) == 0) strip.setPixelColor((strip.numPixels()-1-i), strip.Color(0, 0, 255));
    else strip.setPixelColor(strip.numPixels()-1-i, c);
      strip.show();
      delay(wait);
  }
}

/*void rainbow(uint8_t wait) {
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

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}*/

