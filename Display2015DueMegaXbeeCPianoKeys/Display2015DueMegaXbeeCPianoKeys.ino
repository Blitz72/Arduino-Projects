int tempo = 1664;

byte addressC[4] = {0x40, 0xAA, 0xE6, 0x63};      //address of coordinator

byte address1[4] = {0x40, 0xAA, 0xE5, 0xAD};      //R.I.P. Parallax Xbee Explorer is not 5V tolerant!  Might still be alive!!!
byte address2[4] = {0x40, 0xAA, 0xE6, 0x70};
byte address3[4] = {0x40, 0xAA, 0xE5, 0x8A};
byte address4[4] = {0x40, 0xAA, 0xE5, 0x88};
byte address5[4] = {0x40, 0xAA, 0xE6, 0x7E};
byte addressB[4] = {0x00, 0x00, 0xFF, 0xFF};

byte myAddress1[2] = {0xFF, 0xFE};                //initialize to FFFE for broadcast transmission, use getAPIid later from Xbee library
byte myAddress2[2] = {0xFF, 0xFE};                //initialize to FFFE for broadcast transmission, use getAPIid later from Xbee library
byte myAddress3[2] = {0xFF, 0xFE};                //initialize to FFFE for broadcast transmission, use getAPIid later from Xbee library
byte myAddress4[2] = {0xFF, 0xFE};                //initialize to FFFE for broadcast transmission, use getAPIid later from Xbee library
byte myAddress5[2] = {0xFF, 0xFE};                //initialize to FFFE for broadcast transmission, use getAPIid later from Xbee library

byte zero = byte(0x00);

byte valueA = 0;
byte valueC = 0;
byte valueL = 0;

void xbeeTX(byte valA, byte valC, byte valL){
  Serial1.write(0x7E);                //Start delimiter
  Serial1.write(0x00);                //Length 1
  Serial1.write(0x11);                //Length 2
  Serial1.write(0x10);                //Frame type
  Serial1.write(0x00);                //Frame ID, 0 = no response sent
  Serial1.write(0x00);                //Address high
  Serial1.write(0x13);
  Serial1.write(0xA2);
  Serial1.write(0x00);
  Serial1.write(address2[0]);         //Address low
  Serial1.write(address2[1]);
  Serial1.write(address2[2]);
  Serial1.write(address2[3]);
//  Serial.print("64 bit address 2: ");
//  Serial.print(address2[0], HEX);
//  Serial.print(address2[1], HEX);
//  Serial.print(address2[2], HEX);
//  Serial.print(address2[3], HEX);
//  Serial.println();
  Serial1.write(myAddress2[0]);       //16-bit address
  Serial1.write(myAddress2[1]);
//  Serial.print("16 bit address 2: ");
//  Serial.print(myAddress2[0], HEX);
//  Serial.print(myAddress2[1], HEX);
//  Serial.println();
  Serial1.write(0x00);                //# of hops, 0 = max
  Serial1.write(0x01);                //Options, 1 = disable ACK, 0x20 = EN encryp, 0x40 = use extended TX timeout
  Serial1.write(valA);
//  Serial.print("valA = ");
//  Serial.println(valA, HEX);
  Serial1.write(valC);
//  Serial.print("valC = ");
//  Serial.println(valC, HEX);
  Serial1.write(valL);
//  Serial.print("valL = ");
//  Serial.println(valL, HEX);
  long sum = 0x10 + 0x13 + 0xA2 + address2[0] + address2[1] + address2[2] + address2[3] + myAddress2[0] + myAddress2[1] + 0x01 + valA + valC + valL;
//  byte checksum = 0xFF - (sum & 0xFF);
  Serial1.write(0xFF - (sum & 0xFF));  //Checksum
}

void setup() {
//  Serial.begin(9600);
  Serial1.begin(57600);
//  delay(10000);
  
//  xbeeTX(0x01, 0x02, 0x03);

}

