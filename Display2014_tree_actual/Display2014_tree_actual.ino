
byte ledsA = 1;
byte ledsC = 1;
byte ledsL = 1;
int time = 0;

void test() {                //test to make sure output simulator wiring is correct
  time = 300;
  for(int i = 0; i < 8; i++){
    PORTA = ledsA;
    ledsA <<= 1;
    delay(time);
  }
  PORTA = 0;
  for(int i = 0; i < 8; i++){
    PORTC = ledsC;
    ledsC <<= 1;
    delay(time);
  }
  PORTC = 0;
  for(int i = 0; i < 8; i++){
    PORTL = ledsL;
    ledsL <<= 1;
    delay(time);
  }
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
  DDRL = B11111111;          //set all PORTL pins to be outputs
  
  PORTA = B11111111;
  PORTC = B11111111;
  PORTL = B11111111;
  delay(10000);
  
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------------LOOP---------------------------------------------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void loop(){
  
//  test();

  PORTA = B11111111;
  PORTC = B11111111;
  PORTL = B11111111;
  
  delay(10000);
  
//-------------------------------------------------------------------------------SPLITTING HAIRS---------------------------------------------------------------------------------//
  
  time = 100;
  ledsA = 1;
  ledsC = 1;
  PORTL = B11111111;
  
  for(int x = 0; x < 16; x++){
    
    for(int i = 0; i < 8; i++){
      PORTA = ledsA;
      PORTC = ledsC;
      delay(time);
      ledsA <<= 1;
      ledsC <<= 1;
    }
    ledsA = 1;
    ledsC = 1;
  }
  
  ledsA = B00010001;
  ledsC = B00010001;
  
  for(int x = 0; x < 32; x++){
    
    for(int i = 0; i < 4; i++){
      PORTA = ledsA;
      PORTC = ledsC;
      delay(time);
      ledsA <<= 1;
      ledsC <<= 1;
    }
    ledsA = B00010001;
    ledsC = B00010001;
  }
  
  ledsA = B01010101;
  ledsC = B01010101;
  
  for(int x = 0; x < 64; x++){
    
    for(int i = 0; i < 2; i++){
      PORTA = ledsA;
      PORTC = ledsC;
      delay(time);
      ledsA <<= 1;
      ledsC <<= 1;
    }
    ledsA = B01010101;
    ledsC = B01010101;
  }
  
  ledsL = B01010101;
  
  for(int x = 0; x < 64; x++){
    
    for(int i = 0; i < 2; i++){
      PORTL = ledsL;
      PORTA = ledsA;
      PORTC = ledsC;
      delay(time);
      ledsA <<= 1;
      ledsC <<= 1;
      ledsL <<= 1;
    }
    ledsA = B01010101;
    ledsC = B01010101;
    ledsL = B01010101;
  }
  
  PORTA = B11111111;
  PORTC = B11111111;
  PORTL = B11111111;
  
  delay(10000);
  
  time = 50;
  
//--------------------------------------------------------------------------------ROTATE CW/DOWN---------------------------------------------------------------------------------//
  
  ledsA = B00010001;
  ledsC = B00010001;
  ledsL = B00010001;
  
  for(int x = 0; x < 16; x++){
    
    for(int i = 0; i < 8; i++){
      PORTA = ledsA;
      PORTC = ledsC;
      PORTL = ledsL;
      delay(time);
      ledsA <<= 1;
      ledsC <<= 1;
      ledsL <<= 1;
    }
    ledsA = B00010001;
    ledsC = B00010001;
    ledsL = B00010001;
  }
  
  PORTA = B11111111;
  PORTC = B11111111;
  PORTL = B11111111;
  
  delay(10000);
  
//---------------------------------------------------------------------------------BACK AND FORTH--------------------------------------------------------------------------------//
 
  ledsA = 1;
  ledsC = 1;
  ledsL = 1;
  
  for(int x = 0; x < 8; x++){
    for(int i = 0; i < 7; i++){
      PORTA = ledsA;
      PORTC = ledsC;
      PORTL = ledsL;
      delay(time);
      ledsA <<= 1;
      ledsC <<= 1;
      ledsL <<= 1;
    }
    
    for(int i = 0; i < 7; i++){
      PORTA = ledsA;
      PORTC = ledsC;
      PORTL = ledsL;
      delay(time);
      ledsA >>= 1;
      ledsC >>= 1;
      ledsL >>= 1;
    }
    
    PORTA = ledsA;
    PORTC = ledsC;
    PORTL = ledsL;
    delay(time);
    
  }

  PORTA = B11111111;
  PORTC = B11111111;
  PORTL = B11111111;
  
  delay(10000);

//------------------------------------------------------------------------------ACCELERATE CW/CCW--------------------------------------------------------------------------------//
  
  time = 50;
  
  ledsA = B11111110;
  ledsC = B11111110;
  ledsL = B11111110;
  
  for(int i = 0; i < 7; i++){
    PORTA = ledsA;
    PORTC = ledsC;
    PORTL = ledsL;
    delay(time);
    ledsA <<= 1;
    ledsC <<= 1;
    ledsL <<= 1;
  }
  
  ledsA = 1;
  ledsC = 1;
  ledsL = 1;
  
  for(int x = 0; x < 24; x++){
    
    for(int i = 0; i < 8; i++){
      PORTA = ledsA;
      PORTC = ledsC;
      PORTL = ledsL;
      delay(time);
      ledsA <<= 1;
      ledsC <<= 1;
      ledsL <<= 1;
    }
    
    ledsA = 1;
    ledsC = 1;
    ledsL = 1;
    
    time -= 2;
    
  }
  
  ledsA = B10000000;
  ledsC = B10000000;
  ledsL = B10000000;
  
  for(int x = 0; x < 24; x++){
    
    for(int i = 0; i < 8; i++){
      PORTA = ledsA;
      PORTC = ledsC;
      PORTL = ledsL;
      delay(time);
      ledsA >>= 1;
      ledsC >>= 1;
      ledsL >>= 1;
    }
    
    ledsA = B10000000;
    ledsC = B10000000;
    ledsL = B10000000;
    
    time += 2;
    
  }
  
  time = 50;
  
  for(int i = 0; i < 8; i++){
    PORTA = ledsA;
    PORTC = ledsC;
    PORTL = ledsL;
    delay(time);
    ledsA >>= 1;
    ledsA += B10000000;
    ledsC >>= 1;
    ledsC += B10000000;
    ledsL >>= 1;
    ledsL += B10000000;
  }
  
  PORTA = B11111111;
  PORTC = B11111111;
  PORTL = B11111111;
  
  delay(10000);
      
  
}
