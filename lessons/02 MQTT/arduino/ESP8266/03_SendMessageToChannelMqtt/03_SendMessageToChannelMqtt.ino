#include <ESP8266WiFi.h>
#include <PubSubClient.h>

/**
 * With this project you can send message to a custom topic.
 * Just type your topic and message into the "Serial Monitor":
 * topic:message
 * 
 * For example: IOT:This rulz! 
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

// The port-address of the MQTT broker. Standard is 1883.
const int mqttPort = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);

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

    if (client.connect(mqttClientName, NULL, NULL)) {
      Serial.println("connected");
    } else {
      Serial.print("failed with state ");
      Serial.println(client.state());
      delay(2000);
    }
  }
  client.publish("IOT", "Hello from ESP8266");
}

void loop() {
  if (Serial.available()) {
    /* Modern version */
    String input = Serial.readStringUntil('\n');
    input.trim();
    int pos = input.indexOf(':');
    if(pos != -1) {
      String channel = input.substring(0, pos);
      String message =  input.substring(pos+1);
      sendMessage(channel, message);
    }
  }
  client.loop();
}

void sendMessage(String channel, String input) {
  int strLen = (channel.length());
  char channelChar[strLen];
  channel.toCharArray(channelChar, strLen);
  
  strLen = (input.length());
  char message[strLen];
  input.toCharArray(message, strLen);
  
  Serial.println("Sending " + input + " to " + channel);
  client.publish(channelChar, message);
}

