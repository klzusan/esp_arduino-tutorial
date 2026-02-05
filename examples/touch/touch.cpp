// タッチセンサの例
// ポート4や0のジャンパワイヤに触れるとシリアルの値が変わる

#include <Arduino.h>

// touch sensor GPIO4
#define PIN_T0 T0
// touch sensor GPIO0
#define PIN_T1 T1

void setup()
{
  Serial.begin(9600);
  delay(10);
}

void loop()
{
  int t0, t1;
  t0 = touchRead(PIN_T0);
  t1 = touchRead(PIN_T1);
  Serial.printf("T0: %d, T1: %d, T0 × T1 = %d\n", t0, t1, t0 * t1);
  delay(500);
}