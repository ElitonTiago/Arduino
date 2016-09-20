#include <ESP8266WebServer.h>
#include <SPI.h>
#include <SD.h>
const int chipSelect = 4;  
File myFile;
WiFiServer server(123);
void setup() {
  Serial.begin(115200);  
  while(!SD.begin(chipSelect)) 
  {
    Serial.println("Falha ao acessar o cartao !");
    Serial.println("Verifique o cartao/conexoes e reinicie o Arduino...");
    delay(5000);
  }
  initWifi();  
  novaHora();
  delay(10);
  server.begin();
  delay(10);
  Serial.println("Configuracao concluida");
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    novaHora();
    return;
  }
  Serial.println("cliente conectado");
  int loopBreak = 0;
  while(!client.available()){
    delay(1);
    loopBreak++;
    if(loopBreak > 10){
       return;
    }    
  }
  //Le a string enviada pelo cliente
  String req = client.readStringUntil('\r');
  //Limpa dados/buffer
  SaveValues(req);
  client.flush();
  client.print("OK");
  client.flush();
  client.stop();
}
