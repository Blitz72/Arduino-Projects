
//#define rxPin 19
//#define txPin 18


const byte pp =50;
const byte p = 60;
const byte mp = 70;
const byte mf = 80;
const byte f = 100;
const byte ff = 127;
const byte pizz = 51;
const byte glock = 101;
const byte clarinet1 = 82;
const byte clarinet2 = 83;
const byte oboe = 84;
const byte strings = 48;
const byte brass1 = 95;
const byte brass2 = 96;
const byte tbone1 = 90;
const byte tbone2 = 91;
const byte horn1 = 92;
const byte horn2 = 93;
const byte flute1 = 72;
const byte flute2 = 73;
const byte timp = 112;
const byte harp1 = 57;
const byte harp2 = 58;


byte synthInitialized = 0;
byte zero = 0;
int tempo = 600;

void synthBegin(){
  if (!(synthInitialized)){
    Serial.begin(31250);                                         // Set MIDI baud rate
    delay(5);                                                  // let the port settle
    synthInitialized = 1;                               // Initialization has been done
  }
}

void midiReset(){
  Serial.write(0xff);
}

void noteOn(byte channel, byte pitch, byte velocity){
  byte command[3] = { 0x90 | (channel & 0x0f), pitch, velocity };
  Serial.write(command, 3);
}

void noteOff(byte channel, byte pitch){
  byte command[3] = { 0x80 | (channel & 0x0f), pitch, byte(0x00) };
  Serial.write(command, 3);
}

void allNotesOff(byte channel){    // BnH 7BH 00H
  byte command[3] = { (0xb0 | (channel & 0x0f)), 0x7b, 0x00 };
  Serial.write(command, 3);
}

void setMasterVolume(byte level){
  //F0H 7FH 7FH 04H 01H 00H ll F7H
  byte command[8] = { 0xf0, 0x7f, 0x7f, 0x04, 0x01, 0x00, (level & 0x7f), 0xf7 };
  Serial.write(command, 8);
}

void setChannelVolume(byte channel, byte level){
  byte command[3] = { (0xb0 | (channel & 0x0f)), 0x07, level };
  Serial.write(command, 3);
}

void programChange(byte bank, byte channel, byte voice){    // bank is either 0 or 127
  byte command[3] = { 0xB0 | (channel & 0x0f), byte(0x00), bank };
  Serial.write(command, 3);
  Serial.write(0xc0 | (channel & 0x0f));
  Serial.write(voice);
}

void pitchBend(byte channel, int v){
  // v is a value from 0 to 1023
  // it is mapped to the full range 0 to 0x3fff
  v = map(v, 0, 1023, 0, 0x3fff);
  byte command[3] = { 0xe0 | (channel & 0x0f), byte(v & 0x00ef), byte(v >> 7) };
  Serial.write(command, 3);
}

void pitchBendRange(byte channel, byte v){
  // Also called pitch bend sensitivity
  //BnH 65H 00H 64H 00H 06H vv
  byte command[7] = {0xb0 | (channel & 0x0f), 0x65, 0x00, 0x64, 0x00, 0x06, (v & 0x7f)};
  Serial.write(command, 7);
}

void setReverb(byte channel, byte program, byte level, byte delayFeedback){
  // Program
  // 0: Room1   1: Room2    2: Room3
  // 3: Hall1   4: Hall2    5: Plate
  // 6: Delay   7: Pan delay
  Serial.write(0xb0 | (channel & 0x0f));
  Serial.write(0x50);    
  Serial.write(program & 0x07);
  
  // Set send level
  Serial.write(0xb0 | (channel & 0x0f));
  Serial.write(0x5b);
  Serial.write(level & 0x7f);
  
  if (delayFeedback > 0){
    //F0H 41H 00H 42H 12H 40H 01H 35H vv xx F7H
    byte command[11] = { 0xf0, 0x41, byte(0x00), 0x42, 0x12, 0x40, 0x01, 0x35, (delayFeedback & 0x7f), 0xf7 };
    Serial.write(command, 11);
  }
}

