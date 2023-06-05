
#include <ModbusMaster.h>
#include<SoftwareSerial.h>;
#include "REG.h"
#define baud 9600
#define polling 100
#define timeout 100
#define retry_count 10
#define DE_RE 5

SoftwareSerial s (0, 2);
ModbusMaster node;
byte KeyArus[] = {0x2, 0x4, 0x0, 0x11, 0x0, 0xA, 0x20, 0x3B};
unsigned long Lastmsg;

//float HexToFloat(uint32_t x) {
//  return (*(float*)&x);
//}
//
//uint32_t FloatToHex(float x) {
//  return (*(uint32_t*)&x);
//}
//
//float Read_Meter_float(char addr, uint16_t REG) {
//  float i = 0;
//  uint8_t result, j;
//
//  uint16_t data[2];
//  uint32_t value = 0;
// 
//}

//void GET_METER() {
//  delay(1000);
//  for (int a = 0; a < Total_of_Reg; a++) {
//    DATA_METER [a] = Read_Meter_float(ID_meter, Reg_addr[a]);
//  }
//}
void cntrlHigh() {
  digitalWrite(DE_RE, 1);

}
void cntrlLOW() {
  digitalWrite(DE_RE, 0);

}
void setup() {
  // put your setup code here, to run once:
  pinMode(DE_RE, OUTPUT);
  digitalWrite(DE_RE, 0);
  Serial.begin(9600);
  s.begin(9600);

  node.preTransmission(cntrlHigh);
  node.postTransmission(cntrlLOW);
}

void loop() {
//  GET_METER();
//Serial.println(DATA_METER[1]);
  unsigned long now = millis();
 node.begin(2, s);
 uint8_t result;
  node.preTransmission(cntrlHigh);
  node.postTransmission(cntrlLOW);
  delay(500);
    result = node.readInputRegisters(0x30000, 2);
//  if ((now - Lastmsg) >= 2000) {
//    Lastmsg = now;
//    s.write(KeyArus, 8);
//  }
  if (s.available()) {
    byte bil = s.read();
    Serial.println(bil,HEX);


  } 
  delay(3000);
}
