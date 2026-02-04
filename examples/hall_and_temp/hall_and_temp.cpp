// 磁力センサ（hallRead()）と温度センサ（temperatureRead()）を利用
#include <Arduino.h>

#define PIN_LED12 12
#define PIN_LED26 26

void setup()
{
  Serial.begin(9600);
  pinMode(PIN_LED12, OUTPUT);
  pinMode(PIN_LED26, OUTPUT);
}

void loop()
{
  // 磁力や温度も読み取れる
  int hall = hallRead();
  float temp = temperatureRead();
  Serial.printf("hallRead(): %d, ", hall);
  Serial.printf("temperatureRead(): %f\n", temp);

  // 磁力センサの値の変化によってLED制御を変える
  if (hall > 50) {
    digitalWrite(PIN_LED12, HIGH);
  } else {
    digitalWrite(PIN_LED12, LOW);
  }

  // 温度センサの値の変化によってLED制御を変える
  if (temp > 50) {
    digitalWrite(PIN_LED26, HIGH);
  } else {
    digitalWrite(PIN_LED26, LOW);
  }
}