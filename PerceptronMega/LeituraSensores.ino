//Configuracao sensores
int pinoSensorMov = 22;
Thread threadSensores;
void configuraSensores(){
  pinMode(pinoSensorMov, INPUT);
  threadSensores.setInterval(2000);
  threadSensores.onRun(loopSensores);
  cpu.add(&threadSensores);
}

float getLuminosidade(){  
  int j;  
  float valorLuminosidade = 0;
  for(j = 0; j < 10; j++){
    valorLuminosidade += analogRead(A8);
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

void loopSensores(){
  luminosidade = getLuminosidade();
  movimento = getMovimento();
  Serial.print("Movimento : ");
  Serial.println(movimento);
  Serial.print("Luminosidade : ");
  Serial.println(luminosidade);
}
