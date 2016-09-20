#include <SoftwareSerial.h>

SoftwareSerial mySerial(8, 9); // RX, TX

#include <SPI.h>
#include <SD.h>

File dataFile;
String hora;
String dia;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  mySerial.begin(9600);

  Serial.print("Initializing SD card...");

  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

}

void loop() {
  if(mySerial.available()){
    String req = mySerial.readStringUntil('\r');
    Serial.println(req);
    delay(10);
    if(req.indexOf("gravaSd ") != -1){
      req.remove(0, 9);
      if(req.indexOf("hora") != -1){
        CreateFileHour(req);
      }else if(req.indexOf("dia") != -1){
        CreateDirectoryDay(req);
      }else{
        SaveValues(req);
      }
    }
  }
}

bool SaveValues(String action){
  dataFile = SD.open(hora, FILE_WRITE);
  if(dataFile){         
    dataFile.println(action);
    dataFile.close();
  }else{
    return false;
  }
    return true; 
}

void CreateFileHour(String hour){
  hora = hour;
  dataFile = SD.open(hora,FILE_WRITE);
  if(dataFile){
    Serial.print(hora);
    Serial.println(" criado com sucesso");
  }else{
    Serial.print(hora);
    Serial.println(" não criado com sucesso");
  }
  dataFile.close();  
}

bool CreateDirectoryDay(String day){
  dia = day;
  Serial.println(dia); 
  if(!SD.exists(dia)){    
    SD.mkdir(dia);
    if(SD.exists(dia)){
      Serial.print(dia);
      Serial.println(" exist");
      return true;
    }else{
      Serial.print(dia);
      Serial.println(" doesn't exist");
      mySerial.println("error");
      return false;
    }
  }else{
    Serial.print(dia);
    Serial.println(" exist");
  }
  return true;
}
