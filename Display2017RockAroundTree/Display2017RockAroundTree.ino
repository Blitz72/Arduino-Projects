 
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
  
  ledsA = 1;
  ledsC = 1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------------SETUP--------------------------------------------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void setup(){
  DDRA = 0x3f;          //set first 6 PORTA pins to be outputs
  DDRC = 0x3f;          //set first 6 PORTC pins to be outputs
  
  PORTA = 0x3f;
  PORTC = 0x3f;
  
  delay(2500);
  
//  PORTA = 0x0;
//  PORTC = 0x0;
  
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------------LOOP---------------------------------------------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void loop(){
  
//  test();
  
  splittingHairs();
  rotateCW();
  backAndForth();
  accelDecel();

}

//-------------------------------------------------------------------------------SPLITTING HAIRS---------------------------------------------------------------------------------//
  
  void splittingHairs(){
    
    time = 100;
    
    ledsA = B00111111;
    ledsC = B00111111;
    
    PORTA = ledsA;
    PORTC = ledsC;
    
    delay(2500);
    
    for(int i = 0; i < 6; i++){
      PORTA = ledsA;
      PORTC = ledsC;
      delay(time);
      ledsA <<= 1;
      ledsC <<= 1;
    }
    
    ledsA = 1;
    ledsC = 1;
    
    for(int x = 0; x < 12; x++){
      
      for(int i = 0; i < 6; i++){
        PORTA = ledsA;
        PORTC = ledsC;
        delay(time);
        ledsA <<= 1;
        ledsC <<= 1;
      }
      ledsA = 1;
      ledsC = 1;
    }
    
    PORTA = ledsA;
    PORTC = ledsC;
    
    delay(time);
    
    PORTA = B00000011;
    PORTC = B00000011;
    
    delay(time);
    
    PORTA = B00000101;
    PORTC = B00000101;
    
    delay(time);
    
    ledsA = B00001001;
    ledsC = B00001001;
    
    for(int x = 0; x < 24; x++){
      
      for(int i = 0; i < 3; i++){
        PORTA = ledsA;
        PORTC = ledsC;
        delay(time);
        ledsA <<= 1;
        ledsC <<= 1;
      }
      ledsA = B00001001;
      ledsC = B00001001;
    }
    
    PORTA = B00001001;
    PORTC = B00001001;
    
    delay(time);
    
    PORTA = B00010011;
    PORTC = B00010011;
    
    delay(time);
    
    PORTA = B00100101;
    PORTC = B00100101;
    
    delay(time);
    
    PORTA = B00001011;
    PORTC = B00001011;
    
    delay(time);
    
    ledsA = B00010101;
    ledsC = B00010101;
    
    for(int x = 0; x < 36; x++){
      
      for(int i = 0; i < 2; i++){
        PORTA = ledsA;
        PORTC = ledsC;
        delay(time);
        ledsA <<= 1;
        ledsC <<= 1;
      }
      ledsA = B00010101;
      ledsC = B00010101;
    }
    
    ledsA = B00111111;
    ledsC = B00111111;
    
    PORTA = ledsA;
    PORTC = ledsC;
    
    delay(2500);
    
  }
  
//--------------------------------------------------------------------------------ROTATE CW--------------------------------------------------------------------------------------//
  
  void rotateCW(){
    
    time = 50;
    
    ledsA = B00111111;
    ledsC = B00111111;
    
    PORTA = ledsA;
    PORTC = ledsC;
    
    delay(2500);
    
    for (int i = 0; i < 5; i++){
      PORTA = ledsA;
      PORTC = ledsC;
      delay(time);
      ledsA <<=1;
      ledsC <<=1;
    }
    
    ledsA = 1;
    ledsC = 1;
    
    for(int x = 0; x < 24; x++){
      
      for(int i = 0; i < 6; i++){
        PORTA = ledsA;
        PORTC = ledsC;
        delay(time);
        ledsA <<= 1;
        ledsC <<= 1;
      }
      ledsA = B00000001;
      ledsC = B00000001;
    }
    
    for (int i =0; i < 5; i++){
      PORTA = ledsA;
      PORTC = ledsC;
      delay(time);
      ledsA <<= 1;
      ledsA += 1;
      ledsC <<= 1;
      ledsC += 1;
    }
      
    
    ledsA = B00111111;
    ledsC = B00111111;
    
    PORTA = ledsA;
    PORTC = ledsC;
    
    delay(2500);
    
  }
  
//---------------------------------------------------------------------------------BACK AND FORTH--------------------------------------------------------------------------------//
  
  void backAndForth(){
    
    time = 50;
    
    ledsA = B00111111;
    ledsC = B00111111;
    
    PORTA = ledsA;
    PORTC = ledsC;
    
    delay(2500);
    
    for (int i = 0; i < 5; i++){
      PORTA = ledsA;
      PORTC = ledsC;
      delay(time);
      ledsA >>=1;
      ledsC >>=1;
    }
    
    ledsA = 1;
    ledsC = 1;
  
    for(int x = 0; x < 12; x++){
      for(int i = 0; i < 5; i++){
        PORTA = ledsA;
        PORTC = ledsC;
        delay(time);
        ledsA <<= 1;
        ledsC <<= 1;
      }
      
      for(int i = 0; i < 5; i++){
        PORTA = ledsA;
        PORTC = ledsC;
        delay(time);
        ledsA >>= 1;
        ledsC >>= 1;
      }
    }
    
    ledsA = 1;
    ledsC = 1;
    
    for (int i = 0; i < 5; i++){
      PORTA = ledsA;
      PORTC = ledsC;
      delay(time);
      ledsA <<= 1;
      ledsA += 1;
      ledsC <<=1;
      ledsC += 1;
    }
  
    ledsA = B00111111;
    ledsC = B00111111;
    
    PORTA = ledsA;
    PORTC = ledsC;
    
    delay(2500);
    
  }
  
//------------------------------------------------------------------------------ACCELERATE CW/CCW--------------------------------------------------------------------------------//
  
  void accelDecel(){
    
    time = 70;
    
    ledsA = B00111111;
    ledsC = B00111111;
    
    PORTA = ledsA;
    PORTC = ledsC;
    
    delay(2500);
    
    for(int i = 0; i < 5; i++){
      PORTA = ledsA;
      PORTC = ledsC;
      delay(time);
      ledsA <<= 1;
      ledsC <<= 1;
    }
    ledsA = 1;
    ledsC = 1;
  
    
    for(int x = 0; x < 30; x++){
      
      for(int i = 0; i < 6; i++){
        PORTA = ledsA;
        PORTC = ledsC;
        delay(time);
        ledsA <<= 1;
        ledsC <<= 1;
      }
      
      ledsA = 1;
      ledsC = 1;
      
      time -= 2;
      if (time <= 0){
        time = 2;
      }
      
    }
    
    ledsA = B00100000;
    ledsC = B00100000;
    
    for(int x = 0; x < 30; x++){
      
      for(int i = 0; i < 6; i++){
        PORTA = ledsA;
        PORTC = ledsC;
        delay(time);
        ledsA >>= 1;
        ledsC >>= 1;
      }
      
      ledsA = B00100000;
      ledsC = B00100000;
      
      time += 2;
      
    }
    
    time = 70;
    
    for(int i = 0; i < 6; i++){
      PORTA = ledsA;
      PORTC = ledsC;
      delay(time);
      ledsA >>= 1;
      ledsA += B00100000;
      ledsC >>= 1;
      ledsC += B00100000;
    }
    
    ledsA = B00111111;
    ledsC = B00111111;
    
    PORTA = ledsA;
    PORTC = ledsC;
    
    delay(2500);
    
  }
  
  
