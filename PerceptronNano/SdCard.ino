#include <SPI.h>
#include <SD.h>

File dataFile;

bool initSdCard(){
  Serial.print("Initializing SD card...");

  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    return false;
  }
  Serial.println("initialization done.");
  return true;
}

