#include <ESP8266WebServer.h>
#include <Wire.h>
#define ADDRESS_I2C 8
int hora;
float Wb = -0.2;
float Wm = 0.7;
float Wl = -0.4;
float valorLuzDesejada = 0.68;
int tempoDesliga = 60;
int statusLumi = 0;
int movimento = 0;
float luminosidade = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin(0,2); //Master using GPIO 0(SDA) and 2(SCL)
  initWifi();
  novaHora(); 
  iniciaServidor();
  getValues();
  Serial.println("configuracao concluida");
}

void loop() {
  conexaoServidor();
}
