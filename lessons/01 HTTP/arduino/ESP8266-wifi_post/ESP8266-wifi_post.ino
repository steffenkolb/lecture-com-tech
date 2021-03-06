#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
const char* url = "http://SERVER:PORT/";
const char* message = "All your base are belong to us.";

void setup() {
  Serial.begin(115200);

  // wait for initial boot
  delay(4000);

  // try connecting to wifi
  Serial.print("Connecting to WiFi..");
  WiFi.begin(ssid, password);

  // Wait until connection was successfull
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println(".");
  Serial.print("Connected to the WiFi network with IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
    HTTPClient http;

    // Specify the URL
    http.begin(url);
    Serial.print("Trying to POST to url: ");
    Serial.println(url);
    
    // Make the request
    int httpCode = http.POST(message);

    // Check for the returning code
    if (httpCode > 0) {
      String payload = http.getString();
      Serial.print("HTTP status code: ");
      Serial.println(httpCode);
      
      Serial.print("Payload: ");
      Serial.println(payload);
    } else {
      Serial.print("Error on HTTP request: ");
      Serial.println(httpCode);
    }
    
    // Free the resources
    http.end(); 
  }

  // Wait 10 seconds until retry
  delay(10000);
}
