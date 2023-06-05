#include <Servo.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "Nama-AP";
const char* password = "password-AP";
const int port = 80;
String k = "123";
int messageCount = 0;
int pos1 ;
int pos2 ;
int pos3 ;

WiFiServer server(80);
IPAddress staticIP(192, 168, 4, 5); // Alamat IP statis yang akan digunakan
IPAddress gateway(192, 168, 4, 2); // Gateway dari access point
IPAddress subnet(255, 255, 255, 0); // Subnet mask
Servo servo1;  // create servo object to control a servo
Servo servo2;
Servo servo3;

void setup() {
  servo1.attach(D7, 600, 2300); // (pin, min, max)
  servo2.attach(D6, 600, 2300); 
  servo3.attach(D5, 600, 2300); 
  pinMode(D4, OUTPUT);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA); // Mengaktifkan mode station
  WiFi.config(staticIP, gateway, subnet);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(D4, LOW);
    delay(1000);
    digitalWrite(D4, HIGH);
    delay(1000);
  }
  server.begin();

}

void loop() {
  WiFiClient client = server.available();
  if (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    ESP.reset();
  }
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        String request = client.readString();
        Serial.println(request);
        if (request != "") {
          int countServo = (request.substring(1, request.indexOf('*'))).toInt();
          int cmd = (request.substring(0, 1)).toInt();

          switch (cmd) {
            case 1:
              for (pos1; pos1 < countServo; pos1 += 1) {
                servo1.write(pos1);
                delay(15);
              }
              //          myservo.write(countServo);
              for (pos1; pos1 > countServo; pos1 -= 1) {
                servo1.write(pos1);
                delay(15);
              }

              break;
            case 2:
              for (pos2; pos2 < countServo; pos2 += 1) {
                servo2.write(pos2);
                delay(15);
              }
              //          myservo.write(countServo);
              for (pos2; pos2 > countServo; pos2 -= 1) {
                servo2.write(pos2);
                delay(15);
              }
              break;
            case 3:
              for (pos3; pos3 < countServo; pos3 += 1) {
                servo3.write(pos3);
                delay(15);
              }
              //          myservo.write(countServo);
              for (pos3; pos3 > countServo; pos3 -= 1) {
                servo3.write(pos3);
                delay(15);
              }
              break;
          }
        }
      }
    }



    client.stop();

  }

}
