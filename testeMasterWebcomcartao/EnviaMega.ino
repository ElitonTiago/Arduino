String date;
String newHour;
String req;
char arquivo [20];
bool CreateDirectoryDay(String day){
  date = "dia";
  date += day;  
  Serial.println(date);  
  delay(10);
  return true;
}

bool CreateFileHour(String hour){
  newHour += date; //nome da pasta que ficara o arquivo
  newHour += "_hora";//nome do arquivo
  newHour += hour;
  newHour += ".txt";
  newHour.toCharArray(arquivo, 20);
  Serial.println(newHour);
  myFile = SD.open(arquivo, FILE_WRITE);
  myFile.close();
  delay(10);
  return true;
}

bool SaveValues(String action){
  req = "gravaSd ";// codigo para gravacao no sd card
  req += getMinute();
  req += ": ";
  req += action;
  Serial.println(req);
  newHour.toCharArray(arquivo, 20);
  myFile = SD.open(arquivo, FILE_WRITE);
  Serial.println("arquivo abrindo");
  if(myFile){
    Serial.println("arquivo aberto");
    myFile.println(req);
    myFile.close();
  }
  delay(10);
  return true;
}
