#include <SPI.h>
#include <SD.h>

File myFile;
Sd2Card card;
SdVolume volume;
SdFile root;

int lightCount = 48;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------PIXEL DATA-----------------------------------------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


uint16_t pixelDataA[48][12] = {0};
uint16_t pixelDataC[48][12] = {0};
uint16_t pixelDataL[48][12] = {0};





///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------------SETUP--------------------------------------------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup(){

  Serial.begin(9600);
  
  pinMode(52, OUTPUT);
  SD.begin(52);        //use hardware cs pin 53 for Mega 2560 or pin 52 for Due
                       //CLK --> 52
                       //DO  --> 50
                       //DI  --> 51
                       //CS  --> 53
  
  Serial.begin(9600);
  Serial.print("\nInitializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output
  // or the SD library functions will not work.
  //pinMode(10, OUTPUT);     // change this to 53 on a mega


  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  if (!card.init(SPI_HALF_SPEED, 52)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card is inserted?");
    Serial.println("* Is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    return;
  } else {
    Serial.println("Wiring is correct and a card is present.");
  }

  // print the type of card
  Serial.print("\nCard type: ");
  switch (card.type()) {
    case SD_CARD_TYPE_SD1:
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println("SDHC");
      break;
    default:
      Serial.println("Unknown");
  }

  // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
  if (!volume.init(card)) {
    Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
    return;
  }


  // print the type and size of the first FAT-type volume
  uint32_t volumesize;
  Serial.print("\nVolume type is FAT");
  Serial.println(volume.fatType(), DEC);
  Serial.println();

  volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  volumesize *= 512;                            // SD card blocks are always 512 bytes
  Serial.print("Volume size (bytes): ");
  Serial.println(volumesize);
  Serial.print("Volume size (Kbytes): ");
  volumesize /= 1024;
  Serial.println(volumesize);
  Serial.print("Volume size (Mbytes): ");
  volumesize /= 1024;
  Serial.println(volumesize);


  Serial.println("\nFiles found on the card (name, date and size in bytes): ");
  root.openRoot(volume);

  // list all files in the card with date and size
  root.ls(LS_R | LS_DATE | LS_SIZE);
  
/*
    myFile = SD.open("Red.bmp", FILE_READ);          //test to see how data is parsed out of bitmap file
    delay(500);
    if (!myFile) Serial.println("Error opening file!");
    if (myFile){
      for(int x = 0; x < 54; x++){
        int discard = myFile.read();
      }
      for(int x = 1; x <= 3456; x++){
        int i = myFile.read();
        Serial.print(i, HEX);
        Serial.print(", ");
        if(x % 36 == 0) Serial.println();
        
      }
    myFile.close();
    while(1);
    }
*/
  
  myFile = SD.open("GE_LOGO.bmp", FILE_READ);
  delay(10);
  if (!myFile) Serial.println("Error opening file!");
  
  if (myFile){
    for(int x = 0; x < 54; x++){
      int discard = myFile.read();
    }
    
    //pixelDataL
    for(int i = 0; i < 8; i++){
      for(int x = 0; x <= 47; x++){
        uint16_t y = myFile.read();
        y >>= 4;
        if(bitRead(y, 0) == 1) bitSet(pixelDataL[x][3], 7-i); else bitClear(pixelDataL[x][3], 7-i);
        //Serial.print(y, HEX); Serial.print("\t"); Serial.print(pixelDataL[x][3], HEX); Serial.println();
        y >>= 1;
        if(bitRead(y, 0) == 1) bitSet(pixelDataL[x][2], 7-i); else bitClear(pixelDataL[x][2], 7-i);
        //Serial.print(y, HEX); Serial.print("\t"); Serial.print(pixelDataL[x][2], HEX); Serial.println();
        y >>= 1;
        if(bitRead(y, 0) == 1) bitSet(pixelDataL[x][1], 7-i); else bitClear(pixelDataL[x][1], 7-i);
        //Serial.print(y, HEX); Serial.print("\t"); Serial.print(pixelDataL[x][1], HEX); Serial.println();
        y >>= 1;
        if(bitRead(y, 0) == 1) bitSet(pixelDataL[x][0], 7-i); else bitClear(pixelDataL[x][0], 7-i);
        //Serial.print(y, HEX); Serial.print("\t"); Serial.print(pixelDataL[x][0], HEX); Serial.println();
        y = myFile.read();
        y >>= 4;
        if(bitRead(y, 0) == 1) bitSet(pixelDataL[x][7], 7-i); else bitClear(pixelDataL[x][7], 7-i);
        y >>= 1;
        if(bitRead(y, 0) == 1) bitSet(pixelDataL[x][6], 7-i); else bitClear(pixelDataL[x][6], 7-i);
        y >>= 1;
        if(bitRead(y, 0) == 1) bitSet(pixelDataL[x][5], 7-i); else bitClear(pixelDataL[x][5], 7-i);
        y >>= 1;
        if(bitRead(y, 0) == 1) bitSet(pixelDataL[x][4], 7-i); else bitClear(pixelDataL[x][4], 7-i);
        y = myFile.read();
        y >>= 4;
        if(bitRead(y, 0) == 1) bitSet(pixelDataL[x][11], 7-i); else bitClear(pixelDataL[x][11], 7-i);
        y >>= 1;
        if(bitRead(y, 0) == 1) bitSet(pixelDataL[x][10], 7-i); else bitClear(pixelDataL[x][10], 7-i);
        y >>= 1;
        if(bitRead(y, 0) == 1) bitSet(pixelDataL[x][9], 7-i); else bitClear(pixelDataL[x][9], 7-i);
        y >>= 1;
        if(bitRead(y, 0) == 1) bitSet(pixelDataL[x][8], 7-i); else bitClear(pixelDataL[x][8], 7-i);
      }
    }
    
    //pixelDataC
    for(int i = 0; i < 8; i++){
      for(int x = 0; x <= 47; x++){
        uint16_t y = myFile.read();
        y >>= 4;
        if(bitRead(y, 0) == 1) bitSet(pixelDataC[x][3], 7-i); else bitClear(pixelDataC[x][3], 7-i);
        y >>= 1;
        if(bitRead(y, 0) == 1) bitSet(pixelDataC[x][2], 7-i); else bitClear(pixelDataC[x][2], 7-i);
        y >>= 1;
        if(bitRead(y, 0) == 1) bitSet(pixelDataC[x][1], 7-i); else bitClear(pixelDataC[x][1], 7-i);
        y >>= 1;
        if(bitRead(y, 0) == 1) bitSet(pixelDataC[x][0], 7-i); else bitClear(pixelDataC[x][0], 7-i);
        y = myFile.read();
        y >>= 4;
        if(bitRead(y, 0) == 1) bitSet(pixelDataC[x][7], 7-i); else bitClear(pixelDataC[x][7], 7-i);
        y >>= 1;
        if(bitRead(y, 0) == 1) bitSet(pixelDataC[x][6], 7-i); else bitClear(pixelDataC[x][6], 7-i);
        y >>= 1;
        if(bitRead(y, 0) == 1) bitSet(pixelDataC[x][5], 7-i); else bitClear(pixelDataC[x][5], 7-i);
        y >>= 1;
        if(bitRead(y, 0) == 1) bitSet(pixelDataC[x][4], 7-i); else bitClear(pixelDataC[x][4], 7-i);
        y = myFile.read();
        y >>= 4;
        if(bitRead(y, 0) == 1) bitSet(pixelDataC[x][11], 7-i); else bitClear(pixelDataC[x][11], 7-i);
        y >>= 1;
        if(bitRead(y, 0) == 1) bitSet(pixelDataC[x][10], 7-i); else bitClear(pixelDataC[x][10], 7-i);
        y >>= 1;
        if(bitRead(y, 0) == 1) bitSet(pixelDataC[x][9], 7-i); else bitClear(pixelDataC[x][9], 7-i);
        y >>= 1;
        if(bitRead(y, 0) == 1) bitSet(pixelDataC[x][8], 7-i); else bitClear(pixelDataC[x][8], 7-i);
      }
    }
    
    //pixelDataA
    for(int i = 0; i < 8; i++){
      for(int x = 0; x <= 47; x++){
        uint16_t y = myFile.read();
        y >>= 4;
        if(bitRead(y, 0) == 1) bitSet(pixelDataA[x][3], 7-i); else bitClear(pixelDataA[x][3], 7-i);
        y >>= 1;
        if(bitRead(y, 0) == 1) bitSet(pixelDataA[x][2], 7-i); else bitClear(pixelDataA[x][2], 7-i);
        y >>= 1;
        if(bitRead(y, 0) == 1) bitSet(pixelDataA[x][1], 7-i); else bitClear(pixelDataA[x][1], 7-i);
        y >>= 1;
        if(bitRead(y, 0) == 1) bitSet(pixelDataA[x][0], 7-i); else bitClear(pixelDataA[x][0], 7-i);
        y = myFile.read();
        y >>= 4;
        if(bitRead(y, 0) == 1) bitSet(pixelDataA[x][7], 7-i); else bitClear(pixelDataA[x][7], 7-i);
        y >>= 1;
        if(bitRead(y, 0) == 1) bitSet(pixelDataA[x][6], 7-i); else bitClear(pixelDataA[x][6], 7-i);
        y >>= 1;
        if(bitRead(y, 0) == 1) bitSet(pixelDataA[x][5], 7-i); else bitClear(pixelDataA[x][5], 7-i);
        y >>= 1;
        if(bitRead(y, 0) == 1) bitSet(pixelDataA[x][4], 7-i); else bitClear(pixelDataA[x][4], 7-i);
        y = myFile.read();
        y >>= 4;
        if(bitRead(y, 0) == 1) bitSet(pixelDataA[x][11], 7-i); else bitClear(pixelDataA[x][11], 7-i);
        y >>= 1;
        if(bitRead(y, 0) == 1) bitSet(pixelDataA[x][10], 7-i); else bitClear(pixelDataA[x][10], 7-i);
        y >>= 1;
        if(bitRead(y, 0) == 1) bitSet(pixelDataA[x][9], 7-i); else bitClear(pixelDataA[x][9], 7-i);
        y >>= 1;
        if(bitRead(y, 0) == 1) bitSet(pixelDataA[x][8], 7-i); else bitClear(pixelDataA[x][8], 7-i);
      }
    }

    myFile.close();
  }
  

  Serial.println();
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      Serial.print(pixelDataA[i][j], HEX);
      Serial.print("\t");
      if (j == 11) Serial.println();
    }
  }
  Serial.println();
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      Serial.print(pixelDataC[i][j], HEX);
      Serial.print("\t");
      if (j == 11) Serial.println();
    }
  }
  Serial.println();
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      Serial.print(pixelDataL[i][j], HEX);
      Serial.print("\t");
      if (j == 11) Serial.println();
    }
  }
  Serial.println();

/*      
  if (SD.exists("disp_15/TestRED.txt")) SD.remove("disp_15/TestRED.txt");
  myFile = SD.open("disp_15/TestRED.txt", FILE_WRITE);
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      myFile.write(pixelDataA[i][j]);
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      myFile.write(pixelDataC[i][j]);
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      myFile.write(pixelDataL[i][j]);
    }
  }
*/     
  myFile.close();
  //while(1);


}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------------LOOP---------------------------------------------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loop() {

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------FUNCTIONS------------------------------------------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



