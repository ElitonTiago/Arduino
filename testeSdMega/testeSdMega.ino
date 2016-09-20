#include <SPI.h>
#include <SD.h>

File myFile;
String dia;
String hora;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  Serial3.begin(115200);
  delay(10);
  Serial.print("Initializing SD card...");

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
        Serial.println("hora encontrada");
        //req.toCharArray(hora,13);
        hora = req;
        Serial.println(hora);
        myFile = SD.open(hora,FILE_WRITE);
        if(myFile){
            Serial.print(hora);
            Serial.println(" criado com sucesso");
        }else{
          Serial.print(hora);
          Serial.println(" não criado com sucesso");
        }
        myFile.close();
      }else if(req.indexOf("dia") != -1){
        Serial.println("dia encontrado");
        //req.toCharArray(dia,6);
        dia = req;
        Serial.println(dia); 
        if(!SD.exists(dia)){    
          SD.mkdir(dia);
          if(SD.exists(dia)){
            Serial.print(dia);
            Serial.println(" exist");
          }else{
            Serial.print(dia);
            Serial.println(" doesn't exist");
          }
        }else{
          Serial.print(dia);
          Serial.println(" exist");
        }
      }else{
        Serial.println("gravar arquivo");
        myFile = SD.open(hora, FILE_WRITE);
        if(myFile){         
          myFile.println(req);
          myFile.close();
          Serial.println("gravado arquivo");
        }else{
          Serial.println("Ops... se acalme");
        }
      }
    }
   }
}
