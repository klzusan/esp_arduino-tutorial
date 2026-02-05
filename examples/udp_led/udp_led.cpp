// スマホのUDPレシーバアプリからESPのLEDを操作する例
// スマホのWiFiで[SSID: admin, PASS: password]に接続し，
// IPやPortをコードのように設定するとメッセージを送れるようになる

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>

#define PIN_LED12 12
#define PIN_LED26 26

// アクセスポイント（ESP）用の各設定
#define SSID_AP "admin"
#define PASS_AP "password"
const IPAddress IP(192, 168, 0, 1);
const IPAddress GATEWAY(0, 0, 0, 0);
const IPAddress SUBNET(255, 255, 255, 0);
#define PORT 1024 //udp
WiFiUDP udp; //UDP通信用のインスタンス

void setup()
{
  pinMode(PIN_LED12, OUTPUT);
  pinMode(PIN_LED26, OUTPUT);
  Serial.begin(9600);
  Serial.printf("SSID: %s\n", SSID_AP);
  Serial.printf("PASS: %s\n", PASS_AP);
  // 無線LANを[AP]モードに設定
  WiFi.mode(WIFI_AP); delay(100);
  // SSIDとパスワードを設定
  WiFi.softAP(SSID_AP, PASS_AP);
  // AP設定
  WiFi.softAPConfig(IP, GATEWAY, SUBNET);
  // UDP待ち受け開始
  udp.begin(PORT);

  Serial.println(WiFi.softAPIP());
}

void loop()
{
  char s[65];
  // UDP受信パケット長を変数lenに代入
  int len = udp.parsePacket();
  if (len == 0) return;
  // 文字列変数sの初期化
  memset(s, 0, 65);
  // UDP受信データを文字列変数sへ代入
  udp.read(s, 64);
  Serial.printf("Received: %s\n", s);

  if(!strncmp(s, "g", 1)) {
    // 「g」が送られると緑色LEDを点灯し，黄色LEDを消灯
    digitalWrite(PIN_LED12, HIGH);
    digitalWrite(PIN_LED26, LOW);
  }
  if(!strncmp(s, "y", 1)) {
    // 「y」が送られると黄色LEDを点灯し，緑色LEDを消灯
    digitalWrite(PIN_LED26, HIGH);
    digitalWrite(PIN_LED12, LOW);
  }
  if(!strncmp(s, "n", 4)) {
    // 「n」が送られるとすべてのLEDを消灯
    digitalWrite(PIN_LED12, LOW);
    digitalWrite(PIN_LED26, LOW);
  }
}