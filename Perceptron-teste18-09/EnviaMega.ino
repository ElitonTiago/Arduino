String date;
String newHour;
String buf;

bool CreateDirectoryDay(String day){
  date = "gravaSd "; // codigo para gravacao no sd card
  date += "dia";
  date += day;  
  Serial.println(date);  
  delay(10);
  if(Serial.available()){
    String resposta = Serial.readStringUntil('\r');
    if(resposta.indexOf("error") != -1){
      delay(50);
      CreateDirectoryDay(day);
    }
  }
  return true;
}

bool CreateFileHour(String hour){
  newHour += date; //nome da pasta que ficara o arquivo
  newHour += "/hora";//nome do arquivo
  newHour += hour;
  newHour += ".txt";
  Serial.println(newHour);
  delay(10);
  if(Serial.available()){
    String resposta = Serial.readStringUntil('\r');
    if(resposta.indexOf("error") != -1){
      delay(50);
      CreateFileHour(hour);
    }
  }
  return true;
}

bool SaveValues(String action){
  buf = "gravaSd ";// codigo para gravacao no sd card
  buf += getMinute();
  buf += ": ";
  buf += action;
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
  Serial.println(buf);
  delay(30);
  return true;
}
