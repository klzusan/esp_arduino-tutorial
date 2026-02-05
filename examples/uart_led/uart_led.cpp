// UARTからLEDを制御する例

#include <Arduino.h>

#define PIN_LED12 12 // green
#define PIN_LED26 26 // yellow

void setup()
{
  pinMode(PIN_LED12, OUTPUT);
  pinMode(PIN_LED26, OUTPUT);
  Serial.begin(9600);
  Serial.println("Practice32 uart rx");

  // 各LEDの動作確認
  digitalWrite(PIN_LED12, HIGH);
  digitalWrite(PIN_LED26, HIGH);
  delay(1000);
  digitalWrite(PIN_LED12, LOW);
  digitalWrite(PIN_LED26, LOW);
}

void loop()
{
  char s[65];
  int i, len = Serial.available();
  if (len == 0) return;
  if (len > 64) len = 64;
  for (i = 0; i < len; i++) s[i] = Serial.read();
  s[i] == '\0';
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