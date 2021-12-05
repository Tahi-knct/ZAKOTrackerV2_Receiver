#include <Arduino.h>
#include <SPI.h>
#include <WiFi.h>
#include <esp_now.h>

void OnDataRecv(const uint8_t* mac_addr, const uint8_t* incomingData, int data_len) {
  Serial.print("s\t");
  for (int i = 0; i < data_len; i++) {
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
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {}