
void initWifi() {
  //Configuracao Wifi
  char ssid[] = "Patricia";  //  your network SSID (name)
  char pass[] = "0102030405";       // your network password  
  IPAddress ip(192, 168, 5, 200);
  IPAddress gat(192, 168, 5, 1);
  IPAddress sub(255, 255, 255, 0);
  Serial.println("Conectando no Wifi");
  WiFi.config(ip, gat, sub);
  WiFi.begin(ssid, pass);  

   while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
   }
  Serial.print("\nWiFi connected, IP address: ");
  Serial.println(WiFi.localIP());
} 

