#include <Arduino.h>

// ===================== PIN SETUP =====================
const int ledPin = 9;  // LED terhubung ke pin 9

void setup() {
  // Set pin LED sebagai output
  pinMode(ledPin, OUTPUT);

  // Serial (opsional, untuk debug)
  Serial.begin(9600);
}

void loop() {

  // ===================== LED NYALA =====================
  digitalWrite(ledPin, HIGH);
  Serial.println("LED ON");
  delay(500);  // 0.5 detik

  // ===================== LED MATI =====================
  digitalWrite(ledPin, LOW);
  Serial.println("LED OFF");
  delay(500);  // 0.5 detik
}
