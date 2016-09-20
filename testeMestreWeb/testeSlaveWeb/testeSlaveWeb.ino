#include <ESP8266WebServer.h>
int contador = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  initWifi();
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client;
  int loopBreak=0;
  while (!client.connect("192.168.5.206", 123)) {
    loopBreak++;
    if(loopBreak > 10){
      return;
     }
     delay(10);
  }
  String buf = "teste ";
  buf += contador;
  client.print(buf);
  contador++;
  loopBreak=0;
  while(!client.available()) {
     delay(10);
     loopBreak++;
     if(loopBreak > 10){
      client.flush();
      client.stop();
      return;
     }
  }
  String req = client.readStringUntil('\r');
  client.flush();
  client.stop();
  Serial.println(req);
  delay(2000);
}
