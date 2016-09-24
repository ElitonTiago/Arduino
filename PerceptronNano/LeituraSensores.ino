//Configuracao sensores
int pinoSensorMov = 3;
void configuraSensores(){
  pinMode(pinoSensorMov, INPUT);
}

float getLuminosidade(){  
  int j;  
  float valorLuminosidade = 0;
  for(j = 0; j < 10; j++){
    valorLuminosidade += analogRead(A0);
    yield();
  } 
  valorLuminosidade = (valorLuminosidade/10)/1024;
  return valorLuminosidade;  
}

bool getMovimento(){  
  bool valorSensorMov = 0;
  valorSensorMov = digitalRead(pinoSensorMov);
  return valorSensorMov;
}

