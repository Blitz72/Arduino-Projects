#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int secs = 0;
int mins = 0;
int hours = 12;
int delaytime = 990;
boolean meridian = LOW;

void setup() {
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  
  digitalWrite(0, HIGH);
  digitalWrite(1, HIGH);
  digitalWrite(2, HIGH);

  lcd.begin(20, 4);
  lcd.setCursor(0, 1);
  lcd.print("the time is now:");
}

void loop() {
  
  for (int i = 0; i < 60; i = i + 1) {
    if (digitalRead(0) == LOW  && digitalRead(1) == LOW) {
      if (hours == 11 && secs == 1 && meridian == LOW) {
        meridian = HIGH;}
      else if (hours == 11 && secs == 1 && meridian == HIGH) {
        meridian = LOW;}
      secs = 0;
      hours++;    
    }
    if (digitalRead(0) == LOW && digitalRead(2) == LOW) {
      secs = 0;
      mins++;
    }
    delay(delaytime);
    secs++;
    if (secs == 60) {
      mins++;
      secs = 0;
      i = 0;
      }
    if (mins == 60) {
      hours++;
      mins = 0;
    }
    if (hours == 12 && mins == 0 && secs < 1 && meridian == LOW) {
      meridian = HIGH;
      }
    else if (hours == 12 && mins == 0 && secs < 1 && meridian == HIGH) {
      meridian = LOW;
      }
    if (hours == 13) {
      hours = 1;
      }
  if (hours >= 4 && hours < 12 && meridian == LOW) {
    lcd.setCursor(0, 0);
    lcd.print("Good Morning,       ");
    }
  if (hours == 12 && meridian == HIGH) {
    lcd.setCursor(0, 0);
    lcd.print("Good Afternoon,     ");
    }
  if (hours < 7 && meridian == HIGH) {
    lcd.setCursor(0, 0);
    lcd.print("Good Afternoon,     ");
    }
  if (hours >= 7 && hours < 10 && meridian == HIGH) {
    lcd.setCursor(0, 0);
    lcd.print("Good Evening,       ");
    }
  if (hours >= 10 && hours < 12 && meridian == HIGH) {
    lcd.setCursor(0, 0);
    lcd.print("Good Night,         ");
    }
  if (hours == 12 && meridian == LOW) {
    lcd.setCursor(0, 0);
    lcd.print("Good Night,         ");
    }
  if (hours < 4 && meridian == LOW) {
    lcd.setCursor(0, 0);
    lcd.print("Good Night,         ");
    }
  lcd.setCursor(0, 2);
  if (hours < 10) {
    lcd.print(" ");
    lcd.print(hours);
    }
  else {
    lcd.print(hours);
    }
  lcd.print(":"); 
  if (mins < 10) {
    lcd.print("0");
    lcd.print(mins);
    }
  else {
    lcd.print(mins);
    }
  lcd.print(":");
  if (secs < 10) {
    lcd.print("0");
    lcd.print(secs);
    }
  else {
    lcd.print(secs);
    }
  if (meridian == LOW) {
    lcd.print(" AM");
    }
  else {
    lcd.print(" PM");
    }
  }
}
 
 
 
 
  
  
