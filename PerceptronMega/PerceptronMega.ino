#include <TimerOne.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>
#include <Thread.h>
#include <ThreadController.h>

ThreadController cpu;
float luminosidade = 0;
bool movimento = 0;
uint8_t lampada = 24;
uint8_t statusLampada = 26;
bool alteracaoUsuario = false;

void setup() {
  configuraSensores();
  pinMode(statusLampada,INPUT);
  pinMode(lampada, OUTPUT);
  digitalWrite(lampada, LOW);
  Serial.begin(115200);
  criaTimerParaPerceptron();  
  iniciaTFT();
  configuraLampada();
}

void loop() {
  cpu.run();  
  loopTFT();
  chamaPerceptron();
}


  
