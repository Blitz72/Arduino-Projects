#include <LiquidCrystal.h>
#include "katakana.h"

// make some custom characters:
byte heart[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

byte smiley[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b10001,
  0b01110,
  0b00000
};

byte frownie[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b00000,
  0b01110,
  0b10001
};

byte armsDown[8] = {
  0b00100,
  0b01010,
  0b00100,
  0b00100,
  0b01110,
  0b10101,
  0b00100,
  0b01010
};

byte armsUp[8] = {
  0b00100,
  0b01010,
  0b00100,
  0b10101,
  0b01110,
  0b00100,
  0b00100,
  0b01010
};

void setup(){

  Serial.begin(9600);
  
  lcd.begin(16, 2);
  //lcd.begin(20, 2);  //for use with old Kronos lcd
  lcd.setCursor(0, 0);
//  ko();
//  n();
//  ni();
//  chi();
//  wa();
//  lcd.print(", ");
//  mi();
//  chi();
//  sa();
//  n();
//  lcd.print("!");
//  lcd.setCursor(0,1);
//  o();
//  ge();
//  n();
//  ki();
//  lcd.print(" ");
//  de();
//  su();
//  lcd.print(" ");
//  ka();
//  lcd.print("! ");

  katakana(ko, n, ni, chi, wa);
  lcd.print(" ");
  katakana(mi, chi, sa, n);
  lcd.print("!");
  lcd.setCursor(0,1);
  katakana(o, ge, n, ki);
  lcd.print(" ");
  katakana(de, su);
  lcd.print(" ");
  katakana(ka);
  lcd.print("!");
  
  // create a new character
  
  lcd.createChar(0, heart);
  // create a new character
  lcd.createChar(1, smiley);
  // create a new character
  lcd.createChar(2, frownie);
  // create a new character
  lcd.createChar(3, armsDown);  
  // create a new character
  lcd.createChar(4, armsUp);
}



void loop(){

//  lcd.setCursor(12, 0);
//  lcd.write(byte(0));
//  lcd.write(1);
//  lcd.print(" ");
//  lcd.write(3);
//  delay(1000);
//  lcd.setCursor(12, 0);
//  lcd.write(1);
//  lcd.write(byte(0));
//  lcd.print(" ");
//  lcd.write(4);
//  delay(1000);
}
