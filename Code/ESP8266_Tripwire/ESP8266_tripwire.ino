#include <ESP8266WiFi.h> // Enables the ESP8266 to connect to the local network (via WiFi)
#include <PubSubClient.h> // Allows us to connect to, and publish to the MQTT broker
#include <string>

const int LDR_IN = A0;

// WiFi
// Make sure to update this for your own WiFi network!
const char* SSID = "A501";
const char* WIFI_PASS = "spoo1989";

// MQTT
// Make sure to update this for your own MQTT Broker!
const char* MQTT_SERVER = "192.168.1.106";
const char* MQTT_TOPIC = "trigger_status";

// The client id identifies the ESP8266 device. Think of it a bit like a hostname (Or just a name, like Greg).
const char* CLIENT_ID = "TripWire-000";

// Initialise the WiFi and MQTT Client objects
WiFiClient wifi_client;
PubSubClient client(MQTT_SERVER, 1883, wifi_client); // 1883 is the listener port for the Broker

void MQTT_sub_callback(char* recv_topic, byte* payload, unsigned int msg_length) {
  if(!strcmp(recv_topic, MQTT_TOPIC)){
    delay(0);
  }
}

bool Connect() {
  // Connect to MQTT Server and subscribe to the topic
  if (client.connect(CLIENT_ID)) {
    client.subscribe(MQTT_TOPIC);
    return true;
  }
  else {
    return false;
  }
}

void setup() {
  // Begin Serial on 115200
  // Remember to choose the correct Baudrate on the Serial monitor!
  // This is just for debugging purposes
  Serial.begin(115200);

  Serial.print("Connecting to ");
  Serial.println(SSID);

  // Connect to the WiFi
  WiFi.begin(SSID, WIFI_PASS);

  // Wait until the connection has been confirmed before continuing
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Debugging - Output the IP Address of the ESP8266
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Connect to MQTT Broker
  // setCallback sets the function to be called when a message is received.
  client.setCallback(MQTT_sub_callback);

}

void loop() {
  if (!client.connected()) {
    if (Connect()) {
      Serial.println("Connected Successfully to MQTT Broker!");
    }
    else {
      Serial.println("Connection Failed!");
      Serial.println("Retrying...");
      delay(3000);
    }
  }

  int LDR_value = analogRead(LDR_IN);
  Serial.println(LDR_value);
  
  bool LDR_triggered = LDR_value > 500 ? false:true ;

  if (LDR_triggered) {
      client.publish(MQTT_TOPIC, "Triggered!");
      delay(3000);
      client.publish(MQTT_TOPIC, "----------");
  }

  

  // client.loop() just tells the MQTT client code to do what it needs to do itself (i.e. check for messages, etc.)
  client.loop();
  // Once it has done all it needs to do for this cycle, go back to checking if we are still connected.
}