void loop() {
  //  A7  A6  A5  A4  A3  A2  A1  A0  C7  C6  C5  C4  C3  C2  C1  C0  L7  L6  L5  L4  L3  L2  L1  L0
  //  C   Db  D   Eb  E   F   Gb  G   Ab  A   Bb  B   C   Db  D   Eb  E   F   Gb  G   Ab  A   Bb  B
  
  tempo = 2000;

  xbeeTX(~0x01, 0xff, ~0x10);    //G
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x01, 0xff, ~0x10);    //G
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x01, 0xff, ~0x10);    //G
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x01, 0xff, ~0x10);    //G
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x01, 0xff, ~0x10);    //G
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x04, 0xff, ~0x40);    //F
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x08, 0xff, ~0x80);    //E
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x20, ~0x02, 0xff);    //D
  delay(tempo/8);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo);
  xbeeTX(~0x01, 0xff, ~0x10);    //G
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x01, 0xff, ~0x10);    //G
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x01, 0xff, ~0x10);    //G
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x01, 0xff, ~0x10);    //G
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x01, 0xff, ~0x10);    //G
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x04, 0xff, ~0x40);    //F
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x08, 0xff, ~0x80);    //E
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x20, ~0x02, 0xff);    //D
  delay(tempo/8);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo);
  
  tempo = 1714;
  
  for (int i = 0; i < 8; i++){
    valueA = (1 << (7-i));
    xbeeTX(~valueA, 0xff, 0xff);
    valueA = 0;
    delay(tempo/48);
  }
  for (int i = 0; i < 8; i++){
    valueC = (1 << (7-i));
    xbeeTX(0xff, ~valueC, 0xff);
    valueC = 0;
    delay(tempo/48);
  }
  for (int i = 0; i < 8; i++){
    valueL = (1 << (7-i));
    xbeeTX(0xff, 0xff, ~valueL);
    valueL = 0;
    delay(tempo/48);
  }
  
