byte ledsA = 1;
byte ledsC = 1;
byte ledsL = 1;
int time = 0;

void test() {                //test to make sure wiring is correct
  time = 200;
  for(int i = 0; i < 8; i++){
    PORTA = ledsA;
    ledsA <<= 1;
    delay(time);
  }
  PORTA = 0;
  PORTL = B1;
  delay(time);
  PORTL = B10;
  delay(time);
  PORTL = 0;
  for(int i = 0; i < 8; i++){
    PORTC = ledsC;
    ledsC <<= 1;
    delay(time);
  }
  PORTC = 0;
  PORTL = B1000;
  delay(time);
  PORTL = B100;
  delay(time);
  PORTL = 0;
  ledsA = 1;
  ledsC = 1;
  ledsL = 1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------------SETUP--------------------------------------------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void setup(){
  DDRA = B11111111;          //set all PORTA pins to be outputs
  DDRC = B11111111;          //set all PORTC pins to be outputs
  DDRL = B00001111;          //set all PORTL pins to be outputs
  
  PORTA = B11111111;
  PORTC = B11111111;
  PORTL = B11111111;
  delay(20000);
  
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------------LOOP---------------------------------------------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void loop(){
//  test();

//-----------------------------------------------------------------------------------UP/DOWN-------------------------------------------------------------------------------------//

  time = 600;
  
  for(int i = 0; i < 7; i++){
    PORTA = 0;
    PORTC = 255;
    PORTL = B1100;
    delay(time);
    PORTA = 255;
    PORTL = B11;
    PORTC = 0;
    delay(time);
  }
  PORTA = 0;
  PORTC = 255;
  PORTL = B1100;
  delay(time);
  PORTA = 255;
  PORTC = 255;
  PORTL = B1111;
  delay(10000);
  
//---------------------------------------------------------------------------------WAX OFF LEFT----------------------------------------------------------------------------------//

  time = 75;
  
  delay(time);
  time -= 5;
  PORTL = B1001;
  delay(time);
  time -= 5;
  ledsA = B11111111;
  ledsC = B11111111;
  ledsL = 0;
  for(int i = 0; i < 8; i++){
    PORTA = ledsA;
    PORTC = ledsC;
    PORTL = ledsL;
    delay(time);
    ledsA >>= 1;
    ledsC >>= 1;
    time -= 5;
  }

//----------------------------------------------------------------------------------CCW 4-WIDE-----------------------------------------------------------------------------------//
  
  PORTA = 0;
  PORTC = 0;
  PORTL = 0;

  ledsC = 1;
  ledsL = 0;
  ledsA = 0;
  time = 40;
  
  for(int i = 0; i < 12; i++){
    PORTC = ledsC;
    PORTL = ledsL;
    delay(time);
    ledsC <<= 1;
    if (i < 3) ledsC += 1;
    if (i == 7) ledsL = B1000;
    if (i == 8) ledsL = B1100;
    if (i == 9) ledsL = B1110;
    if (i == 10) ledsL = B1111;
  }
  
  ledsA = B10000000;
  ledsL >>= 1;
  
  for(int i = 0; i < 8; i++){
    PORTA = ledsA;
    PORTC = ledsC;
    PORTL = ledsL;
    delay(time);
    ledsA >>= 1;
    if (i < 3){
      ledsA += B10000000;
      ledsL >>= 1;
    }
  }
  
  ledsC = 1;
  
  for(int x = 0; x < 20; x++){

    for(int i = 0; i < 12; i++){
      PORTA = ledsA;
      PORTC = ledsC;
      PORTL = ledsL;
      delay(time);
      ledsC <<= 1;
      if (i < 3){
        ledsC += 1;
        ledsA >>=1;
      }
      if (i == 7) ledsL = B1000;
      if (i == 8) ledsL = B1100;
      if (i == 9) ledsL = B1110;
      if (i == 10) ledsL = B1111;
    }
  
    ledsA = B10000000;
    ledsL >>= 1;
  
    for(int i = 0; i < 8; i++){
      PORTA = ledsA;
      PORTC = ledsC;
      PORTL = ledsL;
      delay(time);
      ledsA >>= 1;
      if (i < 3){
        ledsA += B10000000;
        ledsL >>= 1;
      }
    }
    
    time -= 2;
    ledsC = 1;
  
  }
  
  ledsA = 1;
  ledsC = 0;
  ledsL = 0;
  
  for(int i = 0; i < 12; i++){
    PORTA = ledsA;
    PORTC = ledsC;
    PORTL = ledsL;
    delay(time);
    ledsA <<= 1;
    if (i < 3) ledsA += 1;
    if (i == 7) ledsL = 1;
    if (i == 8) ledsL = B11;
    if (i == 9) ledsL = B111;
    if (i == 10) ledsL = B1111;
  }
  
  ledsC = B10000000;
  ledsL <<= 1;
  
  for(int i = 0; i < 8; i++){
    PORTA = ledsA;
    PORTC = ledsC;
    PORTL = ledsL;
    delay(time);
    ledsC >>= 1;
    if (i < 3){
      ledsC += B10000000;
      ledsL <<= 1;
    }
  }
  
  ledsA = 1;
  
  for(int x = 0; x < 20; x++){
    
    for(int i = 0; i < 12; i++){
      PORTA = ledsA;
      PORTC = ledsC;
      PORTL = ledsL;
      delay(time);
      ledsA <<= 1;
      if (i < 3){
        ledsA += 1;
        ledsC >>=1;
      }
      if (i == 7) ledsL = B1;
      if (i == 8) ledsL = B11;
      if (i == 9) ledsL = B111;
      if (i == 10) ledsL = B1111;
    }
  
    ledsC = B10000000;
    ledsL <<= 1;
  
    for(int i = 0; i < 8; i++){
      PORTA = ledsA;
      PORTC = ledsC;
      PORTL = ledsL;
      delay(time);
      ledsC >>= 1;
      if (i < 3){
        ledsC += B10000000;
        ledsL <<= 1;
      }
    }
    
    time += 2;
    ledsA = 1;
    
  }
  
  PORTC = ledsC;
  delay(time);
  ledsC >>= 1;
  PORTC = ledsC;
  delay(time);
  ledsC >>= 1;
  PORTC = ledsC;
  delay(time);
  ledsC >>= 1;
  PORTC = ledsC;
  delay(time);
  
//---------------------------------------------------------------------------------WAX ON RIGHT----------------------------------------------------------------------------------//

  time = 50;
  
  ledsA = 1;
  ledsC = 1;
  ledsL = 1;
  for(int i = 0; i < 8; i++){
    PORTA = ledsA;
    PORTC = ledsC;
    delay(time);
    ledsA <<= 1;
    ledsA += 1;
    ledsC <<= 1;
    ledsC += 1;
    time -= 5;
  }
  delay(time-5);
  PORTL = B1001;
  delay(time - 5);
  PORTL = B1111;


  PORTA = 255;
  PORTC = 255;
  PORTL = B1111;
  
  delay(10000);
  
//-------------------------------------------------------------------------------RANDOM SPARKLE----------------------------------------------------------------------------------//

  time = 30;
  
  for(int i = 0; i < 200; i++){
    PORTA = random(0, 255);
    PORTC = random(0, 255);
    PORTL = random(0, 15);
    delay(time);
  }
  
  PORTA = 255;
  PORTC = 255;
  PORTL = B1111;
  
  delay(10000);

//-------------------------------------------------------------------------LEFT/RIGHT OPPOSING CORNERS---------------------------------------------------------------------------//
  
  time = 60;
  
  PORTA = B11111110;
  PORTL = 1101;
  delay(time);
  PORTA = B11111100;
  PORTL = 1100;
  delay(time);
  PORTA = B01111000;
  delay(time);
  PORTA = B00110000;
  delay(time);
  PORTA = 0;
  delay(time);
  
  for(int i = 0; i < 5; i++){    
    PORTA = B00110000;
    PORTC = B11111110;
    PORTL = B1000;
    delay(time);
    PORTA = B01111000;
    PORTC = B11111100;
    PORTL = 0;
    delay(time);
    PORTA = B11111100;
    PORTC = B01111000;
    delay(time);
    PORTA = B11111110;
    PORTC = B00110000;
    PORTL = 1;
    delay(time);
    PORTA = B11111111;
    PORTC = 0;
    PORTL = B11;
    delay(time);
    PORTA = B11111110;
    PORTC = B00110000;
    PORTL = 1;
    delay(time);
    PORTA = B11111100;
    PORTC = B01111000;
    PORTL = 0;
    delay(time);
    PORTA = B01111000;
    PORTC = B11111100;
    delay(time);
    PORTA = B00110000;
    PORTC = B11111110;
    PORTL = B1000;
    delay(time);
    PORTA = 0;
    PORTC = B11111111;
    PORTL = B1100;
    delay(time);
  }
  
  PORTA = B00110000;
  delay(time);
  PORTA = B01111000;
  delay(time);
  PORTA = B11111100;
  delay(time);
  PORTA = B11111110;
  PORTL = 1101;
  delay(time);
  PORTA = B11111111;
  PORTL = B1111;
    
  delay(10000);
  
//----------------------------------------------------------------------------------EVENS/ODDS-----------------------------------------------------------------------------------//
  
  time = 40;
  
  for(int i = 0; i < 32; i ++){
    PORTA = B10101010;
    PORTC = B01010101;
    PORTL = B1010;
    delay(time);
    PORTA = B01010101;
    PORTC = B10101010;
    PORTL = B0101;
    delay(time);
  }
  
  PORTA = B11111111;
  PORTC = B11111111;
  PORTL = B1111;
  
  delay(10000);

}
