//Configuracao Hora
int timeZone = -3;
unsigned long millisHora = 0;
unsigned long checarHora = 60000;// a cada 10 minutos é verificada a hora atual
String theDate;
String strDia;
String strMinuto;

void novaHora(){  
  unsigned long millisAtual = (millis()) - millisHora;
  if(millisAtual >= checarHora || millisAtual < 0){
    millisHora = millis();
    int horaAgora = getTime();
    if(hora != horaAgora){
      if(!alteracaoMemoria){        
        ajusteHoraParada();
        SaveValues("Nesta hora nao ocorreu interracao");
      }
      GravaNovosValores();
      alteracaoMemoria = false;
      hora = horaAgora;
      LeituraInicial();            
    }
  }  
}

int getTime() {
  WiFiClient client;
  int loopBreak=0;
  while (!client.connect("www.google.com", 80)) {
    loopBreak++;
    if(loopBreak > 5){
      return hora;
     }
     delay(1);
  }
  client.print("HEAD / HTTP/1.1\r\n\r\n");
  loopBreak=0;
  while(!client.available()) {     
     loopBreak++;
     if(loopBreak > 10){
      return hora;
     }
     delay(1);
  }
  while(client.available()){
    if (client.read() == '\n') {    
      if (client.read() == 'D') {    
        if (client.read() == 'a') {    
          if (client.read() == 't') {    
            if (client.read() == 'e') {    
              if (client.read() == ':') {    
                client.read();
                theDate = client.readStringUntil('\r');
                Serial.print("Data ");
                Serial.println(theDate);
                client.stop();
                String strDiaSemana = theDate.substring(0,3);
                strDia = theDate.substring(5,7);
                String strHora = theDate.substring(17,19);
                strMinuto = theDate.substring(20,22);
                int horaAgora = ((strHora.toInt())+timeZone);
                if( horaAgora < 0){
                  strDia = String((strDia.toInt())-1);
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

String getDate(){
  return theDate;
}

String getDay(){
  return strDia;
}

String getMinute(){
  return strMinuto;
}

