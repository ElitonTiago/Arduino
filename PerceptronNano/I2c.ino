void requestEvent() {
  String req = "values ";
  req += leLampada();
  req += " ";
  req += Wb;
  req += " ";
  req += Wm;
  req += " ";
  req += Wl;
  req += " ";
  req += valorLuzDesejada;
  req += " ";
  req += tempoDesliga;
  req += " ";
  req += luminosidade;
  req += " ";
  req += movimento;
  req += " ";
  Serial.print("tamanho resposta = ");
  Serial.println(req.length());
  While(req.length() < 44) req += " ";
  Serial.println(req.length();
  Wire.write(req); // respond with message of 44 bytes
}

void receiveEvent(int howMany) {
  if (Wire.available()) { // loop through all but the last
    String req = Wire.readStringUntil('\r'); // receive byte as a character
    Serial.print(req);         // print the character
    if(req.indexOf("gravaSd")){
      req.remove(0,8);
      Serial.println(req);
    }else if(req.indexOf("dia")){
      req.remove(0,3);
      Serial.println(req);
    }else{
      Serial.println("erro na string");
    }
  }
}
