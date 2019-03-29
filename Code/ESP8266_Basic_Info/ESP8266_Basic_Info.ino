#include <ESP8266WiFi.h>
 
const char* ssid = "A501";
const char* password = "spoo1989";
 
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
 
  // Connect to WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
 
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.macAddress());
  Serial.println(WiFi.SSID());
  Serial.println(WiFi.hostname());

  WiFi.hostname("Srijal's ESP");
  Serial.println(WiFi.hostname());
  
  Serial.println(WiFi.status());
  Serial.println(WiFi.RSSI());

}
 
void loop() {
 
}
