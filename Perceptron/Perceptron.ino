#include <ESP8266WebServer.h>
extern "C"{
#include "user_interface.h"
}

float luminosidade = 0;
bool movimento = 0;
int lampada = 0;
int statusLampada = 2;
int hora;
bool alteracaoUsuario = false;

void setup() {  
  configuraSensores();
  luminosidade = getLuminosidade();
  movimento = getMovimento();
  Serial.print("Movimento : ");
  Serial.println(movimento);
  Serial.print("Luminosidade : ");
  Serial.println(luminosidade);
  pinMode(statusLampada,INPUT);
  pinMode(lampada, OUTPUT);
  digitalWrite(lampada, 0);
  Serial.begin(115200);
  initWifi();
  iniciaServidor();
  hora = getTime();
  criaTimerParaGetTime();
  criaTimerParaPerceptron();  
}

void loop() {  
  conexaoServidor();
}
