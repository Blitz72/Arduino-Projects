byte address1[4] = {0x40, 0xAA, 0xE5, 0xAD};
byte address2[4] = {0x40, 0xAA, 0xE6, 0x70};
byte address3[4] = {0x40, 0xAA, 0x00, 0x00};
byte myAddress1[2] = {0xFF, 0xFE};
byte myAddress2[2] = {0xFF, 0xFE};
byte myAddress3[2] = {0xFF, 0xFE};
byte zero = 0;

void xbee1tx(byte valA, byte valC, byte valL){
  Serial1.write(0x7E);                //Start delimiter
  Serial1.write(zero);                //Length 1
  Serial1.write(0x11);                //Length 2
  Serial1.write(0x10);                //Frame type
  Serial1.write(zero);                //Frame ID, 0 = no response sent
  Serial1.write(zero);                //Address high
  Serial1.write(0x13);
  Serial1.write(0xA2);
  Serial1.write(zero);
  Serial1.write(address1[0]);         //Address low
  Serial1.write(address1[1]);
  Serial1.write(address1[2]);
  Serial1.write(address1[3]);
  Serial.print("64 bit address 1: ");
  Serial.write(address1, 4);
  Serial.println();
  Serial1.write(myAddress1[0]);       //16-bit address
  Serial1.write(myAddress1[1]);
  Serial.print("16 bit address 1: ");
  Serial.write(myAddress1, 2);
  Serial.println();
  Serial1.write(zero);                //# of hops, 0 = max
  Serial1.write(0x01);                //Options, 1 = disable ACK, 0x20 = EN encryp, 0x40 = use extended TX timeout
  Serial1.write(valA);
  Serial1.write(valC);
  Serial1.write(valL);
  long sum = 0x10 + 0x13 + 0xA2 + address1[0] + address1[1] + address1[2] + address1[3] + myAddress1[0] + myAddress1[1] + 0x01 + valA + valC + valL;
  byte checksum = 0xFF - (sum & 0xFF);
  Serial1.write(checksum);  //Checksum
}

void xbee2tx(byte valA, byte valC, byte valL){
  Serial1.write(0x7E);                //Start delimiter
  Serial1.write(zero);                //Length 1
  Serial1.write(0x11);                //Length 2
  Serial1.write(0x10);                //Frame type
  Serial1.write(zero);                //Frame ID, 0 = no response sent
  Serial1.write(zero);                //Address high
  Serial1.write(0x13);
  Serial1.write(0xA2);
  Serial1.write(zero);
  Serial1.write(address2[0]);         //Address low
  Serial1.write(address2[1]);
  Serial1.write(address2[2]);
  Serial1.write(address2[3]);
  Serial.print("64 bit address 2: ");
  Serial.write(address2, 4);
  Serial.println();
  Serial1.write(myAddress2[0]);       //16-bit address
  Serial1.write(myAddress2[1]);
  Serial.print("16 bit address 2: ");
  Serial.write(myAddress2, 2);
  Serial.println();
  Serial1.write(zero);                //# of hops, 0 = max
  Serial1.write(0x01);                //Options, 1 = disable ACK, 0x20 = EN encryp, 0x40 = use extended TX timeout
  Serial1.write(valA);
  Serial1.write(valC);
  Serial1.write(valL);
  long sum = 0x10 + 0x13 + 0xA2 + address2[0] + address2[1] + address2[2] + address2[3] + myAddress2[0] + myAddress2[1] + 0x01 + valA + valC + valL;
  byte checksum = 0xFF - (sum & 0xFF);
  Serial1.write(checksum);  //Checksum
}

void xbee3tx(byte valA, byte valC, byte valL){
  Serial1.write(0x7E);                //Start delimiter
  Serial1.write(zero);                //Length 1
  Serial1.write(0x11);                //Length 2
  Serial1.write(0x10);                //Frame type
  Serial1.write(zero);                //Frame ID, 0 = no response sent
  Serial1.write(zero);                //Address high
  Serial1.write(0x13);
  Serial1.write(0xA2);
  Serial1.write(zero);
  Serial1.write(address3[0]);         //Address low
  Serial1.write(address3[1]);
  Serial1.write(address3[2]);
  Serial1.write(address3[3]);
  Serial.print("64 bit address 1: ");
  Serial.write(address3, 4);
  Serial.println();
  Serial1.write(myAddress3[0]);       //16-bit address
  Serial1.write(myAddress3[1]);
  Serial.print("16 bit address 1: ");
  Serial.write(myAddress3, 2);
  Serial.println();
  Serial1.write(zero);                //# of hops, 0 = max
  Serial1.write(0x01);                //Options, 1 = disable ACK, 0x20 = EN encryp, 0x40 = use extended TX timeout
  Serial1.write(valA);
  Serial1.write(valC);
  Serial1.write(valL);
  long sum = 0x10 + 0x13 + 0xA2 + address3[0] + address3[1] + address3[2] + address3[3] + myAddress3[0] + myAddress3[1] + 0x01 + valA + valC + valL;
  byte checksum = 0xFF - (sum & 0xFF);
  Serial1.write(checksum);  //Checksum
}
  
void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  delay(5000);

}

void loop() {
  xbee1tx(B00000001, B00000001, B00000001);
  delay(1000);
  xbee2tx(B00000011, B00000011, B00000011);
  delay(1000);
  xbee3tx(B00000111, B00000111, B00000111);
  delay(1000);
  xbee1tx(B00010000, B00010000, B00010000);
  delay(1000);
  xbee2tx(B00110000, B00110000, B00110000);
  delay(1000);
  xbee3tx(B01110000, B01110000, B01110000);
  delay(1000);
}
