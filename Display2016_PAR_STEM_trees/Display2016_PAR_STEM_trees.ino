//PB0 - PB5 (D8 - D13) for ProTrinket 5V/16MHz
//PAR LEDs on SSRs connected to PB0 - PB5, 2 PARs per SSR

#define white1  0x01
#define white2  0x02
#define green1  0x04
#define green2  0x08
#define red1    0x10
#define red2    0x20

#define bitMask 0xff

//#define time1   5000
//#define time2   2000

void setup(){
  DDRB |= 0x3f;
  PORTB |= 0x3f;
  
}

void loop(){
  PORTB = green1 + green2;
  delay(random(4000, 6000));
  PORTB = green1 + green2 + red1;
  delay(random(1500, 3000));
  PORTB = green1 + green2 + red2;
  delay(random(1500, 3000));
  PORTB = green1 + green2 + red1 + red2;
  delay(random(4000, 6000));
  PORTB = green1 + red1 + red2;
  delay(random(1500, 3000));
  PORTB = green2 + red1 + red2;
  delay(random(1500, 3000));
  PORTB = red1 + red2;
  delay(random(4000, 6000));
  PORTB = white1 + red1 + red2;
  delay(random(1500, 3000));
  PORTB = white2 + red1 + red2;
  delay(random(1500, 3000));
  PORTB = white1 + white2 + red1;
  delay(random(1500, 3000));
  PORTB = white1 + white2 + red2;
  delay(random(1500, 3000));
  PORTB = white1 + white2;
  delay(random(6000, 10000));
    
}
