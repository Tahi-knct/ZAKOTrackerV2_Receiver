#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <espnow.h>

void OnDataRecv(uint8_t* mac_addr, uint8_t* incomingData, uint8_t len) {
  Serial.print("s\t");
  for (int i = 0; i < len; i++) {
    Serial.print(incomingData[i]);
    Serial.print("\t");
  }
  Serial.print("\n");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != 0) {
    Serial.println("Error initialize ESP-NOW");
    return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {}