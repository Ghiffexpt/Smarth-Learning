#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "Class_29";
const char* password = "0idxdgigjhfi";
const char* serverAddress1 = "192.168.4.3";  // Alamat IP perangkat Station 1
const char* serverAddress2 = "192.168.4.4";  // Alamat IP perangkat Station 2
const char* serverAddress3 = "192.168.4.5";
String device;
int messageCount = 0;
int IR;
int TIRAI;
int stat;
String dataFIX;
String dataACT;
void setup() {
  Serial.begin(115200);
  pinMode(D4, OUTPUT);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  Serial.print("Alamat IP Access Point: ");
  Serial.println(WiFi.softAPIP());
  digitalWrite(D4, LOW);

}

void loop() {
  WiFiClient client1;
  WiFiClient client2;
  WiFiClient client3;
  //  if (stat == 0) {
  if (Serial.available()) {
    char a = Serial.read();
    if (a != '-' && a != ';') {
      dataACT += String(a);
    } else if (a == '-') {
      dataACT = "";
      dataFIX = "";
    } else if ( a == ';') {
      dataFIX = dataACT;
      String device = dataFIX.substring(0, 1);
      int AddDev = device.toInt();
      Serial.println(AddDev);
      String DataPars = dataFIX.substring(1, dataFIX.indexOf(';'));
      int dataCTRL = DataPars.toInt();
      Serial.println(dataCTRL);
      switch (AddDev) {
        case 1://usb
          Serial.println("case 1");
          Serial.print("DATA : ");
          Serial.println(dataCTRL);
          client2.stop();
          client3.stop();
          if (client1.connect(serverAddress1, 80)) {
            client1.println(dataCTRL);
            client1.stop();
            digitalWrite(D4, LOW);
            delay(2000);
            digitalWrite(D4, HIGH);
          }  else {
            delay(1000);
            digitalWrite(D4, LOW);
          }
          break;
        case 2:
          Serial.println("case 2");
          Serial.print("DATA : ");
          Serial.println(dataCTRL);
          client3.stop();
          client1.stop();
          if (client2.connect(serverAddress2, 80)) {
            client2.println(dataCTRL);
            client2.stop();
            digitalWrite(D4, LOW);
            delay(2000);
            digitalWrite(D4, HIGH);
          }  else {
            delay(1000);
            digitalWrite(D4, LOW);
          }
          break;
        case 3:// wake
          Serial.println("case 3");
          Serial.print("DATA : ");
          Serial.println(dataCTRL);
          client1.stop();
          client2.stop();
          if (client3.connect(serverAddress3, 80)) {
            client3.println(dataCTRL);
            client3.stop();
            digitalWrite(D4, LOW);
            delay(2000);
            digitalWrite(D4, HIGH);
          }  else {
            delay(1000);
            digitalWrite(D4, LOW);
          }
          break;
        case 4:
          ESP.reset();
          break;
      }
      dataACT = "";
    }
  }
}
