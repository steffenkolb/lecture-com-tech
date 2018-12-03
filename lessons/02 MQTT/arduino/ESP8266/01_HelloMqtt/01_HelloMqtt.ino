#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// replace the following values with your information
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

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

  // wait for board bootup
  delay(4000);
  WiFi.begin(ssid, password);

  // try to connect to wifi continuously
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to the WiFi network");

  // setup mqtt broker
  client.setServer(mqttServer, mqttPort);

  // try to connect to mqtt broker continuously
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
}

void loop() {
  // after connecting sent your hello world message
  client.publish("IOT", "Hello from ESP8266");

  // process incoming messages and maintain connection to the server
  client.loop();

  delay(3000);
}

