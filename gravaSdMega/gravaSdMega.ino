#include <SPI.h>
#include <SD.h>

String dia;
String hora;
File dataFile;
void setup() {
  Serial.begin(115200);
  Serial3.begin(115200);
  delay(10);
  Serial.println("Initializing SD card...");

  if (!SD.begin(53)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
}

void loop() {
  if(Serial3.available()){
    String req = Serial3.readStringUntil('\r');
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
  Serial.println("gravar arquivo");
  dataFile = SD.open(hora, FILE_WRITE);
  if(dataFile){         
    dataFile.println(action);
    dataFile.close();
    Serial.println("gravado arquivo");
  }else{
    Serial.println("Ops... se acalme");
    Serial3.println("error");
    return false;
  }
    return true; 
}

void CreateFileHour(String hour){
  hora = hour;
  Serial.println(hora);
  dataFile = SD.open(hora,FILE_WRITE);
  if(dataFile){
    Serial.print(hora);
    Serial.println(" criado com sucesso");
  }else{
    Serial.print(hora);
    Serial.println(" não criado com sucesso");
    Serial3.println("error");
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
      Serial3.println("error");
      return false;
    }
  }else{
    Serial.print(dia);
    Serial.println(" exist");
  }
  return true;
}
