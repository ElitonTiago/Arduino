#include <ESP8266WebServer.h>
#include <EEPROM.h>

float luminosidade = 0;
bool movimento = 0;
int lampada = 0;
int statusLampada = 2;
int hora;
bool alteracaoUsuario = false;
bool alteracaoMemoria = false;
//valores utilizados na memoria
float Wb = -0.2;
float Wm = 0.7;
float Wl = -0.4;
float valorLuzDesejada = 0.68;
uint8_t tempoDesliga = 60;//valor em que o contador tem que chegar para assim desligar a lampada, multiplicado pelo tempoPercetron ocorre o tempo que fica ligado

void setup() {    
  pinMode(statusLampada,INPUT);
  pinMode(lampada, OUTPUT);
  digitalWrite(lampada, 0); 
  Serial.begin(115200);
  initWifi();
  configuraSensores();
  luminosidade = getLuminosidade();
  movimento = getMovimento();
  Serial.print("Movimento : ");
  Serial.println(movimento);
  Serial.print("Luminosidade : ");
  Serial.println(luminosidade);  
  hora = getTime(); 
  Serial.print("Hora atual : ");
  Serial.println(hora);  
  LeituraInicial();
  iniciaServidor();
  Serial.println("Servidor inicializado");
  chamaPerceptron(); 
}

void loop() {  
  conexaoServidor();
}
