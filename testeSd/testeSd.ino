// Programa : Teste escrita cartao SD
// Autor : Arduino e Cia
// Baseado no arquivo exemplo da biblioteca SD

// Carrega a biblioteca SD
#include <SD.h>

Sd2Card SDcard;
SdVolume volume;

// Pino do Arduino conectado ao pino CS do modulo
const int chipSelect = 15;  
// Pino do Arduino conectado ao push-button
File myFile;
void setup()
{
  // Define o pino do push-button como entrada
  
  Serial.begin(115200);
  //Inicia a comunicacao com o modulo SD
  while (!SD.begin(chipSelect)) 
  {
    Serial.println("Falha ao acessar o cartao !");
    Serial.println("Verifique o cartao/conexoes e reinicie o Arduino...");
    delay(5000);
  }
  Serial.println("Cartao iniciado corretamente !");
  Serial.println("Aguardando acionamento do push-button...");
  Serial.println();
  if (SD.exists("example.txt")) {
    Serial.println("example.txt exists.");
  } else {
    Serial.println("example.txt doesn't exist.");
  }

  // open a new file and immediately close it:
  Serial.println("Creating example.txt...");
  myFile = SD.open("example.txt", FILE_WRITE);
  myFile.close();

  // Check to see if the file exists:
  if (SD.exists("example.txt")) {
    Serial.println("example.txt exists.");
  } else {
    Serial.println("example.txt doesn't exist.");
  }

  // delete the file:
  Serial.println("Removing example.txt...");
  SD.remove("example.txt");

  if (SD.exists("example.txt")) {
    Serial.println("example.txt exists.");
  } else {
    Serial.println("example.txt doesn't exist.");
  }
}

void loop() 
{
  int valor = analogRead(A0);
  // Verifica se o push-button foi acionado
  
    Serial.print("Ldr : ");
    Serial.println(valor);
  
    // Abre o arquivo arquivo.txt do cartao SD
    File dataFile = SD.open("arquivo.txt", FILE_WRITE);
    // Grava os dados no arquivo
    if (dataFile) 
    {
      dataFile.print("Ldr : ");
      dataFile.println(valor);
      dataFile.close();
    }  
    else 
    {
      // Mensagem de erro caso ocorra algum problema
      // na abertura do arquivo
      Serial.println("Erro ao abrir arquivo.txt !");
    } 
  delay(2000);
}
