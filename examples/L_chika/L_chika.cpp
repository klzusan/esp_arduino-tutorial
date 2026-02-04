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
  // Serial.println("Hello, World!!");
  digitalWrite(PIN_LED12, HIGH);
  digitalWrite(PIN_LED26, LOW);
  delay(500);
  digitalWrite(PIN_LED12, LOW);
  digitalWrite(PIN_LED26, HIGH);
  delay(500);
}