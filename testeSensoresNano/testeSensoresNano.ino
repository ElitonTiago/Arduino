void setup() {
  // put your setup code here, to run once:
  analogReference(INTERNAL);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  String req = "valuesNano 1 -0.2 0.7 -0.4 0.68 100 0.90 1 ";
  Serial.println(req);
  Serial.print("index values ");
  
  Serial.println(req.indexOf("values"));
  Serial.println(req.indexOf(" "));
  if(req.indexOf("valuesNano") != -1){
      req.remove(0,11);
      int statusLumi = req.substring(0,req.indexOf(" ")).toInt();
      Serial.println(statusLumi);
      req.remove(0,req.indexOf(" ")+1);
      Serial.println(req);
      float Wb =  req.substring(0,req.indexOf(" ")).toFloat();
      Serial.println(Wb);
      req.remove(0,req.indexOf(" ")+1);
      Serial.println(req);
      float Wm =  req.substring(0,req.indexOf(" ")).toFloat();
      Serial.println(Wm);
      req.remove(0,req.indexOf(" ")+1);
      Serial.println(req);
      float Wl =  req.substring(0,req.indexOf(" ")).toFloat();
      Serial.println(Wl);
      req.remove(0,req.indexOf(" ")+1);
      Serial.println(req);
      float valorLuzDesejada =  req.substring(0,req.indexOf(" ")).toFloat();
      Serial.println(valorLuzDesejada);
      req.remove(0,req.indexOf(" ")+1);
      Serial.println(req);
      int tempoDesliga = req.substring(0,req.indexOf(" ")).toInt();
      Serial.println(tempoDesliga);
      req.remove(0,req.indexOf(" ")+1);
      Serial.println(req);
      float luminosidade =  req.substring(0,req.indexOf(" ")).toFloat();
      Serial.println(luminosidade);
      req.remove(0,req.indexOf(" ")+1);
      Serial.println(req);
      int movimento = (bool) req.substring(0,req.indexOf(" ")).toInt();
      Serial.println(movimento);
      req.remove(0,req.indexOf(" ")+1);
      Serial.println(req);
      Serial.print("sobrou ");
      Serial.println(req);
    }
  Serial.println(analogRead(A0));
  Serial.println(digitalRead(2));
  delay(20000);
}
