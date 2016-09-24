#include <EEPROM.h>
#include <Wire.h>
#define ADDRESS_I2C 8
#define MEM_ALOC_SIZE 120 //Quantidade necessaria para salvar 5 variaveis para cada hora do dia
#define TIME_EXEC 2000 // execução normal de funcionamento do perceptron
#define TIME_DELAY 120000 //após interração pelo usuário o perceptron passar a ficar este tempo sem executar
float luminosidade = 0;
bool movimento = 0;
int hora;
bool alteracaoUsuario = false;
bool alteracaoMemoria = false;
//valores utilizados na memoria
float Wb = -0.2;
float Wm = 0.7;
float Wl = -0.4;
float valorLuzDesejada = 0.68;
uint8_t tempoDesliga = 60;//valor em que o contador tem que chegar para assim desligar a lampada, multiplicado pelo tempoPercetron ocorre o tempo que fica ligado
unsigned long tempoPerceptron = TIME_EXEC;//tempo em que é realizado o perceptron

void setup() {    
  beginLumiControl();
  Serial.begin(115200);
  Wire.begin(ADDRESS_I2C);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
  configuraSensores();
  luminosidade = getLuminosidade();
  movimento = getMovimento(); 
  EEPROM.begin(MEM_ALOC_SIZE);
  LeituraInicial();
  iniciaServidor();
  Serial.println("Servidor inicializado");
  chamaPerceptron(); 
}

void loop() {  
  conexaoServidor();
}
