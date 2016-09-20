String date;
String buf;

bool newTime(){ 
  date += "dia";
  date += getDay();  
  date += ":";
  date += getHour();
  date += ":";
  date += getMinute();
  Serial.println(date);  
  Wire.beginTransmission(ADDRESS_I2C);
  Wire.write(date);
  Wire.endTransmission();
  delay(10);
  return true;
}

bool SaveValues(String action){
  buf = "gravaSd ";// codigo para gravacao no sd card
  buf += getMinute();
  buf += ": ";
  buf += action;
  Serial.println(buf);
  Wire.beginTransmission(ADDRESS_I2C);
  Wire.write(date);
  Wire.endTransmission();
  delay(30);
  getValues();
  return true;
}

bool getValues(){
  Serial.println("values");
  Wire.requestFrom(ADDRESS_I2C, 44);
  if(Wire.available()){
    String req = Wire.readStringUntil('\r');
    Serial.println(req);
    if(req.indexOf("valuesNano") != -1){
      req.remove(0,11);
      int statusLumi = req.substring(0,req.indexOf(" ")).toInt();
      req.remove(0,req.indexOf(" ")+1);
      float Wb =  req.substring(0,req.indexOf(" ")).toFloat();
      req.remove(0,req.indexOf(" ")+1);
      float Wm =  req.substring(0,req.indexOf(" ")).toFloat();
      req.remove(0,req.indexOf(" ")+1);
      float Wl =  req.substring(0,req.indexOf(" ")).toFloat();
      req.remove(0,req.indexOf(" ")+1);
      float valorLuzDesejada =  req.substring(0,req.indexOf(" ")).toFloat();
      req.remove(0,req.indexOf(" ")+1);
      int tempoDesliga = req.substring(0,req.indexOf(" ")).toInt();
      req.remove(0,req.indexOf(" ")+1);
      float luminosidade =  req.substring(0,req.indexOf(" ")).toFloat();
      req.remove(0,req.indexOf(" ")+1);
      int movimento = (bool) req.substring(0,req.indexOf(" ")).toInt();
      req.remove(0,req.indexOf(" ")+1);
    }
    return true;
  }
  return false;
}

