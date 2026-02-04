#include <Arduino.h>

int l_26 = 26;
int l_12 = 12;

void setup()
{
  Serial.begin(9600);
  pinMode(l_12, OUTPUT);
  pinMode(l_26, OUTPUT);
}

void loop()
{
  // Serial.println("Hello, World!!");
  digitalWrite(l_12, HIGH);
  digitalWrite(l_26, LOW);
  delay(500);
  digitalWrite(l_12, LOW);
  digitalWrite(l_26, HIGH);
  delay(500);
}