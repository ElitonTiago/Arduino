#include <ESP8266WiFi.h>

const char* ssid = "Patricia";
const char* password = "0102030405";

void setup() {
  Serial.begin(115200); 
  Serial.println(); 
  initWifi();
}

void loop() {
  Serial.println(getTime());
  delay(5000);
}
  
String getTime() {
  WiFiClient client;
  while (!!!client.connect("www.facebook.com", 80)) {
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
                return theDate;
              }
            }
          }
        }
      }
    }
  }
}

void initWifi() {
   Serial.print("Connecting to ");
   Serial.print(ssid);
  // if (strcmp (WiFi.SSID(),ssid) != 0) {
      WiFi.begin(ssid, password);
   //}

   while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
   }
  Serial.print("\nWiFi connected, IP address: ");
  Serial.println(WiFi.localIP());
} 
