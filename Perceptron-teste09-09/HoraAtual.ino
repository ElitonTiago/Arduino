//Configuracao Hora
int timeZone = -3;
unsigned long millisHora = 0;
unsigned long checarHora = 60000;// a cada 10 minutos é verificada a hora atual


void novaHora(){  
  unsigned long millisAtual = (millis()) - millisHora;
  if(millisAtual >= checarHora || millisAtual < 0){
    millisHora = millis();
    Serial.print("chama nova hora = ");
    int horaAgora = getTime();
    Serial.println(horaAgora);
    if(hora != horaAgora){
      if(!alteracaoMemoria){
        ajusteLuzDesejada();
      }
      GravaNovosValores();
      alteracaoMemoria = false;
      hora = horaAgora;
      LeituraInicial();
    }
  }  
}

int getTime() {
  Serial.println("buscando hora");
  WiFiClient client;
  while (!client.connect("www.google.com", 80)) {
    Serial.println("connection failed, retrying...");
  }

  client.print("HEAD / HTTP/1.1\r\n\r\n");
 
  while(!client.available()) {
     delay(1);
  }
  Serial.println("servidor avaliado");
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
                String strDiaSemana = theDate.substring(0,3);
                String strDia = theDate.substring(5,7);
                String strHora = theDate.substring(17,19);
                String strMinuto = theDate.substring(20,22);
                int horaAgora = ((strHora.toInt())+timeZone);
                if( horaAgora < 0){
                  horaAgora+=24;
                }
                return horaAgora;
              }
            }
          }
        }
      }
    }
  }
}
