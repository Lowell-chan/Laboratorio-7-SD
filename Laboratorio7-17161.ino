/*
  SD card test

 The circuit:
  * SD card attached to SPI bus as follows:
 ** MOSI - pin 11 on Arduino Uno/Duemilanove/Diecimila
 ** MISO - pin 12 on Arduino Uno/Duemilanove/Diecimila
 ** CLK - pin 13 on Arduino Uno/Duemilanove/Diecimila
 ** CS - depends on your SD card shield or module.
 		Pin 4 used here for consistency with other Arduino examples


 created  28/09/2011
 by Daniel Cortez - 17161
 */
// include the SD library:
#include <SPI.h>
#include <SD.h>

int incomingByte = 0; // for incoming serial data


// set up variables using the SD utility library functions:
Sd2Card card;
SdVolume volume;
SdFile root;

const int chipSelect = PA_3; //cs PIN

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
 
SPI.setModule(0);

  Serial.print("\nInitializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output
  // or the SD library functions will not work.
  pinMode(PA_3, OUTPUT);     // change this to 53 on a mega
//********************************************************************************************************
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
//********************************************************************************************************  
  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card is inserted?");
    Serial.println("* Is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    return;
  } else {
    Serial.println("Wiring is correct and a card is present.");
  }
//********************************************************************************************************
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
  
  Serial.println("\nPara visualizar cada archivo presione 1, 2, 3... respectivamente:");
}


void loop(void) {
  
    incomingByte = Serial.read();
    
    // Primer archivo:
    if (incomingByte == 49){
      // open the file. note that only one file can be open at a time,
      // so you have to close this one before opening another.
      File dataFile1 = SD.open("Mario.txt", FILE_READ);
    
      // if the file is available, write to it:
      if (dataFile1) {
        while(dataFile1.available()) {
          Serial.write(dataFile1.read());
        }
        dataFile1.close();
      }
      // if the file isn't open, pop up an error:
      else {
        Serial.println("error opening Mario.txt");
      }
      Serial.println("\nPara visualizar cada archivo presione 1, 2, 3... respectivamente:");
    }
    
    // Segundo archivo:
    if (incomingByte == 50){
    // open the file. note that only one file can be open at a time,
      // so you have to close this one before opening another.
      File dataFile2 = SD.open("Pikachu.txt", FILE_READ);
    
      // if the file is available, write to it:
      if (dataFile2) {
        while(dataFile2.available()) {
          Serial.write(dataFile2.read());
        }
        dataFile2.close();
      }
      // if the file isn't open, pop up an error:
      else {
        Serial.println("error opening Pikachu.txt");
      }
      Serial.println("\nPara visualizar cada archivo presione 1, 2, 3... respectivamente:");
    }
    
    // Tercer archivo:
    if (incomingByte == 51){
    // open the file. note that only one file can be open at a time,
      // so you have to close this one before opening another.
      File dataFile3 = SD.open("CHARIZ~1.txt", FILE_READ);
    
      // if the file is available, write to it:
      if (dataFile3) {
        while(dataFile3.available()) {
          Serial.write(dataFile3.read());
        }
        dataFile3.close();
      }
      // if the file isn't open, pop up an error:
      else {
        Serial.println("error opening Charizard.txt");
      }
      Serial.println("\nPara visualizar cada archivo presione 1, 2, 3... respectivamente:");
    }

}
