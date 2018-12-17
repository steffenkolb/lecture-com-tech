# Hackathon

After the last session about MQTT you are ready to take on the full IoT stack.
It is time to connect sensors and actors to your boards an communicate via MQTT.

## Exercises

Choose a board (eitehr ESP32 or ESP8266) and one sensor or actor.
For starters I suggest using any one of the following Elegoo sensors / actors.
**Important**: You will **not** need any resistors. They are already soldered onto the sensor-boards.

Sensors:
- DHT11 Humidity and Temperature Sensor (digital)
    - Important: Install Arduino library "DHT sensor library" and "Adafruit Unified Sensor" by Adafruit
    - Guide ESP32: https://lastminuteengineers.com/esp32-dht11-dht22-web-server-tutorial/
    - guide ESP8266: https://www.instructables.com/id/Interface-DHT11-Humidity-Sensor-Using-NodeMCU/
- Photoresistor (analog)
    - Guide ESP32: https://www.instructables.com/id/Interfacing-Photoresistor-With-ESP32/
    - Guide ESP8266: https://www.instructables.com/id/NodeMCU-With-LDR/
- Avoidance

Actors:
**Important:** Do not forget to change the pin mode when trying to work with actors: `pinMode(2, OUTPUT);`
- Simple LED
    - Guide ESP32: https://www.instructables.com/id/Blinking-an-LED-With-ESP32/
    - Guide ESP8266: https://www.instructables.com/id/NodeMCU-Basic-Project-Blink-a-LED/
- RGB LED
- TWO Color LED
- 7 Color Flash
- Active Buzzer


## Important information for the boards

The ESP boards are not exchangeble and pins do not reflect Arduino pins perfectly.
I suggest to use the following pins for usage with sensors / actors:

### ESP32 (espressif)
- Digital:
    - Id in code: 16
    - Position on board: G16
- Analog:
    - Id in code: 36
    - Position on board: SP (SENSOR_VP)

### ESP 8622 (NodeMCU)
- Digital:
    - Id in code: D4
    - Position on board: D4
- Analog:
    - Id in code: A0
    - Position on board: A0
