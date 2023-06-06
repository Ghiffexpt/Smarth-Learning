#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "Raw_AC.h"

const char* ssid = "Nama-AP";
const char* password = "password-AP";
const int port = 80;
int messageCount = 0;

WiFiServer server(80);
IPAddress staticIP(192, 168, 4, 4); // Alamat IP statis yang akan digunakan
IPAddress gateway(192, 168, 4, 2); // Gateway dari access point
IPAddress subnet(255, 255, 255, 0); // Subnet mask

void setup() {
  Serial.begin(115200);
  delay(10000);
  pinMode(4, OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFi.config(staticIP, gateway, subnet);
  WiFi.begin(ssid, password);
  irsend.begin();

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(4, HIGH);
    delay(1000);
    Serial.println("Connecting to WiFi...");
    digitalWrite(4, LOW);
    delay(1000);
  }
  server.begin();
  Serial.println("Terhubung ke jaringan WiFi");
  Serial.print("Alamat IP Station: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Disconnect to WiFi...");
    ESP.reset();
  }
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        String request = client.readStringUntil('\r');
        Serial.println(request);
        suhu_sharp(request.toInt());
      }
    }
    client.stop();

  }
}
