#include <WiFi.h>
#include <PubSubClient.h>

/**
 * With this project you can send message to a specific topic.
 * Just type your message into the "Serial Monitor":
 * 
 * For example: IoT rulz! 
 **/

// replace the following values with your information
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// every mqtt client must have its own name; choose anything
const char* mqttClientName = "YOUR_CLIENT_NAME";

// IP address or URL of your MQTT broker/server.
// For demo purposes you can use  the public mosquitto broker "test.mosquitto.org"
// See http://test.mosquitto.org
const char* mqttServer = "test.mosquitto.org";

// basic mqtt port; should not be changed
const int mqttPort = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);

  //
  delay(4000);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to the WiFi network");

  client.setServer(mqttServer, mqttPort);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");

    if (client.connect(mqttClientName)) {

      Serial.println("connected");

    } else {

      Serial.print("failed with state ");
      Serial.println(client.state());
      delay(2000);
    }
  }
  client.publish("IOT", "Hello from ESP32");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    sendMessage(input);
  }
  client.loop();
}

void sendMessage(String input) {
  int strLen = (input.length());
  char message[strLen];
  input.toCharArray(message, strLen);

  Serial.println("Sending " + input);
  client.publish("IOT", message);
}

