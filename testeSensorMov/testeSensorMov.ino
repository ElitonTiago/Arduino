int pinBuzzer = 4;
int pinSensorPIR = 5;
int pinLed = 2;
int valorSensorPIR = 0;
int photocellPin = 0;     // o LDR e seu resistor de pulldown são conectados ao pino a0
int photocellReading;     // leitura analógica do divisor do sensor
void setup() {
  Serial.begin(9600); //Inicializando o serial monitor
 
  //Definido pinos como de entrada ou de saída
  pinMode(pinBuzzer,OUTPUT);
  pinMode(pinSensorPIR,INPUT);
  pinMode(pinLed,OUTPUT);
}
 
void loop() {  
  //Lendo o valor do sensor PIR. Este sensor pode assumir 2 valores
  //1 quando detecta algum movimento e 0 quando não detecta.
  valorSensorPIR = digitalRead(pinSensorPIR);
  photocellReading = analogRead(A0); // faz a leitura do LDR  
  Serial.print("Valor do Sensor PIR: ");  
  Serial.println(valorSensorPIR);
  Serial.print("Valor do Sensor LDR: ");  
  Serial.println(photocellReading);
  Serial.print("Tensao no adc: ");  
  Serial.println(photocellReading/1024);
  //Verificando se ocorreu detecção de movimentos
  if (valorSensorPIR == 1 && photocellReading < 750) {
    ligarAlarme();
  } else {
    desligarAlarme();
  }    
}
 
void ligarAlarme() {
  //Ligando o led
  digitalWrite(pinLed, HIGH);
   
  //Ligando o buzzer com uma frequencia de 1500 hz.
  tone(pinBuzzer,1500);
   
  delay(400); //tempo que o led fica acesso e o buzzer toca
   
  desligarAlarme();
}
 
void desligarAlarme() {
  //Desligando o led
  digitalWrite(pinLed, LOW);
   
  //Desligando o buzzer
  noTone(pinBuzzer);
}
