#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <SPI.h>
#include <WiFi.h>
#include <esp_now.h>
#include <utility/imumaths.h>

#include "config.h"

#if Mode == Mode_Sender

#elif Mode == Mode_Receiver

const int ConnectDevice_Num = 5;  //接続数するデバイスの数

float QuatDataArray[20];

void OnDataRecv(const uint8_t* mac, const uint8_t* recvData, int len) {
    for (size_t i = 0; i < ConnectDevice_Num; i++) {
        if (recvData[0] == i) {
            QuatDataArray[i * 4] = recvData[i * 4 + 1];
            QuatDataArray[i * 4 + 1] = recvData[i * 4 + 2];
            QuatDataArray[i * 4 + 2] = recvData[i * 4 + 3];
            QuatDataArray[i * 4 + 3] = recvData[i * 4 + 4];
        }
    }
}

#else
    #error you need select Mode
#endif

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != 0) {
        Serial.println("Error initialize ESP-NOW");
        return;
    }

#if Mode == Mode_Sender

#elif Mode == Mode_Receiver
    esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
    esp_now_register_recv_cb(OnDataRecv);

#else
    #error you need select Mode
#endif
}

void loop() {
#if Mode == Mode_Sender

#elif Mode == Mode_Receiver
    Serial.print("s\t");
    for (size_t i = 0; i < sizeof(QuatDataArray); i++) {
        Serial.print(QuatDataArray[i]);
        Serial.print("\t");
    }
    Serial.print("\n");
#else
    #error you need select Mode
#endif
}