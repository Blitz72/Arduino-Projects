
#define tempo  1714


void setup() {
  
  DDRA = 0xff;        //  A7  A6  A5  A4  A3  A2  A1  A0  C7  C6  C5  C4  C3  C2  C1  C0  L7  L6  L5  L4  L3  L2  L1  L0
  DDRC = 0xff;        //  C   Db  D   Eb  E   F   Gb  G   Ab  A   Bb  B   C   Db  D   Eb  E   F   Gb  G   Ab  A   Bb  B 
  DDRL = 0xff;
  
  PORTA = 0xff;
  PORTC = 0xff;
  PORTL = 0xff;
  
}

void loop() {
  PORTA = 0xff;
  PORTC = 0xff;
  PORTL = 0xff;
  delay(10000);
  PORTA = ~0x01;    //G
  PORTL = ~0x10;
  delay(tempo/16);
  PORTA = 0xff;
  PORTL = 0xff;
  delay(120);
  PORTA = ~0x01;    //G
  PORTL = ~0x10;
  delay(tempo/16);
  PORTA = 0xff;
  PORTL = 0xff;
  delay(tempo/16);
  PORTA = ~0x01;    //G
  PORTL = ~0x10;
  delay(tempo/16);
  PORTA = 0xff;
  PORTL = 0xff;
  delay(tempo/16);
  PORTA = ~0x01;    //G
  PORTL = ~0x10;
  delay(tempo/16);
  PORTA = 0xff;
  PORTL = 0xff;
  delay(tempo/16);
  PORTA = ~0x01;    //G
  PORTL = ~0x10;
  delay(tempo/16);
  PORTA = 0xff;
  PORTL = 0xff;
  delay(tempo/16);
  PORTA = ~0x04;    //F
  PORTL = ~0x40;
  delay(tempo/16);
  PORTA = 0xff;
  PORTL = 0xff;
  delay(tempo/16);
  PORTA = ~0x08;    //E
  PORTL = ~0x80;
  delay(tempo/16);
  PORTA = 0xff;
  PORTL = 0xff;
  delay(tempo/16);
  PORTA = ~0x20;    //D
  PORTC = ~0x02;
  delay(tempo/16);
  PORTA = 0xff;
  PORTL = 0xff;
  delay(tempo/16);
  delay(tempo);
  PORTA = ~0x01;    //G
  PORTL = ~0x10;
  delay(tempo/16);
  PORTA = 0xff;
  PORTL = 0xff;
  delay(120);
  PORTA = ~0x01;    //G
  PORTL = ~0x10;
  delay(tempo/16);
  PORTA = 0xff;
  PORTL = 0xff;
  delay(tempo/16);
  PORTA = ~0x01;    //G
  PORTL = ~0x10;
  delay(tempo/16);
  PORTA = 0xff;
  PORTL = 0xff;
  delay(tempo/16);
  PORTA = ~0x01;    //G
  PORTL = ~0x10;
  delay(tempo/16);
  PORTA = 0xff;
  PORTL = 0xff;
  delay(tempo/16);
  PORTA = ~0x01;    //G
  PORTL = ~0x10;
  delay(tempo/16);
  PORTA = 0xff;
  PORTL = 0xff;
  delay(tempo/16);
  PORTA = ~0x04;    //F
  PORTL = ~0x40;
  delay(tempo/16);
  PORTA = 0xff;
  PORTL = 0xff;
  delay(tempo/16);
  PORTA = ~0x08;    //E
  PORTL = ~0x80;
  delay(tempo/16);
  PORTA = 0xff;
  PORTL = 0xff;
  delay(tempo/16);
  PORTA = ~0x20;    //D
  PORTC = ~0x02;
  delay(tempo/16);
  PORTA = 0xff;
  PORTL = 0xff;
  delay(tempo/16);
  delay(tempo/2);
  PORTA = ~0x80;
  delay(tempo/48);
  PORTA = ~0x40;
  delay(tempo/48);
  PORTA = ~0x20;
  delay(tempo/48);
  PORTA = ~0x10;
  delay(tempo/48);
  PORTA = ~0x08;
  delay(tempo/48);
  PORTA = ~0x04;
  delay(tempo/48);
  PORTA = ~0x02;
  delay(tempo/48);
  PORTA = ~0x01;
  delay(tempo/48);
  PORTA = 0xff;
  PORTC = ~0x80;
  delay(tempo/48);
  PORTC = ~0x40;
  delay(tempo/48);
  PORTC = ~0x20;
  delay(tempo/48);
  PORTC = ~0x10;
  delay(tempo/48);
  PORTC = ~0x08;
  delay(tempo/48);
  PORTC = ~0x04;
  delay(tempo/48);
  PORTC = ~0x02;
  delay(tempo/48);
  PORTC = ~0x01;
  delay(tempo/48);
  PORTC = 0xff;
  PORTL = ~0x80;
  delay(tempo/48);
  
  PORTA = ~0x80;          //1    C
  delay(tempo/16);
  PORTA = 0xff;
  delay(tempo/16);
  PORTA = 0x7f;          //1 and    C
  delay(tempo/16);
  PORTA = 0xff;
  delay(tempo/16);
  PORTA = 0x7e;          //2    C, G
  PORTC = 0xed;          //     B, D
  delay(tempo/16);
  PORTA = 0xfe;
  delay(tempo/16);

}
