// ESP32 老式电视红外遥控器 — 骨架
// 沿用 ac-remote 架构：IRremoteESP8266 收发 + 本地网页控制
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRsend.h>
#include <IRutils.h>

// 接线与 ac-remote 一致
static const uint16_t kRecvPin = 4;   // 接收器 OUT
static const uint16_t kSendPin = 5;   // 发射器 DAT

IRrecv irrecv(kRecvPin);
IRsend irsend(kSendPin);

void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn();   // 启动接收（学习模式基础）
  irsend.begin();        // 启动发射
  Serial.println("tv-remote booted");
}

void loop() {
  // TODO: 学习模式（解码并存储原始红外码）
  // TODO: Wi-Fi + 本地网页（参考 ac-remote/src/main.cpp）
  // TODO: JSON API：/api/state /api/control /api/learn /api/codes
  if (irrecv.decode(&results)) {
    serialPrintUint64(results.value, HEX);
    Serial.println("");
    irrecv.resume();
  }
  delay(100);
}
