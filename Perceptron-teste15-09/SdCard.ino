#include <SD.h>
Sd2Card SDcard;
SdVolume volume;
// Pino do Arduino conectado ao pino CS do modulo
const int chipSelect = 15; 
bool sdConnected = false;
String date;
String newHour;

void beginSdCard(){
  if (SD.begin(chipSelect)){
    sdConnected = true;
    Serial.println("Cartao iniciado corretamente !");
    CreateDirectoryDay();
    CreateFileHour(String(hora));
    return;
  }
  Serial.println("Falha ao acessar o cartao !");
}

bool CreateDirectoryDay(){
  date = "dia";
  date += getDay();
  Serial.println(date);
  
    /*if(SD.mkdir(date)){
      Serial.println("Diretorio criado com sucesso");
    }else{
      Serial.println("Diretorio nao criado com sucesso");
      return false;
    }*/
  
  return true;
}

bool CreateFileHour(String hour){
  File newFile;
  newHour = date;
  newHour += "-";
  newHour += hour;
  newHour += ".txt";
   Serial.println(newHour);
  /*if(SD.exists(newHour)){
  }else{*/
  if(sdConnected){
    newFile = SD.open(newHour,FILE_WRITE);
    newFile.close();
    Serial.println("Diretorio criado com sucesso");
  }
  return true;
}

bool SaveValues(String action){
  if(sdConnected){
  File dataFile = SD.open(newHour, FILE_WRITE);
  if(dataFile){    
    dataFile.print(action);
    dataFile.print(": in Minute ");
    dataFile.print(getMinute());    
    dataFile.print(": light ");
    dataFile.print(luminosidade);
    dataFile.print(": move ");
    dataFile.print(movimento);
    dataFile.print(": Wb ");
    dataFile.print(Wb);
    dataFile.print(": Wl ");
    dataFile.print(Wl);
    dataFile.print(": Wm ");
    dataFile.print(Wm);
    dataFile.print(": LightControl ");
    dataFile.print(valorLuzDesejada);
    dataFile.print(": TimeOff ");
    dataFile.print(tempoDesliga);
    dataFile.print(": statusLight ");
    dataFile.println(leLampada());
    dataFile.close();
  }else{
    return false;
  }
    return true;
  }
  return false;
}

