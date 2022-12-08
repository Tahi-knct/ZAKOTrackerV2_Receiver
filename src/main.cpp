#include <WiFi.h>
#include <esp_now.h>

#include "config.h"

const int ConnectDevice_Num = 5;

float QuatDataArray[20];

#define WIFI_CHANNEL 1

void OnDataRecv(const uint8_t* mac, const uint8_t* recvData, int len) {
    for (size_t i = 0; i < ConnectDevice_Num; i++) {
        // Serial.println(*((float*)(recvData)), DEC);
        if (*((float*)(recvData)) == i) {
            memcpy(&QuatDataArray[i * 5], recvData, len);  // recvDataの生データだとよくわからない値がくるので
        }
    }

    Serial.print("s\t");
    for (size_t i = 0; i < sizeof(QuatDataArray) / sizeof(float); i++) {
        Serial.print(QuatDataArray[i]);
        Serial.print("\t");
    }
    Serial.print("\n");
    delay(1);  // watchdog_timerのリセット
}

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_AP);
    WiFi.disconnect();
    if (esp_now_init() != ESP_OK) {
        Serial.println("ESP-Now Init Failed....");
        return;
    }
    esp_now_register_recv_cb(OnDataRecv);
}

void loop() {}