#include <WiFi.h>
#include <PubSubClient.h>

#define PIN 36 // ADC1_CH0 = equals Espressif ESP32 pin: SP (SENSOR_VP)

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

/**
 * ESP32 ADCs have 12bits of resolution (versus 10bits on ESP8266 and Arduino),
 * so the total range of ADCs reading go to 4,095 (instead 1,027 on Arduinos and ESP8266)
 * when a maximum of 3.3V is applied to its inputs. 
 */
int readPhotoresistor() {
  int lightVal = analogRead(PIN);
  Serial.print("Current value = ");
  Serial.println(lightVal);

  // If we keep the current value "dark" will be the max value.
  // Better substract current value from max get bigger values for more light.
  return 4095 - lightVal;
}

void sendMessage(String input, char* topic) {
  int strLen = (input.length() + 1);
  char message[strLen] = {};
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
  
  String light = String(readPhotoresistor());
  sendMessage(light, "iot/light");
  mqttClient.loop();

  delay(500);
}

