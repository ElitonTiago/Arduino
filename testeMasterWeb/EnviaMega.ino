String date;
String newHour;
String req;

bool CreateDirectoryDay(String day){
  date = "gravaSd "; // codigo para gravacao no sd card
  date += "dia";
  date += day;  
  Serial.println(date);  
  delay(10);
  return true;
}

bool CreateFileHour(String hour){
  newHour += date; //nome da pasta que ficara o arquivo
  newHour += "/hora";//nome do arquivo
  newHour += hour;
  newHour += ".txt";
  Serial.println(newHour);
  delay(10);
  return true;
}

bool SaveValues(String action){
  req = "gravaSd ";// codigo para gravacao no sd card
  req += getMinute();
  req += ": ";
  req += action;
  Serial.println(req);
  delay(10);
  return true;
}
