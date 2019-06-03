#include <LiquidCrystal.h>

#define COLOR(r,g,b) ((r)+((g)<<4)+((b)<<8))  //Color is 12-bit (4-bit each R, G, B)
#define black        COLOR(0,0,0)  
#define red          COLOR(0xf,0,0)  
#define green        COLOR(0,0xf,0)  
#define blue         COLOR(0,0,0xf)  
#define teal         COLOR(0,0xf,0xf)  
#define magenta      COLOR(0xf,0,0xf)
#define pink         COLOR(0xf,0x2,0xf)
#define yellow       COLOR(0xf,0xf,0)
#define purple       COLOR(0xa,0x0,0xf)
#define orange       COLOR(0xf,0x3,0x0)
#define warmWhite    COLOR(0xf,0x7,0x2)
#define white        COLOR(0xd, 0xd, 0xd)
#define lightCount   1  //need to change to 1 for single pixel test
#define defaultIntensity 0xcc

byte bitMask = B01000000;    // This will pin D6 of the Pro Trinket 5V or pin D12 ItsyBitsy 32u4
uint16_t color = 0;

#define potR A0
#define potG A1
#define potB A2

int valR = 0;
int valG = 0;
int valB = 0;

const int rs = 4, en = 6, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {     /* =============================================================== SETUP ============================================================================== */

  DDRD = DDRD | bitMask;
  Serial.begin(9600);
  lcd.begin(16, 2);

  lcd.print("GE ColorEffects!");
  lcd.setCursor(0, 1);
  lcd.print("  Color Picker");

  delay(3000);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("   R    G    B");

  delay(50);
  enumerate();
  
}

void loop() {      /* =============================================================== LOOP =============================================================================== */

  valR = analogRead(potR);
  valG = analogRead(potG);
  valB = analogRead(potB);

  valR = map(valR, 0, 1023, 0, 15);
  valG = map(valG, 0, 1023, 0, 15);
  valB = map(valB, 0, 1023, 0, 15);

//  Serial.print("R value = ");
//  Serial.println(valR);
//  Serial.print("G value = ");
//  Serial.println(valG);
//  Serial.print("B value = ");
//  Serial.println(valB);
//  Serial.println();

  lcd.setCursor(2, 1);
  if (valR < 10) {
    lcd.print(" ");
  }
  lcd.print(valR);

  lcd.setCursor(7, 1);
  if (valG < 10) {
    lcd.print(" ");
  }
  lcd.print(valG);

  lcd.setCursor(12, 1);
  if (valB < 10) {
    lcd.print(" ");
  }
  lcd.print(valB);

  color = COLOR(valR, valG, valB);

  setColor(0, defaultIntensity, color);

  delay(250);

}

                   /* =============================================================== FUNCTIONS ========================================================================== */

void begin(){          //begins the data frame
  PORTD = PORTD | bitMask;
  delayMicroseconds(10);  //Output should be ~ 10uS long 
  PORTD = PORTD & ~bitMask;
}

void one(){            //defines a one for any bit in the data frame
  PORTD = PORTD & ~bitMask; 
  delayMicroseconds(20); //Output should be ~ 20uS long 
  PORTD = PORTD | bitMask;
  delayMicroseconds(10);  //Output should be ~ 10uS long 
  PORTD = PORTD & ~bitMask;
}

void zero(){           //defines a zero for any bit in the data frame
  PORTD = PORTD & ~bitMask;
  delayMicroseconds(10);  //Output should be ~ 10uS long
  PORTD = PORTD | bitMask;
  delayMicroseconds(20); //Output should be ~ 20uS long  
  PORTD = PORTD & ~bitMask;
}

void end(){            //sets the data line LOW between data frames
  PORTD = PORTD & ~bitMask;
  delayMicroseconds(30);
}

void enumerate(){       //addresses each bulb individually for all outputs
  noInterrupts();
  setColor(0, defaultIntensity, black);
  interrupts();
}

void setColor(uint8_t led, uint8_t intensity, uint16_t color){
  noInterrupts();
  uint8_t i;
  begin();
  for(i=6;i;i--,(led<<=1))
    if(led&(1<<5)) one();
    else zero();
  for(i=8;i;i--,(intensity<<=1))
    if(intensity&(1<<7)) one();
    else zero();
  for(i=12;i;i--,(color<<=1))
    if(color&(1<<11)) one();
    else zero();
  end();
  interrupts();
}
