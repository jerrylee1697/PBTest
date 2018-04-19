// This example uses an ESP32 Development Board
// to connect to shiftr.io.
//
// You can check on your device after a successful
// connection here: https://shiftr.io/try.
//
// by Joël Gähwiler
// https://github.com/256dpi/arduino-mqtt

#include <WiFi.h>
#include "MQTT/MQTT.h"

const char ssid[] = "CalPlugIoT";
const char pass[] = "A8E61C58F8";

WiFiClient net;
MQTTClient client;
//MQTTClient client("m12.cloudmqtt.com", 15384, callback);  //NOTE:  Editted for PB Port # on CloudMQTT

const char* MQTTServerName = "m12.cloudmqtt.com";
const char* MQTTUserName = "cebdwdic";
const char* MQTTPassword = "Ztea94td0S4s";
unsigned long lastMillis = 0;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
   while (!client.connect(MQTTServerName, MQTTUserName, MQTTPassword)) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe("/hello");
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  Serial.println("Setup Right Here");

  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported by Arduino.
  // You need to set the IP address directly.
  client.begin(MQTTServerName, 15384, net);
  client.onMessage(messageReceived);

  connect();
}

void loop() {
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }

  // publish a message roughly every second.
  if (millis() - lastMillis > 10000) {
    lastMillis = millis();
    client.publish("/hello", "world");
  }
}
