#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Pin number on board where LED is connected to
#define LED_PIN D4

// replace the following values with your information
const char* ssid = "mobile medien";
const char* password = "iot_rockz";

// every mqtt client must have its own name; choose anything
const char* mqttClientName = "YOUR_LED_CLIENT_NAME";

// IP address or URL of your MQTT broker/server.
// For demo purposes you can use  the public mosquitto broker "test.mosquitto.org"
// See http://test.mosquitto.org
const char* mqttServer = "192.168.178.27";

// basic mqtt port; should not be changed
const int mqttPort = 1883;

// Your topic to subscribe to
const char* mqttTopic = "iot/temp";

// create a wifi client-variable
WiFiClient wifiClient;

// create a mqtt-client and pass the wifi client to the library
PubSubClient mqttClient(wifiClient);

/**
 * This function is called right after your mirocontroller boots
 */
void setup() {
  Serial.begin(115200);

  // 0. Set mode for this pin to 'Output'
  pinMode(LED_PIN, OUTPUT);

  // 1. Establish connection to the network
  connectToWifi();

  // 2. Establish connection to the MQTT broker
  connectToMqtt();
  
  // 3. Subscribe to a topic you want to receive messages for 
  mqttClient.subscribe(mqttTopic);

  // 4. Specify the function to be called whenever an MQTT message arrives
  mqttClient.setCallback(callback);
}

/**
 * This function is called periodically
 */
void loop() {
  // check if you are still connected to the mqtt broker
  if (!mqttClient.connected()) {
    
    // if not, then reestablish connection
    connectToMqtt();
    
    // it is best to resubscribe after losing connection
    mqttClient.subscribe(mqttTopic);
  }

  // This should be called regularly to allow the client
  // to process incoming messages and maintain its connection to the server.
  mqttClient.loop();
}


/**
 * Helper function to connect to WiFi network
 */
void connectToWifi() {
  // wait for board to be ready
  delay(4000);

  // start connecting to wifi
  WiFi.begin(ssid, password);

  // wait until connected
  while (WiFi.status() != WL_CONNECTED) {
    // wait for a second to give the wifi-chip time to connect
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
}

/**
 * Helper function to connect to MQTT broker
 */
void connectToMqtt() {
  mqttClient.setServer(mqttServer, mqttPort);

  // try connecting until connected
  while (!mqttClient.connected()) {
    Serial.println("Connecting to MQTT...");

    // try connecting to MQTT broker. Will return true if it worked and false otherwise
    boolean isConnected = mqttClient.connect(mqttClientName, NULL, NULL);

    // react accordingly
    if (isConnected) {
      // it worked!
      Serial.println("connected");
    } else {
      // it did not work
      Serial.print("failed with state ");
      Serial.print(mqttClient.state());
      Serial.println();
      delay(2000);
    }
  }
}

/** 
 *  This function is called whenever a new message arrives from the MQTT broker 
 */
void callback(char* topic, byte* payload, unsigned int length) {
  // We will simply print the message to the serial-output
  Serial.print("Message arrived at '");
  Serial.print(topic);
  Serial.print("'");

  digitalWrite(LED_PIN, HIGH);
  delay(200);
  digitalWrite(LED_PIN, LOW);
  delay(100);

  // line-break
  Serial.println();
}