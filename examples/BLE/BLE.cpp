// ESP32とスマートフォンをBLEで接続する例
// スマホ側は「nRF Connect」というアプリを用いて接続している

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

#define PIN_LED12 12
#define PIN_LED26 26

// Bluetooth通信のための定義
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define BLE_DEVICE_NAME     "klzu_ESP32"

BLEServer *pServer;
BLECharacteristic *pCharacteristic;
bool deviceConnected = false;

void setup()
{
  Serial.begin(9600);

  // BLEデバイスの初期化
  BLEDevice::init(BLE_DEVICE_NAME);
  // サーバの作成
  pServer = BLEDevice::createServer();
  // サービスの作成
  BLEService *pService = pServer->createService(SERVICE_UUID);
  // キャラクタリスティックの作成
  pCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_READ |
    BLECharacteristic::PROPERTY_WRITE
  );
  // サービス開始
  pService->start();
  // 電波を出す
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x06);
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();

  pinMode(PIN_LED12, OUTPUT);
  pinMode(PIN_LED26, OUTPUT);

  // 各LEDの動作確認
  digitalWrite(PIN_LED12, HIGH);
  digitalWrite(PIN_LED26, HIGH);
  delay(1000);
  digitalWrite(PIN_LED12, LOW);
  digitalWrite(PIN_LED26, LOW);

  Serial.println("Setup done.");
}

void loop()
{
  // 途中で切断したときに再接続する
  size_t connectedCount = pServer->getConnectedCount();
  if (connectedCount == 0) {
    delay(500);
    BLEDevice::startAdvertising();
  }

  // 受信した値があるかどうか確認
  std::string value = pCharacteristic->getValue();
  if (value.length() == 0) return;

  Serial.printf("Received: %s\n", value.c_str());

  if (value == "g") {
    // 「g」が送られると緑色LEDを点灯or消灯
    if (digitalRead(PIN_LED12) == HIGH) digitalWrite(PIN_LED12, LOW);
    else digitalWrite(PIN_LED12, HIGH);
  }
  if (value == "y") {
    // 「y」が送られると黄色LEDを点灯or消灯
    if (digitalRead(PIN_LED26) == HIGH) digitalWrite(PIN_LED26, LOW);
    else digitalWrite(PIN_LED26, HIGH);
  }
  if (value == "n") {
    // 「n」が送られるとすべてのLEDを消灯
    digitalWrite(PIN_LED12, LOW);
    digitalWrite(PIN_LED26, LOW);
  }

  // 次の受信を待つために値をクリア
  pCharacteristic->setValue("");
  delay(20);
}