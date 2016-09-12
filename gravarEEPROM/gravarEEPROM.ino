#include <EEPROM.h>

#define MEM_ALOC_SIZE 8
//eh armazenado valores de 0 a 255, mas o perceptron trabalha de -1 a 1 para isso os valores serão multiplicados por 100 e somados por mais cem. tendo assim valores de 0 a 200
uint8_t mWb = 0; // -0,26*100 + 100
uint8_t mWl = 0; // -0,47*100 + 100
uint8_t mWm = 0; // 0,61*100 + 100
uint8_t mLd = 0; // 0,68*100
uint8_t mTd = 0; // valor direto

float Wb = -0.26;
float Wl = -0.47;
float Wm = 0.61;
float Ld = 0.68;
uint8_t Td = 60;

void setup() {
  Serial.begin(115200);
  int i = 0;
  Serial.printf("Flash chip ID: %d\n", ESP.getFlashChipId());
  Serial.printf("Flash chip size (in bytes): %d\n", ESP.getFlashChipSize());
  Serial.printf("Flash chip speed (in Hz): %d\n", ESP.getFlashChipSpeed());
  delay(2000);
  EEPROM.begin(MEM_ALOC_SIZE);
  for(i = 0; i < 24; i++){
    Serial.println("Iniciando as gravacoes");
    Serial.printf("Salvando Wb : %f", Wb);
    mWb = (uint8_t) (Wb*100) + 100;
    Serial.printf(" que virou mWb : %d e ", mWb);
    EEPROM.write(0+i,mWb);
    delay(100);
    
    mWb = EEPROM.read(0+i);
    Serial.printf("gravou isso mWb[%d]: %d",i,mWb);
    Serial.printf(" que eh %f\n",(((float)mWb)-100)/100);
    delay(20000);
    
    Serial.printf("Salvando Wl : %f", Wl);
    mWl = (uint8_t) (Wl*100) + 100;
    Serial.printf(" que virou mWl : %d e ", mWl);
    EEPROM.write(24+i,mWl);
    delay(100);
    
    mWl = EEPROM.read(24+i);
    Serial.printf("gravou isso mWl[%d]: %d",i,mWl);
    Serial.printf(" que eh %f\n",(((float)mWl)-100)/100);
    delay(20000);
    
    Serial.printf("Salvando Wm : %f", Wm);
    mWm = (uint8_t) (Wm*100) + 100;
    Serial.printf(" que virou mWm : %d e ", mWm);
    EEPROM.write(48+i,mWm);
    delay(100);

    mWm = EEPROM.read(48+i);
    Serial.printf("gravou isso mWm[%d]: %d",i,mWm);
    Serial.printf(" que eh %f\n",(((float)mWm)-100)/100);
    delay(20000);
    
    Serial.printf("Salvando Ld : %f", Ld);
    mLd = (uint8_t) Ld*100;
    Serial.printf(" que virou mLd : %d e ", mLd);
    EEPROM.write(72+i,mLd);
    delay(100);

    mLd = EEPROM.read(72+i);
    Serial.printf("gravou isso mLd[%d]: %d",i,mLd);
    Serial.printf(" que eh %f\n",((float)mLd)/100);
    delay(20000);
    
    Serial.printf("Salvando Td : %d", Td);
    mTd = (uint8_t) Td;
    Serial.printf(" que virou mTd : %d e ", mTd);
    EEPROM.write(96+i,mTd);
    delay(100);
    
    mTd = EEPROM.read(96+i);
    Serial.printf("gravou isso mTd[%d]: %d",i,mTd);
    Serial.printf(" que eh %d\n",mTd);
    delay(20000);
    
    if (96+i >= ESP.getFlashChipSize()/8) {
      Serial.printf("Fudeu estouro de memória em %d\n",i);
      delay(5000);
    }
  }
  EEPROM.end();
  
  Serial.println("END");

}

void loop() {
  // put your main code here, to run repeatedly:

}
