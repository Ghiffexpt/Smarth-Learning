

#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "Nama-AP";
const char* password = "password-AP";
const int port = 80;
int messageCount = 0;

WiFiServer server(80);
IPAddress staticIP(192, 168, 4, 3); // Alamat IP statis yang akan digunakan
IPAddress gateway(192, 168, 4, 2); // Gateway dari access point
IPAddress subnet(255, 255, 255, 0); // Subnet mask

void setup() {
  Serial.begin(115200);
  pinMode(D4, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D5, OUTPUT);
  digitalWrite(D5, HIGH);
  digitalWrite(D6, HIGH);
  digitalWrite(D7, HIGH);

  WiFi.mode(WIFI_STA); // Mengaktifkan mode station
  WiFi.config(staticIP, gateway, subnet);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(D4, LOW);
    delay(1000);
    Serial.println("Connecting to WiFi...");
    digitalWrite(D4, HIGH);
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
    Serial.println("Disconnect Wifi ...");
    delay(1000);
    ESP.reset();
  }
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        String request = client.readStringUntil('\r');
        Serial.println(request);
        if (request == "2") {
          digitalWrite(D5, LOW);
                    delay(1000);
          digitalWrite(D5, HIGH);

        } else if (request == "1") {
          digitalWrite(D6, LOW);
          delay(1000);
          digitalWrite(D6, HIGH);

        } else if (request == "0") {
          digitalWrite(D7, LOW);
          delay(1000);
          digitalWrite(D7, HIGH);

        }
      }
    }

    client.stop();

  }
}