void setChorus(byte channel, byte program, byte level, byte feedback, byte chorusDelay){
  // Program
  // 0: Chorus1   1: Chorus2    2: Chorus3
  // 3: Chorus4   4: Feedback   5: Flanger
  // 6: Short delay   7: FB delay
  Serial.write(0xb0 | (channel & 0x0f));
  Serial.write(0x51);
  Serial.write(program & 0x07);
  
  // Set send level
  Serial.write(0xb0 | (channel & 0x0f));
  Serial.write(0x5d);
  Serial.write(level & 0x7f);
  
  if (feedback > 0){
    //F0H 41H 00H 42H 12H 40H 01H 3BH vv xx F7H
    byte command[11] = { 0xf0, 0x41, byte(0x00), 0x42, 0x12, 0x40, 0x01, 0x3B, (feedback & 0x7f), 0xf7 };
    Serial.write(command, 11);
  }
  
  if (chorusDelay > 0){
    // F0H 41H 00H 42H 12H 40H 01H 3CH vv xx F7H
    byte command[11] = { 0xf0, 0x41, byte(0x00), 0x42, 0x12, 0x40, 0x01, 0x3C, (chorusDelay & 0x7f), 0xf7 };
    Serial.write(command, 11);
  }
} 


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------------SETUP--------------------------------------------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void setup(){
  DDRA = B11111111;          //set all PORTA pins to be outputs
  DDRC = B11111111;          //set all PORTC pins to be outputs
  DDRL = B11111111;          //set all PORTL pins to be outputs
  PORTA = B11111111;         //set all outputs to ON while Xbee radios sync
  PORTC = B11111111;
  PORTL = B11111111;
  synthBegin();
  midiReset();
  Serial1.begin(115200);
//  Serial2.begin(9600);

//  setReverb( channel , program , level , feedback , delayFeedback )
  // Program 
  // 0: Room1   1: Room2    2: Room3 
  // 3: Hall1   4: Hall2    5: Plate
  // 6: Delay   7: Pan delay
  for(byte x = 0; x < 16; x++){
    setReverb(x, 5, 255, 100); // A Plate Reverb with maximum effect level
  }
  for(byte x = 0; x < 16; x++){
    setChannelVolume(x, 127); // max. channel volume
  }

  setMasterVolume(255);	// max. master volume
  
  delay(10000);          // allow time for Xbees to sync

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------------LOOP---------------------------------------------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void loop() {
//  /*
  tempo = 600;
  setChannelVolume(2, 100);
  programChange(127, 0, pizz);
  programChange(127, 1, glock);
  programChange(127, 2, clarinet1);
  programChange(127, 3, harp1);
  
//                                      DANCE OF THE SUGAR PLUM FAIRY
  for(byte x = 0; x < 2; x++){        //INTRO PIZZ. STRGS.
    Serial1.write(zero);              //        1-1
    Serial1.write(zero);
    Serial1.write(zero);
    PORTA = B00000000;
    PORTC = B11111111;
    PORTL = B00110000;
    noteOn(0, 28, mf);
    noteOn(0, 40, mf);
    delay(tempo/8);
    Serial1.write(zero);
    Serial1.write(zero);
    Serial1.write(B00000001);
    delay(tempo/8);
    Serial1.write(zero);
    Serial1.write(zero);
    Serial1.write(B00000011);
    delay(tempo/8);
    Serial1.write(zero);
    Serial1.write(zero);
    Serial1.write(B00000111);
    delay(tempo/8);
    Serial1.write(zero);
    Serial1.write(zero);
    Serial1.write(B00001111);
    delay(tempo/8);
    Serial1.write(zero);
    Serial1.write(zero);
    Serial1.write(B00011111);
    delay(tempo/8);
    Serial1.write(zero);
    Serial1.write(zero);
    Serial1.write(B00111111);
    delay(tempo/8);
    Serial1.write(B01111111);
    delay(tempo/8);
    Serial1.write(B11111111);         //        1-2
    Serial1.write(B11111111);
    Serial1.write(B11111111);
    PORTA = B11111111;
    PORTC = B00000000;
    PORTL = B11000000;
    allNotesOff(0);
    noteOn(0, 55, mf);
    noteOn(0, 59, mf);
    noteOn(0, 64, mf);
    delay(tempo);
    Serial1.write(B01010101);         //        2-1
    PORTA = B00000000;
    PORTC = B11111111;
    PORTL = B00110000;
    allNotesOff(0);
    noteOn(0, 28, mf);
    noteOn(0, 40, mf);
    delay(tempo);
    Serial1.write(B10101010);         //        2-2
    PORTA = B11111111;
    PORTC = B00000000;
    PORTL = B11000000;
    allNotesOff(0);
    noteOn(0, 57, mf);
    noteOn(0, 60, mf);
    noteOn(0, 66, mf);
    delay(tempo);
    Serial1.write(B01010101);         //        3-1
    PORTA = B00000000;
    PORTC = B11111111;
    PORTL = B00110000;
    allNotesOff(0);
    noteOn(0, 28, mf);
    noteOn(0, 40, mf);
    delay(tempo);
    Serial1.write(B10101010);         //        3-2
    PORTA = B11111111;
    PORTC = B00000000;
    PORTL = B11000000;
    allNotesOff(0);
    noteOn(0, 58, mf);
    noteOn(0, 61, mf);
    noteOn(0, 67, mf);
    delay(tempo);
    Serial1.write(B01010101);         //        4-1
    PORTA = B00000000;
    PORTC = B11111111;
    PORTL = B00110000;
    allNotesOff(0);
    noteOn(0, 28, mf);
    noteOn(0, 40, mf);
    delay(tempo);
    Serial1.write(B10101010);         //        4-2
    PORTA = B11111111;
    PORTC = B00000000;
    PORTL = B11000000;
    allNotesOff(0);
    noteOn(0, 57, mf);
    noteOn(0, 60, mf);
    noteOn(0, 63, mf);
    delay(tempo);
    allNotesOff(0);
  }
  Serial1.write(B11111111);
  noteOn(0, 40, mf);       //GLOCKENSPIEL 5-1
  delay(tempo);
  Serial1.write(B10000000);
  allNotesOff(0);
  noteOn(0, 55, mf);       //      5-1-and
  noteOn(0, 59, mf);
  noteOn(1, 91, f);        //G6
  delay(tempo/2);
  Serial1.write(B01000000);
  noteOff(1, 91);
  noteOn(1, 88, f);        //E6
  delay(tempo/2);
  Serial1.write(B00100000);
  allNotesOff(0);
  allNotesOff(1);
  noteOn(0, 40, mf);       //      5-2
  noteOn(1, 91, f);        //G6
  delay(tempo);
  Serial1.write(B00010000);
  allNotesOff(0);
  allNotesOff(1);
  noteOn(0, 57, mf);       //      5-2-and
  noteOn(0, 60, mf);
  noteOn(1, 90, f);        //F#6
  delay(tempo);
  Serial1.write(B00001000);
  allNotesOff(0);
  allNotesOff(1);
  noteOn(0, 40, mf);       //      6-1
  noteOn(1, 87, f);        //D#6
  delay(tempo);
  Serial1.write(B00000100);
  allNotesOff(0);
  allNotesOff(1);
  noteOn(0, 58, mf);       //      6-1-and
  noteOn(0, 61, mf);
  noteOn(1, 88, f);        //E6
  delay(tempo);
  Serial1.write(B10101010);
  allNotesOff(0);
  allNotesOff(1);
  noteOn(0, 40, mf);       //      6-2
  noteOn(1, 86, f);        //D6
  delay(tempo/2);
  Serial1.write(B01010101);
  noteOff(1, 86);
  noteOn(1, 86, f);        //D6
  delay(tempo/2);
  Serial1.write(B10101010);
  allNotesOff(0);
  noteOff(1, 86);
  noteOn(0, 59, mf);       //      6-2-and
  noteOn(0, 62, mf);
  noteOn(1, 86, f);        //D6
  delay(tempo);
  Serial1.write(B01010101);
  allNotesOff(0);
  allNotesOff(1);
  noteOn(0, 40, mf);       //      7-1
  noteOn(1, 85, f);        //C#6
  delay(tempo/2);
  Serial1.write(B10101010);
  noteOff(1, 85);
  noteOn(1, 85, f);        //C#6
  delay(tempo/2);
  Serial1.write(B01010101);
  noteOff(1, 85);
  noteOn(0, 61, mf);       //      7-1-and
  noteOn(0, 64, mf);
  noteOn(1, 85, f);        //C#6
  delay(tempo);
  Serial1.write(B11111111);
  allNotesOff(0);
  allNotesOff(1);
  noteOn(0, 40, mf);       //      7-2
  noteOn(1, 84, f);        //C6
  delay(tempo/3);
  Serial1.write(zero);
  delay(tempo/6);
  Serial1.write(B11111111);
  noteOff(1, 84);
  noteOn(1, 84, f);        //C6
  delay(tempo/3);
  Serial1.write(zero);
  delay(tempo/6);
  Serial1.write(B11111111);
  noteOff(1, 84);
  noteOn(0, 63, mf);       //      7-2-and
  noteOn(0, 66, mf);
  noteOn(1, 84, f);        //C6
  delay(tempo/3);
//  Serial1.write(zero);
  delay(tempo*2/3);
  Serial1.write(B00011000);
  allNotesOff(0);
  allNotesOff(1);
  noteOn(0, 55, mf);       //      8-1
  noteOn(0, 59, mf);
  noteOn(1, 83, f);        //B5
  delay(tempo/2);
  Serial1.write(B00100100);
  noteOff(1, 83);
  noteOn(1, 88, f);        //E6    8-1-ee
  delay(tempo/2);
  Serial1.write(B01000010);
  allNotesOff(0);
  noteOff(1, 88);
  noteOn(0, 57, mf);       //      8-1-and
  noteOn(0, 60, mf);
  noteOn(1, 84, f);        //C6
  delay(tempo/2);
  Serial1.write(B10000001);
  noteOff(1, 84);
  noteOn(1, 88, f);        //E6    8-1-a
  delay(tempo/2);
  Serial1.write(B11111111);
  allNotesOff(0);
  noteOff(1, 88);
  noteOn(0, 55, mf);       //      8-2
  noteOn(0, 59, mf);
  noteOn(1, 83, f);        //B5
  delay(tempo/4);
  Serial1.write(zero);
  delay(tempo*3/4);
  Serial1.write(B01000000);
  allNotesOff(0);
  allNotesOff(1);
  noteOn(2, 64, mp);       //E4    8-2-and
  delay(tempo/4);
  Serial1.write(B00010000);
  noteOff(2, 64);
  noteOn(2, 62, mp);       //D4
  delay(tempo/4);
  Serial1.write(B00000100);
  noteOff(2, 62);
  noteOn(2, 60, mp);       //C4
  delay(tempo/4);
  Serial1.write(B00000001);
  noteOff(2, 60);
  noteOn(2, 59, mp);       //B3
  delay(tempo/4);
  Serial1.write(B10101010);
  noteOff(2, 59);
  noteOn(0, 46, mf);       //A#3   9-1
  noteOn(2, 58, mp);
  delay(tempo);
  Serial1.write(B10000001);
  noteOff(2, 58);
  noteOn(0, 64, mf);       //      9-1-and
  noteOn(0, 67, mf);
  noteOn(0, 72, mf);
  noteOn(1, 79, 100);      //G5
  delay(tempo/2);
  Serial1.write(B01000010);
  noteOff(1, 79);
  noteOn(1, 76, f);        //E5
  delay(300);
  Serial1.write(B00100100);
  allNotesOff(0);
  allNotesOff(1);
  noteOn(0, 45, mf);       //      9-2
  noteOn(1, 79, f);        //G5
  delay(tempo);
  Serial1.write(B00011000);
  allNotesOff(0);
  allNotesOff(1);
  noteOn(0, 63, mf);       //      9-2-and
  noteOn(0, 66, mf);
  noteOn(0, 72, mf);
  noteOn(1, 78, f);        //F#5
  delay(tempo*5/6);
  Serial1.write(B00011000);
  delay(tempo/18);
  Serial1.write(B00111100);
  delay(tempo/18);
  Serial1.write(B01111110);
  delay(tempo/18);
  Serial1.write(B11111111);
  allNotesOff(0);
  allNotesOff(1);
  noteOn(0, 43, mf);       //      10-1
  noteOn(1, 84, 100);      //C6
  delay(tempo);
  Serial1.write(zero);
  allNotesOff(0);
  allNotesOff(1);
  noteOn(0, 64, mf);       //      10-1-and
  noteOn(0, 67, mf);
  noteOn(0, 71, mf);
  noteOn(1, 83, f);        //B5
  delay(tempo*5/6);
  Serial1.write(B00011000);
  delay(tempo/18);
  Serial1.write(B00111100);
  delay(tempo/18);
  Serial1.write(B01111110);
  delay(tempo/18);
  Serial1.write(B11111111);
  allNotesOff(0);
  allNotesOff(1);
  noteOn(0, 41, mf);       //      10-2
  noteOn(1, 91, f);        //G6
  delay(tempo*7/18);
  Serial1.write(B01111110);
  delay(tempo/18);
  Serial1.write(B00111100);
  delay(tempo/18);
  Serial1.write(B00011000);
  noteOff(1, 91);
  noteOn(1, 91, f);        //G6
  delay(tempo*7/18);
  Serial1.write(B00111100);
  delay(tempo/18);
  Serial1.write(B01111110);
  delay(tempo/18);
  Serial1.write(B11111111);
  allNotesOff(0);
  noteOff(1, 91);
  noteOn(0, 54, mf);       //      10-2-and
  noteOn(0, 58, mf);
  noteOn(1, 91, f);        //G6
  delay(tempo);
  Serial1.write(B01010101);
  allNotesOff(0);
  allNotesOff(1);
  noteOn(0, 54, mf);       //      11-1
  noteOn(1, 90, f);        //F#6
  delay(tempo);
  Serial1.write(B10101010);
  noteOff(1, 90);
  noteOn(1, 90, f);        //F#6
  delay(tempo/2);
  Serial1.write(B11111111);
  allNotesOff(0);
  noteOff(1, 90);
  noteOn(0, 56, mf);       //      11-1-and
  noteOn(0, 59, mf);
  noteOn(1, 90, f);        //F#6
  delay(tempo*33/40);
  Serial1.write(B11111111);
  delay(tempo/40);
  Serial1.write(B01111111);
  delay(tempo/40);
  Serial1.write(B00111111);
  delay(tempo/40);
  Serial1.write(B00011111);
  delay(tempo/40);
  Serial1.write(B00001111);
  delay(tempo/40);
  Serial1.write(B00000111);
  delay(tempo/40);
  Serial1.write(B00000011);
  delay(tempo/40);
  Serial1.write(B00000001);
  allNotesOff(0);
  allNotesOff(1);
  noteOn(0, 54, mf);       //      11-2
  noteOn(1, 88, f);        //E6
  delay(tempo*13/40);
  Serial1.write(B00000001);
  delay(tempo/40);
  Serial1.write(B00000010);
  delay(tempo/40);
  Serial1.write(B00000100);
  delay(tempo/40);
  Serial1.write(B00001000);
  delay(tempo/40);
  Serial1.write(B00010000);
  delay(tempo/40);
  Serial1.write(B00100000);
  delay(tempo/40);
  Serial1.write(B01000000);
  delay(tempo/40);
  Serial1.write(B10000000);
  noteOff(1, 88);
  noteOn(1, 88, f);        //E6
  delay(tempo*13/40);
  Serial1.write(B10000000);
  delay(tempo/40);
  Serial1.write(B01000000);
  delay(tempo/40);
  Serial1.write(B00100000);
  delay(tempo/40);
  Serial1.write(B00010000);
  delay(tempo/40);
  Serial1.write(B00001000);
  delay(tempo/40);
  Serial1.write(B00000100);
  delay(tempo/40);
  Serial1.write(B00000010);
  delay(tempo/40);
  Serial1.write(B00000001);
  allNotesOff(0);
  noteOff(1, 88);
  noteOn(0, 58, mf);       //      11-2-and
  noteOn(0, 61, mf);
  noteOn(1, 88, f);        //E6
  delay(tempo*33/40);
  Serial1.write(B00000001);
  delay(tempo/40);
  Serial1.write(B00000011);
  delay(tempo/40);
  Serial1.write(B00000111);
  delay(tempo/40);
  Serial1.write(B00001111);
  delay(tempo/40);
  Serial1.write(B00011111);
  delay(tempo/40);
  Serial1.write(B00111111);
  delay(tempo/40);
  Serial1.write(B01111111);
  delay(tempo/40);
  Serial1.write(B11111111);
  allNotesOff(0);
  allNotesOff(1);
  noteOn(0, 47, mf);       //      12-1
  noteOn(0, 54, mf);
  noteOn(0, 59, mf);
  noteOn(1, 87, f);        //D#6
  delay(tempo/2);
  Serial1.write(B01010101);
  noteOff(1, 87);
  noteOn(1, 90, f);        //F#6
  delay(tempo/2);
  Serial1.write(B10101010);
  allNotesOff(0);
  noteOff(1, 90);
  noteOn(0, 48, mf);       //      12-1-and
  noteOn(0, 54, mf);
  noteOn(0, 57, mf);
  noteOn(1, 88, f);        //E6
  delay(tempo/2);
  Serial1.write(B01010101);
  noteOff(1, 88);
  noteOn(1, 90, f);        //F#6
  delay(tempo/2);
  Serial1.write(B11111111);
  allNotesOff(0);
  noteOff(1, 90);
  noteOn(0, 47, mf);       //      12-2
  noteOn(0, 54, mf);
  noteOn(0, 59, mf);
  noteOn(1, 87, f);
  delay(tempo);
  Serial1.write(B10000001);
  allNotesOff(0);
  allNotesOff(1);
  noteOn(2, 59, mp);       //B3    12-2-and
  delay(tempo/4);
  Serial1.write(B01000010);
  noteOff(2, 59);
  noteOn(2, 57, mp);       //A3
  delay(tempo/4);
  Serial1.write(B00100100);
  noteOff(2, 57);
  noteOn(2, 55, mp);       //G3
  delay(tempo/4);
  Serial1.write(B00011000);
  noteOff(2, 55);
  noteOn(2, 54, mp);       //F#3
  delay(tempo*5/36);
  Serial1.write(B00111100);
  delay(tempo/18);
  Serial1.write(B01111110);
  delay(tempo/18);
  noteOff(2, 54);
  noteOn(0, 40, mf);       //      13-1
  noteOn(2, 52, mp);       //E3
  for(byte x = 0; x < 6; x++){
    Serial1.write(B01010101);
    delay(tempo/12);
    Serial1.write(B10101010);
    delay(tempo/12);
  }
  Serial1.write(B11111111);
  allNotesOff(0);
  noteOff(2, 52);
  noteOn(0, 55, mf);       //      13-1-and
  noteOn(0, 59, mf);
  noteOn(1, 91, f);        //G6
  delay(tempo/2);
  Serial1.write(B00100000);
  noteOff(1, 91);
  noteOn(1, 88, f);        //E6
  delay(tempo/2);
  Serial1.write(B00000001);
  allNotesOff(0);
  allNotesOff(1);
  noteOn(0, 40, mf);       //      13-2
  noteOn(1, 91, f);        //G6
  delay(tempo);
  Serial1.write(B00001000);
  allNotesOff(0);
  allNotesOff(1);
  noteOn(0, 57, mf);       //      13-2-and
  noteOn(0, 60, mf);
  noteOn(1, 90, f);        //F#6
  delay(tempo);
  Serial1.write(B10000000);
  allNotesOff(0);
  allNotesOff(1);
  noteOn(0, 40, mf);       //      14-1
  noteOn(1, 87, f);        //D#6
  delay(tempo);
  Serial1.write(B00000100);
  allNotesOff(0);
  allNotesOff(1);
  noteOn(0, 58, mf);       //      14-1-and
  noteOn(0, 61, mf);
  noteOn(1, 88, f);        //E6
  delay(tempo);
  Serial1.write(B01010101);
  allNotesOff(0);
  allNotesOff(1);
  noteOn(0, 40, mf);       //      14-2
  noteOn(1, 86, f);        //D6
  delay(tempo/4);
  Serial1.write(zero);
  delay(tempo/4);
  Serial1.write(B01010101);
  noteOff(1, 86);
  noteOn(1, 86, f);        //D6
  delay(tempo/4);
  Serial1.write(zero);
  delay(tempo/4);
  Serial1.write(B01010101);
  allNotesOff(0);
  noteOff(1, 86);
  noteOn(0, 59, mf);       //      14-2-and
  noteOn(0, 62, mf);
  noteOn(1, 86, f);        //D6
  delay(tempo);
  Serial1.write(B10101010);
  allNotesOff(0);
  allNotesOff(1);
  noteOn(0, 40, mf);       //      15-1
  noteOn(1, 85, f);        //C#6
  delay(tempo/4);
  Serial1.write(zero);
  delay(tempo/4);
  Serial1.write(B10101010);
  noteOff(1, 85);
  noteOn(1, 85, f);        //C#6
  delay(tempo/4);
  Serial1.write(zero);
  delay(tempo/4);
  Serial1.write(B10101010);
  noteOff(1, 85);
  noteOn(0, 61, mf);       //      15-1-and
  noteOn(0, 64, mf);
  noteOn(1, 85, f);        //C#6
  delay(tempo);
  Serial1.write(B11111111);
  allNotesOff(0);
  allNotesOff(1);
  noteOn(0, 40, mf);       //      15-2
  noteOn(1, 84, f);        //C6
  delay(tempo/3);
  Serial1.write(zero);
  delay(tempo/6);
  Serial1.write(B11111111);
  noteOff(1, 84);
  noteOn(1, 84, f);        //C6
  delay(tempo/3);
  Serial1.write(zero);
  delay(tempo/6);
  Serial1.write(B11111111);
  noteOff(1, 84);
  noteOn(0, 63, mf);       //      15-2-and
  noteOn(0, 66, mf);
  noteOn(1, 84, f);        //C6
  delay(tempo);
  Serial1.write(B11000000);
  allNotesOff(0);
  allNotesOff(1);
  noteOn(0, 55, mf);       //      16-1
  noteOn(0, 59, mf);
  noteOn(1, 83, f);        //B5
  delay(tempo/2);
  Serial1.write(B00110000);
  noteOff(1, 83);
  noteOn(1, 88, f);        //E6    16-1-ee
  delay(tempo/2);
  Serial1.write(B00001100);
  allNotesOff(0);
  noteOff(1, 88);
  noteOn(0, 57, mf);       //      16-1-and
  noteOn(0, 60, mf);
  noteOn(1, 84, f);        //C6
  delay(tempo/2);
  Serial1.write(B00000011);
  noteOff(1, 84);
  noteOn(1, 88, f);        //E6    16-1-a
  delay(tempo/2);
  Serial1.write(B11111111);
  allNotesOff(0);
  noteOff(1, 88);
  noteOn(0, 55, mf);       //      16-2
  noteOn(0, 59, mf);
  noteOn(1, 83, f);        //B5
  delay(tempo);
  Serial1.write(B10000000);
  allNotesOff(0);
  allNotesOff(1);
  noteOn(2, 67, mp);       //G4    16-2-and
  delay(tempo/4);
  Serial1.write(B00100000);
  noteOff(2, 67);
  noteOn(2, 66, mp);       //F#4
  delay(tempo/4);
  Serial1.write(B00001000);
  noteOff(2, 66);
  noteOn(2, 64, mp);       //E4
  delay(tempo/4);
  Serial1.write(B00000010);
  noteOff(2, 64);
  noteOn(2, 62, mp);       //D4
  delay(tempo/4);
  Serial1.write(B01010101);
  noteOff(2, 62);
  noteOn(0, 49, mf);       //      17-1
  noteOn(2, 61, mp);       //C#4
  delay(tempo/4);
  Serial1.write(B10101010);
  allNotesOff(0);
  noteOff(2, 61);
  noteOn(0, 42, mf);       //      17-1-and
  noteOn(0, 49, mf);
  noteOn(1, 76, f);        //E5
  delay(tempo/2);
  Serial1.write(B01010101);
  noteOff(1, 76);
  noteOn(1, 73, f);        //C#5
  delay(tempo/2);
  Serial1.write(B10101010);
  allNotesOff(0);
  allNotesOff(1);
  noteOn(1, 76, f);        //E5    17-2
  delay(tempo);
  Serial1.write(B00000001);
  noteOff(1, 76);
  noteOn(0, 57, mf);       //      17-2-and
  noteOn(0, 59, mf);
  noteOn(0, 63, mf);
  noteOn(1, 75, f);        //D#5
  noteOn(2, 66, mp);       //F#4
  delay(tempo/4);
  Serial1.write(B00000100);
  noteOff(2, 66);
  noteOn(2, 64, mp);       //E4
  delay(tempo/4);
  Serial1.write(B00010000);
  noteOff(2, 64);
  noteOn(2, 63, mp);       //D#4
  delay(tempo/4);
  Serial1.write(B01000000);
  noteOff(2, 63);
  noteOn(2, 61, mp);       //C#4
  delay(tempo/4);
  Serial1.write(B10101010);
  allNotesOff(0);
  allNotesOff(1);
  noteOff(2, 61);
  noteOn(0, 47, mf);       //      18-1
  noteOn(2, 59, mp);       //B3
  delay(tempo);
  Serial1.write(B11110000);
  allNotesOff(0);
  noteOff(2, 59);
  noteOn(0, 40, mf);       //      18-1-and
  noteOn(0, 47, mf);
  noteOn(1, 74, f);        //D5
  delay(tempo/2);
  Serial1.write(B00001111);
  noteOff(1, 62);
  noteOn(1, 71, f);        //B5
  delay(tempo/2);
  Serial1.write(B11111111);
  allNotesOff(0);
  allNotesOff(1);
  noteOn(1, 74, f);        //D5    18-2
  delay(tempo);
  Serial1.write(B11111111);
  noteOff(1, 62);
  noteOn(0, 55, mf);       //      18-2-and
  noteOn(0, 57, mf);
  noteOn(0, 61, mf);
  noteOn(1, 73, f);
  noteOn(2, 64, mp);       //E4
  delay(tempo/4);
  Serial1.write(B01111110);
  noteOff(2, 64);
  noteOn(2, 62, mp);       //D4
  delay(tempo/4);
  Serial1.write(B00111100);
  noteOff(2, 62);
  noteOn(2, 61, mp);       //C#4
  delay(tempo/4);
  Serial1.write(B00011000);
  noteOff(2, 61);
  noteOn(2, 59, mp);       //B3
  delay(tempo*3/20);
  Serial1.write(B00011000);
  delay(tempo/30);
  Serial1.write(B00111100);
  delay(tempo/30);
  Serial1.write(B01111110);
  delay(tempo/30);
  Serial1.write(B11111111);
  allNotesOff(0);
  allNotesOff(1);
  noteOff(2, 59);
  noteOn(0, 45, mf);       //      19-1
  noteOn(2, 57, mp);       //A3
  delay(tempo);
  Serial1.write(B01010101);
  allNotesOff(0);
  noteOff(2, 57);
  noteOn(0, 38, mf);       //      19-1-and
  noteOn(0, 45, mf);
  noteOn(1, 72, f);        //C5
  delay(tempo/2);
  Serial1.write(B10101010);
  noteOff(1, 72);
  noteOn(1, 69, f);        //A4
  delay(tempo/2);
  Serial1.write(B01010101);
  allNotesOff(0);
  allNotesOff(1);
  noteOn(1, 72, f);        //C5    19-2
  delay(tempo);
  Serial1.write(B11111111);
  noteOff(1, 72);
  noteOn(0, 55, mf);       //      19-2-and
  noteOn(0, 59, mf);
  noteOn(1, 71, f);        //B4
  noteOn(2, 62, mp);       //D4
  delay(tempo/4);
  Serial1.write(B01111110);
  noteOff(2, 62);
  noteOn(2, 60, mp);       //C4
  delay(tempo/4);
  Serial1.write(B00111100);
  noteOff(2, 60);
  noteOn(2, 59, mp);       //B3
  delay(tempo/4);
  Serial1.write(B00011000);
  noteOff(2, 59);
  noteOn(2, 57, mp);       //A3
  delay(tempo/4);
  allNotesOff(0);
  allNotesOff(1);
  noteOff(2, 57);
  noteOn(0, 43, mf);       //      20-1
  noteOn(2, 55, mp);       //G3
  for(byte x = 0; x < 6; x++){
    Serial1.write(B01010101);
    delay(tempo/12);
    Serial1.write(B10101010);
    delay(tempo/12);
  }
  Serial1.write(B11111111);
  allNotesOff(0);
  noteOff(2, 55);
  noteOn(0, 54, mf);       //      20-1-and
  noteOn(0, 57, mf);
  noteOn(1, 71, f);
  noteOn(2, 59, mp);
  delay(tempo/4);
  Serial1.write(B00011000);
  noteOff(2, 59);
  noteOn(2, 63, mp);
  delay(tempo/4);
  Serial1.write(B00111100);
  noteOff(2, 63);
  noteOn(2, 66, mp);
  delay(tempo/4);
  Serial1.write(B01111110);
  noteOff(2, 66);
  noteOn(2, 71, mp);
  delay(tempo/4);
  Serial1.write(B11111111);
  allNotesOff(0);
  allNotesOff(1);
  noteOff(2, 71);
  noteOn(0, 55, mf);       //      20-2
  noteOn(0, 59, mf);
  noteOn(1, 76, f);
  noteOn(2, 64, mp);
  delay(tempo/4);
  Serial1.write(zero);
  noteOff(2, 64);
  delay(tempo*3/4);
  Serial1.write(B11111111);
  allNotesOff(0);
  allNotesOff(1);
  noteOn(0, 28, f);        //      20-2-and
  noteOn(0, 40, f);
  noteOn(0, 55, f);
  noteOn(0, 59, f);
  noteOn(0, 64, f);
  noteOn(1, 64, f);
  noteOn(2, 64, mf);
  delay(tempo/4);
  allNotesOff(2);
  delay(tempo*3/4);
  allNotesOff(0);
  allNotesOff(1);
  //*/
  //                      TREPAK-----------------------------------------------------------------------------------------------------------------------------------------------
  programChange(127, 0, strings);
  programChange(127, 1, brass2);
  programChange(127, 2, tbone2);
  programChange(127, 3, horn2);
  programChange(127, 4, flute1);
  programChange(127, 5, harp1);
  programChange(0, 9, 127);
  noteOn(0, 48, f);
  noteOn(0, 60, f);
  noteOn(0, 64, f);
  noteOn(0, 67, f);
  delay(1000);
  allNotesOff(0);
  noteOn(1, 48, f);
  noteOn(1, 60, f);
  noteOn(1, 64, f);
  noteOn(1, 67, f);
  delay(1000);
  allNotesOff(1);
  noteOn(2, 48, f);
  noteOn(2, 60, f);
  noteOn(2, 64, f);
  noteOn(2, 67, f);
  delay(1000);
  allNotesOff(2);
  noteOn(3, 48, f);
  noteOn(3, 60, f);
  noteOn(3, 64, f);
  noteOn(3, 67, f);
  delay(1000);
  allNotesOff(3);
  noteOn(4, 48, f);
  noteOn(4, 60, f);
  noteOn(4, 64, f);
  noteOn(4, 67, f);
  delay(1000);
  allNotesOff(4);
  noteOn(5, 60, f);
  delay(50);
  noteOff(5, 60);
  noteOn(5, 64, f);
  delay(50);
  noteOff(5, 64);
  noteOn(5, 67, f);
  delay(50);
  noteOff(5, 67);
  noteOn(5, 72, f);
  delay(1000);
  allNotesOff(5);

}
