//Configuracao Hora
int timeZone = -3;
os_timer_t mTimer;
bool checarHora = false;

void tCallback(void *tCall){
    checarHora = true;
}

void criaTimerParaGetTime(){
  os_timer_setfn(&mTimer, tCallback, NULL);
  os_timer_arm(&mTimer, 600000, true);
}

void novaHora(){  
  if(checarHora){
    checarHora = false;
    hora = getTime();
  }  
}

int getTime() {
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
    yield();
  }
}