//  xbeeTX(0xff, 0xff, 0xff);
//  VH

  xbeeTX(~0x80, 0xff, 0xff);    //1    C
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x80, 0xff, 0xff);    //1 and    C
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x81, ~0x12, 0xff);   //2   (C, G), (B, D)
  delay(tempo/16);
  xbeeTX(~0x01, ~0x12, 0xff);
  delay(tempo/16);
  xbeeTX(~0x80, 0xff, 0xff);    //2 and
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x80, 0xff, 0xff);    //3
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x81, ~0x08, ~0x80);   //3 and    (C, G), (C), (E)
  delay(tempo/16);
  xbeeTX(~0x01, ~0x08, ~0x80);
  delay(tempo/16);
  xbeeTX(~0x80, 0xff, 0xff);    //4
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x80, 0xff, 0xff);    //4 and
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x84, ~0x44, 0xff);   //5    (C, F), (A, C)
  delay(tempo/16);
  xbeeTX(~0x04, ~0x44, 0xff);
  delay(tempo/16);
  xbeeTX(~0x80, 0xff, 0xff);    //5 and
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x80, 0xff, 0xff);    //6
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x84, ~0x44, 0xff);   //6 and    (C, F), (A, C)
  delay(tempo/16);
  xbeeTX(~0x04, ~0x44, 0xff);
  delay(tempo/16);
  xbeeTX(~0x80, 0xff, 0xff);    //7
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x81, ~0x12, 0xff);   //7 and   (C, G), (B, D)
  delay(tempo/16);
  xbeeTX(~0x01, ~0x12, 0xff);
  delay(tempo/16);
  xbeeTX(~0x80, 0xff, 0xff);    //8
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x81, ~0x12, 0xff);   //8 and   (C, G), (B, D)  G, B, D hold over until 9 and
  delay(tempo/16);
  xbeeTX(~0x01, ~0x12, 0xff);
  delay(tempo/16);
  xbeeTX(~0x81, ~0x12, 0xff);   //9
  delay(tempo/16);
  xbeeTX(~0x01, ~0x12, 0xff);
  delay(tempo/16);
  xbeeTX(~0x81, ~0x12, 0xff);   //9 and
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x81, ~0x08, ~0x80);  //10    (C, G), (C), (E)
  delay(tempo/16);
  xbeeTX(~0x01, ~0x08, ~0x80);
  delay(tempo/16);
  xbeeTX(~0x80, 0xff, 0xff);    //10 and
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x80, 0xff, 0xff);    //11
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x84, ~0x44, 0xff);   //11 and    (C, F), (A, C)
  delay(tempo/16);
  xbeeTX(~0x04, ~0x44, 0xff);
  delay(tempo/16);
  xbeeTX(~0x80, 0xff, 0xff);    //12
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x80, ~0x08, ~0x44);  //12 and    (C), (C), (F, A)
  delay(tempo/16);
  xbeeTX(0xff, ~0x08, ~0x44);
  delay(tempo/16);
  xbeeTX(~0x80, ~0x08, ~0x44);  //13
  delay(tempo/16);
  xbeeTX(0xff, ~0x08, ~0x44);
  delay(tempo/16);
  xbeeTX(~0x80, ~0x08, ~0x90);  //13 and    (C), (C), (E, G)
  delay(tempo/16);
  xbeeTX(0xff, ~0x08, ~0x90);
  delay(tempo/16);
  xbeeTX(~0x80, ~0x08, ~0x90);  //14
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x80, ~0x0a, ~0x10);  //14 and    (C), (C, D), (G) hold until next measure
  delay(tempo/16);
  xbeeTX(0xff, ~0x0a, ~0x10);
  delay(tempo/16);
  xbeeTX(~0x80, ~0x0a, ~0x10);  //15
  delay(tempo/16);
  xbeeTX(0xff, ~0x0a, ~0x10);
  delay(tempo/16);
  xbeeTX(~0x80, ~0x0a, ~0x10);  //15 and
  delay(tempo/16);
  xbeeTX(0xff, ~0x0a, ~0x10);
  delay(tempo/16);
  xbeeTX(~0x80, ~0x0a, ~0x10);  //16
  delay(tempo/16);
  xbeeTX(0xff, ~0x0a, ~0x10);
  delay(tempo/16);
  xbeeTX(~0x80, ~0x0a, ~0x10);  //16 and
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  
  
  xbeeTX(~0x80, 0xff, 0xff);    //1    C
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x80, 0xff, 0xff);    //1 and    C
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x81, ~0x12, 0xff);   //2   (C, G), (B, D)
  delay(tempo/16);
  xbeeTX(~0x01, ~0x12, 0xff);
  delay(tempo/16);
  xbeeTX(~0x80, 0xff, 0xff);    //2 and
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x80, 0xff, 0xff);    //3
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x81, ~0x08, ~0x80);   //3 and    (C, G), (C), (E)
  delay(tempo/16);
  xbeeTX(~0x01, ~0x08, ~0x80);
  delay(tempo/16);
  xbeeTX(~0x80, 0xff, 0xff);    //4
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x80, 0xff, 0xff);    //4 and
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x84, ~0x44, 0xff);   //5    (C, F), (A, C)
  delay(tempo/16);
  xbeeTX(~0x04, ~0x44, 0xff);
  delay(tempo/16);
  xbeeTX(~0x80, 0xff, 0xff);    //5 and
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x80, 0xff, 0xff);    //6
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x84, ~0x44, 0xff);   //6 and    (C, F), (A, C)
  delay(tempo/16);
  xbeeTX(~0x04, ~0x44, 0xff);
  delay(tempo/16);
  xbeeTX(~0x80, 0xff, 0xff);    //7
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x81, ~0x12, 0xff);   //7 and   (C, G), (B, D)
  delay(tempo/16);
  xbeeTX(~0x01, ~0x12, 0xff);
  delay(tempo/16);
  xbeeTX(~0x80, 0xff, 0xff);    //8
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x81, ~0x12, 0xff);   //8 and   (C, G), (B, D)  G, B, D hold over until 9 and
  delay(tempo/16);
  xbeeTX(~0x01, ~0x12, 0xff);
  delay(tempo/16);
  xbeeTX(~0x81, ~0x12, 0xff);   //9
  delay(tempo/16);
  xbeeTX(~0x01, ~0x12, 0xff);
  delay(tempo/16);
  xbeeTX(~0x81, ~0x12, 0xff);   //9 and
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x81, ~0x08, ~0x80);  //10    (C, G), (C), (E)
  delay(tempo/16);
  xbeeTX(~0x01, ~0x08, ~0x80);
  delay(tempo/16);
  xbeeTX(~0x80, 0xff, 0xff);    //10 and
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x80, 0xff, 0xff);    //11
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x84, ~0x44, 0xff);   //11 and    (C, F), (A, C)
  delay(tempo/16);
  xbeeTX(~0x04, ~0x44, 0xff);
  delay(tempo/16);
  xbeeTX(~0x80, 0xff, 0xff);    //12
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x80, ~0x08, ~0x44);  //12 and    (C), (C), (F, A)
  delay(tempo/16);
  xbeeTX(0xff, ~0x08, ~0x44);
  delay(tempo/16);
  xbeeTX(~0x80, ~0x08, ~0x44);  //13
  delay(tempo/16);
  xbeeTX(0xff, ~0x08, ~0x44);
  delay(tempo/16);
  xbeeTX(~0x80, ~0x08, ~0x90);  //13 and    (C), (C), (E, G)
  delay(tempo/16);
  xbeeTX(0xff, ~0x08, ~0x90);
  delay(tempo/16);
  xbeeTX(~0x80, ~0x08, ~0x90);  //14
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  xbeeTX(~0x80, ~0x0a, ~0x10);  //14 and    (C), (C, D), (G) hold until next measure
  delay(tempo/16);
  xbeeTX(0xff, ~0x0a, ~0x10);
  delay(tempo/16);
  xbeeTX(~0x80, ~0x0a, ~0x10);  //15
  delay(tempo/16);
  xbeeTX(0xff, ~0x0a, ~0x10);
  delay(tempo/16);
  xbeeTX(~0x80, ~0x0a, ~0x10);  //15 and
  delay(tempo/16);
  xbeeTX(0xff, ~0x0a, ~0x10);
  delay(tempo/16);
  xbeeTX(~0x80, ~0x0a, ~0x10);  //16
  delay(tempo/16);
  xbeeTX(0xff, ~0x0a, ~0x10);
  delay(tempo/16);
  xbeeTX(~0x80, ~0x0a, ~0x10);  //16 and
  delay(tempo/16);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo/16);
  
  valueA = 0;
  valueC = 0;
  valueL = 0;
  
  for (int i = 0; i < 8; i++){
    valueL = (1 << i);
    xbeeTX(0xff, 0xff, ~valueL);
    valueL = 0;
    delay(tempo/48);
  }
  for (int i = 0; i < 8; i++){
    valueC = (1 << i);
    xbeeTX(0xff, ~valueC, 0xff);
    valueC = 0;
    delay(tempo/48);
  }
  for (int i = 0; i < 9; i++){
    valueA = (1 << i);
    xbeeTX(~valueA, 0xff, 0xff);
    valueA = 0;
    delay(tempo/48);
  }
  xbeeTX(0xff, 0xff, 0xff);  
  
  delay(tempo/2);
  
  
  xbeeTX(0xff, ~0x80, 0xff);    //1-1
  delay(tempo/8);
  xbeeTX(0xff, ~0x01, 0xff);    //1-1 and
  delay(tempo/8);
  xbeeTX(0xff, 0xff, ~0x08);    //1-2
  delay(tempo/8);
  xbeeTX(0xff, ~0x80, 0xff);    //1-2 and
  delay(tempo/8);
  xbeeTX(0xff, ~0x01, 0xff);    //1-3
  delay(tempo/8);
  xbeeTX(0xff, 0xff, ~0x08);    //1-3 and, 1-4
  delay(tempo/4);
  xbeeTX(0xff, ~0x80, 0xff);    //1-4 and, 2-1
  delay(tempo/4);
  xbeeTX(0xff, ~0x01, 0xff);    //2-1 and
  delay(tempo/8);
  xbeeTX(0xff, 0xff, ~0x40);    //2-2
  delay(tempo/8);
  xbeeTX(0xff, ~0x80, 0xff);    //2-2 and
  delay(tempo/8);
  xbeeTX(0xff, ~0x01, 0xff);    //2-3
  delay(tempo/8);
  xbeeTX(0xff, 0xff, ~0x40);    //2-3 and, 2-4
  delay(tempo/4);
  xbeeTX(0xff, ~0x80, 0xff);    //2-4 and, 3-1
  delay(tempo/4);
  xbeeTX(0xff, ~0x01, 0xff);    //3-1 and
  delay(tempo/8);
  xbeeTX(0xff, 0xff, ~0x08);    //3-2
  delay(tempo/8);
  xbeeTX(0xff, ~0x80, 0xff);    //3-2 and
  delay(tempo/8);
  xbeeTX(0xff, ~0x01, 0xff);    //3-3
  delay(tempo/8);
  xbeeTX(0xff, 0xff, ~0x08);    //3-3 and, 3-4
  delay(tempo/4);
  xbeeTX(0xff, ~0x80, 0xff);    //3-4 and, 4-1
  delay(tempo/4);
  xbeeTX(0xff, ~0x01, 0xff);    //4-1 and
  delay(tempo/8);
  xbeeTX(0xff, 0xff, ~0x40);    //4-2
  delay(tempo/8);
  xbeeTX(0xff, ~0x80, 0xff);    //4-2 and
  delay(tempo/8);
  xbeeTX(0xff, ~0x01, 0xff);    //4-3
  delay(tempo/8);
  xbeeTX(0xff, 0xff, ~0x40);    //4-3 and, 4-4
  delay(tempo/4);
  for (byte i = 0; i < 2; i++){
    xbeeTX(~0x80, ~0x80, 0xff);   //4-4 and, 5-1
    delay(tempo/4);
    xbeeTX(~0x10, ~0x20, 0xff);   //5-1 and
    delay(tempo/8);
    xbeeTX(0xff, ~0x88, 0xff);    //5-2
    delay(tempo/8);
    delay(tempo/16);
    xbeeTX(0xff, 0xff, 0xff);
    delay(tempo/16);
    xbeeTX(0xff, ~0x88, 0xff);    //5-3
    delay(tempo/8);
    xbeeTX(~0x10, ~0x20, 0xff);   //5-3 and
    delay(tempo/8);
    xbeeTX(~0x80, ~0x80, 0xff);   //5-4
    delay(tempo/4);
    xbeeTX(~0x10, ~0x20, 0xff);   //6-1, 6-2
    delay(tempo/4);
    delay(tempo/8);
    xbeeTX(~0x80, ~0x80, 0xff);   //6-2 and to 6-4
    delay(tempo/4);
    delay(tempo/8);
    delay(tempo/16);
    xbeeTX(0xff, 0xff, 0xff);
    delay(tempo/16);
    xbeeTX(~0x80, ~0x80, 0xff);   //6-4 and, 7-1
    delay(tempo/4);
    xbeeTX(~0x10, ~0x20, 0xff);   //7-1 and
    delay(tempo/8);
    xbeeTX(0xff, ~0x88, 0xff);    //7-2
    delay(tempo/8);
    delay(tempo/16);
    xbeeTX(0xff, 0xff, 0xff);
    delay(tempo/16);
    xbeeTX(0xff, ~0x88, 0xff);    //7-3 to 8-4
    delay(tempo);
    xbeeTX(0xff, 0xff, 0xff);
    delay(tempo/4);
    delay(tempo/8);
    xbeeTX(~0x80, ~0x80, 0xff);   //8-4 and, 9-1
    delay(tempo/4);
    xbeeTX(~0x10, ~0x20, 0xff);   //9-1 and
    delay(tempo/8);
    xbeeTX(0xff, ~0x88, 0xff);    //9-2
    delay(tempo/8);
    delay(tempo/16);
    xbeeTX(0xff, 0xff, 0xff);
    delay(tempo/16);
    xbeeTX(0xff, ~0x88, 0xff);    //9-3
    delay(tempo/8);
    xbeeTX(~0x10, ~0x20, 0xff);   //9-3 and
    delay(tempo/8);
    xbeeTX(~0x80, ~0x80, 0xff);   //9-4
    delay(tempo/4);
    xbeeTX(~0x10, ~0x20, 0xff);   //10-1, 10-2
    delay(tempo/4);
    delay(tempo/8);
    xbeeTX(~0x80, ~0x80, 0xff);   //10-2 and to 10-4
    delay(tempo/2);
    xbeeTX(~0x10, ~0x81, ~0x08);   //10-4 and to 11-2
    delay(tempo/4);
    delay(tempo/8);
    delay(tempo/16);
    xbeeTX(0xff, 0xff, 0xff);
    delay(tempo/16);
    xbeeTX(~0x10, ~0x21, ~0x02);   //11-2 and
    delay(tempo/16);
    xbeeTX(0xff, 0xff, 0xff);
    delay(tempo/16);
    xbeeTX(~0x10, ~0x21, ~0x02);   //11-3 to 12-2 and
    delay(tempo);
    xbeeTX(0xff, 0xff, 0xff);     //12-3 to 12-4
    delay(tempo/4);
    delay(tempo/8);
    xbeeTX(~0x80, ~0x88, ~0x08);   //12-4 and to 13-2
    delay(tempo/4);
    delay(tempo/8);
    delay(tempo/16);
    xbeeTX(0xff, 0xff, 0xff);
    delay(tempo/16);
    xbeeTX(~0x10, ~0x21, ~0x02);   //13-2 and
    delay(tempo/16);
    xbeeTX(0xff, 0xff, 0xff);
    delay(tempo/16);
    xbeeTX(~0x10, ~0x21, ~0x02);   //13-3 to 14-2 and
    delay(tempo);
    xbeeTX(0xff, 0xff, 0xff);     //14-3 to 14-4
    delay(tempo/4);
    delay(tempo/8);
  }
  for(byte i = 0; i < 3; i++){
    xbeeTX(0xff, ~0x80, ~0x08);      //14-4 and
    delay(tempo/8);
    xbeeTX(~0x44, ~0x84, 0xff);      //15-1
    delay(tempo/16);
    xbeeTX(0xff, 0xff, 0xff);
    delay(tempo/16);
    xbeeTX(~0x44, ~0x84, 0xff);      //15-1 and
    delay(tempo/16);
    xbeeTX(0xff, 0xff, 0xff);
    delay(tempo/16);
    xbeeTX(~0x44, ~0x84, 0xff);      //15-2
    delay(tempo/16);
    xbeeTX(0xff, 0xff, 0xff);
    delay(tempo/16);
    xbeeTX(~0x11, ~0x21, 0xff);      //15-2 and
    delay(tempo/8);
    xbeeTX(0xff, 0xff, 0xff);      //15-3 eighth rest
    delay(tempo/8);
    xbeeTX(~0x10, ~0x81, ~0x08);      //15-3 and
    delay(tempo/16);
    xbeeTX(~0x08, 0xff, 0xff);      //15-3 and a (grace note)
    delay(tempo/16);
    xbeeTX(~0x04, ~0x80, ~0x48);    //15-4
    delay(tempo/16);
    xbeeTX(0xff, 0xff, 0xff);
    delay(tempo/16);
    xbeeTX(~0x04, ~0x80, ~0x48);    //15-4 and
    delay(tempo/16);
    xbeeTX(0xff, 0xff, 0xff);
    delay(tempo/16);
    xbeeTX(~0x10, ~0x81, ~0x08);      //16-1    15-3 and
    delay(tempo/16);
    xbeeTX(~0x08, 0xff, 0xff);      //16-1 ee    15-3 and a (grace note)
    delay(tempo/16);
    xbeeTX(~0x04, ~0x80, ~0x48);    //16-1 and    15-4
    delay(tempo/16);
    xbeeTX(0xff, 0xff, 0xff);
    delay(tempo/16);
    xbeeTX(~0x04, ~0x80, ~0x48);    //16-2    15-4 and
    delay(tempo/16);
    xbeeTX(0xff, 0xff, 0xff);
    delay(tempo/16);
    xbeeTX(~0x10, ~0x81, ~0x08);      //16-2 and    15-3 and
    delay(tempo/16);
    xbeeTX(~0x08, 0xff, 0xff);      //16-2 and a    15-3 and a (grace note)
    delay(tempo/16);
    xbeeTX(~0x04, ~0x80, ~0x48);    //16-3    15-4
    delay(tempo/16);
    xbeeTX(0xff, 0xff, 0xff);
    delay(tempo/16);
    xbeeTX(~0x04, ~0x80, ~0x48);    //16-3 and    15-4 and
    delay(tempo/16);
    xbeeTX(0xff, 0xff, 0xff);
    delay(tempo/16);
    xbeeTX(~0x10, ~0x81, ~0x08);      //16-4
    delay(tempo/16);
    xbeeTX(0xff, 0xff, 0xff);
    delay(tempo/16);
  }
  xbeeTX(~0x10, ~0x01, 0xff);      //16-4 and
  delay(tempo/8);
  xbeeTX(~0x80, ~0x88, ~0x08);      //17-1 theEnd
  delay(tempo);
  xbeeTX(0xff, 0xff, 0xff);
  delay(tempo);
  
//  xbeeTX(0x01, 0x03, 0x07);
//  delay(10000);
}
