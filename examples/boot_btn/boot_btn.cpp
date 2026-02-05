#include <Arduino.h>

#define PIN_LED12 12
#define PIN_LED26 26
#define PIN_BOOTbtn 0

boolean boot_btn = 1;

void setup()
{
  // 各種ピンを登録
  pinMode(PIN_BOOTbtn, INPUT_PULLUP);
  pinMode(PIN_LED12, OUTPUT);
  pinMode(PIN_LED26, OUTPUT);
  Serial.begin(9600);

  // 各LEDの動作確認
  digitalWrite(PIN_LED12, HIGH);
  digitalWrite(PIN_LED26, HIGH);
  delay(1000);
  digitalWrite(PIN_LED12, LOW);
  digitalWrite(PIN_LED26, LOW);
}

void loop()
{
  // bootボタンの使用
  boot_btn = digitalRead(PIN_BOOTbtn);
  if (boot_btn == 0) {
    digitalWrite(PIN_LED12, HIGH);
  } else {
    digitalWrite(PIN_LED12, LOW);
  }

  // チャタリング防止
  delay(10);
}