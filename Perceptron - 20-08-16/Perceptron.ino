#include<WiFiClient.h>
#include <ESP8266WiFi.h>
//Configuracao Wifi
char ssid[] = "Patricia";  //  your network SSID (name)
char pass[] = "0102030405";       // your network password
IPAddress ip(192, 168, 5, 200);
IPAddress gat(192, 168, 5, 1);
IPAddress sub(255, 255, 255, 0);
//Configuracao Hora
int timeZone = -3;
String diaSemana, dia, hora, minuto;
//Configuracao sensores
int pinoSensorMov = 4;
int valorLuminosidade[10];
float mediaLuminosidade = 0;
bool valorSensorMov = 0;
int i = 0;
//variaveis perceptron
bool bias = 1;
float Wb = -0.2;
float Wm = 0.7;
float Wl = -0.4;
float aprendizagem = 0.01;

void setup() {
  pinMode(pinoSensorMov, INPUT);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  Serial.begin(115200);
  initWifi();
  Serial.println("Ready!");
  for(i = 0; i < 10; i++){
    valorLuminosidade[i] = analogRead(A0);
    delay(100);
    //Serial.print("Leitura Luminosidade : ");
    //Serial.println(valorLuminosidade[i]);
  }
  i = 0;
}

void initWifi() {
  Serial.println("Conectando no Wifi");
  WiFi.config(ip, gat, sub);
  WiFi.begin(ssid, pass);  

   while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
   }
  Serial.print("\nWiFi connected, IP address: ");
  Serial.println(WiFi.localIP());
} 

void atualizaLuminosidade(){  
  int j;
  for(j = 0; j < 8; j++){
    valorLuminosidade[i] = analogRead(A0);
    i++;
    if(i >= 10){
      i = 0;
    }
    //Serial.print("Leitura Luminosidade : ");
    //Serial.println(valorLuminosidade[i]);
    delay(50);
  }
  for(j = 0; j < 10; j++){
    mediaLuminosidade += valorLuminosidade[j];
  }
  mediaLuminosidade = (mediaLuminosidade/10)/1024;
  Serial.print("luminosidade : ");
  Serial.println(mediaLuminosidade);
}

String getTime() {
  Serial.println("Get Time");
  WiFiClient client;
  while (!!!client.connect("www.google.com", 80)) {
    Serial.println("connection failed, retrying...");
  }

  client.print("HEAD / HTTP/1.1\r\n\r\n");
 
  while(!!!client.available()) {
     yield();
  }

  while(client.available()){
    if (client.read() == '\n') {    
      if (client.read() == 'D') {    
        if (client.read() == 'a') {    
          if (client.read() == 't') {    
            if (client.read() == 'e') {    
              if (client.read() == ':') {    
                client.read();
                String theDate = client.readStringUntil('\r');
                client.stop();
                diaSemana = theDate.substring(0,3);
                dia = theDate.substring(5,7);
                hora = theDate.substring(17,19);
                minuto = theDate.substring(20,22);
                return theDate;
              }
            }
          }
        }
      }
    }
  }
}

bool perceptron(){
  float somatoria = (bias * Wb) + (mediaLuminosidade * Wl) + (valorSensorMov * Wm);
  Serial.print("somatoria : ");
  Serial.println(somatoria);
  if(somatoria > 0){
    digitalWrite(2, HIGH);
    return 1;
  }else{
    digitalWrite(2, LOW);
    return 0;
  }
}

void correcaoErro(int erro){
  Serial.print("Wb velho : ");
  Serial.println(Wb);
  Wb = Wb + (erro * aprendizagem * bias);
  Serial.print("Wb novo : ");
  Serial.println(Wb);
  Serial.print("Wl velho : ");
  Serial.println(Wl);
  Serial.print(Wl);
  Serial.print(" + ");
  Serial.print(erro);
  Serial.print(" * ");
  Serial.print(aprendizagem);
  Serial.print(" * ");
  Serial.println(mediaLuminosidade);
  Wl = Wl + (erro * aprendizagem * mediaLuminosidade);
  Serial.print("Wl novo : ");
  Serial.println(Wl);
  Serial.print("Wm velho : ");
  Serial.println(Wm);
  Wm = Wm + (erro * aprendizagem * valorSensorMov);
  Serial.print("Wm novo : ");
  Serial.println(Wm);
}

void verificaErro(bool saida){
  if(mediaLuminosidade < 0.68 && valorSensorMov == 1){
    Serial.print("Ligado ? : ");
    Serial.println(saida);
    //Aqui eu espero que tenha 1 se não tiver, então 1 - 0 = 1
    if(!saida){
      correcaoErro(1);
    }
  }else{
    Serial.print("Desligado ? : ");
    Serial.println(saida);
    //Aqui eu espero que tenha 0 se não tiver, então 0 - 1 = -1
    if(saida){
      correcaoErro(-1);
    }
  }
}

void loop() {
  atualizaLuminosidade();
  valorSensorMov = digitalRead(pinoSensorMov);
  Serial.print("Movimento : ");
  Serial.println(valorSensorMov);
  //Serial.println(getTime());
  //Serial.print("Dia semana : ");
  //Serial.println(diaSemana);
  //Serial.print("Dia : ");
  //Serial.println(dia);
  //Serial.print("hora : ");
  //Serial.println(hora);
  //Serial.print("minuto : ");
  //Serial.println(minuto);
  bool saida = perceptron();
  verificaErro(saida);
  delay(3000);
}
