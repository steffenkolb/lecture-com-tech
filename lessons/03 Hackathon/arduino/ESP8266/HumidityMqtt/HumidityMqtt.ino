#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <dht.h>

#include "DHT.h"
#define dht_apin 2 // Pin number on board where sensor is connected to
dht DHT;

// replace the following values with your information
const char* ssid = "mobile medien";
const char* password = "iot_rockz";

// every mqtt client must have its own name; choose anything
const char* mqttClientName = "YOUR_CLIENT_NAME";

// IP address or URL of your MQTT broker/server.
// For demo purposes you can use  the public mosquitto broker "test.mosquitto.org"
// See http://test.mosquitto.org
const char* mqttServer = "192.168.178.27";

// basic mqtt port; should not be changed
const int mqttPort = 1883;

WiFiClient espClient;
PubSubClient mqttClient(espClient);

void connectToWifi() {
  //
  delay(4000);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to the WiFi network");
}

void connectToMqtt() {
  mqttClient.setServer(mqttServer, mqttPort);
  while (!mqttClient.connected()) {
    Serial.println("Connecting to MQTT...");

    if (mqttClient.connect(mqttClientName)) {
      Serial.println("connected");
    } else {
      Serial.print("failed with state ");
      Serial.print(mqttClient.state());
      Serial.println();
      delay(2000);
    }
  }
}

void readTempertatureHumidity() {
  DHT.read11(dht_apin);
  Serial.print("Current humidity = ");
  Serial.print(DHT.humidity);
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(DHT.temperature);
  Serial.println("C  ");
}

void sendMessage(String input, char* topic) {
  int strLen = (input.length() + 1);
  char message[strLen];
  input.toCharArray(message, strLen);

  Serial.println("Sending " + input);
  mqttClient.publish(topic, message);
}

void setup() {
  Serial.begin(115200);

  connectToWifi();
  connectToMqtt();
  
  mqttClient.publish("esp/test", "Hello from ESP32");
}

void loop() {
  if (!mqttClient.connected()) {
    connectToMqtt();
  }
  
  readTempertatureHumidity();
  String temp = String(DHT.temperature);
  sendMessage(temp, "iot/temp");

  String humidity = String(DHT.humidity);
  sendMessage(humidity, "iot/humidity");
  mqttClient.loop();

  delay(5000);
}

