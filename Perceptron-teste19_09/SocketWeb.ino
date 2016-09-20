
bool SaveValues(String action){
  WiFiClient client;
  int loopBreak=0;
  while (!client.connect("192.168.5.206", 123)) {
    loopBreak++;
    if(loopBreak > 5){
      return false;
     }
     delay(1);
  }
  String buf = action;
  buf += ": light ";
  buf += luminosidade;
  buf += ": move ";
  buf += movimento;
  buf += ": Wb ";
  buf += Wb;
  buf += ": Wl ";
  buf += Wl;
  buf += ": Wm ";
  buf += Wm;  
  buf += ": LightControl ";
  buf += valorLuzDesejada;
  buf += ": TimeOff ";
  buf += tempoDesliga;
  buf += ": statusLight ";
  buf += leLampada();
  client.print(buf);
  loopBreak=0;
  while(!client.available()) {     
     loopBreak++;
     if(loopBreak > 10){
      client.flush();
      client.stop();
      return false;
     }
     delay(1);
  }
  String req = client.readStringUntil('\r');
  client.flush();
  client.stop();
  Serial.println(req);
  if(req.indexOf("OK") != -1){
    return true;
  }else{
    return false;
  }
}

